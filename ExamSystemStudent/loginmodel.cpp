#include "loginmodel.h"

CLoginModel::CLoginModel(){}

CLoginModel::~CLoginModel(){}

//进行登录等数据库操作部分不一定需要网络模块进行操作
bool CLoginModel::login(char* acount,char* password,int acountSize,int passwordSize)
{
    if(acount == nullptr || password == nullptr)
    {
        return  false;
    }

    CDBHelper* dbHelper = new CDBHelper();
    char buffer[1024];
    memset(buffer,'\0',sizeof(buffer));
    sprintf(buffer,"select count(*) from `Student` where studentId = '%s' and password = '%s';",acount,password);
    std::string  sql = buffer;
    int ret =  dbHelper->sqlQueryCount(sql,"ExamSystem");
    bool result = false;
    if(ret == 1)
    {
        result = true;
    }else
    {
        result = false;
    }
    delete dbHelper;
    return result;
}

void CLoginModel::initStudentDatabase()
{
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql =  "create database if not exists `ExamSystem`;";
    dbHelper->sqlExcute(sql);
    delete dbHelper;
}

void CLoginModel::initStudentTable()
{
    CDBHelper* dbHelper = new CDBHelper();
    std::string  sql = "create table if not exists `Student`(\n\
`studentId`  varchar(20) primary key,\n\
`password` varchar(20) not null,\n\
`role` varchar(10) not null default 'student'\n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;";
   bool ret = dbHelper->sqlExcute(sql,"ExamSystem");

   //初始化学生信息表
   QString str = "未设置";
   QByteArray strArr = str.toLocal8Bit();
   const char* pStr = strArr.data();
   char buffer[1024];
   memset(buffer,'\0',sizeof(char) * 1024);
   sprintf(buffer,"create table if not exists `StudentInfo`(\n\
`id` integer primary key auto_increment,\n\
`name` varchar(20) not null default '%s',\n\
`gender` varchar(2) not null default '1',\n\
`phoneNumber` varchar(30) not null default '%s',\n\
`profilePicture` varchar(100) not null default '/root/picture/defaultHead.png',\n\
`studentId`  varchar(20) not null,\n\
foreign key(`studentId`) references `Student`(`studentId`)\n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;",pStr,pStr);
   sql = buffer;
   qDebug()<<sql.c_str();
   ret = dbHelper->sqlExcute(sql,"ExamSystem");
   delete dbHelper;
}
