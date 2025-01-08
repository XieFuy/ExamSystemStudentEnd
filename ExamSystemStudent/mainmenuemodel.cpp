#include "mainmenuemodel.h"

CMainMenueModel::CMainMenueModel()
{
 this->m_mutex = CreateMutex(nullptr,FALSE,nullptr);
}

CMainMenueModel::~CMainMenueModel()
{

}

int CMainMenueModel::getTestPaperTableCount(const char* acount)
{
    if(acount == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"SELECT \n\
count(*)\n\
FROM \n\
`testPaperRelease` tpr\n\
JOIN \n\
`testPaperInfo` tpi ON tpr.`testPaperId` = tpi.`testPaperId`\n\
JOIN \n\
`joinClassStudentManeage` jcsm ON tpr.`teacherId` = jcsm.`teacherId`\n\
WHERE \n\
jcsm.`studentId` = '%s';",acount);
    sql = sqlBuf.get();
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
         result += 1;
    }else
    {
       int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    return result;
}

std::vector<std::vector<std::string>> CMainMenueModel::getTestPaperData(const char* acount,int curIndex)
{
    if(acount == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"SELECT \n\
tpi.`testPaperName`,\n\
tpr.`examStartTime`,\n\
tpr.`examEndTime`,\n\
tpr.`examLongTimeMinute`\n\
FROM \n\
`testPaperRelease` tpr\n\
JOIN \n\
`testPaperInfo` tpi ON tpr.`testPaperId` = tpi.`testPaperId`\n\
JOIN \n\
`joinClassStudentManeage` jcsm ON tpr.`teacherId` = jcsm.`teacherId`\n\
 WHERE \n\
jcsm.`studentId` = '%s' limit 8 offset %d;",acount,(curIndex - 1)*8);
    sql = sqlBuf.get();
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    return ret;
}

bool CMainMenueModel::deleteClassInfoByDateTime(const char* acount
                               ,const char* createTime,const char* className)
{
    if(acount == nullptr || createTime == nullptr || className == nullptr)
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::shared_ptr<char[]> sqlBuf (new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"delete from `joinClassStudentManeage` where `studentId` = '%s' \
and `joinTime` = '%s' and `className` = '%s';",acount,createTime,className);
    sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    return ret;
}

int CMainMenueModel::getClassTableCount(const char* acount)
{
    if(acount == nullptr)
    {
        return -1;
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT\n\
count(*)\n\
FROM\n\
`joinClassStudentManeage` j\n\
WHERE\n\
j.`studentId` = '%s';",acount);
    sql = sqlBuf;
    int tableCount =  dbHelper->sqlQueryCount(sql,"ExamSystem"); //获取的是表的记录条数
    tableCount -= 1; //减去最上面的一条记录
    int result = (tableCount / 8) ;

    if(result < 0) //表示总的记录条数小于8
    {
         result += 1;
    }else
    {
       int yuShu = tableCount - (result * 8);
        if(yuShu >= 0)
        {
            result += 1;
        }
    }
    delete[] sqlBuf;
    delete dbHelper;
    return result;
}

std::vector<std::vector<std::string>> CMainMenueModel::getClassTableData(const char* acount,int curPageIndex)
{
    if(acount == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }

    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"SELECT\n\
(SELECT `classIconPath` FROM `class` WHERE `teacherId` = j.`teacherId` AND `className` = j.`className` LIMIT 1) AS `IconPath`,\n\
j.`className`,\n\
j.`joinTime`,\n\
(SELECT `name` FROM `TeacherInfo` WHERE `teacherId` = j.`teacherId` LIMIT 1) AS `TeacherName`\n\
FROM\n\
`joinClassStudentManeage` j\n\
WHERE\n\
j.`studentId` = '%s' limit 8 offset %d;",acount,(curPageIndex - 1) * 8);
    sql = sqlBuf;
    qDebug()<<sql.c_str();
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

bool CMainMenueModel::initClassTableDatabase()
{
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"create table if not exists `class`(\n\
`id` integer  primary key auto_increment,\n\
`classIconPath` varchar(100) not null,\n\
`className` varchar(50) not null,\n\
`createTime` datetime not null,\n\
`teacherId` varchar(20)  not null,\n\
foreign key(`teacherId`) references `Teacher`(`teacherId`)\n\
)ENGINE=InnoDB DEFAULT CHARSET=utf8;");
    sql = sqlBuf;
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    delete[] sqlBuf;
    delete dbHelper;
    return ret;
}

