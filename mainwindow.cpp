#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <QItemSelectionModel>
#include "addstuwin.h"
#include "addsubjectwin.h"
#include  "initdb.h"
#include "modistuwin.h"
#include "addgradewin.h"
#include "modigradewin.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    stuLabel = new QLabel(tr("学生列表"));
    stuList = new QTableView;
    addStuBtn = new QPushButton(tr("添加"));
    modiStuBtn = new QPushButton(tr("修改"));
    delStuBtn = new QPushButton(tr("删除"));

    modiStuBtn->setEnabled(false);
    delStuBtn->setEnabled(false);

    subLabel = new QLabel(tr("课程列表"));
    subList = new QTableView;
    addSubBtn = new QPushButton(tr("添加课程"));

    gradeLabel = new QLabel(tr("课程成绩"));
    gradeList = new QTableView;
    addGradeBtn = new QPushButton(tr("添加成绩"));
    modiGradeBtn = new QPushButton(tr("修改成绩"));
    delGradeBtn = new QPushButton(tr("删除成绩"));
    showGradeBtn = new QPushButton(tr("返回"));


    quitBtn = new QPushButton(tr("退出"));
    /* search widget*/
    N_ID = new QLabel(tr("姓名/学号"));
    N_IDBox = new QLineEdit;
    N_IDBtn = new QPushButton(tr("搜索"));
    N_IDBtn->setDisabled(true);
    Dorm = new QLabel(tr("宿舍号  "));
    DormBox = new QLineEdit;
    DormBtn = new QPushButton(tr("搜索"));
    DormBtn->setDisabled(true);
    findGrade = new QLabel(tr("查找成绩"));
    findGradeBox = new QLineEdit();
    findGradeBox->setPlaceholderText(tr("输入学号查询成绩"));
    findGradeBtn = new QPushButton(tr("搜索"));
    findGradeBtn->setDisabled(true);

    //left bottom btn
    QHBoxLayout *LBBtnLayout = new QHBoxLayout;
    LBBtnLayout->addWidget(addStuBtn);
    LBBtnLayout->addWidget(modiStuBtn);
    LBBtnLayout->addWidget(delStuBtn);
    LBBtnLayout->setSpacing(delStuBtn->width()/9);

    //search layout
    QGridLayout *searchLayout = new QGridLayout;
    searchLayout->addWidget(N_ID,0,0,1,1,Qt::AlignCenter|Qt::AlignVCenter);
    searchLayout->addWidget(N_IDBox,0,1,1,2);
    searchLayout->addWidget(N_IDBtn,0,3,1,1);
    searchLayout->addWidget(Dorm,1,0,1,1,Qt::AlignCenter|Qt::AlignVCenter);
    searchLayout->addWidget(DormBox,1,1,1,2);
    searchLayout->addWidget(DormBtn,1,3,1,1);
    searchLayout->setRowMinimumHeight(0, 10);
    searchLayout->addWidget(findGrade,2,0,1,1,Qt::AlignCenter|Qt::AlignVCenter);
    searchLayout->addWidget(findGradeBox,2,1,1,2);
    searchLayout->addWidget(findGradeBtn,2,3,1,1);


    //学生信息
    QVBoxLayout *leftLayout = new QVBoxLayout;
    stuList->setFixedWidth(403);
    leftLayout->addWidget(stuLabel);
    leftLayout->addWidget(stuList);
    leftLayout->addLayout(LBBtnLayout);

    //sublayout
    QHBoxLayout *subLaLayout = new QHBoxLayout;
    subLaLayout->addWidget(subLabel);
    subLaLayout->addStretch();
    subLaLayout->addWidget(addSubBtn);

    QVBoxLayout *subLayout = new QVBoxLayout;
    subLayout->addLayout(subLaLayout);
    subLayout->addWidget(subList);
    //***sublayout

    //gradelayout
    QGridLayout *gradeBtn = new QGridLayout;
    gradeBtn->addWidget(addGradeBtn,0,0,1,1);
    gradeBtn->setColumnStretch(1,1);
    gradeBtn->addWidget(modiGradeBtn,0,2,1,1);
    gradeBtn->setColumnStretch(3,1);
    gradeBtn->addWidget(delGradeBtn,0,4,1,1);
    gradeBtn->setColumnStretch(5,1);
    gradeBtn->addWidget(showGradeBtn,0,6,1,1);

    QVBoxLayout *gradeLayout = new QVBoxLayout;
    gradeLayout->addWidget(gradeLabel);
    gradeLayout->addWidget(gradeList);
    gradeLayout->addLayout(gradeBtn);
    //*****gradelayout
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addLayout(subLayout);
    rightLayout->addLayout(gradeLayout);
    rightLayout->addLayout(searchLayout);
    //quit
    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addStretch();
    bottomLayout->addWidget(quitBtn);

    QHBoxLayout *upLayout = new QHBoxLayout;
    upLayout->addLayout(leftLayout);
    upLayout->addLayout(rightLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(upLayout);
    //mainLayout->addStretch();
    mainLayout->addSpacing(20);
    mainLayout->addLayout(bottomLayout);
    QWidget *mainWidget = new QWidget;
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
    setWindowTitle(tr("学生信息管理系统"));
    setMinimumSize(1060,700);

    /******************main_window design ends*****************/
    init();

    /*学生信息列表显示*/
    stu_model = new QSqlRelationalTableModel(this);
    newStuList();
    stuList->setAlternatingRowColors(true);
    stuList->show();
    QItemSelectionModel *stu_sel = stuList->selectionModel();

    /**********课程列表显示****/
    sub_model = new QSqlRelationalTableModel();
    newSubList();
    subList->setAlternatingRowColors(true);
    subList->show();
    QItemSelectionModel *sub_sel = subList->selectionModel();


    /******成绩列表显示grade*******/
    grade_model = new QSqlRelationalTableModel(this);
    newGradeList();
    grade_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    gradeList->setSortingEnabled(true);
    gradeList->setAlternatingRowColors(true);

    gradeList->show();


    QItemSelectionModel *grade_sel = gradeList->selectionModel();


 //*********************signals and slots************//
    connect(quitBtn, SIGNAL(clicked()),
            this, SLOT(exit()));

    connect(addStuBtn, SIGNAL(clicked()),
            this, SLOT(addStuent()));
    connect(addSubBtn,SIGNAL(clicked()),
            this, SLOT(addSubject()));
    connect(modiStuBtn,SIGNAL(clicked()),
            this, SLOT(modiStudent()));
    connect(delStuBtn, SIGNAL(clicked()),
            this, SLOT(delStudent()));
    connect(addGradeBtn, SIGNAL(clicked()),
            this, SLOT(addGrade()));
    connect(modiGradeBtn, SIGNAL(clicked()),
            this, SLOT(modiGrade()));
    connect(delGradeBtn, SIGNAL(clicked()),
            this, SLOT(delGrade()));

    connect(stu_sel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(select_stu()));
    connect(sub_sel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(select_sub()));
    connect(grade_sel, SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(select_grade()));

    connect(showGradeBtn, SIGNAL(clicked()),
            this, SLOT(newList()));
    //FIND
    connect(N_IDBtn,SIGNAL(clicked()),
            this, SLOT(find_id()));
    connect(DormBtn, SIGNAL(clicked()),
            this, SLOT(find_dorm()));
    connect(findGradeBtn,SIGNAL(clicked()),
            this, SLOT(find_grade()));
    connect(N_IDBox, SIGNAL(textChanged(QString)),
            this, SLOT(check_idBox()));
    connect(DormBox, SIGNAL(textChanged(QString)),
            this, SLOT(check_dormBox()));
    connect(findGradeBox,SIGNAL(textChanged(QString)),
            this, SLOT(check_gradeBox()));
    connect(this, SIGNAL(idBox_ok()),
            this, SLOT(enableIDBtn()));
    connect(this, SIGNAL(idBox_no()),
            this, SLOT(disableIDBtn()));
    connect(this, SIGNAL(dormBox_ok()),
            this, SLOT(enableDormBtn()));
    connect(this, SIGNAL(dormBox_no()),
            this, SLOT(disableDormBtn()));
    connect(this, SIGNAL(gradeBox_ok()),
            this,SLOT(enableGradeBtn()));
    connect(this,  SIGNAL(gradeBox_no()),
            this, SLOT(disableGradeBtn()));

}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::exit(){
    this->~MainWindow();
}

