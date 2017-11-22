#ifndef ADDGRADEWIN_H
#define ADDGRADEWIN_H

#include <QObject>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>



class addGradeWin :public QDialog
{
    Q_OBJECT
public:
    addGradeWin();
    ~addGradeWin();

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
    void addGrade_ok();
    void addGrade_ok(QString);

private slots:
    void exit();
    void sureClicked();
    void enableSureBtn();
    void disableSureBtn();
    void checkInfo();


public:
    void setSub(QString q);
    void showWin();

};

#endif // ADDGRADEWIN_H
