#include "mainmenuedlg.h"
#include "ui_mainmenuedlg.h"

CMainMenueDlg::CMainMenueDlg(QWidget *parent) : //主菜单界面类
    QDialog(parent),
    ui(new Ui::CMainMenueDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("在线考试系统-学生端");
    this->setWindowIcon(QIcon(":/icons/winIcon.png"));

    //生成控制层
    this->m_mainMenueContorller = new CMainMenueContorller();
    //设置标题栏头像为圆形
    this->ui->label_head->setMask(QRegion(ui->label_head->rect(),QRegion::RegionType::Ellipse));
    this->ui->label_head2->setMask(QRegion(ui->label_head2->rect(),QRegion::RegionType::Ellipse));
    //鼠标进入人物姓名的时候需要实现对话框的动态效果
//    this->m_exitLoginDlg->move(this->ui->label_name->x(),this->ui->label->height()+1);
//    this->m_exitLoginDlg->hide();
    this->ui->label_name->installEventFilter(this);
//    this->m_exitLoginDlg->installEventFilter(this);

    this->m_acount = "";
    this->m_classCount = "";
    this->sortNumberClass = 0;
    this->m_classCurPageIndex = 1;
    this->classIconIndex = 0;
    this->m_Event = CreateEvent(nullptr,FALSE,FALSE,nullptr);
    this->m_Event_2 = CreateEvent(nullptr,FALSE,FALSE,nullptr);
    //界面初始化的默认选中项
    this->ui->pushButton_3->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");

    this->ui->stackedWidget->setCurrentIndex(0);

    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(5);
    });

    QObject::connect(this->ui->pushButton_3,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(0);
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
//        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->getClassTableData();
        this->getClassTableCount();
    });

    QObject::connect(this->ui->pushButton_4,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(1);    
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
//        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_5,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(2);
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
//        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_6,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(3);
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
//        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    //进行员工职员姓名和头像回显
    QObject::connect(this,&CMainMenueDlg::startShowStudentInfo,this,&CMainMenueDlg::showStudentInfo);
    //监听头像UI更新信号
    QObject::connect(this,&CMainMenueDlg::startShowHeadImage,this,&CMainMenueDlg::showHeadImageUI);
    //显示职工账号管理信息
    //QObject::connect(this->ui->pushButton,&QPushButton::clicked,this,&CMainMenueDlg::showTeacherAcountInfo);
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,this,&CMainMenueDlg::getStudentAcountInfoData);

    QObject::connect(this->ui->pushButton_22,&QPushButton::clicked,[=](){
        if(this->m_nameChangeDlg == nullptr)
        {
            this->m_nameChangeDlg = new CNameChangeDlg();
            this->m_nameChangeDlg->m_acount = this->m_acount;
            this->m_nameChangeDlg->move((this->width() - this->m_nameChangeDlg->width()) / 2,(this->height() - this->m_nameChangeDlg->height()) / 2);
            this->m_nameChangeDlg->show();
            //监听返回信号
            QObject::connect(this->m_nameChangeDlg,&CNameChangeDlg::rejected,[=](){
                if(this->m_nameChangeDlg != nullptr)
                {
                    delete this->m_nameChangeDlg;
                    this->m_nameChangeDlg = nullptr;
                }
                emit this->startShowStudentInfo(this->m_acount);
                emit this->ui->pushButton->clicked();
            });
        }
    });
    QObject::connect(this->ui->pushButton_24,&QPushButton::clicked,[=](){
        if(this->m_phoneNumChangeDlg == nullptr)
        {
            this->m_phoneNumChangeDlg = new CPhoneNumberChangeDlg();
            this->m_phoneNumChangeDlg->m_acount = this->m_acount;
            this->m_phoneNumChangeDlg->move((this->width() - this->m_phoneNumChangeDlg->width()) / 2,(this->height() - this->m_phoneNumChangeDlg->height()) / 2);
            this->m_phoneNumChangeDlg->show();
            //监听返回信号
            QObject::connect(this->m_phoneNumChangeDlg,&CNameChangeDlg::rejected,[=](){
                if(this->m_phoneNumChangeDlg != nullptr)
                {
                    delete this->m_phoneNumChangeDlg;
                    this->m_phoneNumChangeDlg = nullptr;
                }
                emit this->ui->pushButton->clicked();
            });
        }
    });
    //如果选的不是男就设置为女
    QObject::connect(this->ui->radioButton_7,&QRadioButton::toggled,this,&CMainMenueDlg::changeGender);
    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,this,&CMainMenueDlg::headPictureChange);

    QObject::connect(this,&CMainMenueDlg::startShowStudentAcountInfo,this,&CMainMenueDlg::showStudentAcountInfo);

    QObject::connect(this->ui->pushButton_29,&QPushButton::clicked,[=](){
        if(this->m_joinClassdlg == nullptr)
        {
            this->m_joinClassdlg = new CJoinClassDlg();
            this->m_joinClassdlg->setAcount(this->m_acount);
            this->m_joinClassdlg->setStudentName(this->ui->label_3->text().trimmed());
            this->m_joinClassdlg->move((this->width() - this->m_joinClassdlg->width()) / 2,(this->height() - this->m_joinClassdlg->height()) / 2);
            this->m_joinClassdlg->exec();
            if(this->m_joinClassdlg != nullptr)
            {
                delete this->m_joinClassdlg;
                this->m_joinClassdlg = nullptr;
            }
        }
    });
    this->initJoinClassTableUI();
    this->initJoinClassTableContorl();

    QObject::connect(this,&CMainMenueDlg::startShowClassTable,this,&CMainMenueDlg::showClassTableInfo);
    QObject::connect(this,&CMainMenueDlg::startShowClassIcon,this,&CMainMenueDlg::showClassIconUI);
    QObject::connect(this,&CMainMenueDlg::startGetClassTableInfo,this,&CMainMenueDlg::getClassTableData);
    QObject::connect(this,&CMainMenueDlg::startShowClassTableIndex,&CMainMenueDlg::showClassTableIndex);
    QObject::connect(this,&CMainMenueDlg::startGetClassTableCount,this,&CMainMenueDlg::getClassTableCount);
    QObject::connect(this->ui->pushButton_31,&QPushButton::clicked,this,&CMainMenueDlg::showClassTableNextPage);
    QObject::connect(this->ui->pushButton_30,&QPushButton::clicked,this,&CMainMenueDlg::showClassTableLastPage);
}