void MainWindow::addStuent(){
    addStuWin *addwin = new addStuWin;
    addwin->setModal(true);
    addwin->showWin();
    connect(addwin, SIGNAL(addStu_ok()),
            this, SLOT(newStuList()));
}

void MainWindow::addSubject(){
    addSubjectWin *addwin = new addSubjectWin;
    addwin->setModal(true);
    addwin->showWin();
    connect(addwin, SIGNAL(addSub_ok()),
            this, SLOT(newSubList()));
}

void MainWindow::addGrade(){
    addGradeWin *addwin = new addGradeWin;
    addwin->setModal(true);
    int r = subList->currentIndex().row();
    if(r != -1){
        QSqlRecord record = sub_model->record(r);
        QString id = record.value("sub_id").toString();
        addwin->setSub(id);
        connect(addwin,SIGNAL(addGrade_ok(QString)),
                this, SLOT(showSubGrade(QString)));
    }
    else
        connect(addwin, SIGNAL(addGrade_ok()),
                this, SLOT(newGradeList()));
    addwin->showWin();
}
void MainWindow::delGrade(){
    int r = gradeList->currentIndex().row();

    QString stu_id = grade_model->record(r).value("stu_id").toString();
    QString sub_name = grade_model->record(r).value("sub_name").toString();

    int ok = QMessageBox::warning(this, tr("删除此记录"), tr("确认删除此项成绩吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::Yes){
        QSqlQuery q;
        q.prepare("DELETE FROM grade WHERE sub_name = ? AND stu_id = ?");
        q.bindValue(0, sub_name);
        q.bindValue(1, stu_id);
        q.exec();
        int r = subList->currentIndex().row();
        if(r == -1) newGradeList();
        else showSubGrade(sub_name);
    }
}
void MainWindow::delStudent(){
    int r = stuList->currentIndex().row();
    QSqlRecord record = stu_model->record(r);
    QString stuId = record.value("ID").toString();

    int ok = QMessageBox::warning(this, tr(" 删除学生信息！"),
                                  tr("删除操作不可撤回，确定删除此学生吗？"),
                                  QMessageBox::Yes,QMessageBox::No);
    if(ok == QMessageBox::Yes){
        QSqlQuery q;
        q.prepare("DELETE FROM student WHERE ID = ?");
        q.bindValue(0,stuId);
        q.exec();
        q.prepare("DELETE FROM grade WHERE stu_id = ?");
        q.bindValue(0, stuId);
        q.exec();
        newStuList();
        if(subList->currentIndex().row()==-1)newGradeList();
        else select_sub();
    }
}

void MainWindow::modiStudent(){
    int curRow = stuList->currentIndex().row();
    QSqlRecord record = stu_model->record(curRow);
    QString stuId = record.value("ID").toString();
    QString name = record.value("name").toString();
    QString dorm = record.value("dorm").toString();

    modiStuWin *modiwin = new modiStuWin();
    modiwin->setModal(true);
    modiwin->setInfo(stuId, name, dorm);
    modiwin->show();
    connect(modiwin, SIGNAL(modiStu_ok()),
            this, SLOT(newStuList()));
    connect(modiwin, SIGNAL(modiStu_ok()),
            this,SLOT(newGradeList()));
}

void MainWindow:: modiGrade(){
    int r = gradeList->currentIndex().row();
    QSqlRecord record = grade_model->record(r);

    QString sub = record.value("sub_name").toString();
    QString stuid = record.value("stu_id").toString();
    QString ps = record.value("ps_s").toString();
    QString sy = record.value("sy_s").toString();
    QString jm = record.value("jm_s").toString();

    modiGradeWin *modiwin = new modiGradeWin;
    modiwin->setModal(true);
    modiwin->setInfo(sub, stuid, ps, sy, jm);
    modiwin->show();
    connect(modiwin, SIGNAL(modiGrade_ok()),
            this, SLOT(newGradeList()));
    if(subList->currentIndex().row()>=0)
        connect(modiwin, SIGNAL(modiGrade_ok(QString)),
                this, SLOT(showSubGrade(QString)));

}

void MainWindow::find_id(){
    QString stu = N_IDBox->text();

    QSqlQuery q;
    q.prepare("SELECT * FROM student WHERE ID = :id OR name = :name");
    q.bindValue(":id",stu);
    q.bindValue(":name", stu);
    q.exec();
    if(!q.first()){
        QMessageBox::warning(this, tr("!"), tr("未找到该学生信息！"));
    }
    else{
        showStuInfo(stu);
        N_IDBox->clear();
    }
}
void MainWindow::find_dorm(){
    QString d = DormBox->text();
    QSqlQuery q;
    q.prepare("SELECT * FROM student WHERE dorm = :d");
    q.bindValue(":d",d);
    q.exec();
    if(!q.first()){
        QMessageBox::warning(this, tr("!"), tr("未找到该宿舍信息！"));
    }
    else{
        showDormInfo(d);
        DormBox->clear();
    }
}
void MainWindow::find_grade(){
    QString id = findGradeBox->text();
    QSqlQuery q;
    q.prepare("SELECT * FROM grade WHERE stu_id = :id");
    q.bindValue(":id", id);
    q.exec();
    if(!q.first()){
        QMessageBox::warning(this, tr("!"), tr("未找到该学生成绩信息！"));
    }
    else{
        showStuGrade(id);
        findGradeBox->clear();
    }
}

void MainWindow:: select_stu(){
    modiStuBtn->setEnabled(true);
    delStuBtn->setEnabled(true);
}

void MainWindow::select_sub(){
    int r = subList->currentIndex().row();
    QSqlRecord record = sub_model->record(r);
    QString findid = record.value("sub_name").toString();
    showSubGrade(findid);
}

void MainWindow::select_grade(){
    modiGradeBtn->setEnabled(true);
    delGradeBtn->setEnabled(true);
}


void MainWindow::newStuList(){

    stu_model->setTable("student");
    stu_model->select();

    setStuList();
    stuList->show();

    modiStuBtn->setDisabled(true);
    delStuBtn->setDisabled(true);
}

void MainWindow::showStuInfo(QString stu){
    stu_model->setTable("student");
    stu_model->setFilter(tr("ID = '%1' OR name = '%2' ").arg(stu).arg(stu));
    stu_model->select();

    setStuList();
    stuList->show();

    modiStuBtn->setDisabled(true);
    delStuBtn->setDisabled(true);
}
void MainWindow::showDormInfo(QString dorm){
    stu_model->setTable("student");
    stu_model->setFilter(tr("dorm ='%1' ").arg(dorm));
    stu_model->select();

    setStuList();
    stuList->show();

    modiStuBtn->setDisabled(true);
    delStuBtn->setDisabled(true);
}
void MainWindow::newSubList(){
    sub_model->setTable("subject");
    sub_model->setHeaderData(0, Qt::Horizontal,tr("课程编号"));
    sub_model->setHeaderData(1, Qt::Horizontal,tr("课程名称"));
    sub_model->setHeaderData(2, Qt::Horizontal,tr("任课教师"));
    sub_model->setHeaderData(3, Qt::Horizontal,tr("课程学分"));
    sub_model->removeColumn(4);
    sub_model->select();
    subList->setModel(sub_model);

    for(int i = 0; i < 4; i++){
        subList->setColumnWidth(i,128);
        subList->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Fixed);
    }
    subList->setSelectionBehavior(QAbstractItemView::SelectRows);// 整行选中
    subList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为只读
    subList->verticalHeader()->hide();//隐藏列标题
    subList->show();
}

