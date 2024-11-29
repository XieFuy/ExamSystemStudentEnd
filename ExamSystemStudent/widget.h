#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QRegularExpression>
#include "logincontorller.h"
#include <QMessageBox>
#include "registerdlg.h"
#include "mainmenuedlg.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
signals:
    void initStudentDatabase(); //创建学生数据库(跟ExamSystem同数据库)
    void initStudentTable(); //创建学生表
public slots:
    void onAccountChange(QString str);//账号输入改变
    void onPasswordChange(QString str);//密码输入改变
private:
    void login(); //登录函数
    void initRegisterDlg();//初始化注册界面
private:
    QRegularExpression reAacount;
    QRegularExpression rePassword;
    bool m_isAcountOk;
    bool m_isPasswordOk;
    CLoginContorller* m_loginContorller = nullptr;
    RegisterDlg* m_registerDlg = nullptr; //注册界面
    CMainMenueDlg* m_mainMenueDlg = nullptr; //主菜单界面
private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