void CMainMenueDlg::showClassTableLastPage()
{
    if(this->m_classCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->m_classCurPageIndex <= 1)
    {
        return ;
    }
    //清除当前表中的记录
   this->clearClassTableControl();
    //给当前页递减，并且不能低于1
    if(this->m_classCurPageIndex > 1)
    {
       this->m_classCurPageIndex -= 1;
    }
    emit this->ui->checkBox_8->toggled(false);
    this->ui->checkBox_8->setChecked(false);
    emit this->startGetClassTableInfo();
    this->getClassTableCount();
}

void CMainMenueDlg::showClassTableNextPage()
{
    if(this->m_classCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->m_classCurPageIndex) == this->m_classCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearClassTableControl();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->m_classCurPageIndex) != this->m_classCount)
    {
        this->m_classCurPageIndex += 1;
    }

    //清除选中项
    emit this->ui->checkBox_8->toggled(false);
    this->ui->checkBox_8->setChecked(false);
    emit this->startGetClassTableInfo();
    this->getClassTableCount();
}

void CMainMenueDlg::showClassTableIndex()
{
    QString first = QString::number(this->m_classCurPageIndex);
    first += "/";
    first += this->m_classCount;
    this->ui->label_58->setText(first);
}

typedef struct getClassTableCountArg
{
    QString acount;
    CMainMenueDlg* thiz;
}GetClassTableCountArg;