void MainWindow::showStuGrade(QString stu){
    grade_model->setTable("grade");
    grade_model->setFilter(tr("grade.stu_id = '%1' ").arg(stu));
    grade_model->select();
    setGradeList();

}
///*****************find****************///
void MainWindow::check_idBox(){
    QString s = N_IDBox->text();
    if(s.isEmpty()) emit idBox_no();
    else emit idBox_ok();
}
void MainWindow::check_dormBox(){
    QString s = DormBox->text();
    if(s.isEmpty()) emit dormBox_no();
    else emit dormBox_ok();
}
void MainWindow::check_gradeBox(){
    QString s = findGradeBox->text();
    if(s.isEmpty()) emit gradeBox_no();
    else emit gradeBox_ok();
}

void MainWindow::enableIDBtn(){
    N_IDBtn->setEnabled(true);
}
void MainWindow::disableIDBtn(){
    N_IDBtn->setDisabled(true);
}
void MainWindow::enableDormBtn(){
    DormBtn->setEnabled(true);
}
void MainWindow::disableDormBtn(){
    DormBtn->setDisabled(true);
}
void MainWindow::enableGradeBtn(){
    findGradeBtn->setEnabled(true);
}
void MainWindow::disableGradeBtn(){
    findGradeBtn->setDisabled(true);
}

