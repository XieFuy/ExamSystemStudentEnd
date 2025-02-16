#include "examdlg.h"
#include "ui_examdlg.h"

HHOOK CExamDlg::g_hookHandle = nullptr;
HWND  CExamDlg::hwnd = nullptr;
CExamDlg* CExamDlg::m_thiz = nullptr;

CExamDlg::CExamDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CExamDlg)
{
    ui->setupUi(this);
    this->m_contorller = new CExamContorller();
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    QObject::connect(this->ui->pushButton_5,&QPushButton::clicked,[=](){

        //进行执行添加提交记录
        this->addCommitTestPaper();
        UnhookWindowsHookEx(g_hookHandle);
        CExamDlg::g_hookHandle = nullptr;
        emit this->rejected();
    });

    //每次窗口创建的时候窗机进行获取本窗口的句柄
    CExamDlg::hwnd = reinterpret_cast<HWND>(this->winId());
    CExamDlg::m_thiz = this;

    this->m_isMouseRestricted = true;

    this->setMouseTracking(true);

    this->timer = new QTimer();
    this->totalSeconds = 0;
    this->signalChoiceCount = 0;
    this->multiChoiceCount = 0;
    this->judgeCount = 0;
    this->shortAnswerCount = 0;
    this->judgeChoiceCurIndex = 1;
    this->signalChoiceCurIndex = 1;
    this->multiChoiceCurIndex = 1;
    this->shortAnswerCurIndex = 1;
    this->testPaperName = "";

    this->m_mutex = CreateMutex(nullptr,FALSE,nullptr);

    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(0);
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getSignalChoiceCount();
        this->getCurIndexSignalChoice();
        this->getSignalChoice();
        //先进行解除钩子
        UnhookWindowsHookEx(g_hookHandle);
        CExamDlg::g_hookHandle = nullptr;
        CExamDlg::g_hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL,CExamDlg::HookProc, NULL, 0); //安装钩子，禁止键盘操作
    });

    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(1);
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getMultiChoiceCount();
        this->getCurIndexMultiChoice();
        this->getMultiChoice();
        UnhookWindowsHookEx(g_hookHandle);
        CExamDlg::g_hookHandle = nullptr;
        CExamDlg::g_hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL,CExamDlg::HookProc, NULL, 0);
    });

    QObject::connect(this->ui->pushButton_3,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(2);
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getJudgeChoiceCount();
        this->getCurIndexJudegChoice();
        this->getJudgeChoice();
        UnhookWindowsHookEx(g_hookHandle);
        CExamDlg::g_hookHandle = nullptr;
        CExamDlg::g_hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL,CExamDlg::HookProc, NULL, 0);
    });

    QObject::connect(this->ui->pushButton_4,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(3);
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getShortAnswerCount();
        this->getCurIndexShortAnswerChoice();
        this->getShortAnswer();
        //简答题解除钩子，恢复键盘操作
        UnhookWindowsHookEx(g_hookHandle);
        CExamDlg::g_hookHandle = nullptr;
        CExamDlg::g_hookHandle = SetWindowsHookEx(WH_KEYBOARD_LL,CExamDlg::HookProcScreen, NULL, 0);
    });

    //TODO:明天接着这里继续
    //将Ui中的题号按钮都加入到容器中
    for(int i = 8 ; i <= 85 ; i++ )
    {
        QString strName = "pushButton_";
        strName += QString::number(i);
        QPushButton* btn =  this->findChild<QPushButton*>(strName);
        this->m_signalChoice.push_back(btn);  //这些按钮 不需要我们去释放，UI文件自动管理
    }

    //将Ui中的多选题题号按钮都加入到容器中
    for(int i = 90;i <= 167 ; i++)
    {
        QString strName = "pushButton_";
        strName += QString::number(i);
        QPushButton* btn =  this->findChild<QPushButton*>(strName);
        this->m_multiChoice.push_back(btn);  //这些按钮 不需要我们去释放，UI文件自动管理
    }

    //将UI中的判断题题号按钮都加入到容器中
    for(int i = 171;i <= 248 ; i++)
    {
        QString strName = "pushButton_";
        strName += QString::number(i);
        QPushButton* btn =  this->findChild<QPushButton*>(strName);
        this->m_judgeChoice.push_back(btn);  //这些按钮 不需要我们去释放，UI文件自动管理
    }

    //将Ui中的简答题题号按钮加入到容器中
    for(int i = 252;i <= 329 ; i++)
    {
        QString strName = "pushButton_";
        strName += QString::number(i);
        QPushButton* btn =  this->findChild<QPushButton*>(strName);
        this->m_shortAnswerChoice.push_back(btn);
    }

    int i = 1;
    //给每一个按钮进行设置样式
    for(QPushButton* btn: this->m_signalChoice)
    {
        btn->setText(QString::number(i++));
        btn->setFont(QFont("黑体",12));
        btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
    }

    //给多选题的每一个按钮进行设置样式
    i = 1;
    for(QPushButton* btn: this->m_multiChoice)
    {
        btn->setText(QString::number(i++));
        btn->setFont(QFont("黑体",12));
        btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
    }

    //给判断题的每一个按钮进行设置样式
    i = 1;
    for(QPushButton* btn: this->m_judgeChoice)
    {
        btn->setText(QString::number(i++));
        btn->setFont(QFont("黑体",12));
        btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
    }

    //给简答题的每一个按钮进行设置样式
    i = 1;
    for(QPushButton* btn: this->m_shortAnswerChoice)
    {
        btn->setText(QString::number(i++));
        btn->setFont(QFont("黑体",12));
        btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
    }

    //进行绑定信号槽，实现单击只有一个题号是绿色
    for(QPushButton* btn : this->m_signalChoice)
    {
        QObject::connect(btn,&QPushButton::clicked,[=](){
            //被点击的按钮设置为绿色，其他的所有按钮恢复原来的状态
            btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;background-color:green;}");
            for(QPushButton* btn2 : this->m_signalChoice)
            {
                if(btn2 != btn)
                {
                    btn2->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
                }
            }
            QString str = btn->text().trimmed();
            int num = str.toInt();
            //设置题号
            this->ui->pushButton_86->setText(str);
            //更新当前题的下标
            this->signalChoiceCurIndex = num;
            //获取当先题的
            this->getCurIndexSignalChoice();
            this->getSignalChoice();
        });
    }

    //多选题题号进行信号槽绑定，实现单击只有一个题号是绿色
    for(QPushButton* btn : this->m_multiChoice)
    {
        QObject::connect(btn,&QPushButton::clicked,[=](){
            //被点击的按钮设置为绿色，其他的所有按钮恢复原来的状态
            btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;background-color:green;}");
            for(QPushButton* btn2 : this->m_multiChoice)
            {
                if(btn2 != btn)
                {
                    btn2->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
                }
            }
            QString str = btn->text().trimmed();
            int num = str.toInt();
            //设置题号
            this->ui->pushButton_87->setText(str);
            //更新当前题的下标
            this->multiChoiceCurIndex = num;
            //获取当先题的
            this->getCurIndexMultiChoice(); 
            this->getMultiChoice();
        });
    }

    //判断题题号进行信号槽绑定，实现单击只有一个题号是绿色
    for(QPushButton* btn : this->m_judgeChoice)
    {
        QObject::connect(btn,&QPushButton::clicked,[=](){
            //被点击的按钮设置为绿色，其他的所有按钮恢复原来的状态
            btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;background-color:green;}");
            for(QPushButton* btn2 : this->m_judgeChoice)
            {
                if(btn2 != btn)
                {
                    btn2->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
                }
            }
            QString str = btn->text().trimmed();
            int num = str.toInt();
            //设置题号
            this->ui->pushButton_168->setText(str);
            //更新当前题的下标
            this->judgeChoiceCurIndex = num;
            //获取当先题的
            this->getCurIndexJudegChoice();
            this->getJudgeChoice();
        });
    }

    //简答题题号进行信号槽绑定，实现单击只有一个题号是绿色
    for(QPushButton* btn : this->m_shortAnswerChoice)
    {
        QObject::connect(btn,&QPushButton::clicked,[=](){
            //被点击的按钮设置为绿色，其他的所有按钮恢复原来的状态
            btn->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;background-color:green;}");
            for(QPushButton* btn2 : this->m_shortAnswerChoice)
            {
                if(btn2 != btn)
                {
                    btn2->setStyleSheet("QPushButton{border:none;border:2px solid black;border-radius:25;}");
                }
            }
            QString str = btn->text().trimmed();
            int num = str.toInt();
            //设置题号
            this->ui->pushButton_249->setText(str);
            //更新当前题的下标
            this->shortAnswerCurIndex = num;
            //获取当先题的
            this->getCurIndexShortAnswerChoice();
            this->getShortAnswer();
        });
    }

    //一开始将全部的按钮进行隐藏
    for(QPushButton* btn : this->m_signalChoice)
    {
        btn->setVisible(false);
    }

    //将多选题号按钮进行隐藏
    for(QPushButton* btn : this->m_multiChoice)
    {
        btn->setVisible(false);
    }

    //将判断题号按钮进行隐藏
    for(QPushButton* btn : this->m_judgeChoice)
    {
        btn->setVisible(false);
    }

    //将简答题题号按钮进行隐藏
    for(QPushButton* btn : this->m_shortAnswerChoice)
    {
        btn->setVisible(false);
    }

    // Connect the timer's timeout signal to the updateCountdown slot
    QObject::connect(timer, &QTimer::timeout, this, &CExamDlg::updateCountdown);

    QObject::connect(this,&CExamDlg::startDoModel,[=](){
        this->getCurTestPaperId();
        this->ui->label->setText(this->studentName);
        this->ui->label_2->setText(this->studentId);
        qDebug()<<"时长："<<this->longTime;
        QString time = this->longTime;
        time.remove(time.length() - 2 ,2);
        qDebug()<<"转换："<<time;
        // Example: Start countdown for 5 minutes (300 seconds)
        this->startCountdown(time.toInt());
        emit this->ui->pushButton->clicked();
    });

    QObject::connect(this,&CExamDlg::startShowMenueBtn,this,&CExamDlg::showMenueBtn);
    QObject::connect(this,&CExamDlg::startShowMultiMenueBtn,this,&CExamDlg::showMultiMenueBtn);
    QObject::connect(this,&CExamDlg::startShowJudgeMenueBtn,this,&CExamDlg::showJudgeMenueBtn);
    QObject::connect(this,&CExamDlg::startShowShortAnswerBtn,this,&CExamDlg::showSHortAnswerBtn);

    QObject::connect(this,&CExamDlg::startShowSignalChoice,this,&CExamDlg::showSignalChoice);
    QObject::connect(this,&CExamDlg::startShowMultiChoice,this,&CExamDlg::showMultiChoice);
    QObject::connect(this,&CExamDlg::startShowJudgeChoice,this,&CExamDlg::showJudgeChoice);
    QObject::connect(this,&CExamDlg::startShowShortAnswerChoice,this,&CExamDlg::showShortAnswer);
    QObject::connect(this->ui->pushButton_7,&QPushButton::clicked,this,&CExamDlg::getNextSignalChoive);
    QObject::connect(this->ui->pushButton_89,&QPushButton::clicked,this,&CExamDlg::getNextMultiChoic);
    QObject::connect(this->ui->pushButton_170,&QPushButton::clicked,this,&CExamDlg::getNextJudgeChoice);
    QObject::connect(this->ui->pushButton_251,&QPushButton::clicked,this,&CExamDlg::getNextShortAnswerChoice);
    QObject::connect(this->ui->pushButton_6,&QPushButton::clicked,this,&CExamDlg::getLastSignalChoice);
    QObject::connect(this->ui->pushButton_88,&QPushButton::clicked,this,&CExamDlg::getLastMultiChoic);
    QObject::connect(this->ui->pushButton_169,&QPushButton::clicked,this,&CExamDlg::getLastJudgeChoice);
    QObject::connect(this->ui->pushButton_250,&QPushButton::clicked,this,&CExamDlg::getLastShortAnswerChoice);
    QObject::connect(this,&CExamDlg::startWarning,this,&CExamDlg::showWarningInfo);

    QObject::connect(this->ui->radioButton,&QRadioButton::toggled,this,&CExamDlg::updateSignalAnswertoA);
    QObject::connect(this->ui->radioButton_2,&QRadioButton::toggled,this,&CExamDlg::updateSignalAnswertoB);
    QObject::connect(this->ui->radioButton_3,&QRadioButton::toggled,this,&CExamDlg::updateSignalAnswertoC);
    QObject::connect(this->ui->radioButton_4,&QRadioButton::toggled,this,&CExamDlg::updateSignalAnswertoD);

    QObject::connect(this->ui->checkBox,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerA);
    QObject::connect(this->ui->checkBox_2,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerB);
    QObject::connect(this->ui->checkBox_3,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerC);
    QObject::connect(this->ui->checkBox_4,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerD);
    QObject::connect(this->ui->checkBox_5,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerE);
    QObject::connect(this->ui->checkBox_6,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerF);

    QObject::connect(this->ui->radioButton_5,&QRadioButton::toggled,this,&CExamDlg::updateJudgeAnswerTrue);
    QObject::connect(this->ui->radioButton_6,&QRadioButton::toggled,this,&CExamDlg::updateJudgeAnswerFalse);

    QObject::connect(this->ui->pushButton_330,&QPushButton::clicked,this,&CExamDlg::updateShortAnswer);
    QObject::connect(this,&CExamDlg::startShowShortAnswer,this,&CExamDlg::showShortAnswerUI);


     QTimer* timer = new QTimer(this);
     QObject::connect(timer,&QTimer::timeout,[=](){
         QPoint point = this->pos(); //mapToGlobal将局部坐标转为系统坐标
         RECT mainWinRect;
         mainWinRect.left = point.x();
         mainWinRect.right = point.x() + this->width();
         mainWinRect.top = point.y();
         mainWinRect.bottom = point.y() + this->height();
         ClipCursor(&mainWinRect);
         qDebug()<<"x: "<< point.x()<<" Y:"<<point.y()<<this->width()<<" "<<this->height();
         timer->stop();
     });
     timer->start(1000);
}