void CMainMenueDlg::getClassTableCount()
{
    GetClassTableCountArg* arg = new GetClassTableCountArg();
    arg->acount = this->m_acount;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetClassTableCountEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetClassTableCountEntry(LPVOID arg)
{
    GetClassTableCountArg* gInfo = (GetClassTableCountArg*)arg;
    int ret =  gInfo->thiz->m_mainMenueContorller->getClassTableCount(gInfo->acount);
    gInfo->thiz->m_classCount = QString::number(ret);
    //进行发送信号，进行显示总页数
    emit gInfo->thiz->startShowClassTableIndex();
    delete gInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::clearClassTableControl()
{
    //隐藏序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QCheckBox*> buttons = this->m_classCheckVec.at(i)->findChildren<QCheckBox*>();
        for (QCheckBox *button : buttons) {
            button->setVisible(false);
        }
    }

    //清除课程图标
    for(int i = 0 ; i < 8 ; i++)
    {
       QList<QLabel*> labels = this->m_classIconVec.at(i)->findChildren<QLabel*>();
       for(QLabel* lab : labels)
       {
           lab->setPixmap(QPixmap());
       }
    }

    //清除课程名称
    for(int i = 0 ; i < 8 ; i++)
    {
        for (QLabel *button : this->m_classNameVec) {
            button->setText("");
        }
    }

    //清除创建时间
    for(int i = 0 ; i < 8;i++)
    {
        for (QLabel *button : this->m_classCreateTimeVec) {
            button->setText("");
        }
    }

    //清除创建人
    for(int i = 0 ; i < 8 ;i++)
    {
        for (QLabel *button : this->m_classCreatorVec) {
            button->setText("");
        }
    }

    //清除化操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QPushButton*> optButton = this->m_classOperationsVec.at(i)->findChildren<QPushButton*>();
        for (QPushButton *button : optButton) {
            button->setVisible(false);
        }
    }
}

void CMainMenueDlg::showClassIconUI(QImage* image)
{
    QList<QLabel*> ret =  this->m_classIconVec.at(this->classIconIndex++)->findChildren<QLabel*>();
    for(QLabel* lab : ret)
    {
        if(image->isNull())
        {
            qDebug()<<"图像无效";
        }
        lab->setPixmap(QPixmap::fromImage(*image));
        lab->setScaledContents(true);
        delete image;
    }
}

unsigned WINAPI CMainMenueDlg::showClassIcon(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    //进行接收图片并且显示到UI上
//    CClientSocket* clientSocket = CClientSocket::getInstance();
    CClientSocket* clientSocket = new CClientSocket();
    clientSocket->initSocket();
    bool ret2 =  clientSocket->connectToServer();
    if(!ret2)
    {
        return 0;
    }
    //进行封包操作
    char* data = new char[1024];
    memset(data,'\0',sizeof(char) * 1024);
    WaitForSingleObject(thiz->m_Event,INFINITE);
    strcpy(data,thiz->m_ClassIconPath.c_str());
    ResetEvent(thiz->m_Event);
    SetEvent(thiz->m_Event_2);
    ResetEvent(thiz->m_Event_2);
    clientSocket->makePacket(data,strlen(data),2); //获取课程图标的指令为2
    delete[] data;
    //发送数据包
    char* packet = clientSocket->getPacket();
    long long packetSize = clientSocket->getPacketSize();
    int size =  clientSocket->Send(packet);
    qDebug()<<"send size: "<<size;

    //先获取服务端发送的文件大小 8字节
    char* fileSize = new char[8];
    memset(fileSize,'\0',sizeof(char) * 8);
    size = clientSocket->Recv(fileSize,8);
    long long fileSizeNum;
    memmove(&fileSizeNum,fileSize,8);
    delete[] fileSize;
    qDebug()<<"fileSize: "<<fileSizeNum;

    char* recvBuffer = new char[fileSizeNum];
    memset(recvBuffer,'\0',sizeof(char) * fileSizeNum);
    size = clientSocket->Recv(recvBuffer,fileSizeNum); //直接接收到的就是图片文件数据，没有多余内容
    qDebug()<<"recv size: "<<size;
    clientSocket->closeSocket();
    delete clientSocket;

    QByteArray ba(recvBuffer,fileSizeNum);
    QImage* image = new QImage();
    bool ret3 = image->loadFromData(ba,"PNG");
    if(!ret3)
    {
     qDebug()<<"返回false";
    }
    if(image->isNull())
    {
        qDebug()<<"原先获取的图像无效,";
    }
    emit  thiz->startShowClassIcon(image);
//    delete[] pixmapData;
    delete[] recvBuffer;
    _endthreadex(0);
    return 0;
}


