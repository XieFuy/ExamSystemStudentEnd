#ifndef CEXAMMODEL_H
#define CEXAMMODEL_H

#include "DBHelper.h"
#include<memory>
#include<QDebug>
class CExamModel
{
public:
    CExamModel();
    ~CExamModel();
    std::vector<std::vector<std::string>> getCurTestPaperId(const char* classId
                                                            ,const char* teacherId
                                                            ,const char* startTime,const char* endTime
                                                            ,const char* longTime);
    int getSignalChoiceCount(const char* testPaperId);
    int getMultiChoiceCount(const char* testPaperId);
    int getJudgeChoiceCount(const char* testPaperId);
    int getShortAnswerCount(const char* testPaperId);
};

#endif // CEXAMMODEL_H
