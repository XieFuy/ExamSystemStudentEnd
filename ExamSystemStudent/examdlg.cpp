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
    this->judgeChoiceCurIndex = 1;
    this->signalChoiceCurIndex = 1;
    this->multiChoiceCurIndex = 1;
    this->shortAnswerCurIndex = 1;
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(0);
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getSignalChoiceCount();
        this->getCurIndexSignalChoice();
    });

    QObject::connect(this->ui->pushButton_2,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(1);
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getMultiChoiceCount();
        this->getCurIndexMultiChoice();
    });

    QObject::connect(this->ui->pushButton_3,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(2);
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getJudgeChoiceCount();
        this->getCurIndexJudegChoice();
    });

    QObject::connect(this->ui->pushButton_4,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(3);
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;color:#FFFFFF;  background-color:#f7115b;}");
        this->ui->pushButton->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_2->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;background-color:#0082EB;color:#FFFFFF;}QPushButton:hover{background-color:#2998F5;}");
        this->getShortAnswerCount();
        this->getCurIndexShortAnswerChoice();
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
        this->ui->label->setText(this->studentName);
        this->ui->label_2->setText(this->studentId);
        qDebug()<<"时长："<<this->longTime;
        QString time = this->longTime;
        time.remove(time.length() - 2 ,2);
        qDebug()<<"转换："<<time;
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
    // Example: Start countdown for 5 minutes (300 seconds)

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
    _endthreadex(0);
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
    _endthreadex(0);
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
    _endthreadex(0);
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
    _endthreadex(0);
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