void CMainMenueDlg::showClassTableInfo(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    this->classIconIndex = 0;
    //进行UI显示
    this->clearClassTableControl();
   //将数据进行插入到表格中
   for(int i = 0 ; i < ret->size(); i++)
   {
       //显示序号
       QList<QCheckBox*> buttons = this->m_classCheckVec.at(i)->findChildren<QCheckBox*>();
       for (QCheckBox *button : buttons) {
           button->setVisible(true);
       }

       //显示试卷图标
//       QString str = ret->at(i).at(0);
//       this->m_testPaperName.at(i)->setText(str);
       QByteArray arr =  ret->at(i).at(0).toLocal8Bit();
       this->m_ClassIconPath = arr.data();
       SetEvent(this->m_Event);
       HANDLE thread =  (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::showClassIcon,this,0,nullptr);

       WaitForSingleObject(this->m_Event_2,INFINITE);

       //显示课程名称
       QString str = ret->at(i).at(1);
       this->m_classNameVec.at(i)->setText(str);

       //显示创建时间
       str = ret->at(i).at(2);
       this->m_classCreateTimeVec.at(i)->setText(str);

       //创建人
       str = ret->at(i).at(3);
       this->m_classCreatorVec.at(i)->setText(str);

       //显示操作按钮
       QList<QPushButton*> optButton = this->m_classOperationsVec.at(i)->findChildren<QPushButton*>();
       for (QPushButton *button : optButton) {
           button->setVisible(true);
       }
   }
   if(ret != nullptr)
   {
       delete ret;
   }
   qDebug()<<"试卷表格UI显示完成!";
}

typedef struct getClassTableDataArg
{
    QString acount;
    int curPageIndex;
    CMainMenueDlg* thiz;
}GetClassTableDataArg;