void CExamDlg::clearMultiOption() //原因是在设置setChecked的时候也会影响 触发tologed信号
{
    //清除多选框的选中
    QObject::disconnect(this->ui->checkBox,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerA);
    this->ui->checkBox->setChecked(false);
    QObject::connect(this->ui->checkBox,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerA);

    QObject::disconnect(this->ui->checkBox_2,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerB);
    this->ui->checkBox_2->setChecked(false);
    QObject::connect(this->ui->checkBox_2,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerB);

    QObject::disconnect(this->ui->checkBox_3,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerC);
    this->ui->checkBox_3->setChecked(false);
    QObject::connect(this->ui->checkBox_3,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerC);

    QObject::disconnect(this->ui->checkBox_4,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerD);
    this->ui->checkBox_4->setChecked(false);
    QObject::connect(this->ui->checkBox_4,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerD);

    QObject::disconnect(this->ui->checkBox_5,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerE);
    this->ui->checkBox_5->setChecked(false);
    QObject::connect(this->ui->checkBox_5,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerE);

    QObject::disconnect(this->ui->checkBox_6,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerF);
    this->ui->checkBox_6->setChecked(false);
    QObject::connect(this->ui->checkBox_6,&QCheckBox::toggled,this,&CExamDlg::updateMultiAnswerF);

//    this->ui->checkBox->setChecked(false);
//    this->ui->checkBox_2->setChecked(false);
//    this->ui->checkBox_3->setChecked(false);
//    this->ui->checkBox_4->setChecked(false);
//    this->ui->checkBox_5->setChecked(false);
//    this->ui->checkBox_6->setChecked(false); 
}

typedef struct addCommitTestPaper{
    QString teacherId;
    QString classId;
    QString testPaperId;
    QString studentId;
    QString testPaperName;
    CExamDlg* thiz;
}AddCommitTestPaper;

void CExamDlg::addCommitTestPaper()
{
    std::shared_ptr<AddCommitTestPaper> arg = std::make_shared<AddCommitTestPaper>();
    arg->teacherId = this->teacherId;
    arg->classId = this->classId;
    arg->testPaperId = this->testPaperId;
    arg->studentId = this->studentId;
    arg->testPaperName = this->testPaperName;
    arg->thiz = this;
    std::shared_ptr<AddCommitTestPaper>* p = new std::shared_ptr<AddCommitTestPaper>(arg);
    _beginthreadex(nullptr,0,&CExamDlg::threadAddCommitTestPaper,p,0,nullptr);
}

