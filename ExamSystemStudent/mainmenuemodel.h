#ifndef CMAINMENUEMODEL_H
#define CMAINMENUEMODEL_H

#include "DBHelper.h"
#include <string>
#include <QString>
#include <QDebug>
#include "clientsocket.h"
#include <stdlib.h>
class CMainMenueModel //主菜单页面模型层
{
public:
    CMainMenueModel();
    ~CMainMenueModel();
public:
    std::vector<std::vector<std::string>> showStudentInfo(char* pAcount);
    std::vector<std::vector<std::string>> showStudentAcountInfo(char* pAcount);
    void changeGender(bool isMan,char* pAcount);
    void changeHeadPicture(char* localFilePath,char* fileName,char* acount);
private:
      HANDLE m_mutex; //因为所有操作都是使用的一个CDBHelper对象，所以要给每一个执行sql的步骤进行上锁
};

#endif // CMAINMENUEMODEL_H
