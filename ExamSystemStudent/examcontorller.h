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
};

#endif // CEXAMCONTORLLER_H
