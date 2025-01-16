#include "examdlg.h"
#include "ui_examdlg.h"

CExamDlg::CExamDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CExamDlg)
{
    ui->setupUi(this);
    this->m_contorller = new CExamContorller();
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
    QObject::connect(this->ui->pushButton_5,&QPushButton::clicked,[=](){
      emit this->rejected();
    });

    this->timer = new QTimer();
    this->totalSeconds = 0;
    this->signalChoiceCount = 0;
    this->multiChoiceCount = 0;
    this->judgeCount = 0;
    this->shortAnswerCount = 0;
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(0);
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getSignalChoiceCount();
    });

    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(1);
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getMultiChoiceCount();
//        this->getCurIndexMultiChoice();
    });

    QObject::connect(this->ui->pushButton_3,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(2);
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getJudgeChoiceCount();
//        this->getCurIndexJudegChoice();
    });

    QObject::connect(this->ui->pushButton_4,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(3);
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getShortAnswerCount();
//        this->getCurIndexShortAnswerChoice();
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
        emit this->ui->pushButton->clicked();
    });

    QObject::connect(this,&CExamDlg::startShowMenueBtn,this,&CExamDlg::showMenueBtn);
    QObject::connect(this,&CExamDlg::startShowMultiMenueBtn,this,&CExamDlg::showMultiMenueBtn);
    QObject::connect(this,&CExamDlg::startShowJudgeMenueBtn,this,&CExamDlg::showJudgeMenueBtn);
    QObject::connect(this,&CExamDlg::startShowShortAnswerBtn,this,&CExamDlg::showSHortAnswerBtn);
    // Example: Start countdown for 5 minutes (300 seconds)
    startCountdown(120);
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
    _endthreadex(0);
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
    _endthreadex(0);
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
    _endthreadex(0);
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
    _endthreadex(0);
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
    _endthreadex(0);
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
    delete ui;
}