unsigned WINAPI  CExamDlg::threadAddCommitTestPaper(LPVOID arg)
{
    std::shared_ptr<AddCommitTestPaper>* p = (std::shared_ptr<AddCommitTestPaper>*)arg;
    std::shared_ptr<AddCommitTestPaper> aInfo = *p;
    aInfo->thiz->m_contorller->addCommitTestPaper(aInfo->teacherId,aInfo->classId,aInfo->testPaperId,
                                                  aInfo->studentId,aInfo->testPaperName);

    delete p;
    //_endthreadex(0);
    return 0;
}

void CExamDlg::clearShortAnswerOption()
{
    this->ui->textEdit_2->clear();
}

void CExamDlg::clearJudgeOption()
{
    this->ui->radioButton_5->setAutoExclusive(false);
    QObject::disconnect(this->ui->radioButton_5,&QRadioButton::toggled,this,&CExamDlg::updateJudgeAnswerTrue);
    this->ui->radioButton_5->setChecked(false);
    QObject::connect(this->ui->radioButton_5,&QRadioButton::toggled,this,&CExamDlg::updateJudgeAnswerTrue);
    this->ui->radioButton_5->setAutoExclusive(true);

    this->ui->radioButton_6->setAutoExclusive(false);
    QObject::disconnect(this->ui->radioButton_6,&QRadioButton::toggled,this,&CExamDlg::updateJudgeAnswerFalse);
    this->ui->radioButton_6->setChecked(false);
    QObject::connect(this->ui->radioButton_6,&QRadioButton::toggled,this,&CExamDlg::updateJudgeAnswerFalse);
    this->ui->radioButton_6->setAutoExclusive(true);
}

typedef struct updateMultiAnswerArg{
    QString teacherId;
    QString classId;
    QString testPaperId;
    QString studentId;
    QString order;
    QString answer;
    CExamDlg* thiz;
}UpdateMultiAnswerArg;

void CExamDlg::updateShortAnswer()
{
    std::shared_ptr<UpdateMultiAnswerArg> arg = std::make_shared<UpdateMultiAnswerArg>();
    std::shared_ptr<UpdateMultiAnswerArg>* p = new std::shared_ptr<UpdateMultiAnswerArg>(arg);
    arg->thiz = this;
    arg->classId = this->classId;
    arg->order = this->ui->pushButton_249->text().trimmed();
    arg->studentId = this->studentId;
    arg->teacherId = this->teacherId;
    arg->testPaperId = this->testPaperId;
    arg->answer = this->ui->textEdit_2->toPlainText().trimmed();
    _beginthreadex(nullptr,0,&CExamDlg::threadUpdateShortAnswer,p,0,nullptr);
}

unsigned WINAPI CExamDlg::threadUpdateShortAnswer(LPVOID arg)
{
    std::shared_ptr<UpdateMultiAnswerArg>* p = (std::shared_ptr<UpdateMultiAnswerArg>*)arg;
    std::shared_ptr<UpdateMultiAnswerArg> uInfo = *p;
    uInfo->thiz->m_contorller->updateShortAnswer(uInfo->teacherId,uInfo->classId
                                                     ,uInfo->testPaperId,uInfo->studentId,uInfo->order,uInfo->answer);
    delete p;
    //_endthreadex(0);
    return 0;
}

void CExamDlg::updateMultiAnswerF(bool isChecked)  //回显的时候会进行设置状态也会重新触发
{
    WaitForSingleObject(this->m_mutex,INFINITE);
    if(isChecked) //如果不存在F选项的话，进行添加选项F
    {
        if(this->multiAnswer == "NULL")
        {
            this->multiAnswer = "";
        }
        qDebug()<<"选中选项F";
        if(this->multiAnswer.contains("F") == false)
        {
            this->multiAnswer += "F,";
        }
    }else //如果存在F选项，进行删除选项F
    {
        qDebug()<<"撤销选项F";
        if(this->multiAnswer.contains("F"))
        {
            this->multiAnswer.remove("F,");
        }
    }
    if(this->multiAnswer == "")
    {
        this->multiAnswer = "NULL";
    }
    std::shared_ptr<UpdateMultiAnswerArg> arg = std::make_shared<UpdateMultiAnswerArg>();
    std::shared_ptr<UpdateMultiAnswerArg>* p = new std::shared_ptr<UpdateMultiAnswerArg>(arg);
    arg->answer = this->multiAnswer;
    arg->classId = this->classId;
    arg->order = this->ui->pushButton_87->text().trimmed();
    arg->studentId = this->studentId;
    arg->teacherId = this->teacherId;
    arg->testPaperId = this->testPaperId;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CExamDlg::threadUpdateMultiAnswer,p,0,nullptr);
}

void CExamDlg::updateMultiAnswerE(bool isChecked)
{
    WaitForSingleObject(this->m_mutex,INFINITE);
    if(isChecked) //如果不存在D选项的话，进行添加选项D
    {
        if(this->multiAnswer == "NULL")
        {
            this->multiAnswer = "";
        }
         qDebug()<<"选中选项E";
        if(this->multiAnswer.contains("E") == false)
        {
            this->multiAnswer += "E,";
        }
    }else //如果存在E选项，进行删除选项E
    {
        qDebug()<<"撤销选项E";
        if(this->multiAnswer.contains("E"))
        {
            this->multiAnswer.remove("E,");
        }
    }
    if(this->multiAnswer == "")
    {
        this->multiAnswer = "NULL";
    }
    std::shared_ptr<UpdateMultiAnswerArg> arg = std::make_shared<UpdateMultiAnswerArg>();
    std::shared_ptr<UpdateMultiAnswerArg>* p = new std::shared_ptr<UpdateMultiAnswerArg>(arg);
    arg->answer = this->multiAnswer;
    arg->classId = this->classId;
    arg->order = this->ui->pushButton_87->text().trimmed();
    arg->studentId = this->studentId;
    arg->teacherId = this->teacherId;
    arg->testPaperId = this->testPaperId;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CExamDlg::threadUpdateMultiAnswer,p,0,nullptr);
}

void CExamDlg::updateMultiAnswerD(bool isChecked)
{

    WaitForSingleObject(this->m_mutex,INFINITE);

    if(isChecked) //如果不存在D选项的话，进行添加选项D
    {
        if(this->multiAnswer == "NULL")
        {
            this->multiAnswer = "";
        }
         qDebug()<<"选中选项D";
        if(this->multiAnswer.contains("D") == false)
        {
            this->multiAnswer += "D,";
        }
    }else //如果存在D选项，进行删除选项D
    {
        qDebug()<<"撤销选项D";
        if(this->multiAnswer.contains("D"))
        {
            this->multiAnswer.remove("D,");
        }
    }
    if(this->multiAnswer == "")
    {
        this->multiAnswer = "NULL";
    }
    std::shared_ptr<UpdateMultiAnswerArg> arg = std::make_shared<UpdateMultiAnswerArg>();
    std::shared_ptr<UpdateMultiAnswerArg>* p = new std::shared_ptr<UpdateMultiAnswerArg>(arg);
    arg->answer = this->multiAnswer;
    arg->classId = this->classId;
    arg->order = this->ui->pushButton_87->text().trimmed();
    arg->studentId = this->studentId;
    arg->teacherId = this->teacherId;
    arg->testPaperId = this->testPaperId;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CExamDlg::threadUpdateMultiAnswer,p,0,nullptr);
}

void CExamDlg::updateMultiAnswerC(bool isChecked)
{
    WaitForSingleObject(this->m_mutex,INFINITE);
    if(isChecked) //如果不存在C选项的话，进行添加选项C
    {
        if(this->multiAnswer == "NULL")
        {
            this->multiAnswer = "";
        }
         qDebug()<<"选中选项C";
        if(this->multiAnswer.contains("C") == false)
        {
            this->multiAnswer += "C,";
        }
    }else //如果存在C选项，进行删除选项C
    {
        qDebug()<<"撤销选项C";
        if(this->multiAnswer.contains("C"))
        {
            this->multiAnswer.remove("C,");
        }
    }
    if(this->multiAnswer == "")
    {
        this->multiAnswer = "NULL";
    }
    std::shared_ptr<UpdateMultiAnswerArg> arg = std::make_shared<UpdateMultiAnswerArg>();
    std::shared_ptr<UpdateMultiAnswerArg>* p = new std::shared_ptr<UpdateMultiAnswerArg>(arg);
    arg->answer = this->multiAnswer;
    arg->classId = this->classId;
    arg->order = this->ui->pushButton_87->text().trimmed();
    arg->studentId = this->studentId;
    arg->teacherId = this->teacherId;
    arg->testPaperId = this->testPaperId;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CExamDlg::threadUpdateMultiAnswer,p,0,nullptr);
}

