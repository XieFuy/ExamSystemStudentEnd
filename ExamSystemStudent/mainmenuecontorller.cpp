#include "mainmenuecontorller.h"

CMainMenueContorller::CMainMenueContorller()
{
 this->m_mainMenueModel = new CMainMenueModel();
}

int CMainMenueContorller::checkJoinExam(QString& classId,QString& teacherId
                   ,QString& studentId,QString& testPaperName)
{

    QByteArray classIdArr = classId.toLocal8Bit();
    QByteArray teacherIdArr  = teacherId.toLocal8Bit();
    QByteArray studentIdArr = studentId.toLocal8Bit();
    QByteArray testPaperNameArr = testPaperName.toLocal8Bit();

    const char* pClassId = classIdArr.data();
    const char* pTeacherId = teacherIdArr.data();
    const char* pStudentId = studentIdArr.data();
    const char* pTestPaperName = testPaperNameArr.data();
    return this->m_mainMenueModel->checkJoinExam(pClassId,pTeacherId,pStudentId,pTestPaperName);
}

int CMainMenueContorller::getTestPaperTableCount(QString acount)
{
    QByteArray acountArr = acount.toLocal8Bit();
    const char* pAcount = acountArr.data();
    return this->m_mainMenueModel->getTestPaperTableCount(pAcount);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getTestPaperData(QString acount,int curIndex)
{
    QByteArray acountArr = acount.toLocal8Bit();
    const char* pAcount = acountArr.data();
    return this->m_mainMenueModel->getTestPaperData(pAcount,curIndex);
}

typedef struct deleteMultiClassInfoArg
{
    CMainMenueContorller*thiz;
    const char* acount;
    const char* createTime;
    const char* className;
}DeleteMultiClassInfoArg;

bool CMainMenueContorller::deleteMultiClassInfo(QString acount,QList<QString>& createTimeLst,QList<QString>& classNameLst)
{
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    for(int i = 0 ; i < createTimeLst.size();i++)
    {
        QByteArray createTimeArr = createTimeLst.at(i).toLocal8Bit();
        const char* pCreateTime = createTimeArr.data();
        QByteArray classNameArr = classNameLst.at(i).toLocal8Bit();
        const char* pClassName = classNameArr.data();

        DeleteMultiClassInfoArg* arg = new DeleteMultiClassInfoArg();
        arg->thiz = this;
        arg->acount = pAcount;
        arg->createTime = pCreateTime;
        arg->className = pClassName;
        HANDLE thread = (HANDLE) _beginthreadex(nullptr,0,&CMainMenueContorller::threadDeleteMultiClassInfo,arg,0,nullptr);
        WaitForSingleObject(thread,INFINITE);
    }
    return true;
}

unsigned WINAPI CMainMenueContorller::threadDeleteMultiClassInfo(LPVOID arg)
{
    DeleteMultiClassInfoArg* dInfo = (DeleteMultiClassInfoArg*)arg;
    dInfo->thiz->m_mainMenueModel->deleteClassInfoByDateTime(dInfo->acount,dInfo->createTime,dInfo->className);
    delete dInfo;
    //_endthreadex(0);
    return 0;
}

bool CMainMenueContorller::deleteClassInfoByDateTime(QString acount,QString createTime,QString className)
{
    QByteArray acountArr = acount.toUtf8();
    QByteArray createTimeArr = createTime.toLocal8Bit();
    QByteArray classNameArr = className.toLocal8Bit();
    const char* pAcount = acountArr.data();
    const char* pCreateTime = createTimeArr.data();
    const char* pClassName = classNameArr.data();
    return this->m_mainMenueModel->deleteClassInfoByDateTime(pAcount,pCreateTime,pClassName);
}

int CMainMenueContorller::getClassTableCount(QString acount)
{
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount =  acountArr.data();
    return this->m_mainMenueModel->getClassTableCount(pAcount);
}

std::vector<std::vector<std::string>> CMainMenueContorller::getClassTableData(QString acount,int curPageIndex)
{
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    return this->m_mainMenueModel->getClassTableData(pAcount,curPageIndex);
}

bool CMainMenueContorller::initClassTableDatabase()
{
  return this->m_mainMenueModel->initClassTableDatabase();
}

CMainMenueContorller::~CMainMenueContorller()
{
 if(this->m_mainMenueModel != nullptr)
 {
     delete this->m_mainMenueModel;
     this->m_mainMenueModel = nullptr;
 }
}

void CMainMenueContorller::changeHeadPicture(QString LocalFilePath,QString acount)
{
    QString tempFileName;
    for(int i = LocalFilePath.size() - 1 ; i >= 0 ; i--)
    {
        if(LocalFilePath.at(i) == '/')
        {
            break;
        }
        tempFileName.push_back(LocalFilePath.at(i));
    }

    QString fileName;
    for(QString::reverse_iterator pos = tempFileName.rbegin(); pos != tempFileName.rend(); pos++)
    {
         fileName.push_back(*pos);
    }

    QByteArray localFilePathArr = LocalFilePath.toLocal8Bit();
    QByteArray acountArr = acount.toUtf8();
    QByteArray fileNameArr = fileName.toLocal8Bit();
    const char* pLocalFilePath = localFilePathArr.data();
    const char* pAcount = acountArr.data();
    const char* pFileName = fileNameArr.data();
    return  this->m_mainMenueModel->changeHeadPicture(const_cast<char*>(pLocalFilePath),const_cast<char*>( pFileName),const_cast<char*>(pAcount));
}

std::vector<std::vector<std::string>> CMainMenueContorller::showStudentInfo(QString acount)
{
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    return  this->m_mainMenueModel->showStudentInfo(const_cast<char*>(pAcount));
}

std::vector<std::vector<std::string>> CMainMenueContorller::showStudentAcountInfo(QString acount)
{
    QByteArray acountArr = acount.toUtf8();
    const char* pAcount = acountArr.data();
    return this->m_mainMenueModel->showStudentAcountInfo(const_cast<char*>(pAcount));
}

void CMainMenueContorller::changeGender(bool isMan,QString pAcount)
{
    QByteArray acountArr = pAcount.toUtf8();
    const char* acount = acountArr.data();
    this->m_mainMenueModel->changeGender(isMan,const_cast<char*>(acount));
}
