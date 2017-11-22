#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QTableView>
#include <QPushButton>
#include <QLineEdit>
#include <QSqlRelationalTableModel>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    //
    QLabel *stuLabel;
    QTableView *stuList;
    QPushButton *addStuBtn;
    QPushButton *modiStuBtn;
    QPushButton *delStuBtn;


    QLabel *subLabel;
    QTableView *subList;
    QPushButton *addSubBtn;

    QLabel *gradeLabel;
    QTableView *gradeList;
    QPushButton *addGradeBtn;
    QPushButton *modiGradeBtn;
    QPushButton *delGradeBtn;
    QPushButton *showGradeBtn;  //返回按钮

    QPushButton *quitBtn;


    //查询
    QLabel *N_ID;
    QLabel *Dorm;
    QLabel *findGrade;
    QLineEdit *N_IDBox;
    QLineEdit *DormBox;
    QLineEdit *findGradeBox;
    QPushButton *N_IDBtn;
    QPushButton *DormBtn;
    QPushButton *findGradeBtn;

    QSqlRelationalTableModel *stu_model;
    QSqlRelationalTableModel *sub_model;
    QSqlRelationalTableModel *grade_model;

public slots:
    void exit();

    void delStudent();
    void modiStudent();
    void addStuent();
    void addSubject();
    void addGrade();
    void modiGrade();
    void delGrade();


    void newList();
    void newStuList();
    void newSubList();
    void newGradeList();
    void showSubGrade(QString sub);//显示课程成绩
    void showStuGrade(QString stu);
    void showStuInfo(QString stu); //显示学号、姓名查询结果
    void showDormInfo(QString dorm);//显示宿舍查询结果
    void setGradeList();
    void setStuList();

    void select_stu();
    void select_sub();
    void select_grade();

    //find
    void find_id();
    void find_dorm();
    void find_grade();
    void disableIDBtn();
    void enableIDBtn();
    void disableDormBtn();
    void enableDormBtn();
    void disableGradeBtn();
    void enableGradeBtn();
    void check_idBox();
    void check_dormBox();
    void check_gradeBox();
signals:
    void idBox_ok();
    void idBox_no();
    void dormBox_ok();
    void dormBox_no();
    void gradeBox_ok();
    void gradeBox_no();



};

#endif // MAINWINDOW_H