///*****find function end**********///

void MainWindow::showSubGrade(QString sub){
    grade_model->setTable("grade");

    grade_model->setFilter(tr("grade.sub_name = '%1' ").arg(sub));
    grade_model->select();

    setGradeList();
    modiGradeBtn->setDisabled(true);
    delGradeBtn->setDisabled(true);
}

void MainWindow::newGradeList(){
    grade_model->setTable("grade");
    grade_model->select();

    setGradeList();
    modiGradeBtn->setDisabled(true);
    delGradeBtn->setDisabled(true);
}

void MainWindow:: setGradeList(){

    grade_model->setHeaderData(0, Qt::Horizontal,tr("课程"));
    grade_model->setHeaderData(1, Qt::Horizontal,tr("学号"));
    grade_model->setHeaderData(2, Qt::Horizontal,tr("姓名"));
    grade_model->setHeaderData(3, Qt::Horizontal,tr("平时成绩"));
    grade_model->setHeaderData(4, Qt::Horizontal,tr("实验成绩"));
    grade_model->setHeaderData(5, Qt::Horizontal,tr("考试成绩"));
    grade_model->setHeaderData(6, Qt::Horizontal,tr("总分"));
    grade_model->setHeaderData(7, Qt::Horizontal,tr("应得学分"));

    gradeList->setModel(grade_model);

    for(int i = 0; i < 3; i++){
        gradeList->setColumnWidth(i,97);
        gradeList->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Fixed);
    }
    for(int i = 3; i < 8; i++){
        gradeList->setColumnWidth(i,64);
        gradeList->horizontalHeader()->setSectionResizeMode(i,QHeaderView::Fixed);
    }
    gradeList->setSelectionBehavior(QAbstractItemView::SelectRows);// 整行选中
    gradeList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为只读
    gradeList->verticalHeader()->hide();//隐藏列标题
    gradeList->show();
}
void MainWindow::setStuList(){
    stu_model->QSqlQueryModel::setHeaderData(0,Qt::Horizontal,tr("学号"));
    stu_model->QSqlQueryModel::setHeaderData(1,Qt::Horizontal,QObject::tr("姓名"));
    stu_model->QSqlQueryModel::setHeaderData(2,Qt::Horizontal,QObject::tr("宿舍"));

    stuList->setModel(stu_model);
    stuList->resizeColumnsToContents();
    stuList->setColumnWidth(0,96);
    stuList->setColumnWidth(1,146);
    stuList->setColumnWidth(2,146);
    stuList->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Fixed);
    stuList->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Fixed);
    stuList->horizontalHeader()->setSectionResizeMode(2,QHeaderView::Fixed);

    stuList->setSelectionBehavior(QAbstractItemView::SelectRows);// 整行选中
    stuList->setEditTriggers(QAbstractItemView::NoEditTriggers);//设置为只读
    stuList->verticalHeader()->hide();//隐藏列标题
}

void MainWindow::newList(){
    newStuList();
    newSubList();
    newGradeList();
}
