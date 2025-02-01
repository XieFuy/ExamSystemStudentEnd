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
    void startWarning();
    void startShowShortAnswer(QString str);
public:
    QString classId;
    QString teacherId;
    QString startTime;
    QString endTime;
    QString longTime;
    QString studentName;
    QString studentId;
    QString multiAnswer; //用于存储多选题的选项
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

     void showWarningInfo(); //显示警告信息

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

    //点击下一题，进行显示下一题的单选题目
    void getNextSignalChoive();

    //点击下一题，显示下一题的多选题目
    void getNextMultiChoic();

    //点击下一题，进行显示下一题的判断题
    void getNextJudgeChoice();

    //点击下一题，进行显示下一题的简答题
    void getNextShortAnswerChoice();

    //点击上一题，进行显示上一题的单选题目
    void getLastSignalChoice();

    //点击上一题，显示上一题的多选题目
    void getLastMultiChoic();

    //点击上一题，进行显示上一题的判断题
    void getLastJudgeChoice();

    //点击上一题，进行显示上一题的简答题
    void getLastShortAnswerChoice();

    //禁止使用键盘
    static LRESULT CALLBACK HookProc(int nCode, WPARAM wParam, LPARAM lParam);

   //禁止切屏
    static LRESULT CALLBACK HookProcScreen(int nCode, WPARAM wParam, LPARAM lParam);

    //进行存储的是单选题的A选项
    void updateSignalAnswertoA(bool isChecked);
    static unsigned WINAPI threadUpdateSignalAnswertoA(LPVOID arg);
    void updateSignalAnswertoB(bool isChecked);
    static unsigned WINAPI threadUpdateSignalAnswertoB(LPVOID arg);
    void updateSignalAnswertoC(bool isChecked);
    static unsigned WINAPI threadUpdateSignalAnswertoC(LPVOID arg);
    void updateSignalAnswertoD(bool isChecked);
    static unsigned WINAPI threadUpdateSignalAnswertoD(LPVOID arg);

    //进行存储多选题的选项
    void updateMultiAnswerA(bool isChecked); //进行存储多选题的A答案
    void updateMultiAnswerB(bool isChecked);
    void updateMultiAnswerC(bool isChecked);
    void updateMultiAnswerD(bool isChecked);
    void updateMultiAnswerE(bool isChecked);
    void updateMultiAnswerF(bool isChecked);

    static unsigned WINAPI threadUpdateMultiAnswer(LPVOID arg);

    //进行存储判断题的答案
    void updateJudgeAnswerTrue(bool isChecked);
    static unsigned WINAPI threadUpdateJudgeAnswerTrue(LPVOID arg);

    void updateJudgeAnswerFalse(bool isChecked);
    static  unsigned WINAPI threadUpdateJudgeAnswerFalse(LPVOID arg);

    //进行存储简答题的答案
    void updateShortAnswer();
    static unsigned WINAPI threadUpdateShortAnswer(LPVOID arg);

    //清除单选题被选中的Ui
    void clearSignalOption();

    //清除多选题被选中的UI
    void clearMultiOption();

    //清除判断题选中的UI
    void clearJudgeOption();

    //清除简答题的中的答题答案
    void clearShortAnswerOption();

    //实现点击上一题或者下一题的时候进行回显该题的选项，如果为NULL则进行清空所有选项，有选项则进行回显
    void getSignalChoice();
    static unsigned WINAPI threadGetSignalChoice(LPVOID arg);

    //实现点击上一题或者下一题的时候进行回显学生选中的选项
    void getMultiChoice();
    static unsigned WINAPI threadGetMultiChoice(LPVOID arg);

    //实现点击上一题或者下一题的时候进行回显该题选项，如果为NULL则清空所有的选项，有则进行回显
    void getJudgeChoice();
    static unsigned WINAPI threadGetJudgeChoice(LPVOID arg);

    //实现点击上一题或者下一题的时候进行回显该题的作答过的答案
    void getShortAnswer();
    static unsigned WINAPI threadGetShortAnswer(LPVOID arg);

    //显示简答题的文本信息
    void showShortAnswerUI(QString str);
private:
     HANDLE m_mutex;
     static CExamDlg* m_thiz ;
     static HWND hwnd;
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
     static HHOOK g_hookHandle ;
private:
    Ui::CExamDlg *ui;
};

#endif // EXAMDLG_H
