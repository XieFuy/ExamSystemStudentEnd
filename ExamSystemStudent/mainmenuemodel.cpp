#include "mainmenuemodel.h"

CMainMenueModel::CMainMenueModel()
{
 this->m_mutex = CreateMutex(nullptr,FALSE,nullptr);
}

CMainMenueModel::~CMainMenueModel()
{

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
    CClientSocket* clientsocket = CClientSocket::getInstance();
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

    //对数据库进行操作,更该当前用户的头像的存储路径
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
