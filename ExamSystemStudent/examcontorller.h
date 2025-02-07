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
    bool updateSignalAnswertoA(QString& teacherId,QString& classId
                               ,QString testPaperId
                               ,QString& studentId,QString& order);
    bool updateSignalAnswertoB(QString& teacherId,QString& classId
                               ,QString testPaperId
                               ,QString& studentId,QString& order);
    bool updateSignalAnswertoC(QString& teacherId,QString& classId
                               ,QString testPaperId
                               ,QString& studentId,QString& order);
    bool updateSignalAnswertoD(QString& teacherId,QString& classId
                               ,QString testPaperId
                               ,QString& studentId,QString& order);
    std::vector<std::vector<std::string>> getSignalChoice(QString& teacherId,QString& classId
                                                          ,QString testPaperId
                                                          ,QString& studentId,QString& order);
    bool UpdateMultiAnswer(QString& teacherId,QString& classId
                           ,QString testPaperId
                           ,QString& studentId,QString& order,QString& answer);
    std::vector<std::vector<std::string>> getMultiChoice(QString& teacherId,QString& classId
                                                          ,QString testPaperId
                                                          ,QString& studentId,QString& order);
    bool updateJudgeAnswerTrue(QString& teacherId,QString& classId
                               ,QString testPaperId
                               ,QString& studentId,QString& order);

    bool updateJudgeAnswerFalse(QString& teacherId,QString& classId
                               ,QString testPaperId
                               ,QString& studentId,QString& order);
    std::vector<std::vector<std::string>> getJudgeChoice(QString& teacherId,QString& classId
                                                         ,QString& testPaperId
                                                         ,QString& studentId,QString& order);

    bool updateShortAnswer(QString& teacherId,QString& classId
                           ,QString testPaperId
                           ,QString& studentId,QString& order,QString& answer);
    std::vector<std::vector<std::string>> getShortAnswer(QString& teacherId,QString& classId
                                                         ,QString& testPaperId
                                                         ,QString& studentId,QString& order);
    bool addCommitTestPaper(QString& teacherId,QString& classId,QString& testPaperId
                            ,QString& studentId,QString& testPaperName);

};

#endif // CEXAMCONTORLLER_H
