#include "addsubjectwin.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QDialog>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

addSubjectWin::addSubjectWin()
{
    sub_name = new QLabel(tr("课程名称"));
    nameBox = new QLineEdit();

    ID = new QLabel(tr("课程编号"));
    IDBox = new QLineEdit();

    teacher = new QLabel(tr("任课教师"));
    teacherBox = new QLineEdit();

    score = new QLabel(tr("学    分"));
    scoreBox = new QLineEdit();

    syBtn = new QRadioButton(tr("课程包含实验"));

    information = new QLabel(tr("**课程信息一经添加不可修改！"));
    information2 = new QLabel(tr("**请认真进行填写！"));

    sureBtn = new QPushButton(tr("确认"));
    quitBtn = new QPushButton(tr("取消"));

    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(sub_name);
    nameLayout->addWidget(nameBox);
    QHBoxLayout *IDLayout = new QHBoxLayout;
    IDLayout->addWidget(ID);
    IDLayout->addWidget(IDBox);
    QHBoxLayout *teacherLayout = new QHBoxLayout;
    teacherLayout->addWidget(teacher);
    teacherLayout->addWidget(teacherBox);
    QHBoxLayout *scoreLayout = new QHBoxLayout;
    scoreLayout->addWidget(score);
    scoreLayout->addWidget(scoreBox);

    QHBoxLayout *syLayout = new QHBoxLayout;
    syLayout->addWidget(syBtn);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addSpacing(10);
    btnLayout->addWidget(sureBtn);
    btnLayout->addWidget(quitBtn);
    btnLayout->addSpacing(10);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    //mainLayout->setSpacing(50);
    mainLayout->addLayout(IDLayout);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(nameLayout);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(teacherLayout);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(scoreLayout);
    mainLayout->addSpacing(30);
    mainLayout->addLayout(syLayout);
    mainLayout->addSpacing(10);
    mainLayout->addWidget(information);
    mainLayout->addWidget(information2);
    mainLayout->addSpacing(10);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);
    setFixedSize(sizeHint().width()+50, sizeHint().height());
    setWindowTitle(tr("添加课程"));

//*************layout set ends**************//
    connect(quitBtn,SIGNAL(clicked()),
            this,SLOT(close()));
    connect(sureBtn, SIGNAL(clicked()),
            this, SLOT(addClicked()));
    connect(this, SIGNAL(info_conf()),
            this,SLOT(enableSureBtn()));
    connect(this, SIGNAL(info_conf_no()),
            this, SLOT(disableSureBtn()));

    connect(nameBox,SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
    connect(IDBox,SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
    connect(teacherBox,SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
    connect(scoreBox,SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
}


addSubjectWin:: ~addSubjectWin(){}
void addSubjectWin::addClicked(){
    QString name = nameBox->text();
    QString id = IDBox->text();
    QString teacher = teacherBox->text();
    int score = scoreBox->text().toInt();
    bool check = syBtn->isChecked();
    int sy;
    if(check == true) sy = 1;
    else sy = 0;

    if(score == 0){
        QMessageBox::information(this, tr("添加课程"), tr("课程学分不得为零！"));
    }
    else{

        QSqlQuery q;
        q.prepare("INSERT INTO subject(sub_id, sub_name, teacher, xuefen, sy)"
                  "VALUES (:id, :name, :teacher, :xuefen, :sy)");
        q.bindValue(":name", name);
        q.bindValue(":id", id);
        q.bindValue(":teacher", teacher);
        q.bindValue(":xuefen", score);
        q.bindValue(":sy", sy);
        q.exec();
        if(q.lastError().databaseText() =="UNIQUE constraint failed: subject.sub_id" ){
            QMessageBox::information(this, tr("添加课程"), tr("添加失败，已存在该课程编号的信息！"));
        }
        else{
            this->close();
            emit addSub_ok();
            QMessageBox::information(this, tr("添加课程"), tr("添加成功！"));
        }
    }
}

void addSubjectWin::enableSureBtn(){
    sureBtn->setEnabled(true);
}
void addSubjectWin::disableSureBtn(){
    sureBtn->setDisabled(true);
}
void addSubjectWin::checkInfo(){
    QString s1 = nameBox->text();
    QString s2 = IDBox->text();
    QString s3 = teacherBox->text();
    QString s4 = scoreBox->text();
    if((!s1.isEmpty())&&(!s2.isEmpty())&&(!s3.isEmpty())&&(!s4.isEmpty()))  emit info_conf();
    else emit info_conf_no();
}

void addSubjectWin::showWin(){
    nameBox->clear();
    IDBox->clear();
    teacherBox->clear();
    scoreBox->clear();
    sureBtn->setDisabled(true);
    show();
}