void CMainMenueDlg::getClassTableData()
{
    GetClassTableDataArg* arg = new GetClassTableDataArg();
    arg->acount = this->m_acount;
    arg->curPageIndex = this->m_classCurPageIndex;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetClassTableDataEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetClassTableDataEntry(LPVOID arg)
{
    GetClassTableDataArg* dInfo = (GetClassTableDataArg*)arg;
    std::vector<std::vector<std::string>>ret = dInfo->thiz->m_mainMenueContorller->getClassTableData(dInfo->thiz->m_acount,dInfo->curPageIndex);
    //通过信号将结果显示到页面中
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
    emit dInfo->thiz->startShowClassTable(result);
    delete dInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::initClassTableDatabase()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadInitClassTableDatabaseEntry,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadInitClassTableDatabaseEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->m_mainMenueContorller->initClassTableDatabase();
    _endthreadex(0);
    return 0;
}


void CMainMenueDlg::bindClassOperators()
{
    for(QVector<QWidget*>::iterator pos = this->m_classOperationsVec.begin(); pos != this->m_classOperationsVec.end();pos++)
    {
         QList<QPushButton*> ret = (*pos)->findChildren<QPushButton*>();
         for(QPushButton* btn : ret)
         {
             if(btn->text() == "退课")
             {
                 //绑定的删除操作的槽函数
                 QObject::connect(btn,&QPushButton::clicked,[=](){
                     //进行遍历是哪一个按钮，并获取对应的行号
                     int row = 0;
                     for(int i = 0 ; i < this->m_classOperationsVec.size();i++)
                     {
                         QList<QPushButton*> buttons = this->m_classOperationsVec.at(i)->findChildren<QPushButton*>();
                         for(QPushButton* clickedBtn: buttons)
                         {
                             if(clickedBtn == btn)
                             {
                                 this->m_classCurPageIndex = 1;
//                                 this->deleteClassInfoByDateTime(row);
                                 break;
                             }
                         }
                         row++;
                     }
                 });
             }
         }
    }
}

void CMainMenueDlg::initJoinClassTableContorl()
{
    //初始化序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout();
        widget->setLayout(layout);
        QCheckBox* checkBox = new QCheckBox();
        checkBox->setText(QString::number(++this->sortNumberClass));
        checkBox->setFont(QFont("黑体"));
        checkBox->setStyleSheet("QCheckBox{margin-left:25px;}");
        checkBox->setVisible(false);
        layout->addWidget(checkBox);
        checkBox->setParent(widget);
        this->ui->tableWidget_2->setCellWidget(i,0,widget);
        this->m_classCheckVec.push_back(widget);
    }

    //初始化课程图标
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QLabel* testName = new QLabel(widget);
        testName->setGeometry(0,0,135,159);
//        testName->setPixmap(QPixmap(":/icons/acount.png"));
        testName->setScaledContents(true);
        this->ui->tableWidget_2->setCellWidget(i,1,widget);
        this->m_classIconVec.push_back(widget);
    }

    //初始化课程名称
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_2->setCellWidget(i,2,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_classNameVec.push_back(testName);
    }

    //初始化创建时间
    for(int i = 0 ; i < 8;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_2->setCellWidget(i,3,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_classCreateTimeVec.push_back(testName);
    }

    //初始化创建人
    for(int i = 0 ; i < 8 ;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_2->setCellWidget(i,4,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_classCreatorVec.push_back(testName);
    }


    //初始化操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QPushButton* deleteBtn = new QPushButton("退课");
        deleteBtn->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        deleteBtn->setParent(widget);
//        QPushButton* release = new QPushButton("查看详情");
//        release->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
//        release->setParent(widget);
        deleteBtn->setGeometry(100,63,150,40);
//        release->setGeometry(deleteBtn->width() + 30,deleteBtn->y(),150,40);
        deleteBtn->setFont(QFont("黑体",12));
//        release->setFont(QFont("黑体",12));
        deleteBtn->setVisible(false);
//        release->setVisible(false);
        this->ui->tableWidget_2->setCellWidget(i,5,widget);
        this->m_classOperationsVec.push_back(widget);
    }

    this->bindClassOperators();
}

