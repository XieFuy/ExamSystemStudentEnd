#include "mainmenuecontorller.h"

CMainMenueContorller::CMainMenueContorller()
{
 this->m_mainMenueModel = new CMainMenueModel();
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
