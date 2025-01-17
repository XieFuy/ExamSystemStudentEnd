#ifndef INFOMATIONDLG_H
#define INFOMATIONDLG_H

#include <QDialog>
#include "examdlg.h"

namespace Ui {
class CInfoMationDlg;
}

class CInfoMationDlg : public QDialog  //进入考试提示对话框
{
    Q_OBJECT

public:
    explicit CInfoMationDlg(QWidget *parent = nullptr);
    ~CInfoMationDlg();
public:
    QString classId;
    QString teacherId;
    QString startTime;
    QString endTime;
    QString longTime;
    QString studentName;
    QString studentId;
signals:
    void returnToMainMenueDlg();
private:
   CExamDlg* m_examDlg = nullptr;
private:
    Ui::CInfoMationDlg *ui;
};

#endif // INFOMATIONDLG_H
