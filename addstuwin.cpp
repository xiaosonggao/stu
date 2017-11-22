#include "addstuwin.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
addStuWin::addStuWin()
    :QDialog(0)
{
    name = new QLabel(tr("姓名"));
    nameBox = new QLineEdit;
    ID = new QLabel(tr("学号"));
    IDBox = new QLineEdit;
    Dormitory = new QLabel(tr("宿舍"));
    DormitoryBox = new QLineEdit;
    sureBtn = new QPushButton(tr("确认"));
    sureBtn->setDefault(true);
    sureBtn->setEnabled(false);
    quitBtn = new QPushButton(tr("取消"));

    QHBoxLayout *nameLayout = new QHBoxLayout;
    nameLayout->addWidget(name);
    nameLayout->addWidget(nameBox);
    QHBoxLayout *IDLayout = new QHBoxLayout;
    IDLayout->addWidget(ID);
    IDLayout->addWidget(IDBox);
    QHBoxLayout *DormLayout = new QHBoxLayout;
    DormLayout->addWidget(Dormitory);
    DormLayout->addWidget(DormitoryBox);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addSpacing(10);
    btnLayout->addWidget(sureBtn);
    btnLayout->addWidget(quitBtn);
    btnLayout->addSpacing(10);
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(50);
    mainLayout->addLayout(IDLayout);
    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(DormLayout);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);
    setFixedSize(sizeHint().width(), sizeHint().height());
    setWindowTitle(tr("添加学生信息"));

//*************layout set ends**************//

    connect(quitBtn,SIGNAL(clicked()),
            this, SLOT(close()));
    connect(sureBtn,SIGNAL(clicked()),
            this,SLOT(addClicked()));
    connect(this, SIGNAL(info_conf()),
            this, SLOT(enableSureBtn()));
    connect(this, SIGNAL(info_conf_no()),
            this, SLOT(disableSureBtn()));

//* box changed and  check box   *//
    connect(nameBox,SIGNAL(textChanged(QString)),
            this,SLOT(checkInfo()));
    connect(IDBox,SIGNAL(textChanged(QString)),
            this,SLOT(checkInfo()));
    connect(DormitoryBox ,SIGNAL(textChanged(QString)),
            this,SLOT(checkInfo()));
}

addStuWin:: ~addStuWin(){}

void addStuWin:: addClicked(){
    QString name = nameBox->text();
    QString id = IDBox->text();
    QString dorm = DormitoryBox->text();

    if(id.toInt()<10000000||id.toInt()>99999999){
        QMessageBox::information(this, tr("添加学生"),tr("请检查学号格式，学号为八位数字！"));
    }
    else{
        QSqlQuery q;
        q.prepare("INSERT INTO student(ID, name, dorm) VALUES (:ID, :name, :dorm)");
        q.bindValue(":ID",id);
        q.bindValue(":name", name);
        q.bindValue(":dorm", dorm);
        q.exec();

        if(q.lastError().databaseText() == "UNIQUE constraint failed: student.ID"){
            QMessageBox::information(this, tr("添加学生"),tr("添加失败，已存在该学号学生信息！"));
        }
        else{
            emit addStu_ok();
            this->close();
            QMessageBox::information(this, tr("添加学生"),tr("添加成功！"));
        }
    }
}

void addStuWin::enableSureBtn(){
    sureBtn->setEnabled(true);
}
void addStuWin::disableSureBtn(){
    sureBtn->setDisabled(true);
}

void addStuWin::checkInfo(){
    QString s1 = nameBox->text();
    QString s2 = IDBox->text();
    QString s3 = DormitoryBox->text();

    if((!s1.isEmpty())&&(!s2.isEmpty())&&(!s3.isEmpty()))  emit info_conf();
    else emit info_conf_no();
}
void addStuWin::showWin(){
    nameBox->clear();
    IDBox->clear();
    DormitoryBox->clear();
    sureBtn->setDisabled(true);
    show();
}