void CExamDlg::updateMultiAnswerB(bool isChecked)
{
    WaitForSingleObject(this->m_mutex,INFINITE);
    if(isChecked) //如果不存在B选项的话，进行添加选项B
    {
        if(this->multiAnswer == "NULL")
        {
            this->multiAnswer = "";
        }
        qDebug()<<"选中选项B";
        if(this->multiAnswer.contains("B") == false)
        {
            this->multiAnswer += "B,";
        }
    }else //如果存在A选项，进行删除选项B
    {
        qDebug()<<"撤销选项B";
        if(this->multiAnswer.contains("B"))
        {
            this->multiAnswer.remove("B,");
        }
    }
    if(this->multiAnswer == "")
    {
        this->multiAnswer = "NULL";
    }
    std::shared_ptr<UpdateMultiAnswerArg> arg = std::make_shared<UpdateMultiAnswerArg>();
    std::shared_ptr<UpdateMultiAnswerArg>* p = new std::shared_ptr<UpdateMultiAnswerArg>(arg);
    arg->answer = this->multiAnswer;
    arg->classId = this->classId;
    arg->order = this->ui->pushButton_87->text().trimmed();
    arg->studentId = this->studentId;
    arg->teacherId = this->teacherId;
    arg->testPaperId = this->testPaperId;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CExamDlg::threadUpdateMultiAnswer,p,0,nullptr);
}

void CExamDlg::updateMultiAnswerA(bool isChecked)
{
    //在开始进行上锁
    WaitForSingleObject(this->m_mutex,INFINITE);
    if(isChecked) //如果不存在A选项的话，进行添加选项A
    {
        if(this->multiAnswer == "NULL")
        {
            this->multiAnswer = "";
        }
        qDebug()<<"选中选项A";
        if(this->multiAnswer.contains("A") == false)
        {
            this->multiAnswer += "A,";
        }
    }else //如果存在A选项，进行删除选项A
    {
        qDebug()<<"撤销选项A";
        if(this->multiAnswer.contains("A"))
        {
            //进行去除A选项
            this->multiAnswer.remove("A,");
        }
    }
    if(this->multiAnswer == "")
    {
        this->multiAnswer = "NULL";
    }
    std::shared_ptr<UpdateMultiAnswerArg> arg = std::make_shared<UpdateMultiAnswerArg>();
    std::shared_ptr<UpdateMultiAnswerArg>* p = new std::shared_ptr<UpdateMultiAnswerArg>(arg);
    arg->answer = this->multiAnswer;
    arg->classId = this->classId;
    arg->order = this->ui->pushButton_87->text().trimmed();
    arg->studentId = this->studentId;
    arg->teacherId = this->teacherId;
    arg->testPaperId = this->testPaperId;
    arg->thiz = this;
    _beginthreadex(nullptr,0,&CExamDlg::threadUpdateMultiAnswer,p,0,nullptr);
}

unsigned WINAPI CExamDlg::threadUpdateMultiAnswer(LPVOID arg)
{
    std::shared_ptr<UpdateMultiAnswerArg>* p = (std::shared_ptr<UpdateMultiAnswerArg>*)arg;
    std::shared_ptr<UpdateMultiAnswerArg> uInfo = *p;
    //进行判断是不是空串，如果是空串则进行设置为答案为NULL


    qDebug()<<"存入的多选题的选项："<<uInfo->thiz->multiAnswer;
    uInfo->thiz->m_contorller->UpdateMultiAnswer(uInfo->teacherId,uInfo->classId
                                                 ,uInfo->testPaperId,uInfo->studentId
                                                 ,uInfo->order,uInfo->answer);
    delete p;
    ReleaseMutex(uInfo->thiz->m_mutex);
    //_endthreadex(0);
    return 0;
}

void CExamDlg::clearSignalOption()
{
    //设置所有的radiobutton都为未点击
    this->ui->radioButton->setAutoExclusive(false);
    this->ui->radioButton->setChecked(false);
    this->ui->radioButton->setAutoExclusive(true);

    this->ui->radioButton_2->setAutoExclusive(false);
    this->ui->radioButton_2->setChecked(false);
    this->ui->radioButton_2->setAutoExclusive(true);

    this->ui->radioButton_3->setAutoExclusive(false);
    this->ui->radioButton_3->setChecked(false);
    this->ui->radioButton_3->setAutoExclusive(true);

    this->ui->radioButton_4->setAutoExclusive(false);
    this->ui->radioButton_4->setChecked(false);
    this->ui->radioButton_4->setAutoExclusive(true);
}

typedef struct updateSignalArg{
    QString teacherId;
    QString classId;
    QString testPaperId;
    QString studentId;
    QString order;
    CExamDlg* thiz;
}UpdateSignalArg;

void CExamDlg::updateJudgeAnswerTrue(bool isChecked)
{
    if(isChecked)
    {
        std::shared_ptr<UpdateSignalArg> arg = std::make_shared<UpdateSignalArg>();
        std::shared_ptr<UpdateSignalArg>* p = new std::shared_ptr<UpdateSignalArg>(arg);
        arg->thiz = this;
        arg->classId = this->classId;
        arg->order = this->ui->pushButton_168->text().trimmed();
        arg->studentId = this->studentId;
        arg->teacherId = this->teacherId;
        arg->testPaperId = this->testPaperId;
        _beginthreadex(nullptr,0,&CExamDlg::threadUpdateJudgeAnswerTrue,p,0,nullptr);
    }
}

unsigned WINAPI CExamDlg::threadUpdateJudgeAnswerTrue(LPVOID arg)
{
    std::shared_ptr<UpdateSignalArg>* p = (std::shared_ptr<UpdateSignalArg>*)arg;
    std::shared_ptr<UpdateSignalArg> uInfo = *p;
    uInfo->thiz->m_contorller->updateJudgeAnswerTrue(uInfo->teacherId,uInfo->classId
                                                     ,uInfo->testPaperId,uInfo->studentId,uInfo->order);
    delete p;
    //_endthreadex(0);
    return 0;
}

void CExamDlg::updateJudgeAnswerFalse(bool isChecked)
{
    if(isChecked)
    {
        std::shared_ptr<UpdateSignalArg> arg = std::make_shared<UpdateSignalArg>();
        std::shared_ptr<UpdateSignalArg>* p = new std::shared_ptr<UpdateSignalArg>(arg);
        arg->thiz = this;
        arg->classId = this->classId;
        arg->order = this->ui->pushButton_168->text().trimmed();
        arg->studentId = this->studentId;
        arg->teacherId = this->teacherId;
        arg->testPaperId = this->testPaperId;
        _beginthreadex(nullptr,0,&CExamDlg::threadUpdateJudgeAnswerFalse,p,0,nullptr);
    }
}

unsigned WINAPI CExamDlg::threadUpdateJudgeAnswerFalse(LPVOID arg)
{
    std::shared_ptr<UpdateSignalArg>* p = (std::shared_ptr<UpdateSignalArg>*)arg;
    std::shared_ptr<UpdateSignalArg> uInfo = *p;
    uInfo->thiz->m_contorller->updateJudgeAnswerFalse(uInfo->teacherId,uInfo->classId
                                                     ,uInfo->testPaperId,uInfo->studentId,uInfo->order);
    delete p;
    //_endthreadex(0);
    return 0;
}

void CExamDlg::getMultiChoice()
{
    this->clearMultiOption();
    std::shared_ptr<UpdateSignalArg> uArg = std::make_shared<UpdateSignalArg>();
    std::shared_ptr<UpdateSignalArg>* p = new  std::shared_ptr<UpdateSignalArg>(uArg);
    uArg->teacherId = this->teacherId;
    uArg->classId = this->classId;
    uArg->testPaperId = this->testPaperId;
    uArg->studentId = this->studentId;
    uArg->order = this->ui->pushButton_87->text().trimmed();
    uArg->thiz = this;
    _beginthreadex(nullptr,0,&CExamDlg::threadGetMultiChoice,p,0,nullptr);
}

