#include "examcontorller.h"

CExamContorller::CExamContorller()
{
 this->m_model = new CExamModel();
}

bool CExamContorller::addCommitTestPaper(QString& teacherId,QString& classId,QString& testPaperId
                        ,QString& studentId,QString& testPaperName)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId  = testPaperIdArr.data();
    const char* pStudentId = studentIdArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_model->addCommitTestPaper(pTeacherId,pClassId,pTestPaperId
                                             ,pStudentId,pTestPaperName);
}

std::vector<std::vector<std::string>> CExamContorller::getShortAnswer(QString& teacherId,QString& classId
                                                     ,QString& testPaperId
                                                     ,QString& studentId,QString& order)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId  = testPaperIdArr.data();
    const char* pStudentId = studentIdArr.data();

    int iOrder = order.toInt();
    return this->m_model->getShortAnswer(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder);
}

bool CExamContorller::updateShortAnswer(QString& teacherId,QString& classId
                       ,QString testPaperId
                       ,QString& studentId,QString& order,QString& answer)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr  = studentId.toLocal8Bit();
    int iOrder = order.toInt();
    QByteArray answerArr = answer.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId = testPaperIdArr.data();
    const char* pStudentId  = studentIdArr.data();
    const char* pAnswer = answerArr.data();
    return this->m_model->updateShortAnswer(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder,pAnswer);
}

std::vector<std::vector<std::string>>  CExamContorller::getJudgeChoice(QString& teacherId,QString& classId
                                                     ,QString& testPaperId
                                                     ,QString& studentId,QString& order)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId  = testPaperIdArr.data();
    const char* pStudentId = studentIdArr.data();

    int iOrder = order.toInt();
    return this->m_model->getJudgeChoice(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder);
}

bool CExamContorller::updateJudgeAnswerFalse(QString& teacherId,QString& classId
                           ,QString testPaperId
                           ,QString& studentId,QString& order)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId  = testPaperIdArr.data();
    const char* pStudentId = studentIdArr.data();

    int iOrder = order.toInt();
    return this->m_model->updateJudgeAnswerFalse(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder);
}

bool CExamContorller::updateJudgeAnswerTrue(QString& teacherId,QString& classId
                           ,QString testPaperId
                           ,QString& studentId,QString& order)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId  = testPaperIdArr.data();
    const char* pStudentId = studentIdArr.data();

    int iOrder = order.toInt();
    return this->m_model->updateJudgeAnswerTrue(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder);
}

std::vector<std::vector<std::string>> CExamContorller::getMultiChoice(QString& teacherId,QString& classId
                                                      ,QString testPaperId
                                                      ,QString& studentId,QString& order)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId  = testPaperIdArr.data();
    const char* pStudentId = studentIdArr.data();

    int iOrder = order.toInt();
    return this->m_model->getMultiChoice(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder);
}

bool CExamContorller::UpdateMultiAnswer(QString& teacherId,QString& classId
                       ,QString testPaperId
                       ,QString& studentId,QString& order,QString& answer)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr  = studentId.toLocal8Bit();
    int iOrder = order.toInt();
    QByteArray answerArr = answer.toUtf8();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId = testPaperIdArr.data();
    const char* pStudentId  = studentIdArr.data();
    const char* pAnswer = answerArr.data();
    return this->m_model->UpdateMultiAnswer(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder,pAnswer);
}

std::vector<std::vector<std::string>> CExamContorller::getSignalChoice(QString& teacherId,QString& classId
                                                      ,QString testPaperId
                                                      ,QString& studentId,QString& order)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId  = testPaperIdArr.data();
    const char* pStudentId = studentIdArr.data();

    int iOrder = order.toInt();
    return this->m_model->getSignalChoice(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder);
}

bool CExamContorller::updateSignalAnswertoD(QString& teacherId,QString& classId
                           ,QString testPaperId
                           ,QString& studentId,QString& order)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId  = testPaperIdArr.data();
    const char* pStudentId = studentIdArr.data();

    int iOrder = order.toInt();
    return this->m_model->updateSignalAnswertoD(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder);
}

bool CExamContorller::updateSignalAnswertoC(QString& teacherId,QString& classId
                           ,QString testPaperId
                           ,QString& studentId,QString& order)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId  = testPaperIdArr.data();
    const char* pStudentId = studentIdArr.data();

    int iOrder = order.toInt();
    return this->m_model->updateSignalAnswertoC(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder);
}

bool CExamContorller::updateSignalAnswertoB(QString& teacherId,QString& classId
                           ,QString testPaperId
                           ,QString& studentId,QString& order)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId  = testPaperIdArr.data();
    const char* pStudentId = studentIdArr.data();

    int iOrder = order.toInt();
    return this->m_model->updateSignalAnswertoB(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder);
}

bool CExamContorller::updateSignalAnswertoA(QString& teacherId,QString& classId
                           ,QString testPaperId
                           ,QString& studentId,QString& order)
{
    QByteArray teacherIdArr = teacherId.toLocal8Bit();
    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray testPaperIdArr = testPaperId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();

    const char* pTeacherId = teacherIdArr.data();
    const char* pClassId = classIdArr.data();
    const char* pTestPaperId  = testPaperIdArr.data();
    const char* pStudentId = studentIdArr.data();

    int iOrder = order.toInt();
    return this->m_model->updateSignalAnswertoA(pTeacherId,pClassId,pTestPaperId,pStudentId,iOrder);
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
