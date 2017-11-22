#ifndef MODIGRADEWIN_H
#define MODIGRADEWIN_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>

class modiGradeWin :public QDialog
{
    Q_OBJECT
public:
    modiGradeWin();
    ~modiGradeWin();
private:
    QLabel *subID;
    QLineEdit *subIDBox;
    QLabel *stuID;
    QLineEdit *stuIDBox;
    QLabel *ps;
    QLineEdit *psBox;
    QLabel *sy;
    QLineEdit *syBox;
    QLabel *jm;
    QLineEdit *jmBox;

    QPushButton *sureBtn;
    QPushButton *quitBtn;

signals:
    void info_conf();
    void info_conf_no();
    void modiGrade_ok();
    void modiGrade_ok(QString);

private slots:
    void sureClicked();
    void enableSureBtn();
    void disableSureBtn();
    void checkInfo();

public:
    void setInfo(QString sub, QString stu, QString p, QString s, QString j);

};

#endif // MODIGRADEWIN_H