unsigned WINAPI  CExamDlg::threadGetMultiChoice(LPVOID arg)
{
    std::shared_ptr<UpdateSignalArg>* p = (std::shared_ptr<UpdateSignalArg>*)arg;
    std::shared_ptr<UpdateSignalArg> uInfo = *p;
    uInfo->thiz->multiAnswer = "";
    std::vector<std::vector<std::string>> ret =  uInfo->thiz->m_contorller->getMultiChoice(uInfo->teacherId,uInfo->classId
                                               ,uInfo->testPaperId
                                               ,uInfo->studentId,uInfo->order);

    QString str = QString::fromLocal8Bit(ret.at(0).at(0).c_str());
     qDebug()<<"数据回显："<<str;
    if(str == "NULL")
    {
        uInfo->thiz->clearMultiOption();
        uInfo->thiz->multiAnswer = "NULL";
    }else
    {
       //先清空所有的选项，然后选中答案所选的项
        uInfo->thiz->multiAnswer = str;
        uInfo->thiz->clearMultiOption();
        if(str.contains("A"))
        {
            QObject::disconnect(uInfo->thiz->ui->checkBox,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerA);
            uInfo->thiz->ui->checkBox->setChecked(true);
            QObject::connect(uInfo->thiz->ui->checkBox,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerA);
        }
        if(str.contains("B"))
        {
            QObject::disconnect(uInfo->thiz->ui->checkBox_2,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerB);
            uInfo->thiz->ui->checkBox_2->setChecked(true);
            QObject::connect(uInfo->thiz->ui->checkBox_2,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerB);
        }
        if(str.contains("C"))
        {
            QObject::disconnect(uInfo->thiz->ui->checkBox_3,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerC);
             uInfo->thiz->ui->checkBox_3->setChecked(true);
             QObject::connect(uInfo->thiz->ui->checkBox_3,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerC);
        }
        if(str.contains("D"))
        {
             QObject::disconnect(uInfo->thiz->ui->checkBox_4,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerD);
             uInfo->thiz->ui->checkBox_4->setChecked(true);
              QObject::connect(uInfo->thiz->ui->checkBox_4,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerD);
        }
        if(str.contains("E"))
        {
            QObject::disconnect(uInfo->thiz->ui->checkBox_5,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerE);
             uInfo->thiz->ui->checkBox_5->setChecked(true);
             QObject::connect(uInfo->thiz->ui->checkBox_5,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerE);
        }
        if(str.contains("F"))
        {
            QObject::disconnect(uInfo->thiz->ui->checkBox_6,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerF);
             uInfo->thiz->ui->checkBox_6->setChecked(true);
             QObject::connect(uInfo->thiz->ui->checkBox_6,&QCheckBox::toggled,uInfo->thiz,&CExamDlg::updateMultiAnswerF);
        }
    }
    delete p;
    //_endthreadex(0);
    return 0;
}

void CExamDlg::showShortAnswerUI(QString str)
{
    if(str == "NULL" || str == "")
    {
        //清空所有的选项
       this->clearShortAnswerOption();
    }else
    {
        //进行显示
        this->ui->textEdit_2->setText(str);
    }
}

void CExamDlg::getShortAnswer()
{
    this->clearShortAnswerOption();
    std::shared_ptr<UpdateSignalArg> uArg = std::make_shared<UpdateSignalArg>();
    std::shared_ptr<UpdateSignalArg>* p = new  std::shared_ptr<UpdateSignalArg>(uArg);
    uArg->teacherId = this->teacherId;
    uArg->classId = this->classId;
    uArg->testPaperId = this->testPaperId;
    uArg->studentId = this->studentId;
    uArg->order = this->ui->pushButton_249->text().trimmed();
    uArg->thiz = this;
    _beginthreadex(nullptr,0,&CExamDlg::threadGetShortAnswer,p,0,nullptr);
}

unsigned WINAPI CExamDlg::threadGetShortAnswer(LPVOID arg)
{
    std::shared_ptr<UpdateSignalArg>* p = (std::shared_ptr<UpdateSignalArg>*)arg;
    std::shared_ptr<UpdateSignalArg> uInfo = *p;
    std::vector<std::vector<std::string>> ret =  uInfo->thiz->m_contorller->getShortAnswer(uInfo->teacherId,uInfo->classId
                                               ,uInfo->testPaperId
                                               ,uInfo->studentId,uInfo->order);
    qDebug()<<"回显的答案："<<ret.size();
    //进行对结果进行处理
    QString str = QString::fromLocal8Bit(ret.at(0).at(0).c_str());
    emit uInfo->thiz->startShowShortAnswer(str);
    delete p;
    //_endthreadex(0);
    return 0;
}

void CExamDlg::getJudgeChoice()
{
    this->clearJudgeOption();
    std::shared_ptr<UpdateSignalArg> uArg = std::make_shared<UpdateSignalArg>();
    std::shared_ptr<UpdateSignalArg>* p = new  std::shared_ptr<UpdateSignalArg>(uArg);
    uArg->teacherId = this->teacherId;
    uArg->classId = this->classId;
    uArg->testPaperId = this->testPaperId;
    uArg->studentId = this->studentId;
    uArg->order = this->ui->pushButton_168->text().trimmed();
    uArg->thiz = this;
    _beginthreadex(nullptr,0,&CExamDlg::threadGetJudgeChoice,p,0,nullptr);
}

unsigned WINAPI CExamDlg::threadGetJudgeChoice(LPVOID arg)
{
    std::shared_ptr<UpdateSignalArg>* p = (std::shared_ptr<UpdateSignalArg>*)arg;
    std::shared_ptr<UpdateSignalArg> uInfo = *p;
    std::vector<std::vector<std::string>> ret =  uInfo->thiz->m_contorller->getJudgeChoice(uInfo->teacherId,uInfo->classId
                                               ,uInfo->testPaperId
                                               ,uInfo->studentId,uInfo->order);
    qDebug()<<"回显的答案："<<ret.at(0).at(0).c_str();
    //进行对结果进行处理
    if(ret.at(0).at(0) == "NULL")
    {
        //清空所有的选项
        uInfo->thiz->clearJudgeOption();
    }else if(ret.at(0).at(0) == "0")
    {
        //选中 错
        uInfo->thiz->ui->radioButton_6->setChecked(true);
    }else if(ret.at(0).at(0) == "1")
    {
        //选中 对
        uInfo->thiz->ui->radioButton_5->setChecked(true);
    }
    delete p;
    //_endthreadex(0);
    return 0;
}

void CExamDlg::getSignalChoice()
{
    std::shared_ptr<UpdateSignalArg> uArg = std::make_shared<UpdateSignalArg>();
    std::shared_ptr<UpdateSignalArg>* p = new  std::shared_ptr<UpdateSignalArg>(uArg);
    uArg->teacherId = this->teacherId;
    uArg->classId = this->classId;
    uArg->testPaperId = this->testPaperId;
    uArg->studentId = this->studentId;
    uArg->order = this->ui->pushButton_86->text().trimmed();
    uArg->thiz = this;
    _beginthreadex(nullptr,0,&CExamDlg::threadGetSignalChoice,p,0,nullptr);
}

unsigned WINAPI CExamDlg::threadGetSignalChoice(LPVOID arg)
{
    std::shared_ptr<UpdateSignalArg>* p = (std::shared_ptr<UpdateSignalArg>*)arg;
    std::shared_ptr<UpdateSignalArg> uInfo = *p;
    std::vector<std::vector<std::string>> ret =  uInfo->thiz->m_contorller->getSignalChoice(uInfo->teacherId,uInfo->classId
                                               ,uInfo->testPaperId
                                               ,uInfo->studentId,uInfo->order);
    //进行对结果进行处理
    if(ret.at(0).at(0) == "NULL")
    {
        //清空所有的选项
        uInfo->thiz->clearSignalOption();
    }else if(ret.at(0).at(0) == "A")
    {
        //选中A
        uInfo->thiz->ui->radioButton->setChecked(true);
    }else if(ret.at(0).at(0) == "B")
    {
        //选中B
        uInfo->thiz->ui->radioButton_2->setChecked(true);
    }else if(ret.at(0).at(0) == "C")
    {
        //选中C
        uInfo->thiz->ui->radioButton_3->setChecked(true);
    }else if(ret.at(0).at(0) == "D")
    {
        //选中D
        uInfo->thiz->ui->radioButton_4->setChecked(true);
    }
    delete p;
    //_endthreadex(0);
    return 0;
}

