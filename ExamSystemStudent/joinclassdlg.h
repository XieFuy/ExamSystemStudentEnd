#ifndef JOINCLASSDLG_H
#define JOINCLASSDLG_H

#include <QDialog>
#include<windows.h>
#include"DBHelper.h"
#include<memory>
#include<QDebug>
#include<QMessageBox>

namespace Ui {
class CJoinClassDlg;
}

class CJoinClassDlg : public QDialog
{
    Q_OBJECT

public:
    explicit CJoinClassDlg(QWidget *parent = nullptr);
    ~CJoinClassDlg();
    void setAcount(QString acount);
    void setStudentName(QString);
signals:
    void startShowClass(QVector<QVector<QString>>* result);
private:
    //进行查询获取到职工号的所有课程名称
    QVector<QVector<QString>>* getClassByTeacherId(QString teacherId);
    static unsigned WINAPI threadGetClassByTeacherId(LPVOID arg);

    void showClass(QVector<QVector<QString>>* result);

    void addRequestJoinClass(QString teacherId,QString className,QString studentName,QString StudentId);
    static unsigned WINAPI threadAddRequestJoinClass(LPVOID arg);

private:
    QString acount;
    QString studentName;
private:
    Ui::CJoinClassDlg *ui;
};

#endif // JOINCLASSDLG_H
