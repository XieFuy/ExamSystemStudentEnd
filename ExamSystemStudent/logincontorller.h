#ifndef CLOGINCONTORLLER_H
#define CLOGINCONTORLLER_H
#include <QString>
#include "loginmodel.h"

class CLoginContorller //登录界面的控制层
{
public:
    CLoginContorller();
    ~CLoginContorller();
    bool login(QString acount,QString password);
    void initStudentDatabase(); //初始化教师数据库
    void initStudentTable();//初始化教师表
private:
    CLoginModel* m_loginModel = nullptr;
};

#endif // CLOGINCONTORLLER_H