unsigned WINAPI CExamDlg::threadUpdateSignalAnswertoA(LPVOID arg)
{
   std::shared_ptr<UpdateSignalArg>* p = (std::shared_ptr<UpdateSignalArg>*)arg;
   std::shared_ptr<UpdateSignalArg> uInfo = *p;
   uInfo->thiz->m_contorller->updateSignalAnswertoA(uInfo->teacherId,uInfo->classId
                                                    ,uInfo->testPaperId,uInfo->studentId,uInfo->order);
   delete p;
   //_endthreadex(0);
   return 0;
}

void CExamDlg::updateSignalAnswertoA(bool isChecked)
{
    if(isChecked)
    {
        std::shared_ptr<UpdateSignalArg> arg = std::make_shared<UpdateSignalArg>();
        std::shared_ptr<UpdateSignalArg>* p = new std::shared_ptr<UpdateSignalArg>(arg);
        arg->thiz = this;
        arg->classId = this->classId;
        arg->order = this->ui->pushButton_86->text().trimmed();
        arg->studentId = this->studentId;
        arg->teacherId = this->teacherId;
        arg->testPaperId = this->testPaperId;
        _beginthreadex(nullptr,0,&CExamDlg::threadUpdateSignalAnswertoA,p,0,nullptr);
    }
}

unsigned WINAPI CExamDlg::threadUpdateSignalAnswertoB(LPVOID arg)
{
    std::shared_ptr<UpdateSignalArg>* p = (std::shared_ptr<UpdateSignalArg>*)arg;
    std::shared_ptr<UpdateSignalArg> uInfo = *p;
    uInfo->thiz->m_contorller->updateSignalAnswertoB(uInfo->teacherId,uInfo->classId
                                                     ,uInfo->testPaperId,uInfo->studentId,uInfo->order);
    delete p;
    //_endthreadex(0);
    return 0;
}

void CExamDlg::updateSignalAnswertoB(bool isChecked)
{
    if(isChecked)
    {
        std::shared_ptr<UpdateSignalArg> arg = std::make_shared<UpdateSignalArg>();
        std::shared_ptr<UpdateSignalArg>* p = new std::shared_ptr<UpdateSignalArg>(arg);
        arg->thiz = this;
        arg->classId = this->classId;
        arg->order = this->ui->pushButton_86->text().trimmed();
        arg->studentId = this->studentId;
        arg->teacherId = this->teacherId;
        arg->testPaperId = this->testPaperId;
        _beginthreadex(nullptr,0,&CExamDlg::threadUpdateSignalAnswertoB,p,0,nullptr);
    }
}

//TODO:明天接着继续简答题的部分。目前是答案没有存储进数据库。
unsigned WINAPI CExamDlg::threadUpdateSignalAnswertoC(LPVOID arg)
{
    std::shared_ptr<UpdateSignalArg>* p = (std::shared_ptr<UpdateSignalArg>*)arg;
    std::shared_ptr<UpdateSignalArg> uInfo = *p;
    uInfo->thiz->m_contorller->updateSignalAnswertoC(uInfo->teacherId,uInfo->classId
                                                     ,uInfo->testPaperId,uInfo->studentId,uInfo->order);
    delete p;
    //_endthreadex(0);
    return 0;
}

void CExamDlg::updateSignalAnswertoC(bool isChecked)
{
    if(isChecked)
    {
        std::shared_ptr<UpdateSignalArg> arg = std::make_shared<UpdateSignalArg>();
        std::shared_ptr<UpdateSignalArg>* p = new std::shared_ptr<UpdateSignalArg>(arg);
        arg->thiz = this;
        arg->classId = this->classId;
        arg->order = this->ui->pushButton_86->text().trimmed();
        arg->studentId = this->studentId;
        arg->teacherId = this->teacherId;
        arg->testPaperId = this->testPaperId;
        _beginthreadex(nullptr,0,&CExamDlg::threadUpdateSignalAnswertoC,p,0,nullptr);
    }
}

unsigned WINAPI CExamDlg::threadUpdateSignalAnswertoD(LPVOID arg)
{
    std::shared_ptr<UpdateSignalArg>* p = (std::shared_ptr<UpdateSignalArg>*)arg;
    std::shared_ptr<UpdateSignalArg> uInfo = *p;
    uInfo->thiz->m_contorller->updateSignalAnswertoD(uInfo->teacherId,uInfo->classId
                                                     ,uInfo->testPaperId,uInfo->studentId,uInfo->order);
    delete p;
    //_endthreadex(0);
    return 0;
}

void CExamDlg::updateSignalAnswertoD(bool isChecked)
{
    if(isChecked)
    {
        std::shared_ptr<UpdateSignalArg> arg = std::make_shared<UpdateSignalArg>();
        std::shared_ptr<UpdateSignalArg>* p = new std::shared_ptr<UpdateSignalArg>(arg);
        arg->thiz = this;
        arg->classId = this->classId;
        arg->order = this->ui->pushButton_86->text().trimmed();
        arg->studentId = this->studentId;
        arg->teacherId = this->teacherId;
        arg->testPaperId = this->testPaperId;
        _beginthreadex(nullptr,0,&CExamDlg::threadUpdateSignalAnswertoD,p,0,nullptr);
    }
}

void CExamDlg::showWarningInfo()
{
    QMessageBox* box = new QMessageBox(QMessageBox::Warning,"警告","考试中禁止切屏，请规范考试！",QMessageBox::Ok);
    box->setParent(this);
    box->exec();
    delete box;
}

LRESULT CALLBACK CExamDlg::HookProc(int nCode, WPARAM wParam, LPARAM lParam)
{
   // 拦截键盘消息
    if (nCode == HC_ACTION) {  //触发键盘事件，将键盘事件及进行禁止
        if (wParam == WM_KEYDOWN || wParam == WM_KEYUP ||
                wParam == WM_SYSKEYDOWN || wParam == WM_SYSKEYUP) {
            // 忽略键盘事件，返回1表示拦截事件，不传递给下一个钩子或目标窗口
            return 1;
        }
    }
    // 对于其他事件，继续传递
    return CallNextHookEx(CExamDlg::g_hookHandle, nCode, wParam, lParam);
}

LRESULT CALLBACK CExamDlg::HookProcScreen(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION) // 应用窗体切换事件或键盘事件
    {
        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)
        {
            KBDLLHOOKSTRUCT* kbdStruct = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
            // 检查是否是Win键或Tab键
            if (kbdStruct->vkCode == VK_LWIN || kbdStruct->vkCode == VK_RWIN ||
                kbdStruct->vkCode == VK_TAB)
            {
                // 发出警告信号（这里假设m_thiz和startWarning()已经正确设置）
                emit CExamDlg::m_thiz->startWarning();
                // 阻止这些键的作用
                return 1;
            }
        }
    }

    // 对于其他事件，继续传递
    return CallNextHookEx(CExamDlg::g_hookHandle, nCode, wParam, lParam);
}

void CExamDlg::getLastShortAnswerChoice()
{
    if(this->shortAnswerCurIndex > 1)
    {
        this->shortAnswerCurIndex -= 1;

        //重新显示题目
//        this->getCurIndexShortAnswerChoice();

        //更改题号
         this->ui->pushButton_249->setText(QString::number(this->shortAnswerCurIndex));
        //重新显示题号高光
         emit this->m_shortAnswerChoice.at(this->shortAnswerCurIndex - 1)->clicked();
    }
}

void CExamDlg::getLastJudgeChoice()
{
    if(this->judgeChoiceCurIndex > 1)
    {
        this->judgeChoiceCurIndex -= 1;

        //重新显示题目
//        this->getCurIndexJudegChoice();

        //更改题号
        this->ui->pushButton_168->setText(QString::number(this->judgeChoiceCurIndex));
        //重新显示题号高光
        emit this->m_judgeChoice.at(this->judgeChoiceCurIndex - 1)->clicked();
    }
}