void CMainMenueDlg::initJoinClassTableUI()
{
    this->ui->tableWidget_2->setRowCount(8);
    this->ui->tableWidget_2->setColumnCount(6);
    this->ui->tableWidget_2->horizontalHeader()->hide();
    this->ui->tableWidget_2->verticalHeader()->hide();

    //设置列宽
    int width = this->ui->tableWidget_2->width();
    int heigth = this->ui->tableWidget_2->height();
    this->ui->tableWidget_2->setColumnWidth(0,width / 15);
    this->ui->tableWidget_2->setColumnWidth(1,width / 10);
    this->ui->tableWidget_2->setColumnWidth(2,width / 5);
    this->ui->tableWidget_2->setColumnWidth(3,width / 5);
    this->ui->tableWidget_2->setColumnWidth(4,width / 6);
    this->ui->tableWidget_2->setColumnWidth(5,width / 4);

    this->ui->tableWidget_2->setRowHeight(0,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(1,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(2,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(3,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(4,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(5,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(6,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(7,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(8,heigth/ 4);
    this->ui->tableWidget_2->setRowHeight(9,heigth/ 4);
}

void CMainMenueDlg::headPictureChange()
{
    QString fileName = QFileDialog::getOpenFileName(
         this,
         tr("请选择PNG图片,并且单张图片不得超过400KB"),
         QDir::homePath(),
         tr("PNG Files (*.png);;All Files (*)")
     );
     if (!fileName.isEmpty()) {
       qDebug()<<fileName;
       this->m_mainMenueContorller->changeHeadPicture(fileName,this->m_acount);
       emit this->startShowStudentInfo(this->m_acount);
     } else {
       return;
     }
}

typedef struct changeGenderArg
{
   bool isChecked;
   CMainMenueDlg* thiz;
}ChangeGenderArg;

void CMainMenueDlg::changeGender(bool isChecked)
{
   ChangeGenderArg* arg = new ChangeGenderArg();
   arg->thiz = this;
   arg->isChecked = isChecked;
   _beginthreadex(nullptr,0,&CMainMenueDlg::threadChangeGenderEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadChangeGenderEntry(LPVOID arg)
{
    ChangeGenderArg* cInfo =  (ChangeGenderArg*)arg;
    cInfo->thiz->m_mainMenueContorller->changeGender(cInfo->isChecked,cInfo->thiz->m_acount);
    delete cInfo;
    _endthreadex(0);
    return 0;
}

typedef struct studentAcountInfoArg
{
    QString acount;
    CMainMenueDlg* thiz;
}StudentAcountInfoArg;

void CMainMenueDlg::getStudentAcountInfoData()
{
    StudentAcountInfoArg* arg = new StudentAcountInfoArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentAcountInfoDataEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetStudentAcountInfoDataEntry(LPVOID arg)
{
    StudentAcountInfoArg* tInfo = (StudentAcountInfoArg*)arg;
    std::vector<std::vector<std::string>> ret =  tInfo->thiz->m_mainMenueContorller->showStudentAcountInfo(tInfo->acount); //view层调用conntorller层的接口全部写到子线程中
    emit tInfo->thiz->startShowStudentAcountInfo(&ret);
    delete tInfo;
    _endthreadex(0);
    return 0;
}

void CMainMenueDlg::showStudentAcountInfo(std::vector<std::vector<std::string>>* ret)
{
    QString name = QString::fromLocal8Bit(ret->at(0).at(0).c_str());
    QString teacherId = QString::fromLocal8Bit(ret->at(0).at(1).c_str());
    QString gender = QString::fromLocal8Bit(ret->at(0).at(2).c_str());
    QString phoneNumber = QString::fromLocal8Bit(ret->at(0).at(3).c_str());

    this->ui->label_39->setText(name);
    this->ui->label_40->setText(teacherId);
    if(gender == "1")
    {
      this->ui->radioButton_7->setChecked(true);
    }else if(gender == "0")
    {
        this->ui->radioButton_8->setChecked(true);
    }
    this->ui->label_41->setText(phoneNumber);
}

void CMainMenueDlg::setLoginedAcount(QString acount)
{
    this->m_acount = acount;
}

/*
网络通信的解决办法，1、定好一个数据包的包长
                2、循环发送
                3、循环接收
*/

void  CMainMenueDlg::showStudentInfo(QString acount)
{ 
   std::vector<std::vector<std::string>> ret =  this->m_mainMenueContorller->showStudentInfo(acount);
   std::string tempStr =  ret.at(0).at(0);
   QString str = QString::fromLocal8Bit(tempStr.c_str());
   qDebug()<<str;
   //对数据进行回显
   this->ui->label_3->setText(str);
   this->ui->label_name->setText(str);

   //头像回显
   if(ret.at(0).at(1) != "null")
   {
       //进行回显头像
       this->m_headPath = ret.at(0).at(1);
       this->m_recvHeadThead = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadShowHeadEntry,this,0,nullptr);
   }
}

void CMainMenueDlg::showHeadImageUI(QImage image)
{
    this->ui->label_head->setPixmap(QPixmap::fromImage(image));
    this->ui->label_head->setScaledContents(true);
    this->ui->label_head2->setPixmap(QPixmap::fromImage(image));
    this->ui->label_head2->setScaledContents(true);
}

void CMainMenueDlg::threadShowHead()
{
    //    CClientSocket* clientSocket = CClientSocket::getInstance();
        CClientSocket* clientSocket = new CClientSocket();
        clientSocket->initSocket();
        bool ret2 =  clientSocket->connectToServer();
        if(!ret2)
        {
            return;
        }
        //进行封包操作
        char* data = new char[1024];
        memset(data,'\0',sizeof(char) * 1024);
        strcpy(data,this->m_headPath.c_str());
        clientSocket->makePacket(data,strlen(data),0);
        delete[] data;
        //发送数据包
        char* packet = clientSocket->getPacket();
        long long packetSize = clientSocket->getPacketSize();
        int size =  clientSocket->Send(packet);
        qDebug()<<"send size: "<<size;
        char* recvBuffer = new char[packetSize]; //服务器返回也是一个包的大小
        size =  clientSocket->Recv(recvBuffer);
        qDebug()<<"recv size: "<<size;
        clientSocket->closeSocket();
        delete clientSocket;
        //解包拿去数据
        char* p = recvBuffer;
        WORD head ;
        memcpy(&head,p,sizeof(WORD));
        p += sizeof(WORD);
        DWORD length;
        memcpy(&length,p,sizeof(DWORD));
        p += sizeof(DWORD);
        WORD cmd;
        memcpy(&cmd,p,sizeof(WORD));
        p += sizeof(WORD);
        char* pixmapData = new char[length]; //只要数据，不包含\0
        memmove(pixmapData,p,length);

        QByteArray ba(pixmapData,length);
        QImage image;
        image.loadFromData(ba,"PNG");
        if(image.isNull())
        {
            qDebug()<<"头像获取失败！";
        }
        emit this->startShowHeadImage(image);
        delete[] pixmapData;
        delete[] recvBuffer;
}

unsigned WINAPI CMainMenueDlg::threadShowHeadEntry(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    thiz->threadShowHead();
    _endthreadex(0);
    return 0;
}

//bool CMainMenueDlg::eventFilter (QObject* obj, QEvent* e) //原理底层跟一个定时器一样一直触发执行的函数
//{
//    if(obj == this->ui->label_name)
//    {
//        if(e->type() == QEvent::Enter)
//        {
//            this->m_exitLoginDlg->show();
//        }
//    }else if(obj == this->m_exitLoginDlg)
//    {
//        if(e->type() == QEvent::Leave)
//        {
//            this->m_exitLoginDlg->hide();
//        }
//    }
//    return QDialog::eventFilter(obj,e);
//}

CMainMenueDlg::~CMainMenueDlg()
{
//    if(this->m_exitLoginDlg != nullptr)
//    {
//        delete this->m_exitLoginDlg;
//        this->m_exitLoginDlg = nullptr;
//    }
    if(this->m_mainMenueContorller != nullptr)
    {
        delete this->m_mainMenueContorller;
        this->m_mainMenueContorller = nullptr;
    }

    for(QWidget* widget : this->m_classCheckVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_classCheckVec.clear();

    for(QWidget* widget : this->m_classIconVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_classIconVec.clear();

    for(QLabel* widget : this->m_classNameVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_classNameVec.clear();

    for(QLabel* widget : this->m_classCreateTimeVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_classCreateTimeVec.clear();

    for(QLabel* widget :   this->m_classCreatorVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_classCreatorVec.clear();

    for(QWidget* widget : this->m_classOperationsVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_classOperationsVec.clear();

    //如果关闭界面，接收头像信息的线程还在执行的话就等待接收后结束线程
    WaitForSingleObject(this->m_recvHeadThead,INFINITE); //找到退出崩溃的原因，因为关闭界面的时候，接收头像线程还在执行，但是UI已经释放导致异常
    delete ui;
}
