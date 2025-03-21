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
    bool updateSignalAnswertoA(const char* teacherId,const char* classId
                               ,const char* testPaperId
                               ,const char* studentId,int order);
    bool updateSignalAnswertoB(const char* teacherId,const char* classId
                               ,const char* testPaperId
                               ,const char* studentId,int order);
    bool updateSignalAnswertoC(const char* teacherId,const char* classId
                               ,const char* testPaperId
                               ,const char* studentId,int order);
    bool updateSignalAnswertoD(const char* teacherId,const char* classId
                               ,const char* testPaperId
                               ,const char* studentId,int order);
    std::vector<std::vector<std::string>> getSignalChoice(const char* teacherId,const char* classId
                                                          ,const char* testPaperId
                                                          ,const char* studentId,int order);
    bool UpdateMultiAnswer(const char* teacherId,const char* classId
                           ,const char* testPaperId
                           ,const char* studentId,int order,const char* answer);
    std::vector<std::vector<std::string>> getMultiChoice(const char* teacherId,const char* classId
                                                          ,const char* testPaperId
                                                          ,const char* studentId,int order);
    bool updateJudgeAnswerTrue(const char* teacherId,const char* classId
                               ,const char* testPaperId
                               ,const char* studentId,int order);

    bool updateJudgeAnswerFalse(const char* teacherId,const char* classId
                               ,const char* testPaperId
                               ,const char* studentId,int order);
    std::vector<std::vector<std::string>>  getJudgeChoice(const char* teacherId,const char* classId
                                                          ,const char* testPaperId
                                                          ,const char* studentId,int order);

    bool  updateShortAnswer(const char* teacherId,const char* classId
                           ,const char* testPaperId
                           ,const char* studentId,int order,const char* answer);

    std::vector<std::vector<std::string>>   getShortAnswer(const char* teacherId,const char* classId
                                                          ,const char* testPaperId
                                                          ,const char* studentId,int order);
    bool addCommitTestPaper(const char* teacherId,const char* classId,const char* testPaperId
                            ,const char* studentId,const char* testPaperName);
};

#endif // CEXAMMODEL_H
