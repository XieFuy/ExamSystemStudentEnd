#ifndef EXAMDLG_H
#define EXAMDLG_H

#include <QDialog>
#include <QTimer>
#include <QMessageBox>
#include "examcontorller.h"
#include "windows.h"
#include <QDebug>

namespace Ui {
class CExamDlg;
}

class CExamDlg : public QDialog  //学生进行考试的窗口
{
    Q_OBJECT

public:
    explicit CExamDlg(QWidget *parent = nullptr);
    ~CExamDlg();
signals:
    void startDoModel(); //开始执行后端操作
    void startShowMenueBtn(int signalCount);
    void testPaperIdIsOk();
    void startShowMultiMenueBtn(int Count);
    void startShowJudgeMenueBtn(int Count);
    void startShowShortAnswerBtn(int Count);
    void startShowSignalChoice(QVector<QVector<QString>>* ret);
    void startShowMultiChoice(QVector<QVector<QString>>* ret);
    void startShowJudgeChoice(QVector<QVector<QString>>* ret);
    void startShowShortAnswerChoice(QVector<QVector<QString>>* ret);
public:
    QString classId;
    QString teacherId;
    QString startTime;
    QString endTime;
    QString longTime;
private:
    //获取当前正在考试的试卷的id
    void getCurTestPaperId();
    static unsigned WINAPI threadGetCurTestPaperId(LPVOID arg);

    //获取该份试卷的单选题的总数量  根据试卷名和职工号确定
    void getSignalChoiceCount();
    static unsigned WINAPI threadGetSignalChoiceCount(LPVOID arg);

    void getMultiChoiceCount();
    static unsigned WINAPI threadGetMultiChoiceCount(LPVOID arg);

    //获取该份试卷的判断题的总数量
    void getJudgeChoiceCount();
    static unsigned WINAPI threadGetJudgeChoiceCount(LPVOID arg);

    //获取该份试卷的简答题题的总数量
    void getShortAnswerCount();
    static unsigned WINAPI threadGetShortAnswerCount(LPVOID arg);

    void startCountdown(int totalMinutes); //进行开始执行倒计时的函数
    void updateCountdown();

    void showMenueBtn(int Count);
    void showMultiMenueBtn(int Count);
    void showJudgeMenueBtn(int Count);
    void showSHortAnswerBtn(int Count);


     void showSignalChoice(QVector<QVector<QString>>* ret);
     void showMultiChoice(QVector<QVector<QString>>* ret);
     void showJudgeChoice(QVector<QVector<QString>>* ret);
     void showShortAnswer(QVector<QVector<QString>>* ret);
    //获取当前题号的单选题的内容
    void getCurIndexSignalChoice();
    static unsigned WINAPI  threadGetCurIndexSignalChoice(LPVOID arg);

    //获取当前多选题的内容
    void getCurIndexMultiChoice();
    static unsigned WINAPI threadGetCurIndexMultiChoice(LPVOID arg);

    //获取当前判断题的内容
    void getCurIndexJudegChoice();
    static unsigned WINAPI threadGetCurIndexJudegChoice(LPVOID arg);

    //获取当前简答题的内容
    void getCurIndexShortAnswerChoice();
    static unsigned WINAPI threadGetCurIndexShortAnswerChoice(LPVOID arg);

    //进行动态调整，并且调整选项的位置
    void DynemicShowSignalChoice();

    //进行动态调整，并且调整多选的位置
    void DynemicShowMultiChoice();

    void DynemicShowJudgeChoice();

private:
     QTimer *timer = nullptr;
     int totalSeconds;
     QVector<QPushButton*> m_signalChoice;
     QVector<QPushButton*> m_multiChoice;
     QVector<QPushButton*> m_judgeChoice;
     QVector<QPushButton*> m_shortAnswerChoice;
     CExamContorller* m_contorller = nullptr;
     QString testPaperId; //记录正在考试的试卷的id。
     int signalChoiceCount;
     int multiChoiceCount;
     int judgeCount;
     int shortAnswerCount;
     int signalChoiceCurIndex; //当前单选题题号
     int multiChoiceCurIndex; //当前多选题题号
     int judgeChoiceCurIndex;
     int shortAnswerCurIndex;
private:
    Ui::CExamDlg *ui;
};

#endif // EXAMDLG_H
