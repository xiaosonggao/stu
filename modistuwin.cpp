#include "modistuwin.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>


modiStuWin::modiStuWin()
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
    QHBoxLayout *dormLayout = new QHBoxLayout;
    dormLayout->addWidget(Dormitory);
    dormLayout->addWidget(DormitoryBox);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addSpacing(10);
    btnLayout->addWidget(sureBtn);
    btnLayout->addWidget(quitBtn);
    btnLayout->addSpacing(10);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(50);
    mainLayout->addLayout(IDLayout);
    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(dormLayout);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);
    setFixedSize(sizeHint().width(), sizeHint().height());
    setWindowTitle(tr("修改学生信息"));

//*************layout set ends**************//

    connect(quitBtn, SIGNAL(clicked()),
            this, SLOT(close()));
    connect(sureBtn, SIGNAL(clicked()),
            this, SLOT(sureClicked()));
    connect(this, SIGNAL(info_conf()),
            this, SLOT(enableSureBtn()));
    connect(this, SIGNAL(info_conf_no()),
            this, SLOT(disableSureBtn()));

//****CHECK BOX*****/
    connect(nameBox, SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
    connect(IDBox, SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
    connect(DormitoryBox, SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
}

modiStuWin:: ~modiStuWin(){

}

void modiStuWin:: sureClicked(){
    QString name = nameBox->text();
    QString id = IDBox->text();
    QString dorm = DormitoryBox->text();

    QSqlQuery q;
    //更新信息表
    q.prepare("UPDATE student SET ID = ?, name = ?, dorm = ?"
           "WHERE ID = ?");
    q.bindValue(0, id);
    q.bindValue(1, name);
    q.bindValue(2, dorm);
    q.bindValue(3, this->oldID);
    q.exec();

    if(id.toInt()<10000000||id.toInt()>99999999){
        QMessageBox::information(this, tr("添加学生"),tr("请检查学号格式，学号为八位数字！"));
    }

    else if(q.lastError().databaseText() == "UNIQUE constraint failed: student.ID"){
        QMessageBox::information(this, tr("修改信息"),tr("修改失败，已存在该学号学生信息！"));
    }
    else{
        /********更新成绩表********/
        q.prepare("UPDATE grade SET stu_id = ?"
                  "WHERE stu_id = ?");
        q.bindValue(0, id);
        q.bindValue(1, this->oldID);
        q.exec();

        emit modiStu_ok();
        this->close();
        QMessageBox::information(this, tr("修改学生信息"), tr("修改成功"));
    }
}

void modiStuWin:: enableSureBtn(){
    sureBtn->setEnabled(true);
}
void modiStuWin::disableSureBtn(){
    sureBtn->setDisabled(true);
}

void modiStuWin::checkInfo(){
    QString q1 = nameBox->text();
    QString q2 = IDBox->text();
    QString q3 = DormitoryBox->text();

    if((!q1.isEmpty())&&(!q2.isEmpty())&&(!q3.isEmpty())) emit info_conf();
    else emit info_conf_no();
}

void modiStuWin:: setInfo(QString i, QString n, QString d){
    nameBox->setText(n);
    IDBox->setText(i);
    DormitoryBox->setText(d);
    oldID = i;
}
