#ifndef CLOGINMODEL_H
#define CLOGINMODEL_H
#include <QString>
//#include "clientsocket.h"
#include "DBHelper.h"
#include <string>
#include <QDebug>
class CLoginModel //登录模型层
{
public:
    CLoginModel();
    ~CLoginModel();
     bool login(char* acount,char* password,int acountSize,int passwordSize);
     void initStudentDatabase();
     void initStudentTable();
private:
};

#endif // CLOGINMODEL_H
