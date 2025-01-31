#include "exammodel.h"

CExamModel::CExamModel()
{

}

std::vector<std::vector<std::string>> CExamModel::getJudgeChoice(const char* teacherId,const char* classId
                                                      ,const char* testPaperId
                                                      ,const char* studentId,int order)
{
    if(teacherId == nullptr || classId == nullptr || testPaperId == nullptr
            || studentId == nullptr )
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `AnswerGiven` from `studentAnswerJudge` \
where `teacherId` = '%s' and `classId` = '%s' and `testPaperId` = '%s' and `studentId` = '%s' and `order` = %d;"
            ,teacherId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    qDebug()<<sql.c_str();
    return dbHelper->sqlQuery(sql,"ExamSystem");
}

bool CExamModel::updateJudgeAnswerFalse(const char* teacherId,const char* classId
                           ,const char* testPaperId
                           ,const char* studentId,int order)
{
    if(teacherId == nullptr || classId == nullptr || testPaperId == nullptr
            || studentId == nullptr )
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"update `studentAnswerJudge` set `AnswerGiven` = '0' \
where `teacherId` = '%s' and `classId` = '%s' and `testPaperId` = '%s' and `studentId` = '%s' and `order` = %d;",
            teacherId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    return ret;
}

bool CExamModel::updateJudgeAnswerTrue(const char* teacherId,const char* classId
                           ,const char* testPaperId
                           ,const char* studentId,int order)
{
    if(teacherId == nullptr || classId == nullptr || testPaperId == nullptr
            || studentId == nullptr )
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"update `studentAnswerJudge` set `AnswerGiven` = '1' \
where `teacherId` = '%s' and `classId` = '%s' and `testPaperId` = '%s' and `studentId` = '%s' and `order` = %d;",
            teacherId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    return ret;
}

std::vector<std::vector<std::string>> CExamModel::getMultiChoice(const char* teacherId,const char* classId
                                                      ,const char* testPaperId
                                                      ,const char* studentId,int order)
{
    if(teacherId == nullptr || classId == nullptr || testPaperId == nullptr
            || studentId == nullptr )
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `AnswerGiven` from `studentAnswerMulti` \
where `teacherId` = '%s' and `classId` = '%s' and `testPaperId` = '%s' and `studentId` = '%s' and `order` = %d;"
            ,teacherId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    return dbHelper->sqlQuery(sql,"ExamSystem");
}

bool CExamModel::UpdateMultiAnswer(const char* teacherId,const char* classId
                       ,const char* testPaperId
                       ,const char* studentId,int order,const char* answer)
{
    if(teacherId == nullptr || classId == nullptr || testPaperId == nullptr
            || studentId == nullptr || answer == nullptr )
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"update `studentAnswerMulti` set `AnswerGiven` = '%s' \
where  `teacherId` = '%s' and `classId` = '%s' and `testPaperId` = '%s' and `studentId` = '%s' and `order` = %d;"
            ,answer,teacherId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    qDebug()<<sql.c_str();
    return dbHelper->sqlExcute(sql,"ExamSystem");
}

//TODO:写到这里明天继续
std::vector<std::vector<std::string>> CExamModel::getSignalChoice(const char* teacherId,const char* classId
                                                      ,const char* testPaperId
                                                      ,const char* studentId,int order)
{
    if(teacherId == nullptr || classId == nullptr || testPaperId == nullptr
            || studentId == nullptr )
    {
        return std::vector<std::vector<std::string>>();
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    std::string sql;
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    sprintf(sqlBuf.get(),"select `AnswerGiven` from `studentAnswerSingal` \
where `teacherId` = '%s' and `classId` = '%s' and `testPaperId` = '%s' and `studentId` = '%s' and `order` = %d;"
            ,teacherId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    return dbHelper->sqlQuery(sql,"ExamSystem");
}

bool CExamModel::updateSignalAnswertoD(const char* teacherId,const char* classId
                           ,const char* testPaperId
                           ,const char* studentId,int order)
{
    if(teacherId == nullptr || classId == nullptr || testPaperId == nullptr
            || studentId == nullptr )
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"update `studentAnswerSingal` set `AnswerGiven` = 'D' \
where `teacherId` = '%s' and `classId` = '%s' and `testPaperId` = '%s' and `studentId` = '%s' and `order` = %d;",
            teacherId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    return ret;
}

bool CExamModel::updateSignalAnswertoC(const char* teacherId,const char* classId
                           ,const char* testPaperId
                           ,const char* studentId,int order)
{
    if(teacherId == nullptr || classId == nullptr || testPaperId == nullptr
            || studentId == nullptr )
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"update `studentAnswerSingal` set `AnswerGiven` = 'C' \
where `teacherId` = '%s' and `classId` = '%s' and `testPaperId` = '%s' and `studentId` = '%s' and `order` = %d;",
            teacherId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    return ret;
}

bool CExamModel::updateSignalAnswertoB(const char* teacherId,const char* classId
                           ,const char* testPaperId
                           ,const char* studentId,int order)
{
    if(teacherId == nullptr || classId == nullptr || testPaperId == nullptr
            || studentId == nullptr )
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"update `studentAnswerSingal` set `AnswerGiven` = 'B' \
where `teacherId` = '%s' and `classId` = '%s' and `testPaperId` = '%s' and `studentId` = '%s' and `order` = %d;",
            teacherId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    return ret;
}

bool CExamModel::updateSignalAnswertoA(const char* teacherId,const char* classId
                           ,const char* testPaperId
                           ,const char* studentId,int order)
{
    if(teacherId == nullptr || classId == nullptr || testPaperId == nullptr
            || studentId == nullptr )
    {
        return false;
    }
    std::shared_ptr<CDBHelper> dbHelper = std::make_shared<CDBHelper>();
    std::unique_ptr<char[]> sqlBuf(new char[1024000]);
    memset(sqlBuf.get(),'\0',sizeof(char) * 1024000);
    std::string sql;
    sprintf(sqlBuf.get(),"update `studentAnswerSingal` set `AnswerGiven` = 'A' \
where `teacherId` = '%s' and `classId` = '%s' and `testPaperId` = '%s' and `studentId` = '%s' and `order` = %d;",
            teacherId,classId,testPaperId,studentId,order);
    sql = sqlBuf.get();
    bool ret =  dbHelper->sqlExcute(sql,"ExamSystem");
    return ret;
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