void CExamDlg::getLastMultiChoic()
{
    if(this->multiChoiceCurIndex > 1)
    {
        this->multiChoiceCurIndex -= 1;

        //重新显示题目
//        this->getCurIndexMultiChoice();

        //更改题号
        this->ui->pushButton_87->setText(QString::number(this->multiChoiceCurIndex));
        //重新显示题号高光
        emit this->m_multiChoice.at(this->multiChoiceCurIndex - 1)->clicked();
    }
}

void CExamDlg::getLastSignalChoice()
{
    if(this->signalChoiceCurIndex > 1)
    {
        this->signalChoiceCurIndex -= 1;

        //重新显示题目
//        this->getCurIndexSignalChoice();

        //更改题号
        this->ui->pushButton_86->setText(QString::number(this->signalChoiceCurIndex));
        //重新显示题号高光
        emit this->m_signalChoice.at(this->signalChoiceCurIndex - 1)->clicked();
//        this->clearSignalOption();
    }
}

void CExamDlg::getNextShortAnswerChoice()
{
    if(this->shortAnswerCurIndex < this->shortAnswerCount)
    {
        this->shortAnswerCurIndex += 1;

        //重新显示题目
//        this->getCurIndexShortAnswerChoice();

        //更改题号
        this->ui->pushButton_249->setText(QString::number(this->shortAnswerCurIndex));
        //重新显示题号高光
        emit this->m_shortAnswerChoice.at(this->shortAnswerCurIndex - 1)->clicked();
    }
}

void CExamDlg::getNextJudgeChoice()
{
    if(this->judgeChoiceCurIndex < this->judgeCount)
    {
        this->judgeChoiceCurIndex += 1;

        //重新显示题目
//        this->getCurIndexJudegChoice();

        //更改题号
        this->ui->pushButton_168->setText(QString::number(this->judgeChoiceCurIndex));
        //重新显示题号高光
        emit this->m_judgeChoice.at(this->judgeChoiceCurIndex - 1)->clicked();
    }
}

void CExamDlg::getNextMultiChoic()
{
    if(this->multiChoiceCurIndex < this->multiChoiceCount)
    {
        this->multiChoiceCurIndex += 1;

        //重新显示题目
//        this->getCurIndexMultiChoice();

        //更改题号
        this->ui->pushButton_87->setText(QString::number(this->multiChoiceCurIndex));
        //重新显示题号高光
        emit this->m_multiChoice.at(this->multiChoiceCurIndex - 1)->clicked();
    }
}


void CExamDlg::getNextSignalChoive()
{
    if(this->signalChoiceCurIndex < this->signalChoiceCount)
    {
        this->signalChoiceCurIndex += 1;

        //重新显示题目
//        this->getCurIndexSignalChoice();

        //更改题号
        this->ui->pushButton_86->setText(QString::number(this->signalChoiceCurIndex));
        //重新显示题号高光
        emit this->m_signalChoice.at(this->signalChoiceCurIndex - 1)->clicked();
//        this->clearSignalOption();
    }
}

void CExamDlg::showShortAnswer(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    //显示题干
    this->ui->textEdit->setText(ret->at(0).at(0));

    delete ret;
}

void CExamDlg::getCurIndexShortAnswerChoice()
{
    _beginthreadex(nullptr,0,&CExamDlg::threadGetCurIndexShortAnswerChoice,this,0,nullptr);
}

unsigned WINAPI CExamDlg::threadGetCurIndexShortAnswerChoice(LPVOID arg)
{
    CExamDlg* thiz = (CExamDlg*)arg;
    std::vector<std::vector<std::string>> ret =  thiz->m_contorller->getCurIndexShortAnswerChoice(thiz->testPaperId,thiz->shortAnswerCurIndex);

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
    emit thiz->startShowShortAnswerChoice(result);
    //_endthreadex(0);
    return 0;
}

void CExamDlg::DynemicShowJudgeChoice()
{
    this->ui->radioButton_5->move(this->ui->verticalLayoutWidget_3->x(),this->ui->verticalLayoutWidget_3->height() + this->ui->verticalLayoutWidget_3->y() + 10);
    this->ui->radioButton_6->move(this->ui->radioButton_5->x(),this->ui->radioButton_5->y() + this->ui->radioButton_5->height() + 10);
}

void CExamDlg::showJudgeChoice(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    //显示题干
    this->ui->label_20->setText(ret->at(0).at(0));
    this->ui->verticalLayoutWidget_3->adjustSize();
    this->DynemicShowJudgeChoice();

    //显示A选项
    this->ui->radioButton_5->setText(ret->at(0).at(1));

    //显示B选项
    this->ui->radioButton_6->setText(ret->at(0).at(2));

    delete ret;
}

void CExamDlg::getCurIndexJudegChoice()
{
    _beginthreadex(nullptr,0,&CExamDlg::threadGetCurIndexJudegChoice,this,0,nullptr);
}

unsigned WINAPI CExamDlg::threadGetCurIndexJudegChoice(LPVOID arg)
{
    CExamDlg* thiz = (CExamDlg*)arg;
    std::vector<std::vector<std::string>> ret =  thiz->m_contorller->getCurIndexJudegChoice(thiz->testPaperId,thiz->judgeChoiceCurIndex);

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
    emit thiz->startShowJudgeChoice(result);
    //_endthreadex(0);
    return 0;
}

void CExamDlg::DynemicShowMultiChoice()
{
    //进行设置第一个选项的位置
    this->ui->checkBox->move(this->ui->verticalLayoutWidget_2->x(),this->ui->verticalLayoutWidget_2->height() + this->ui->verticalLayoutWidget_2->y() + 10);
    this->ui->label_12->move(this->ui->checkBox->x() - 50,this->ui->checkBox->y());
    this->ui->checkBox_2->move(this->ui->checkBox->x(),this->ui->checkBox->y() + this->ui->checkBox->height() + 1);
    this->ui->label_13->move(this->ui->checkBox_2->x() - 50,this->ui->checkBox_2->y());
    this->ui->checkBox_3->move(this->ui->checkBox_2->x(),this->ui->checkBox_2->y() + this->ui->checkBox_2->height() + 1);
    this->ui->label_14->move(this->ui->checkBox_3->x() - 50,this->ui->checkBox_3->y());
    this->ui->checkBox_4->move(this->ui->checkBox_3->x(),this->ui->checkBox_3->y() + this->ui->checkBox_3->height() + 1);
    this->ui->label_15->move(this->ui->checkBox_4->x() - 50,this->ui->checkBox_4->y());

    this->ui->checkBox_5->move(this->ui->checkBox_4->x(),this->ui->checkBox_4->y() + this->ui->checkBox_4->height() + 1);
    this->ui->label_16->move(this->ui->checkBox_5->x() - 50,this->ui->checkBox_5->y());

    this->ui->checkBox_6->move(this->ui->checkBox_5->x(),this->ui->checkBox_5->y() + this->ui->checkBox_5->height() + 1);
    this->ui->label_17->move(this->ui->checkBox_6->x() - 50,this->ui->checkBox_6->y());

}

void CExamDlg::showMultiChoice(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    //显示题干

    this->ui->label_11->setText(ret->at(0).at(0));
    this->ui->verticalLayoutWidget_2->adjustSize();
    this->DynemicShowMultiChoice();
    //显示A选项
    this->ui->checkBox->setText(ret->at(0).at(1));

    //显示B选项
    this->ui->checkBox_2->setText(ret->at(0).at(2));

    //显示C选项
    this->ui->checkBox_3->setText(ret->at(0).at(3));

    //显示D选项
    this->ui->checkBox_4->setText(ret->at(0).at(4));

    //显示E选项
    this->ui->checkBox_5->setText(ret->at(0).at(5));

    //显示F选项
    this->ui->checkBox_6->setText(ret->at(0).at(6));

    delete ret;
}


