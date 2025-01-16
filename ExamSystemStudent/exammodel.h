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
    std::vector<std::vector<std::string>> getCurIndexSignalChoice(const char* testPaperId
                                                                  ,int curIndex);
    std::vector<std::vector<std::string>> getCurIndexMultiChoice(const char* testPaperId
                                                                  ,int CurIndex);
    std::vector<std::vector<std::string>> getCurIndexJudegChoice(const char* testPaperId
                                                                 ,int curIndex);
    std::vector<std::vector<std::string>> getCurIndexShortAnswerChoice(const char* testPaperId
                                 ,int curIndex);
};

#endif // CEXAMMODEL_H
