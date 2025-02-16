#include "joinclassdlg.h"
#include "ui_joinclassdlg.h"

typedef struct getClassByTeacherIdArg{
    QString teacherId;
    CJoinClassDlg* thiz;
}GetClassByTeacherIdArg;

typedef struct addRequestJoinClassArg{
    QString teacherId;
    QString className;
    QString acount;
    QString studentName;
    CJoinClassDlg* thiz;
}AddRequestJoinClassArg;

CJoinClassDlg::CJoinClassDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CJoinClassDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("加入课程");
    this->setWindowIcon(QIcon(":/icons/winIcon.png"));

    this->acount = "";
    this->studentName = "";

    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,[=](){
       GetClassByTeacherIdArg* arg = new GetClassByTeacherIdArg();
       arg->teacherId = this->ui->lineEdit->text().trimmed();
       arg->thiz = this;
       _beginthreadex(nullptr,0,&CJoinClassDlg::threadGetClassByTeacherId,arg,0,nullptr);
    });

    QObject::connect(this,&CJoinClassDlg::startShowClass,this,&CJoinClassDlg::showClass);

    //点击申请加入
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        QString className = this->ui->comboBox->currentText().trimmed();
        QString teacherId = this->ui->lineEdit->text().trimmed();
        if(className == "" || teacherId == "")
        {
            return;
        }
        AddRequestJoinClassArg* arg = new AddRequestJoinClassArg();
        arg->className = className;
        arg->teacherId = teacherId;
        arg->acount = this->acount;
        arg->studentName = this->studentName;
        HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CJoinClassDlg::threadAddRequestJoinClass,arg,0,nullptr);
        WaitForSingleObject(thread,INFINITE);
        //进行申请成功提示
        QMessageBox* dlg = new QMessageBox(QMessageBox::Information,"申请提示","提交申请成功，请等待教师同意。",QMessageBox::Ok);
        dlg->exec();
        delete dlg;
        this->reject();
    });
}

void CJoinClassDlg::setAcount(QString acount)
{
    this->acount = acount;
}

void CJoinClassDlg::setStudentName(QString studentName)
{
    this->studentName = studentName;
}

void CJoinClassDlg::addRequestJoinClass(QString teacherId,QString className,QString studentName,QString StudentId)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classNameArr = className.toLocal8Bit();
    QByteArray studentNameArr = studentName.toLocal8Bit();
    QByteArray studentIdArr = StudentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassName = classNameArr.data();
    const char* pStudentName = studentNameArr.data();
    const char* pStudentId = studentIdArr.data();

    //进行数据库操作
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::shared_ptr<char[]> sqlBuf(new char[1024000]);
    sprintf(sqlBuf.get(),"insert into `requestJoinClass`(`studentName`,`studentId`,`requestTime`,`className`,`teacherId`) \
values('%s','%s',now(),'%s','%s');",pStudentName,pStudentId,pClassName,pTeacherId);
    std::string sql;
    sql = sqlBuf.get();
    dbHelper->sqlExcute(sql,"ExamSystem");
}

unsigned WINAPI CJoinClassDlg::threadAddRequestJoinClass(LPVOID arg)
{
    AddRequestJoinClassArg* aInfo = (AddRequestJoinClassArg*)arg;
    aInfo->thiz->addRequestJoinClass(aInfo->teacherId,aInfo->className,aInfo->studentName,aInfo->acount);
    delete aInfo;
    //_endthreadex(0);
    return 0;
}

void CJoinClassDlg::showClass(QVector<QVector<QString>>* result)
{
    if(result == nullptr)
    {
        return ;
    }
    this->ui->comboBox->clear();
    for(int i = 0 ; i < result->size();i++)
    {
        this->ui->comboBox->addItem(result->at(i).at(0));
    }
    this->ui->comboBox->setCurrentIndex(0);
    delete result;
}

QVector<QVector<QString>>* CJoinClassDlg::getClassByTeacherId(QString teacherId)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    const char* pTeacherId = teacherIdArr.data();

    //进行数据库操作
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::shared_ptr<char[]> sqlBuf(new char[1024000]);
    sprintf(sqlBuf.get(),"select `className` from `class` where  `teacherId` = '%s';",pTeacherId);
    std::string sql;
    sql = sqlBuf.get();
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");

    //将结果集进行转换存储到返回的结果集
    QVector<QVector<QString>>* result = new QVector<QVector<QString>>();
    for(int i = 0 ; i < ret.size();i++)
    {
        QVector<QString> temp;
        for(int j = 0 ; j < ret.at(i).size();j++)
        {
            QString str = QString::fromLocal8Bit(ret.at(i).at(j).c_str());
            temp.push_back(str);
        }
        result->push_back(temp);
    }
    return result;
}

unsigned WINAPI CJoinClassDlg::threadGetClassByTeacherId(LPVOID arg)
{
    GetClassByTeacherIdArg* gInfo = (GetClassByTeacherIdArg*)arg;
    QVector<QVector<QString>>* ret =  gInfo->thiz->getClassByTeacherId(gInfo->teacherId);
    //发送信号，将结果进行显示
    emit gInfo->thiz->startShowClass(ret);
    delete gInfo;
    //_endthreadex(0);
    return 0;
}

CJoinClassDlg::~CJoinClassDlg()
{
    delete ui;
}
