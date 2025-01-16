#ifndef CEXAMCONTORLLER_H
#define CEXAMCONTORLLER_H

#include "exammodel.h"
#include<QString>
#include<string>
#include<vector>

class CExamContorller
{
private:
    CExamModel* m_model = nullptr;
public:
    CExamContorller();
    ~CExamContorller();
    std::vector<std::vector<std::string>> getCurTestPaperId(QString classId
                                                            ,QString teacherId
                                                            ,QString startTime,QString endTime
                                                            ,QString longTime);
    int getSignalChoiceCount(QString testPaperId);
    int getMultiChoiceCount(QString testPaperId);
    int getJudgeChoiceCount(QString testPaperId);
    int getShortAnswerCount(QString testPaperId);
    std::vector<std::vector<std::string>> getCurIndexSignalChoice(QString testPaperId
                                                                  ,int CurIndex);
    std::vector<std::vector<std::string>> getCurIndexMultiChoice(QString testPaperId
                                                                  ,int CurIndex);
    std::vector<std::vector<std::string>> getCurIndexJudegChoice(QString testPaperId
                                                                 ,int curIndex);
    std::vector<std::vector<std::string>> getCurIndexShortAnswerChoice(QString testPaperId
                                 ,int curIndex);
};

#endif // CEXAMCONTORLLER_H
