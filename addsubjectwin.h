#ifndef ADDSUBJECTWIN_H
#define ADDSUBJECTWIN_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QDialog>
#include <QRadioButton>
class QLabel;
class QWidget;
class QPushButton;
class QLineEdit;
class QDialog;

class addSubjectWin :public QDialog{
    Q_OBJECT

public:
    addSubjectWin();
    ~addSubjectWin();

private:
    QLabel *sub_name;
    QLineEdit *nameBox;
    QLabel *ID;
    QLineEdit *IDBox;
    QLabel *teacher;
    QLineEdit *teacherBox;
    QLabel * score;
    QLineEdit *scoreBox;
    QRadioButton * syBtn;
    QPushButton *sureBtn;
    QPushButton *quitBtn;
    QLabel *information;
    QLabel *information2;


signals:
    void info_conf();
    void info_conf_no();
    void addSub_ok();

public slots:
    void addClicked();
    void enableSureBtn();
    void disableSureBtn();
    void checkInfo(); //检查信息是否填写完整
    void showWin();


};

#endif // ADDSUBJECTWIN_H
