#ifndef MAINMENUEDLG_H
#define MAINMENUEDLG_H

#include <QDialog>
#include <QIcon>
//#include "exitlogindlg.h"
#include <QDebug>
#include <QTreeWidgetItem>
#include <QList>
#include "mainmenuecontorller.h"
#include <vector>
#include <string>
#include <iostream>
#include "clientsocket.h"
#include "namechangedlg.h"
#include "phonenumberchangedlg.h"
#include <QFileDialog>
#include <QCheckBox>
#include <QLabel>
#include <QHBoxLayout>
#include "joinclassdlg.h"

namespace Ui {
class CMainMenueDlg;  //主菜单管理页面
}

class CMainMenueDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CMainMenueDlg(QWidget *parent = nullptr);
    ~CMainMenueDlg();
public:
//    bool eventFilter (QObject* obj, QEvent* e) override;
    void setLoginedAcount(QString acount); //设置已经登录的账号
signals:
    void startShowStudentInfo(QString acount);
    void startShowHeadImage(QImage image);
    void startShowStudentAcountInfo(std::vector<std::vector<std::string>>* ret);
private:
//    CExitLoginDlg* m_exitLoginDlg = nullptr;
    CMainMenueContorller* m_mainMenueContorller = nullptr; //主菜单页面控制层
    QString m_acount; // 存储当前正在登录的用户账号
    std::string m_headPath; //用于存储用户登录的请求头像路径
    CNameChangeDlg* m_nameChangeDlg = nullptr; //修改姓名信息对话框
    CPhoneNumberChangeDlg* m_phoneNumChangeDlg = nullptr;//修改电话对话框
    HANDLE m_recvHeadThead; //接收头像信息的线程
    CJoinClassDlg* m_joinClassdlg = nullptr;
private: 
    void  showStudentInfo(QString acount); //显示主页的职工个人姓名和头像

    static unsigned WINAPI threadShowHeadEntry(LPVOID arg); //进行与服务器进行网络通信获取头像数据的线程函数
    void threadShowHead(); //执行向服务器的网络请求头像数据线程函数
    void showHeadImageUI(QImage image); //从服务器中请求到数据后进行UI更新

    void showStudentAcountInfo(std::vector<std::vector<std::string>>* ret);//显示职工账号管理信息
    void getStudentAcountInfoData();//获取职工账号信息数据
    static unsigned WINAPI threadGetStudentAcountInfoDataEntry(LPVOID arg);

    void changeGender(bool isChecked); //进行更改性别
    static unsigned WINAPI threadChangeGenderEntry(LPVOID arg);

    void headPictureChange();//进行头像更换


private:
    Ui::CMainMenueDlg *ui;
};

#endif // MAINMENUEDLG_H
