#ifndef CMAINMENUECONTORLLER_H
#define CMAINMENUECONTORLLER_H

#include "mainmenuemodel.h"
#include<vector>
#include<string>
class CMainMenueContorller  //主菜单页面的控制层
{
public:
    CMainMenueContorller();
    ~CMainMenueContorller();
public :
    std::vector<std::vector<std::string>> showStudentInfo(QString acount);
    std::vector<std::vector<std::string>> showStudentAcountInfo(QString acount);
    void changeGender(bool isMan,QString pAcount);
    void changeHeadPicture(QString LocalFilePath,QString acount);
    bool initClassTableDatabase();
    std::vector<std::vector<std::string>> getClassTableData(QString acount,int curPageIndex);
    int getClassTableCount(QString acount);
    bool deleteClassInfoByDateTime(QString acount,QString createTime,QString className);
    bool deleteMultiClassInfo(QString acount,QList<QString>& createTimeLst,QList<QString>& classNameLst);
    static unsigned threadDeleteMultiClassInfo(LPVOID arg);
 private:
    CMainMenueModel* m_mainMenueModel = nullptr;
};

#endif // CMAINMENUECONTORLLER_H
