#include "mainmenuedlg.h"
#include "ui_mainmenuedlg.h"

CMainMenueDlg::CMainMenueDlg(QWidget *parent) : //主菜单界面类
    QDialog(parent),
    ui(new Ui::CMainMenueDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("在线考试系统-学生端");
    this->setWindowIcon(QIcon(":/icons/winIcon.png"));
    this->ui->pushButton_6->setVisible(false);


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


    this->strSignalLabelStyleSheet = "QLabel{border:none;background-color:#E1EFD8;border-bottom:1px solid #646465;}";
    this->strSignalWidgetStyleSheet = "QWidget{border:none;background-color:#E1EFD8;border-bottom:1px solid #646465;}";

    this->strDoubleLabelStyleSheet = "QLabel{border:none;background-color:#FFFFFF;border-bottom:1px solid #646465;}";
    this->strDoubleWidgetStyleSheet = "QWidget{border:none;background-color:#FFFFFF;border-bottom:1px solid #646465;}";

    this->zoreToTen = 0;
    this->TenToTwoty = 0;
    this->twotyToThirty = 0;
    this->thirtyToForty = 0;
    this->fourtyToFifty = 0;
    this->FiftyToSixty = 0;
    this->SixtyToSeventy = 0;
    this->seventyToEighty = 0;
    this->EightToNighty = 0;
    this->nightyToHunder = 0;

    this->m_acount = "";
    this->m_classCount = "";
    this->sortNumberClass = 0;
    this->sortNumberTestPaper = 0;
    this->m_classCurPageIndex = 1;
    this->classIconIndex = 0;
    this->m_testPaperCurPageIndex = 1;
    this->m_testPaperCount = "";
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
        this->getTestPaperData();
        this->getTestPaperTableCount();
    });

    QObject::connect(this->ui->pushButton_5,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(2);
        this->ui->pushButton_5->setStyleSheet("QPushButton{border:1px solid #50b8f7;background-color:#50b8f7;color:#ffffff;border-radius:20;}");
        //其他的都要设置为原样
        this->ui->pushButton_3->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_4->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        this->ui->pushButton_6->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
//        this->ui->pushButton_7->setStyleSheet("QPushButton{border:none;border:1px solid #faa046;color:#faa046;border-radius:20;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        HANDLE thread = INVALID_HANDLE_VALUE;
        this->getStudentScoreCount(thread);
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
    this->initTestPaperInfoUI();
    this->initTestPaperInfoContorl();

    QObject::connect(this,&CMainMenueDlg::startShowClassTable,this,&CMainMenueDlg::showClassTableInfo);
    QObject::connect(this,&CMainMenueDlg::startShowClassIcon,this,&CMainMenueDlg::showClassIconUI);
    QObject::connect(this,&CMainMenueDlg::startGetClassTableInfo,this,&CMainMenueDlg::getClassTableData);
    QObject::connect(this,&CMainMenueDlg::startShowClassTableIndex,&CMainMenueDlg::showClassTableIndex);
    QObject::connect(this,&CMainMenueDlg::startGetClassTableCount,this,&CMainMenueDlg::getClassTableCount);
    QObject::connect(this->ui->pushButton_31,&QPushButton::clicked,this,&CMainMenueDlg::showClassTableNextPage);
    QObject::connect(this->ui->pushButton_30,&QPushButton::clicked,this,&CMainMenueDlg::showClassTableLastPage);
    QObject::connect(this->ui->checkBox_8,&QCheckBox::toggled,this,&CMainMenueDlg::changeClassCurPageCheckBoxStatus);
    QObject::connect(this->ui->pushButton_32,&QPushButton::clicked,this,&CMainMenueDlg::deleteMultiClassInfo);
    QObject::connect(this,&CMainMenueDlg::startShowTestPaperTableInfo,this,&CMainMenueDlg::showTestPaperTableInfo);
    QObject::connect(this,&CMainMenueDlg::startShowTestPaperTableIndex,this,&CMainMenueDlg::showTestPaperTableIndex);
    QObject::connect(this->ui->pushButton_34,&QPushButton::clicked,this,&CMainMenueDlg::showTestPaperTableNextPage);
    QObject::connect(this->ui->pushButton_33,&QPushButton::clicked,this,&CMainMenueDlg::showTestPaperTableLastPage);
    QObject::connect(this,&CMainMenueDlg::startShowStudentScore,this,&CMainMenueDlg::showStudentScoreUI);
    QObject::connect(this,&CMainMenueDlg::startInitStudentScoreContorlUI,this,&CMainMenueDlg::setStudentScoreContorlUI);
    //在这里监听查询完毕总数后发送的消息
    QObject::connect(this,&CMainMenueDlg::startSendStudentScoreCount,[=](int count){
        qDebug()<<"总人数："<<count;
        //进行设置UI样式
        emit this->startInitStudentScoreContorlUI(count);
    });
    QObject::connect(this,&CMainMenueDlg::startGetStudentScoreInfo,this,&CMainMenueDlg::getSubjectTestPaperRelease);
    QObject::connect(this->ui->pushButton_92,&QPushButton::clicked,this,&CMainMenueDlg::writeStudentScoreToExcel);
    QObject::connect(this->ui->pushButton_93,&QPushButton::clicked,[=](){
        if(this->m_studentScoreSumScore.size() == 0)
        {
            std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>(QMessageBox::Warning,"信息提示","当前未选择试卷，不能进行成绩分析！",QMessageBox::Ok);
            box->exec();
            return;
        }
        this->ui->stackedWidget->setCurrentIndex(3);
        this->barWidget = std::make_shared<BarWidget>();
        this->barWidget->setValue(this->zoreToTen,this->TenToTwoty,this->twotyToThirty
                                  ,this->thirtyToForty,this->fourtyToFifty,this->FiftyToSixty
                                  ,this->SixtyToSeventy,this->seventyToEighty,this->EightToNighty
                                  ,this->nightyToHunder);
        this->barWidget->setGeometry(0,0,this->ui->widget_23->width()
                                     ,this->ui->widget_23->height());
        this->barWidget->setParent(this->ui->widget_23);
        this->barWidget->show();
        emit this->barWidget->startShowUI();
    });

    QObject::connect(this->ui->pushButton_46,&QPushButton::clicked,[=](){
        this->ui->stackedWidget->setCurrentIndex(2);
        this->barWidget.reset();
    });
}

