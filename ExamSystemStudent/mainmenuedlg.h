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
    void startShowClassTable(QVector<QVector<QString>>* ret);
    void startShowClassIcon(QImage* image);
    void startGetClassTableInfo();
    void startShowClassTableIndex();
    void startGetClassTableCount();
    void startShowTestPaperTableInfo(QVector<QVector<QString>>* ret);
    void startShowTestPaperTableIndex();
private:
//    CExitLoginDlg* m_exitLoginDlg = nullptr;
    CMainMenueContorller* m_mainMenueContorller = nullptr; //主菜单页面控制层
    QString m_acount; // 存储当前正在登录的用户账号
    std::string m_headPath; //用于存储用户登录的请求头像路径
    CNameChangeDlg* m_nameChangeDlg = nullptr; //修改姓名信息对话框
    CPhoneNumberChangeDlg* m_phoneNumChangeDlg = nullptr;//修改电话对话框
    HANDLE m_recvHeadThead; //接收头像信息的线程
    CJoinClassDlg* m_joinClassdlg = nullptr;
    int sortNumberClass;
    QVector<QWidget*> m_classCheckVec ;
    QVector<QWidget*> m_classIconVec;
    QVector<QLabel*> m_classNameVec;
    QVector<QLabel*> m_classCreateTimeVec;
    QVector<QLabel*> m_classCreatorVec;
    QVector<QWidget*> m_classOperationsVec;
    int m_classCurPageIndex;
    int classIconIndex;
    std::string m_ClassIconPath;
    HANDLE m_Event;
    HANDLE m_Event_2;
    QString m_classCount;

    //考试管理部分
    int sortNumberTestPaper;
    QVector<QWidget*> m_TestPaperCheckVec;
    QVector<QLabel*> m_TestPaperNameVec;
    QVector<QLabel*> m_TestPaperStartTimeVec;
    QVector<QLabel*> m_TestPaperEndTimeVec;
    QVector<QLabel*> m_TestPaperLongTimeVec;
    QVector<QWidget*> m_TestPaperOperationsVec;
    int m_testPaperCurPageIndex;
    QString m_testPaperCount;
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

    //初始化课程管理表UI
    void initJoinClassTableUI(); //初始化加入课程表的UI

    //初始化课程表控件
    void initJoinClassTableContorl();

    //绑定课程表的按钮操作
    void bindClassOperators();

    //初始化课程数据库表
    void initClassTableDatabase();
    static unsigned WINAPI threadInitClassTableDatabaseEntry(LPVOID arg);

    //获取当前页的加入课程数据
    void getClassTableData();
    static unsigned WINAPI threadGetClassTableDataEntry(LPVOID arg);

    //UI显示课程表信息(更新UI)
    void showClassTableInfo(QVector<QVector<QString>>* ret);

    void clearClassTableControl(); //清除课程表UI

    static unsigned WINAPI showClassIcon(LPVOID arg);

    void showClassIconUI(QImage* image);

    void getClassTableCount();//进行获取课程表所有符合条件的总页数
    static unsigned WINAPI threadGetClassTableCountEntry(LPVOID arg);

    void showClassTableIndex();

    //拿取课程表的下一页数据
    void showClassTableNextPage(); //显示课程表的下一页

    //拿到课程表的上一页数据
    void showClassTableLastPage();//显示课程表的上一页数据

    //删除课程表单条记录
    void deleteClassInfoByDateTime(int row);//删除课程表的单条记录
    static unsigned WINAPI threadDeleteClassInfoByDateTimeEntry(LPVOID arg);

    //将课程表当前页的所有选项进行设置状态
    void changeClassCurPageCheckBoxStatus(bool status);

    //实现课程表的批量删除
    void deleteMultiClassInfo();
    static unsigned WINAPI threadDeleteMultiClassInfo(LPVOID arg);

    //初始化考试管理信息表Ui
    void initTestPaperInfoUI();

    //初始化考试管理信息表Ui控件
    void initTestPaperInfoContorl();


    void getTestPaperData();
    static unsigned WINAPI threadGetTestPaperDataEntry(LPVOID arg);

    //显示考试发布信息
    void showTestPaperTableInfo(QVector<QVector<QString>>* ret);

    //清除考试信息Ui
    void clearTestPaperTableUI();

    void getTestPaperTableCount();//进行获取课程表所有符合条件的总页数
    static unsigned WINAPI threadGetTestPaperTableCountEntry(LPVOID arg);

    void showTestPaperTableIndex();

    //拿取考试发布表的下一页数据
    void showTestPaperTableNextPage(); //显示课程表的下一页

    //拿到课程表的上一页数据
    void showTestPaperTableLastPage();//显示课程表的上一页数据
private:
    Ui::CMainMenueDlg *ui;
};

#endif // MAINMENUEDLG_H
