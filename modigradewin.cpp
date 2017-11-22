#include "modigradewin.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QDebug>
#include <QDialog>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

modiGradeWin::modiGradeWin():QDialog(0)
{

    subID= new QLabel(tr("课程名称"));
    subIDBox = new QLineEdit;
    stuID = new QLabel(tr("考生学号"));
    stuIDBox = new QLineEdit;
    ps = new QLabel(tr("平时成绩"));
    psBox = new QLineEdit();
    sy = new QLabel(tr("实验成绩"));
    syBox = new QLineEdit;
    jm = new QLabel(tr("卷面成绩"));
    jmBox = new QLineEdit;

    sureBtn = new QPushButton(tr("确定"));
    sureBtn->setDisabled(true);
    quitBtn = new QPushButton(tr("取消"));

    QHBoxLayout *subLayout = new QHBoxLayout;
    subLayout->addWidget(subID);
    subLayout->addWidget(subIDBox);

    QHBoxLayout *stuLayout = new QHBoxLayout;
    stuLayout->addWidget(stuID);
    stuLayout->addWidget(stuIDBox);

    QHBoxLayout *psLayout = new QHBoxLayout;
    psLayout->addWidget(ps);
    psLayout->addWidget(psBox);

    QHBoxLayout *syLayout = new QHBoxLayout;
    syLayout->addWidget(sy);
    syLayout->addWidget(syBox);

    QHBoxLayout *jmLayout = new QHBoxLayout;
    jmLayout->addWidget(jm);
    jmLayout->addWidget(jmBox);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(sureBtn);
    btnLayout->addStretch();
    btnLayout->addWidget(quitBtn);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(30);
    mainLayout->addLayout(subLayout);
    mainLayout->addLayout(stuLayout);
    mainLayout->addLayout(psLayout);
    mainLayout->addLayout(syLayout);
    mainLayout->addLayout(jmLayout);
    mainLayout->addLayout(btnLayout);

    setLayout(mainLayout);
    setFixedSize(sizeHint().width(), sizeHint().height());
    setWindowTitle(tr("添加成绩"));

//*****layoout ends **********//
    connect(quitBtn, SIGNAL(clicked()),
            this, SLOT(close()));
    connect(sureBtn, SIGNAL(clicked()),
            this, SLOT(sureClicked()));
    connect(this, SIGNAL(info_conf()),
            this, SLOT(enableSureBtn()));
    connect(this, SIGNAL(info_conf_no()),
            this, SLOT(enableSureBtn()));

    connect(subIDBox, SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
    connect(stuIDBox, SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
    connect(psBox, SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
    connect(syBox, SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
    connect(jmBox, SIGNAL(textChanged(QString)),
            this, SLOT(checkInfo()));
}
modiGradeWin::~modiGradeWin(){}

void modiGradeWin:: sureClicked(){
    QString sub = subIDBox->text();//课程名称
    QString stu = stuIDBox->text();

    double ps = psBox->text().toDouble();
    double sy = syBox->text().toDouble();
    double jm = jmBox->text().toDouble();

    if((ps == 0.0 && psBox->text()!='0')){
        QMessageBox::information(this, tr("添加成绩"), tr("成绩存在非法输入"));
    }
    else if((sy == 0.0 &&syBox->text()!='0')){
        QMessageBox::information(this, tr("添加成绩"), tr("成绩存在非法输入"));
    }
    else if((sy == 0.0 && syBox->text()!='0')){
        QMessageBox::information(this, tr("添加成绩"), tr("成绩存在非法输入"));
    }
    else if(!((ps>=0&&ps<=100)&&(jm>=0&&jm<=100)&&
        ((sy>=0&&sy<=100)||sy == -1))){
        QMessageBox::information(this, tr("添加成绩"), tr("所有成绩必须介于0到100之间"));
    }
    else{
        QSqlQuery q;
        q.prepare("SELECT xuefen FROM subject WHERE sub_name = :sub");
        q.bindValue(":sub", sub);
        q.exec();
        q.first();
        int t = q.value(0).toInt(); //课程总学分
        double xf;//所得学分

        QSqlQuery q1;
        q1.prepare("SELECT sy_con FROM subject WHERE sub_name = :sub");
        q1.bindValue(":sub", sub);
        q1.exec();
        q1.first();

        int sy_exist = q.value(0).toInt();
        if(sy_exist == 1 && sy == -1){
            QMessageBox::information(this, tr("添加成绩"), tr("该课程包含实验，请正确填写实验成绩"));
        }
        else{
            if(sy_exist == 0 && sy != -1){
                QMessageBox::information(this, tr("添加成绩"), tr("该课程不包含实验，实验成绩填写无效"));
                sy = -1;
            }

            double zf = 0.0;//总分数
            if(sy == -1) zf = ps*0.3 + jm*0.7;
            else zf = ps*0.15 + sy*0.15 + jm*0.7;

            if(zf < 60)  xf = 0.0;
            else if(zf < 70) xf = t*0.6;
            else if(zf < 80) xf = t*0.75;
            else if(zf < 90) xf = t*0.8;
            else xf = t*1.0;

            q.prepare("UPDATE grade SET ps_s = ?, sy_s = ?, jm_s = ?, zf_s = ?, yd_score = ?"
                      "WHERE sub_name = ? AND stu_id = ?");
            q.bindValue(0, ps);
            q.bindValue(1, sy);
            q.bindValue(2, jm);
            q.bindValue(3, zf);
            q.bindValue(4, xf);
            q.bindValue(5, sub);
            q.bindValue(6, stu);
            q.exec();
            emit modiGrade_ok();
            emit modiGrade_ok(sub);
            this->close();
        }
    }
}

void modiGradeWin:: enableSureBtn(){
    sureBtn->setEnabled(true);
}
void modiGradeWin::disableSureBtn(){
    sureBtn->setDisabled(true);
}
void modiGradeWin:: checkInfo(){
    QString q1 = subIDBox->text();
    QString q2 = stuIDBox->text();
    QString q3 = psBox->text();
    QString q4 = syBox->text();
    QString q5 = jmBox->text();

    if((!q1.isEmpty())&&(!q2.isEmpty())&&
       (!q3.isEmpty())&&(!q4.isEmpty())&&
       (!q5.isEmpty()))  emit info_conf();
    else emit info_conf_no();

}
void modiGradeWin:: setInfo(QString subname, QString stu, QString p, QString s, QString j){
    subIDBox->setText(subname);
    subIDBox->setDisabled(true);
    stuIDBox->setText(stu);
    stuIDBox->setDisabled(true);
    psBox->setText(p);
    syBox->setText(s);
    jmBox->setText(j);
}








