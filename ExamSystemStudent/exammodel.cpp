#include "exammodel.h"

CExamModel::CExamModel()
{

}

std::vector<std::vector<std::string>> CExamModel::getCurIndexShortAnswerChoice(const char* testPaperId
                             ,int curIndex)
{
    if(testPaperId == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `question` from `shortAnswer`\n\
where `testPaperId` = '%s' order by `order` limit 1 offset %d;",testPaperId,(curIndex - 1));
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

std::vector<std::vector<std::string>> CExamModel::getCurIndexJudegChoice(const char* testPaperId
                                                             ,int curIndex)
{
    if(testPaperId == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `question`,`sessionTrue`,`sessionFalse` from `judge`\n\
where `testPaperId` = '%s' order by `order` limit 1 offset %d;",testPaperId,(curIndex - 1));
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

std::vector<std::vector<std::string>> CExamModel::getCurIndexMultiChoice(const char* testPaperId
                                                              ,int CurIndex)
{
    if(testPaperId == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `question`,`sessionA`,`sessionB`,`sessionC`,`sessionD`,`sessionE`,`sessionF` from `multiChoice`\n\
where `testPaperId` = '%s' order by `order` limit 1 offset %d;",testPaperId,(CurIndex - 1));
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

std::vector<std::vector<std::string>> CExamModel::getCurIndexSignalChoice(const char* testPaperId,int curIndex)
{
    if(testPaperId == nullptr)
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    char* sqlBuf = new char[1024000];
    memset(sqlBuf,'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf,"select `question`,`sessionA`,`sessionB`,`sessionC`,`sessionD` from `singleChoice`\n\
where `testPaperId` = '%s' order by `order` limit 1 offset %d;",testPaperId,(curIndex - 1));
    sql = sqlBuf;
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    delete[] sqlBuf;
    return ret;
}

int CExamModel::getShortAnswerCount(const char* testPaperId)
{
    if(testPaperId == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    int num = atoi(testPaperId);
    sprintf(sqlBuf.get(),"SELECT COUNT(*) FROM `shortAnswer` \
WHERE `testPaperId` = %d;",num);
    qDebug()<<sqlBuf.get();
    sql = sqlBuf.get();
    int ret =  dbHelper->sqlQueryCount(sql,"ExamSystem");
    return ret;
}

int CExamModel::getJudgeChoiceCount(const char* testPaperId)
{
    if(testPaperId == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    int num = atoi(testPaperId);
    sprintf(sqlBuf.get(),"SELECT COUNT(*) FROM `judge` \
WHERE `testPaperId` = %d;",num);
    qDebug()<<sqlBuf.get();
    sql = sqlBuf.get();
    int ret =  dbHelper->sqlQueryCount(sql,"ExamSystem");
    return ret;
}

int CExamModel::getMultiChoiceCount(const char* testPaperId)
{
    if(testPaperId == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    int num = atoi(testPaperId);
    sprintf(sqlBuf.get(),"SELECT COUNT(*) FROM `multiChoice` \
WHERE `testPaperId` = %d;",num);
    qDebug()<<sqlBuf.get();
    sql = sqlBuf.get();
    int ret =  dbHelper->sqlQueryCount(sql,"ExamSystem");
    return ret;
}

int CExamModel::getSignalChoiceCount(const char* testPaperId)
{
    if(testPaperId == nullptr)
    {
        return -1;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    int num = atoi(testPaperId);
    sprintf(sqlBuf.get(),"SELECT COUNT(*) FROM `singleChoice` \
WHERE `testPaperId` = %d;",num);
    qDebug()<<sqlBuf.get();
    sql = sqlBuf.get();
    int ret =  dbHelper->sqlQueryCount(sql,"ExamSystem");
    return ret;
}

std::vector<std::vector<std::string>> CExamModel::getCurTestPaperId(const char* classId
                                                        ,const char* teacherId
                                                        ,const char* startTime,const char* endTime
                                                        ,const char* longTime)
{
    if(classId == nullptr || teacherId == nullptr || startTime == nullptr
            || endTime == nullptr || longTime == nullptr)
    {
       std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `testPaperId` from `testPaperRelease` \
where `classId` = '%s' and `teacherId` = '%s' and `examStartTime` = '%s' and `examEndTime` = '%s' and `examLongTimeMinute` ='%s' limit 1;"
            ,classId,teacherId,startTime,endTime,longTime);
    sql = sqlBuf.get();
    std::vector<std::vector<std::string>> ret =  dbHelper->sqlQuery(sql,"ExamSystem");
    return ret;
}

CExamModel::~CExamModel()
{

}