void CMainMenueModel::changeHeadPicture(char* localFilePath ,char* fileName,char* acount)
{
    if(localFilePath == nullptr || fileName == nullptr || acount == nullptr)
    {
        return ;
    }
    //先进行网络通信，将头像上传到服务器磁盘保存
    FILE* pFile = fopen(localFilePath,"rb+");
    if(pFile == nullptr)
    {
        fclose(pFile);
        return;
    }

    fseek(pFile,0,SEEK_END);
    long long fileSize =  _ftelli64(pFile);
    fseek(pFile,0,SEEK_SET);

    std::string headPath = "/root/picture/";
    headPath += fileName;
    qDebug()<<headPath.size();
    char* data = new char[2 + fileSize + headPath.size()]; //全是文件数据
    memset(data,'\0',sizeof(char) * (2 + fileSize + headPath.size()));
    WORD pathLenght = headPath.size();
    memcpy(data,&pathLenght,sizeof(WORD));
    long long size =  fread(data + 2,1,fileSize,pFile);
    fclose(pFile);
    memcpy(data + fileSize + 2,headPath.c_str(),headPath.size());
    //进行封包操作
//    CClientSocket* clientsocket = CClientSocket::getInstance();
    CClientSocket* clientsocket = new CClientSocket();
    clientsocket->initSocket();
    bool ret =  clientsocket->connectToServer();
    if(!ret)
    {
        return;
    }
    clientsocket->makePacket(data,fileSize + headPath.size() + 2,1);
    char* packet =  clientsocket->getPacket();
    clientsocket->Send(packet);
    delete[] data;
    clientsocket->closeSocket();
    delete clientsocket;
    //对数据库进行操作,更该当前用户的头像的存储路径
//    CDBHelper* dbHelper = CDBHelper::getInstance();
    CDBHelper* dbHelper = new CDBHelper();
    char sqlBuf[1024];
    memset(sqlBuf,'\0',sizeof(sqlBuf));

    sprintf(sqlBuf,"update  `StudentInfo` set `profilePicture` = '%s' where `studentId` = '%s'; ",headPath.c_str(),acount);
    std::string sql = sqlBuf;
    bool ret2 =   dbHelper->sqlExcute(sql,"ExamSystem");
    delete dbHelper;
    return;
}

void CMainMenueModel::changeGender(bool isMan,char* pAcount)
{
    std::string gender;
    if(isMan)
    {
        gender = "1";
    }else
    {
        gender = "0";
    }
    CDBHelper* dbHelper = new CDBHelper();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"update  `StudentInfo` set `gender` = '%s' where `studentId` = '%s'; ",gender.c_str(),pAcount);
    std::string sql  = sqlBuf;
    delete[] sqlBuf;
    bool ret =   dbHelper->sqlExcute(sql,"ExamSystem");
    delete dbHelper;
    return;
}

std::vector<std::vector<std::string>> CMainMenueModel::showStudentAcountInfo(char* pAcount)
{
    if(pAcount == nullptr)
    {
        return std::vector<std::vector<std::string>>(); //返回一个空结果集
    }
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf,"select `name`,`studentId`,`gender`,`phoneNumber` from `StudentInfo` where `studentId` = '%s';",pAcount);
    sql = sqlBuf;
    delete[] sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete dbHelper;
    return ret;
}

//显示主页头像和姓名
std::vector<std::vector<std::string>> CMainMenueModel::showStudentInfo(char* pAcount)
{
    if(pAcount == nullptr)
    {
        return std::vector<std::vector<std::string>>(); //返回一个空结果集
    }
    //进行查询显示 姓名和头像
    CDBHelper* dbHelper = new CDBHelper();
    std::string sql;
    char sqlBuf[1024];
    memset(sqlBuf,0,sizeof(char)*1024);
    sprintf(sqlBuf,"select `name`,`profilePicture` from `StudentInfo` where `studentId` = '%s';",pAcount);
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete dbHelper;
    return ret;
}
