#include "mainmenuedlg.h"
#include "ui_mainmenuedlg.h"

CMainMenueDlg::CMainMenueDlg(QWidget *parent) : //主菜单界面类
    QDialog(parent),
    ui(new Ui::CMainMenueDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("在线考试系统-教师端");
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
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_4,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(1);    
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_5,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(2);
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_6,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(3);
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
    });

    QObject::connect(this->ui->pushButton_7,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(4);
        this->ui->pushButton_7->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
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
}

void CMainMenueDlg::headPictureChange()
{
    QString fileName = QFileDialog::getOpenFileName(
         this,
         tr("请选择PNG图片,并且单张图片不得超过2MB"),
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
    CClientSocket* clientSocket = CClientSocket::getInstance();
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

    //如果关闭界面，接收头像信息的线程还在执行的话就等待接收后结束线程
    WaitForSingleObject(this->m_recvHeadThead,INFINITE); //找到退出崩溃的原因，因为关闭界面的时候，接收头像线程还在执行，但是UI已经释放导致异常
    delete ui;
}