typedef struct getStudentScoreCountArg{
    CMainMenueDlg* thiz;
}GetStudentScoreCountArg;

void CMainMenueDlg::getStudentScoreCount(HANDLE& out_handle)
{
    std::shared_ptr<GetStudentScoreCountArg> arg = std::make_shared<GetStudentScoreCountArg>();
    arg->thiz = this;
    std::shared_ptr<GetStudentScoreCountArg>* p = new std::shared_ptr<GetStudentScoreCountArg>(arg);
    out_handle = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadGetStudentScoreCount,p,0,nullptr);
}

unsigned WINAPI  CMainMenueDlg::threadGetStudentScoreCount(LPVOID arg)
{
    std::shared_ptr<GetStudentScoreCountArg>* p = (std::shared_ptr<GetStudentScoreCountArg>*)arg;
    std::shared_ptr<GetStudentScoreCountArg> gInfo = *p;
    int ret =  gInfo->thiz->m_mainMenueContorller->getStudentScoreCount(gInfo->thiz->m_acount);
    //进行发送信号进行传递查询结果
    emit gInfo->thiz->startSendStudentScoreCount(ret);
    delete p;
    return 0;
}

void CMainMenueDlg::setStudentScoreContorlUI(int rowCount)
{
    this->ui->tableWidget_7->horizontalHeader()->hide();
    this->ui->tableWidget_7->verticalHeader()->hide();
    //进行设置每一列的列宽
    this->ui->tableWidget_7->setColumnCount(6);
    int width = this->ui->tableWidget_7->width();
    int heigth = this->ui->tableWidget_7->height();
    this->ui->tableWidget_7->setColumnWidth(0,width / 4);
    this->ui->tableWidget_7->setColumnWidth(1,width / 6);
    this->ui->tableWidget_7->setColumnWidth(2,width / 6);
    this->ui->tableWidget_7->setColumnWidth(3,width / 6);
    this->ui->tableWidget_7->setColumnWidth(4,width / 6);
    this->ui->tableWidget_7->setColumnWidth(5,width / 12);

    //对表行进行清除，并且清除控件容器
    this->ui->tableWidget_7->setRowCount(0);

    for(QLabel* lab : this->m_studentScoreName)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreName.clear();

    for(QLabel* lab : this->m_studentScoreId)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreId.clear();

    for(QLabel* lab : this->m_studentScoreId)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreId.clear();

    for(QLabel* lab : this->m_studentScoreSubject)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreSubject.clear();

    for(QLabel* lab : this->m_studentScoreKeGuanScore)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreKeGuanScore.clear();

    for(QLabel* lab : this->m_studentScoreZhuGuanScore)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreZhuGuanScore.clear();

    for(QLabel* lab : this->m_studentScoreSumScore)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreSumScore.clear();

    //进行设置行
    this->ui->tableWidget_7->setRowCount(rowCount);
    for(int i = 0;i < rowCount ;i++)
    {
        this->ui->tableWidget_7->setRowHeight(i,heigth/ 12);
    }

    //给每一格进行添加控件
    // 学生名称
    for(int i = 0 ; i < rowCount ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_7->setCellWidget(i,0,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentScoreName.push_back(testName);
    }

    //学号
    for(int i = 0 ; i < rowCount ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_7->setCellWidget(i,1,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentScoreId.push_back(testName);
    }

    //科目
    for(int i = 0 ; i < rowCount ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_7->setCellWidget(i,2,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentScoreSubject.push_back(testName);
    }

    //客观题分数
    for(int i = 0 ; i < rowCount;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_7->setCellWidget(i,3,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentScoreKeGuanScore.push_back(testName);
    }

    //主观题分数
    for(int i = 0 ; i < rowCount;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_7->setCellWidget(i,4,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentScoreZhuGuanScore.push_back(testName);
    }

    //总分
    for(int i = 0 ; i < rowCount;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_7->setCellWidget(i,5,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_studentScoreSumScore.push_back(testName);
    }

    //给每一行根据单双设置样式
    for(int i = 0 ; i < rowCount ; i++)
    {
        //同一行的所有控件都进行设置同样的背景颜色
        if(i % 2 == 0)//
        {
            this->m_studentScoreName.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentScoreId.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentScoreSubject.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentScoreKeGuanScore.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentScoreZhuGuanScore.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_studentScoreSumScore.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
        }else
        {
            this->m_studentScoreName.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentScoreId.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentScoreSubject.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentScoreKeGuanScore.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentScoreZhuGuanScore.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_studentScoreSumScore.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
        }
    }

    //发送信号，再进行获取表数据
    emit this->startGetStudentScoreInfo();
}

void CMainMenueDlg::writeStudentScoreToExcel()
{
    int width = this->ui->tableWidget_7->width();
    //弹出文件弹框
    QString filePath = QFileDialog::getSaveFileName(this, "保存文件", "", "所有文件 (*);;文本文件 (*.xlsx)");

    //获取文件路径 检查用户是否选择了文件
    if (!filePath.isEmpty()) {

        // 创建一个 Xlsx 文档
           QXlsx::Document xlsx;

           QXlsx::Format headerFormat;
           headerFormat.setFontBold(true);
           headerFormat.setPatternBackgroundColor(Qt::yellow);

           //设置表头样式 写入表头
           QStringList strHeader;
           strHeader<<"学生姓名"<<"学号"<<"科目"<<"客观总分"<<"主观题总分"<<"总分";
           for (int col = 0; col < 6; ++col) {
               xlsx.write(1, col + 1, strHeader.at(col), headerFormat);
           }

           //导出数据 将二维数据写入 Excel
           for(int row = 1;row < this->m_studentScoreName.size() + 1;row++)
           {
               //写入姓名
               xlsx.write(row + 1, 1, this->m_studentScoreName.at(row - 1)->text());// 将数据写入单元格（行和列从 1 开始）
               //写入学号
               xlsx.write(row + 1, 2, this->m_studentScoreId.at(row - 1)->text());
               //写入科目
               xlsx.write(row + 1, 3, this->m_studentScoreSubject.at(row - 1)->text());
               //写入客观
               xlsx.write(row + 1, 4, this->m_studentScoreKeGuanScore.at(row - 1)->text());
               //写入主观
               xlsx.write(row + 1, 5, this->m_studentScoreZhuGuanScore.at(row - 1)->text());
               //写入总分
               xlsx.write(row + 1, 6, this->m_studentScoreSumScore.at(row - 1)->text());
           }

           // 设置列宽
           xlsx.setColumnWidth(1, 20);  // 设置第 1 列（A 列）的宽度为 15
           xlsx.setColumnWidth(2, 20);  // 设置第 2 列（B 列）的宽度为 10
           xlsx.setColumnWidth(3, 20);  // 设置第 3 列（C 列）的宽度为 20
           xlsx.setColumnWidth(4, 20);
           xlsx.setColumnWidth(5, 20);
           xlsx.setColumnWidth(6, 20);

           // 保存文件
           if (xlsx.saveAs(filePath)) {
               qDebug() << "Excel 文件已成功生成！";
               std::shared_ptr<QMessageBox> box = std::make_shared<QMessageBox>(QMessageBox::Information,"信息提示","数据导出成功！",QMessageBox::Ok);
               box->exec();
           } else {
               qDebug() << "生成 Excel 文件失败！";
           }
    }
}

void CMainMenueDlg::showStudentScoreUI(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return;
    }
    for(int i = 0 ; i < ret->size();i++)
    {
        //进行显示学生姓名
        QString str = ret->at(i).at(0).trimmed();
        this->m_studentScoreName.at(i)->setText(str);

        //显示学生Id
        str = ret->at(i).at(1).trimmed();
        this->m_studentScoreId.at(i)->setText(str);

        //显示科目
        str = ret->at(i).at(2).trimmed();
        this->m_studentScoreSubject.at(i)->setText(str);

        //显示客观分数
        str = ret->at(i).at(3).trimmed();
        this->m_studentScoreKeGuanScore.at(i)->setText(str);

        //显示主观分数
        str = ret->at(i).at(4).trimmed();
        this->m_studentScoreZhuGuanScore.at(i)->setText(str);

        //显示总分
        str = ret->at(i).at(5).trimmed();
        this->m_studentScoreSumScore.at(i)->setText(str);
    }

    //进行统计各个区间总分的人数
    // 遍历每个 QLabel 对象
        for (QLabel* label : this->m_studentScoreSumScore) {
            // 将 QLabel 的文本转换为整数
            bool ok;
            double score = label->text().toDouble(&ok);

            // 如果转换成功，根据分数将其分配到相应的区间
            if (ok) {
                if (score >= 0.0 && score < 10.0) {
                    this->zoreToTen++;
                } else if (score >= 10.0 && score < 20.0) {
                    this->TenToTwoty++;
                } else if (score >= 20.0 && score < 30.0) {
                    this->twotyToThirty++;
                } else if (score >= 30.0 && score < 40.0) {
                    this->thirtyToForty++;
                } else if (score >= 40.0 && score < 50.0) {
                    this->fourtyToFifty++;
                } else if (score >= 50.0 && score < 60.0) {
                    this->FiftyToSixty++;
                } else if (score >= 60.0 && score < 70.0) {
                    this->SixtyToSeventy++;
                } else if (score >= 70.0 && score < 80.0) {
                    this->seventyToEighty++;
                } else if (score >= 80.0 && score < 90.0) {
                    this->EightToNighty++;
                }else if (score >= 90.0 && score <= 100.0) {
                    this->nightyToHunder++;
                }
            }
        }
    delete ret;
}

void CMainMenueDlg::getSubjectTestPaperRelease()
{
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetSubjectTestPaperRelease,this,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetSubjectTestPaperRelease(LPVOID arg)
{
    CMainMenueDlg* thiz = (CMainMenueDlg*)arg;
    std::vector<std::vector<std::string>> ret = thiz->m_mainMenueContorller->getSubjectTestPaperRelease(thiz->m_acount);

    //进行处理返回结果
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
    //进行发送信号回显
    emit thiz->startShowStudentScore(result);
    return 0;
}

void CMainMenueDlg::bindTestPaperOperators()
{
    for(QVector<QWidget*>::iterator pos = this->m_TestPaperOperationsVec.begin(); pos != this->m_TestPaperOperationsVec.end();pos++)
    {
         QList<QPushButton*> ret = (*pos)->findChildren<QPushButton*>();
         for(QPushButton* btn : ret)
         {
             if(btn->text() == "进入考试")
             {
                 //绑定的删除操作的槽函数
                 QObject::connect(btn,&QPushButton::clicked,[=](){
                     //进行遍历是哪一个按钮，并获取对应的行号
                     int row = 0;
                     for(int i = 0 ; i < this->m_TestPaperOperationsVec.size();i++)
                     {
                         QList<QPushButton*> buttons = this->m_TestPaperOperationsVec.at(i)->findChildren<QPushButton*>();
                         for(QPushButton* clickedBtn: buttons)
                         {
                             if(clickedBtn == btn)
                             {
                                 QString classId = this->m_classId.at(row);
                                 QString teacherId = this->m_teacherId.at(row);
                                 QString startTime = this->m_TestPaperStartTimeVec.at(row)->text().trimmed();
                                 QString endTime = this->m_TestPaperEndTimeVec.at(row)->text().trimmed();
                                 QString longTime = this->m_TestPaperLongTimeVec.at(row)->text().trimmed();
                                 QString testPaperName = this->m_TestPaperNameVec.at(row)->text().trimmed();
                                 //进行考前提示
                                 showInfomationDlg(classId,teacherId,startTime,endTime,longTime,testPaperName);
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

typedef struct checkJoinExamArg{
    QString testPaperName;
    QString teacherId;
    QString studentId;
    QString classId;
    CMainMenueDlg* thiz;
    bool ret_out;
}CheckJoinExamArg;

//如果已经参加考试并且提交过后，则返回true,否则返回false
bool CMainMenueDlg::checkJoinExam(QString& classId,QString& teacherId,QString& studentId,QString& testPaperName)
{
    std::shared_ptr<CheckJoinExamArg> arg = std::make_shared<CheckJoinExamArg>();
    arg->testPaperName = testPaperName;
    arg->teacherId = teacherId;
    arg->studentId = studentId;
    arg->classId = classId;
    arg->thiz = this;
    arg->ret_out = false;
    std::shared_ptr<CheckJoinExamArg>* p = new std::shared_ptr<CheckJoinExamArg>(arg);
    HANDLE thread = (HANDLE)_beginthreadex(nullptr,0,&CMainMenueDlg::threadCheckJoinExam,p,0,nullptr);
    WaitForSingleObject(thread,INFINITE);
    delete p;
    qDebug()<<"对象的引用计数：预期：1 实际："<<arg.use_count();
    return arg->ret_out;
}

unsigned WINAPI CMainMenueDlg::threadCheckJoinExam(LPVOID arg)
{
    std::shared_ptr<CheckJoinExamArg>* p = (std::shared_ptr<CheckJoinExamArg>*)arg;
    std::shared_ptr<CheckJoinExamArg> cInfo = *p;
    int ret =  cInfo->thiz->m_mainMenueContorller->checkJoinExam(cInfo->classId,cInfo->teacherId
                                                                 ,cInfo->studentId,cInfo->testPaperName);
    if(ret > 0)
    {
        cInfo->ret_out = true;
    }else
    {
        cInfo->ret_out = false;
    }
    qDebug()<<"返回结果："<<ret;
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::showInfomationDlg(QString classId,QString teacherId,QString startTime,QString endTime,QString longTime,QString testPaperName)
{ 
    //进行检验是否可以进入考试，如果不可以进入考试则进行退出函数以及提示
    if(this->checkJoinExam(classId,teacherId,this->m_acount,testPaperName))
    {
        //进行UI提示
        QMessageBox* box = new QMessageBox(QMessageBox::Information,"提示","您已提交试卷，不可以再进入考试！",QMessageBox::Ok);
        box->exec();
        delete box;
        return;
    }

    if(this->m_infomationdlg == nullptr)  //找到崩溃原因，要先进行显示父窗口，再进行释放类内的对象
    {
       this->m_infomationdlg = new CInfoMationDlg();
       this->m_infomationdlg->move((this->width() - this->m_infomationdlg->width()) / 2, (this->height() - this->m_infomationdlg->height()) / 2);
       this->m_infomationdlg->classId = classId;
       this->m_infomationdlg->teacherId = teacherId;
       this->m_infomationdlg->startTime = startTime;
       this->m_infomationdlg->endTime = endTime;
       this->m_infomationdlg->longTime = longTime;
       this->m_infomationdlg->testPaperName = testPaperName;
       this->m_infomationdlg->studentId =  this->m_acount;
       this->m_infomationdlg->studentName = this->ui->label_3->text().trimmed();
       this->m_infomationdlg->show();
       this->hide();

       //监听如果执行的是执行返回的话，不进入考试则返回到主界面
        QObject::connect(this->m_infomationdlg,&CInfoMationDlg::rejected,[=](){
           if(this->m_infomationdlg != nullptr)
           {
               this->show();
               delete this->m_infomationdlg;
               this->m_infomationdlg = nullptr;
           }
        });
    }
}

void CMainMenueDlg::showTestPaperTableNextPage()
{
    if(this->m_testPaperCount == "0") //如果查询的结果集为空则不进行操作
    {
        return;
    }

    if(QString::number(this->m_testPaperCurPageIndex) == this->m_testPaperCount)
    {
        return;
    }
    //清除当前表中的记录
    this->clearTestPaperTableUI();

    //给当前页自增，并且不能超过总页
    if(QString::number(this->m_testPaperCurPageIndex) != this->m_testPaperCount)
    {
        this->m_testPaperCurPageIndex += 1;
    }

    //清除选中项
//    emit this->ui->checkBox_8->toggled(false);
//    this->ui->checkBox_8->setChecked(false);
    this->getTestPaperData();
    this->getTestPaperTableCount();
}

void CMainMenueDlg::showTestPaperTableLastPage()
{
    if(this->m_testPaperCount == "0")
    {
        return;
    }
    //防止恶意刷新
    if(this->m_testPaperCurPageIndex <= 1)
    {
        return ;
    }
    //清除当前表中的记录
    this->clearTestPaperTableUI();
    //给当前页递减，并且不能低于1
    if(this->m_testPaperCurPageIndex > 1)
    {
       this->m_testPaperCurPageIndex -= 1;
    }
//    emit this->ui->checkBox_8->toggled(false);
//    this->ui->checkBox_8->setChecked(false);
    this->getTestPaperData();
    this->getTestPaperTableCount();
}

void CMainMenueDlg::showTestPaperTableInfo(QVector<QVector<QString>>* ret)
{
    if(ret == nullptr)
    {
        return ;
    }
    //进行UI显示
    this->clearTestPaperTableUI();
    this->m_classId.clear();
    this->m_teacherId.clear();
   //将数据进行插入到表格中
   for(int i = 0 ; i < ret->size(); i++)
   {
       //显示序号
       QList<QCheckBox*> buttons = this->m_TestPaperCheckVec.at(i)->findChildren<QCheckBox*>();
       for (QCheckBox *button : buttons) {
           button->setVisible(true);
       }

       //显示试卷名称
       QString str = ret->at(i).at(0);
       this->m_TestPaperNameVec.at(i)->setText(str);

       //显示开始时间
       str = ret->at(i).at(1);
       this->m_TestPaperStartTimeVec.at(i)->setText(str);

       //显示结束时间
       str = ret->at(i).at(2);
       this->m_TestPaperEndTimeVec.at(i)->setText(str);

       //显示总时长
       str = ret->at(i).at(3);
       this->m_TestPaperLongTimeVec.at(i)->setText(str);

       //显示出题人
       str = ret->at(i).at(4);
       this->m_TestPaperCreatorVec.at(i)->setText(str);

       //存储当前页的课程id
       str = ret->at(i).at(5);
       this->m_teacherId.push_back(str);

       //存储当前页的职工id
       str = ret->at(i).at(6);
       this->m_classId.push_back(str);

       //显示操作按钮
       QList<QPushButton*> optButton = this->m_TestPaperOperationsVec.at(i)->findChildren<QPushButton*>();
       for (QPushButton *button : optButton) {
           button->setVisible(true);
       }
   }
   if(ret != nullptr)
   {
       delete ret;
   }
   qDebug()<<"学生管理UI显示完成!";
}

void CMainMenueDlg::clearTestPaperTableUI()
{
    //隐藏序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QCheckBox*> buttons = this->m_TestPaperCheckVec.at(i)->findChildren<QCheckBox*>();
        for (QCheckBox *button : buttons) {
            button->setVisible(false);
        }
    }

    //清除试卷名称
    for (QLabel *button : this->m_TestPaperNameVec) {
        button->setText("");
    }

    //清除开始时间
    for (QLabel *button : this->m_TestPaperStartTimeVec) {
        button->setText("");
    }

    //清除结束时间
    for (QLabel *button : this->m_TestPaperEndTimeVec) {
        button->setText("");
    }

    //清除总时长
    for (QLabel *button : this->m_TestPaperLongTimeVec) {
        button->setText("");
    }

    //清除出题人
    for (QLabel *button : this->m_TestPaperCreatorVec) {
        button->setText("");
    }

    //清除操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QList<QPushButton*> optButton = this->m_TestPaperOperationsVec.at(i)->findChildren<QPushButton*>();
        for (QPushButton *button : optButton) {
            button->setVisible(false);
        }
    }
}

//TODO:明天接着这里继续
typedef struct getTestPaperDataArg{
    QString acount;
    int curIndex;
    CMainMenueDlg* thiz;
}GetTestPaperDataArg;

void CMainMenueDlg::getTestPaperData()
{
    std::shared_ptr<GetTestPaperDataArg> arg = std::make_shared<GetTestPaperDataArg>();
    arg->acount = this->m_acount;
    arg->thiz = this;
    arg->curIndex = this->m_testPaperCurPageIndex;
    std::shared_ptr<GetTestPaperDataArg>* ptr = new std::shared_ptr<GetTestPaperDataArg>(arg);
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetTestPaperDataEntry,ptr,0,nullptr);
}


unsigned WINAPI CMainMenueDlg::threadGetTestPaperDataEntry(LPVOID arg)
{
    std::shared_ptr<GetTestPaperDataArg>* temp = static_cast<std::shared_ptr<GetTestPaperDataArg>*>(arg);
    std::shared_ptr<GetTestPaperDataArg> gInfo = *temp;
    //测试打印对象的引用计数
    qDebug()<<"use_count: "<<gInfo.use_count();
    std::vector<std::vector<std::string>> ret = gInfo->thiz->m_mainMenueContorller->getTestPaperData(gInfo->acount,gInfo->curIndex);
    QVector<QVector<QString>>* result = new QVector<QVector<QString>>();
    for(int i = 0 ; i < ret.size();i++)
    {
        QVector<QString> temp;
        for(int j = 0 ; j < ret.at(i).size();j++)
        {
            //添加分钟
            QString str = QString::fromLocal8Bit(ret.at(i).at(j).c_str());
            if(j == 3)
            {
                str += "分钟";
            }
            temp.push_back(str);
        }
        result->push_back(temp);
    }
    //发送回显信号
    emit  gInfo->thiz->startShowTestPaperTableInfo(result);
    delete temp;
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::showTestPaperTableIndex()
{
    QString first = QString::number(this->m_testPaperCurPageIndex);
    first += "/";
    first += this->m_testPaperCount;
    this->ui->label_64->setText(first);
}

typedef struct  getTestPaperTableCountArg{
    QString acount;
    CMainMenueDlg* thiz;
}GetTestPaperTableCountArg;

void CMainMenueDlg::getTestPaperTableCount()
{
    std::shared_ptr<GetTestPaperTableCountArg> arg = std::make_shared<GetTestPaperTableCountArg>();
    arg->acount = this->m_acount;
    arg->thiz = this;
    std::shared_ptr<GetTestPaperTableCountArg>* temp = new std::shared_ptr<GetTestPaperTableCountArg>(arg);
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadGetTestPaperTableCountEntry,temp,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadGetTestPaperTableCountEntry(LPVOID arg)
{
   std::shared_ptr<GetTestPaperTableCountArg>* temp = (std::shared_ptr<GetTestPaperTableCountArg>*)arg;
   std::shared_ptr<GetTestPaperTableCountArg> gInfo = *temp;
   int ret =  gInfo->thiz->m_mainMenueContorller->getTestPaperTableCount(gInfo->acount);
   gInfo->thiz->m_testPaperCount = QString::number(ret);
   //进行发送信号，进行显示总页数
   emit gInfo->thiz->startShowTestPaperTableIndex();
   delete temp;
   //_endthreadex(0);
   return 0;
}

void CMainMenueDlg::initTestPaperInfoContorl()
{
    //初始化序号
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QHBoxLayout* layout = new QHBoxLayout();
        widget->setLayout(layout);
        QCheckBox* checkBox = new QCheckBox();
        checkBox->setText(QString::number(++this->sortNumberTestPaper));
        checkBox->setFont(QFont("黑体"));
        checkBox->setStyleSheet("QCheckBox{border:none;}");
        checkBox->setVisible(false);
        layout->addWidget(checkBox);
        checkBox->setParent(widget);
        this->ui->tableWidget_3->setCellWidget(i,0,widget);
        this->m_TestPaperCheckVec.push_back(widget);
    }

    //初始化试卷名称
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_3->setCellWidget(i,1,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_TestPaperNameVec.push_back(testName);
    }

    //初始化开始考试时间
    for(int i = 0 ; i < 8 ; i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_3->setCellWidget(i,2,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_TestPaperStartTimeVec.push_back(testName);
    }

    //初始化结束考试时间
    for(int i = 0 ; i < 8;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_3->setCellWidget(i,3,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_TestPaperEndTimeVec.push_back(testName);
    }

    //初始化总时长
    for(int i = 0 ; i < 8 ;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_3->setCellWidget(i,4,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_TestPaperLongTimeVec.push_back(testName);
    }

    //初始化出题人
    for(int i = 0 ; i < 8 ;i++)
    {
        QLabel* testName = new QLabel();
        testName->setText("");
        testName->setFont(QFont("黑体",12));
        this->ui->tableWidget_3->setCellWidget(i,5,testName);
        testName->setAlignment(Qt::AlignCenter);
        this->m_TestPaperCreatorVec.push_back(testName);
    }

    //初始化操作
    for(int i = 0 ; i < 8 ; i++)
    {
        QWidget* widget = new QWidget();
        QPushButton* deleteBtn = new QPushButton("进入考试");
        deleteBtn->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
        deleteBtn->setParent(widget);
//        QPushButton* release = new QPushButton("查看详情");
//        release->setStyleSheet("QPushButton{border:none; border:1px solid #faa046; color:#faa046;border-radius:5;}QPushButton:hover{border:1px solid #50b8f7;color:#50b8f7;}");
//        release->setParent(widget);
        deleteBtn->setGeometry(50,20,150,40);
//        release->setGeometry(deleteBtn->width() + 30,deleteBtn->y(),150,40);
        deleteBtn->setFont(QFont("黑体",12));
//        release->setFont(QFont("黑体",12));
        deleteBtn->setVisible(false);
//        release->setVisible(false);
        this->ui->tableWidget_3->setCellWidget(i,6,widget);
        this->m_TestPaperOperationsVec.push_back(widget);
    }

    //进行初始化样式表
    for(int i = 0 ; i < 8 ; i++)
    {
        if(i % 2 == 0)
        {
            this->m_TestPaperCheckVec.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
            this->m_TestPaperNameVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_TestPaperStartTimeVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_TestPaperEndTimeVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_TestPaperLongTimeVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_TestPaperCreatorVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_TestPaperOperationsVec.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
        }else
        {
            this->m_TestPaperCheckVec.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
            this->m_TestPaperNameVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_TestPaperStartTimeVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_TestPaperEndTimeVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_TestPaperLongTimeVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_TestPaperCreatorVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_TestPaperOperationsVec.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
        }
    }
    this->bindTestPaperOperators();
}

void CMainMenueDlg::initTestPaperInfoUI()
{
    this->ui->tableWidget_3->setRowCount(8);
    this->ui->tableWidget_3->setColumnCount(7);
    this->ui->tableWidget_3->horizontalHeader()->hide();
    this->ui->tableWidget_3->verticalHeader()->hide();

    //设置列宽
    int width = this->ui->tableWidget_3->width();
    int heigth = this->ui->tableWidget_3->height();
    this->ui->tableWidget_3->setColumnWidth(0,width / 25);
    this->ui->tableWidget_3->setColumnWidth(1,width / 5);
    this->ui->tableWidget_3->setColumnWidth(2,width / 5);
    this->ui->tableWidget_3->setColumnWidth(3,width / 5);
    this->ui->tableWidget_3->setColumnWidth(4,width / 13);
    this->ui->tableWidget_3->setColumnWidth(5,width / 10);
    this->ui->tableWidget_3->setColumnWidth(6,width / 6);

    this->ui->tableWidget_3->setRowHeight(0,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(1,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(2,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(3,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(4,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(5,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(6,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(7,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(8,heigth/ 8);
    this->ui->tableWidget_3->setRowHeight(9,heigth/ 8);
}

typedef struct deleteMultiClassInfoArg
{
    QString acount;
    QList<QString>* createTimeLst;
    QList<QString>* classNameLst;
    CMainMenueDlg* thiz;
}DeleteMultiClassInfoArg;

void CMainMenueDlg::deleteMultiClassInfo()
{
    DeleteMultiClassInfoArg*  arg = new DeleteMultiClassInfoArg();
    arg->thiz = this;
    arg->acount = this->m_acount;

    QList<QString>* createTimeLst = new QList<QString>();
    arg->classNameLst = new QList<QString>();
    for(int i = 0 ; i < this->m_classCheckVec.size();i++)
    {
        QList<QCheckBox*> ret =  this->m_classCheckVec.at(i)->findChildren<QCheckBox*>();
        for(QCheckBox* check :ret)
        {
            if(check->isChecked())
            {
                QString createTime = this->m_classCreateTimeVec.at(i)->text().trimmed();
                if(createTime != "")
                {
                    createTimeLst->push_back(createTime);
                }
                QString className = this->m_classNameVec.at(i)->text().trimmed();
                if(className != "")
                {
                    arg->classNameLst->push_back(className);
                }
            }
        }
    }
    arg->createTimeLst = createTimeLst;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteMultiClassInfo,arg,0,nullptr);
    //将复选框进行设置为未选中
    for(int i = 0 ; i < this->m_classCheckVec.size();i++)
    {
        QList<QCheckBox*> ret =  this->m_classCheckVec.at(i)->findChildren<QCheckBox*>();
        for(QCheckBox* check : ret)
        {
            check->setChecked(false);
        }
    }
    this->ui->checkBox_8->setChecked(false);
}

unsigned WINAPI CMainMenueDlg::threadDeleteMultiClassInfo(LPVOID arg)
{
    DeleteMultiClassInfoArg* dInfo = (DeleteMultiClassInfoArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteMultiClassInfo(dInfo->acount,*dInfo->createTimeLst,*dInfo->classNameLst);
    delete dInfo->createTimeLst;
    delete dInfo->classNameLst;
    delete dInfo;

    //批量操作后需要将下表进行设置为1
    dInfo->thiz->m_classCurPageIndex = 1;
    emit dInfo->thiz->startGetClassTableInfo();
    dInfo->thiz->getClassTableCount();
    //_endthreadex(0);
    return 0;
}

typedef struct deleteClassInfoByDateTimeArg
{
    CMainMenueDlg* thiz;
    QString acount;
    QString createTime;
    QString className;
}DeleteClassInfoByDateTimeArg;

void CMainMenueDlg::deleteClassInfoByDateTime(int row)
{
    //获取到同一行的创建时间
    QString createTime = this->m_classCreateTimeVec.at(row)->text().trimmed();
    qDebug()<<"createTime: "<<createTime;

    QString className = this->m_classNameVec.at(row)->text().trimmed();

    DeleteClassInfoByDateTimeArg* arg = new DeleteClassInfoByDateTimeArg();
    arg->thiz = this;
    arg->acount = this->m_acount;
    arg->createTime = createTime;
    arg->className = className;
    _beginthreadex(nullptr,0,&CMainMenueDlg::threadDeleteClassInfoByDateTimeEntry,arg,0,nullptr);
}

unsigned WINAPI CMainMenueDlg::threadDeleteClassInfoByDateTimeEntry(LPVOID arg)
{
    DeleteClassInfoByDateTimeArg* dInfo = (DeleteClassInfoByDateTimeArg*)arg;
    dInfo->thiz->m_mainMenueContorller->deleteClassInfoByDateTime(dInfo->acount,dInfo->createTime,dInfo->className);
    //重新显示和请求数据
    emit dInfo->thiz->startGetClassTableInfo();
    dInfo->thiz->getClassTableCount();
    delete dInfo;
    //_endthreadex(0);
    return 0;
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
    //_endthreadex(0);
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
                                 this->deleteClassInfoByDateTime(row);
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

void CMainMenueDlg::changeClassCurPageCheckBoxStatus(bool status)
{
    for(int i = 0 ; i < this->m_classCheckVec.size();i++)
    {
       QList<QCheckBox*> ret =  this->m_classCheckVec.at(i)->findChildren<QCheckBox*>();
       for(QCheckBox* check : ret)
       {
          check->setChecked(status);
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
        checkBox->setStyleSheet("QCheckBox{border:none;margin-left:25px;}");
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

    //进行设置样式表
    for(int i = 0 ; i < 8; i++)
    {
        if(i % 2 == 0)
        {
            this->m_classCheckVec.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
            this->m_classIconVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_classNameVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_classCreateTimeVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_classCreatorVec.at(i)->setStyleSheet(strSignalLabelStyleSheet);
            this->m_classOperationsVec.at(i)->setStyleSheet(strSignalWidgetStyleSheet);
        }else
        {
            this->m_classCheckVec.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
            this->m_classIconVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_classNameVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_classCreateTimeVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_classCreatorVec.at(i)->setStyleSheet(strDoubleLabelStyleSheet);
            this->m_classOperationsVec.at(i)->setStyleSheet(strDoubleWidgetStyleSheet);
        }
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
    //_endthreadex(0);
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
    std::vector<std::vector<std::string>>* result  = new std::vector<std::vector<std::string>>();
    for(int i = 0 ; i < ret.size() ; i++)
    {
        std::vector<std::string> temp;
        for(int j = 0 ; j < ret.at(i).size();j++)
        {
            temp.push_back(ret.at(i).at(j));
        }
        result->push_back(temp);
    }
    emit tInfo->thiz->startShowStudentAcountInfo(result);
    delete tInfo;
    //_endthreadex(0);
    return 0;
}

void CMainMenueDlg::showStudentAcountInfo(std::vector<std::vector<std::string>>* ret)
{
    if(ret == nullptr || ret->size() == 0)
    {
        return;
    }
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
    if(ret != nullptr)
    {
        delete ret;
    }
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
    //_endthreadex(0);
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

    for(QWidget* widget : this->m_TestPaperCheckVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_TestPaperCheckVec.clear();

    for(QLabel* widget : this->m_TestPaperNameVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_TestPaperNameVec.clear();

    for(QLabel* widget : this->m_TestPaperStartTimeVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_TestPaperStartTimeVec.clear();

    for(QLabel* widget : this->m_TestPaperEndTimeVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_TestPaperEndTimeVec.clear();

    for(QLabel* widget : this->m_TestPaperLongTimeVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this->m_TestPaperLongTimeVec.clear();

    for(QLabel* widget : this-> m_TestPaperCreatorVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
    this-> m_TestPaperCreatorVec.clear();

    for(QWidget* widget :  this->m_TestPaperOperationsVec)
    {
        if(widget != nullptr)
        {
            delete widget;
        }
    }
     this->m_TestPaperOperationsVec.clear();


    for(QLabel* lab : this->m_studentScoreName)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreName.clear();

    for(QLabel* lab : this->m_studentScoreId)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreId.clear();

    for(QLabel* lab : this->m_studentScoreId)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreId.clear();

    for(QLabel* lab : this->m_studentScoreSubject)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreSubject.clear();

    for(QLabel* lab : this->m_studentScoreKeGuanScore)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreKeGuanScore.clear();

    for(QLabel* lab : this->m_studentScoreZhuGuanScore)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreZhuGuanScore.clear();

    for(QLabel* lab : this->m_studentScoreSumScore)
    {
        if(lab != nullptr)
        {
            delete lab;
        }
    }
    this->m_studentScoreSumScore.clear();
    //如果关闭界面，接收头像信息的线程还在执行的话就等待接收后结束线程
    WaitForSingleObject(this->m_recvHeadThead,INFINITE); //找到退出崩溃的原因，因为关闭界面的时候，接收头像线程还在执行，但是UI已经释放导致异常
    delete ui;
}
