#include "examcontorller.h"

CExamContorller::CExamContorller()
{
 this->m_model = new CExamModel();
}

std::vector<std::vector<std::string>> CExamContorller::getCurIndexShortAnswerChoice(QString testPaperId
                             ,int curIndex)
{
    QByteArray testPaperIdArr  = testPaperId.toLocal8Bit();
    const char* pTestPaperId = testPaperIdArr.data();
    return this->m_model->getCurIndexShortAnswerChoice(pTestPaperId,curIndex);
}

std::vector<std::vector<std::string>> CExamContorller::getCurIndexJudegChoice(QString testPaperId
                                                             ,int curIndex)
{
    QByteArray testPaperIdArr  = testPaperId.toLocal8Bit();
    const char* pTestPaperId = testPaperIdArr.data();
    return this->m_model->getCurIndexJudegChoice(pTestPaperId,curIndex);
}

std::vector<std::vector<std::string>> CExamContorller::getCurIndexMultiChoice(QString testPaperId
                                                              ,int CurIndex)
{
    QByteArray testPaperIdArr  = testPaperId.toLocal8Bit();
    const char* pTestPaperId = testPaperIdArr.data();
    return this->m_model->getCurIndexMultiChoice(pTestPaperId,CurIndex);
}

std::vector<std::vector<std::string>> CExamContorller::getCurIndexSignalChoice
                                                       (QString testPaperId,
                                                        int CurIndex)
{
    QByteArray testPaperIdArr  = testPaperId.toLocal8Bit();
    const char* pTestPaperId = testPaperIdArr.data();
    return this->m_model->getCurIndexSignalChoice(pTestPaperId,CurIndex);
}

int CExamContorller::getShortAnswerCount(QString testPaperId)
{
    QByteArray testPaperIdArr  = testPaperId.toLocal8Bit();
    const char* pTestPaperId = testPaperIdArr.data();
    return this->m_model->getShortAnswerCount(pTestPaperId);
}

int CExamContorller::getJudgeChoiceCount(QString testPaperId)
{
    QByteArray testPaperIdArr  = testPaperId.toLocal8Bit();
    const char* pTestPaperId = testPaperIdArr.data();
    return this->m_model->getJudgeChoiceCount(pTestPaperId);
}

int CExamContorller::getMultiChoiceCount(QString testPaperId)
{
    QByteArray testPaperIdArr  = testPaperId.toLocal8Bit();
    const char* pTestPaperId = testPaperIdArr.data();
    return this->m_model->getMultiChoiceCount(pTestPaperId);
}

int CExamContorller::getSignalChoiceCount(QString testPaperId)
{
    QByteArray testPaperIdArr  = testPaperId.toLocal8Bit();
    const char* pTestPaperId = testPaperIdArr.data();
    return this->m_model->getSignalChoiceCount(pTestPaperId);
}

std::vector<std::vector<std::string>> CExamContorller::getCurTestPaperId(QString classId
                                                        ,QString teacherId
                                                        ,QString startTime,QString endTime
                                                        ,QString longTime)
{
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray startTimeArr = startTime.toLocal8Bit();
    QByteArray endTimeArr = endTime.toLocal8Bit();
    QByteArray longTimeArr = longTime.toLocal8Bit();

    const char* pClassId = classIdArr.data();
    const char* pTeacherId = teacherIdArr.data();
    const char* pStartTime = startTimeArr.data();
    const char* pEndTime = endTimeArr.data();
    const char* pLongTime = longTimeArr.data();
    return this->m_model->getCurTestPaperId(pClassId,pTeacherId,pStartTime,pEndTime,pLongTime);
}

CExamContorller:: ~CExamContorller()
{
    if(this->m_model != nullptr)
    {
        delete this->m_model;
        this->m_model = nullptr;
    }
}
