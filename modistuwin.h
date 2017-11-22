#ifndef MODISTUWIN_H
#define MODISTUWIN_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>

class QLabel;
class QWidget;
class QPushButton;
class QLineEdit;
class QDialog;

class modiStuWin :public QDialog{
    Q_OBJECT
public:
    modiStuWin();
    ~modiStuWin();

private:
    QLabel *name;
    QLineEdit *nameBox;
    QLabel *ID;
    QLineEdit *IDBox;
    QLabel *Dormitory;
    QLineEdit *DormitoryBox;
    QPushButton *sureBtn;
    QPushButton *quitBtn;
    QString oldID;

signals:
    void info_conf();
    void info_conf_no();
    void modiStu_ok();

public slots:
    void sureClicked();
    void enableSureBtn();
    void disableSureBtn();
    void checkInfo();

private:
    void check();

public:
    void setInfo(QString i, QString n, QString d);
};

#endif // MODISTUWIN_H
