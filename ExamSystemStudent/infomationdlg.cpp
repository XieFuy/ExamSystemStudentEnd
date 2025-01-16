#include "infomationdlg.h"
#include "ui_infomationdlg.h"

CInfoMationDlg::CInfoMationDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CInfoMationDlg)
{
    ui->setupUi(this);
    this->setWindowTitle("考前注意事项");
    this->setWindowIcon(QIcon(":/icons/infomation.png"));

    //如果点击的确定进行生成考试界面
    QObject::connect(this->ui->pushButton,&QPushButton::clicked,[=](){
        if(this->m_examDlg == nullptr)
        {
            this->m_examDlg = new CExamDlg();
            this->m_examDlg->move(40,40);
            this->m_examDlg->classId = this->classId;
            this->m_examDlg->teacherId = this->teacherId;
            this->m_examDlg->startTime = this->startTime;
            this->m_examDlg->endTime = this->endTime;
            this->m_examDlg->longTime = this->longTime;
            this->m_examDlg->show();
            this->hide();
            emit this->m_examDlg->startDoModel();
            QObject::connect(this->m_examDlg,&CExamDlg::rejected,[=](){
                if(this->m_examDlg != nullptr)
                {
                    this->show();
                    delete this->m_examDlg;
                    this->m_examDlg = nullptr;
                    emit this->rejected();
                }
            });
        }
    });
}

CInfoMationDlg::~CInfoMationDlg()
{
    delete ui;
}