void  CExamDlg::DynemicShowSignalChoice()
{
    //进行设置第一个选项的位置
    this->ui->radioButton->move(this->ui->verticalLayoutWidget->x(),this->ui->verticalLayoutWidget->height() + this->ui->verticalLayoutWidget->y() + 10);
    this->ui->label_7->move(this->ui->radioButton->x() - 50,this->ui->radioButton->y());
    this->ui->radioButton_2->move(this->ui->radioButton->x(),this->ui->radioButton->y() + this->ui->radioButton->height() + 10);
    this->ui->label_8->move(this->ui->radioButton_2->x() - 50,this->ui->radioButton_2->y());
    this->ui->radioButton_3->move(this->ui->radioButton_2->x(),this->ui->radioButton_2->y() + this->ui->radioButton_2->height() + 10);
    this->ui->label_9->move(this->ui->radioButton_3->x() - 50,this->ui->radioButton_3->y());
    this->ui->radioButton_4->move(this->ui->radioButton_3->x(),this->ui->radioButton_3->y() + this->ui->radioButton_3->height() + 10);
    this->ui->label_10->move(this->ui->radioButton_4->x() - 50,this->ui->radioButton_4->y());
}

void CExamDlg::getCurIndexMultiChoice()
{
    _beginthreadex(nullptr,0,&CExamDlg::CExamDlg::threadGetCurIndexMultiChoice,this,0,nullptr);
}

unsigned WINAPI CExamDlg::threadGetCurIndexMultiChoice(LPVOID arg)
{
    CExamDlg* thiz = (CExamDlg*)arg;
    std::vector<std::vector<std::string>> ret =  thiz->m_contorller->getCurIndexMultiChoice(thiz->testPaperId,thiz->multiChoiceCurIndex);

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
    emit thiz->startShowMultiChoice(result);
    //_endthreadex(0);
    return 0;
}

void CExamDlg::showSignalChoice(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    //显示题干
    qDebug()<<"["<<ret->at(0).at(0)<<"]";
    this->ui->label_4->setText(ret->at(0).at(0));
    this->ui->verticalLayoutWidget->adjustSize();

    //设置题干自适应
    this->DynemicShowSignalChoice();
    //显示A选项
    this->ui->radioButton->setText(ret->at(0).at(1));

    //显示B选项
    this->ui->radioButton_2->setText(ret->at(0).at(2));

    //显示C选项
    this->ui->radioButton_3->setText(ret->at(0).at(3));

    //显示D选项
    this->ui->radioButton_4->setText(ret->at(0).at(4));

    delete ret;
}

void CExamDlg::getCurIndexSignalChoice()
{
    _beginthreadex(nullptr,0,&CExamDlg::threadGetCurIndexSignalChoice,this,0,nullptr);
}

unsigned WINAPI CExamDlg::threadGetCurIndexSignalChoice(LPVOID arg)
{
    CExamDlg* thiz = (CExamDlg*)arg;
    std::vector<std::vector<std::string>> ret =  thiz->m_contorller->getCurIndexSignalChoice(thiz->testPaperId,thiz->signalChoiceCurIndex);

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
    emit thiz->startShowSignalChoice(result);
    //_endthreadex(0);
    return 0;
}

void CExamDlg::showSHortAnswerBtn(int Count)
{
    for(int i = 0 ; i < Count;i++)
    {
        this->m_shortAnswerChoice.at(i)->setVisible(true);
    }
}

void CExamDlg::showJudgeMenueBtn(int Count)
{
    for(int i = 0 ; i < Count;i++)
    {
        this->m_judgeChoice.at(i)->setVisible(true);
    }
}

void CExamDlg::getJudgeChoiceCount()
{
    _beginthreadex(nullptr,0,&CExamDlg::threadGetJudgeChoiceCount,this,0,nullptr);
}

unsigned WINAPI CExamDlg::threadGetJudgeChoiceCount(LPVOID arg)
{
    CExamDlg* thiz = (CExamDlg*)arg;
    int JudgeCount =  thiz->m_contorller->getJudgeChoiceCount(thiz->testPaperId);
    thiz->judgeCount = JudgeCount;
    //显示对应的按钮数量
    emit thiz->startShowJudgeMenueBtn(thiz->judgeCount);
    //_endthreadex(0);
    return 0;
}

void CExamDlg::getShortAnswerCount()
{
  _beginthreadex(nullptr,0,&CExamDlg::WINAPI threadGetShortAnswerCount,this,0,nullptr);
}

unsigned CExamDlg::WINAPI threadGetShortAnswerCount(LPVOID arg)
{
    CExamDlg* thiz = (CExamDlg*)arg;
    int shortAnswerCount =  thiz->m_contorller->getShortAnswerCount(thiz->testPaperId);
    thiz->shortAnswerCount = shortAnswerCount;
    //显示对应的按钮数量
    emit thiz->startShowShortAnswerBtn(thiz->shortAnswerCount);
    //_endthreadex(0);
    return 0;
}

void CExamDlg::showMultiMenueBtn(int Count)
{
    for(int i = 0 ; i < Count;i++)
    {
        this->m_multiChoice.at(i)->setVisible(true);
    }
}

void CExamDlg::getMultiChoiceCount()
{
    //确保对象的属性已经赋值
    _beginthreadex(nullptr,0,&CExamDlg::threadGetMultiChoiceCount,this,0,nullptr);
}

unsigned WINAPI CExamDlg::threadGetMultiChoiceCount(LPVOID arg)
{
    CExamDlg* thiz = (CExamDlg*)arg;
    int MultiCount =  thiz->m_contorller->getMultiChoiceCount(thiz->testPaperId);
    thiz->multiChoiceCount = MultiCount;
    //显示对应的按钮数量
    emit thiz->startShowMultiMenueBtn(thiz->multiChoiceCount);
    //_endthreadex(0);
    return 0;
}

void CExamDlg::showMenueBtn(int Count)
{
    for(int i = 0 ; i < Count;i++)
    {
        this->m_signalChoice.at(i)->setVisible(true);
    }
}

void CExamDlg::getCurTestPaperId()
{
  HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CExamDlg::threadGetCurTestPaperId,this,0,nullptr);
  WaitForSingleObject(thread,INFINITE);
}

unsigned WINAPI CExamDlg::threadGetCurTestPaperId(LPVOID arg)
{
    CExamDlg* thiz = (CExamDlg*)arg;
    std::vector<std::vector<std::string>> ret =  thiz->m_contorller->getCurTestPaperId(thiz->classId
                                          ,thiz->teacherId,thiz->startTime,thiz->endTime
                                          ,thiz->longTime);
    QString str = QString::fromLocal8Bit(ret.at(0).at(0).c_str());
    thiz->testPaperId = str;
    qDebug()<<"获取到的试卷id"<<thiz->testPaperId;
    //_endthreadex(0);
    return 0;
}

void CExamDlg::getSignalChoiceCount()
{
    //确保对象的属性已经赋值
    _beginthreadex(nullptr,0,&CExamDlg::threadGetSignalChoiceCount,this,0,nullptr);
}

unsigned WINAPI CExamDlg::threadGetSignalChoiceCount(LPVOID arg)
{
    CExamDlg* thiz = (CExamDlg*)arg;
    qDebug()<<"测试："<<thiz->testPaperId;
    int signalCount =  thiz->m_contorller->getSignalChoiceCount(thiz->testPaperId);
    thiz->signalChoiceCount = signalCount;
    qDebug()<<"单选题题数："<<thiz->signalChoiceCount;
    //显示对应的按钮数量
    emit thiz->startShowMenueBtn(signalCount);
    //_endthreadex(0);
    return 0;
}

void CExamDlg::startCountdown(int totalMinutes)
{
    totalSeconds = totalMinutes * 60; // Convert minutes to seconds
    if (timer->isActive()) {
        timer->stop();
    }
    timer->start(1000); // Timer interval is 1 second
}

void CExamDlg::updateCountdown()
{
    if (totalSeconds < 0) {
        timer->stop();
        QMessageBox::information(this, "Countdown", "Time's up!");
        this->totalSeconds = 0;
        return;
    }

    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    QString minuteStr = QString::number(minutes, 10).rightJustified(2, '0');
    QString secondStr = QString::number(seconds, 10).rightJustified(2, '0');

    this->ui->lcdNumber->display(minuteStr);
    this->ui->lcdNumber_2->display(secondStr);
    totalSeconds--;
}

CExamDlg::~CExamDlg()
{
    if(this->timer != nullptr)
    {
        if(this->timer->isActive())
        {
            timer->stop();
        }
        delete this->timer;
        this->timer = nullptr;
    }
    if(this->m_contorller != nullptr)
    {
        delete this->m_contorller;
        this->m_contorller = nullptr;
    }
    CExamDlg::hwnd = nullptr;
    CExamDlg::m_thiz = nullptr;
    ClipCursor(NULL);
    delete ui;
}
