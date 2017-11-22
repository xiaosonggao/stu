#ifndef ADDSTUW_H
#define ADDSTUW_H

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

class addStuWin :public QDialog{
    Q_OBJECT

public:
    addStuWin();
    ~addStuWin();

private:
    QLabel *name;
    QLineEdit *nameBox;
    QLabel *ID;
    QLineEdit *IDBox;
    QLabel *Dormitory;
    QLineEdit *DormitoryBox;
    QPushButton *sureBtn;
    QPushButton *quitBtn;
signals:
    void info_conf(); //信息填写完整信号
    void info_conf_no();//信息填写不完整信号
    void addStu_ok();

public slots:
    void addClicked(); //单击确认按钮
    void enableSureBtn();
    void disableSureBtn();
    void checkInfo(); //检查信息是否填写完整
    void showWin();

private :
    void checked();

};

#endif // ADDSTUW_H
