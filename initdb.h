#ifndef INITDB_H
#define INITDB_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>
#include <qdebug.h>
#include <QtSql>

QSqlError insertStu(const QString ID, const QString name, const  QString dorm){
    QSqlQuery q;
    q.prepare("INSERT INTO student (ID, name, dormmm ) VALUES(:ID, :name, :dorm)");
    q.bindValue(":ID",ID);
    q.bindValue(":name",name);
    q.bindValue(":dorm",dorm);
    q.exec();
    qDebug()<<"insert"<<q.lastError();
    return q.lastError();
}

//QSqlError insertStu(const QString name, const QString id, const QString dorm ){
//    QSqlQuery q;
//    q.exec(QLatin1String("INSERT INTO STUDENT()"));

//}

QSqlError init(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(":memory:");
    db.open();
    if(!db.open()){
        return db.lastError();
    }
    QSqlQuery q;

    q.exec("CREATE TABLE student(ID STRING PRIMARY KEY, "
                             "name STRING, "
                             "dorm STRING);");
    q.exec("CREATE TABLE grade("
                             "sub_name STRING,"
                             "stu_id STRING,"
                             "stu_name STRING,"
                             "ps_s double,"
                             "sy_s double,"
                             "jm_s double,"
                             "zf_s double,"
                             "yd_score double,"
                             "PRIMARY KEY(sub_name, stu_id));");

    q.exec("CREATE TABLE subject(sub_id STRING PRIMARY KEY,"
                         "sub_name STRING,"
                         "teacher STRING,"
                         "xuefen INT,"
                         "sy_con bool);");

    q.exec("INSERT INTO subject VALUES('A2981','近代史','秦立海',4, 0 )");
    q.exec("INSERT INTO subject VALUES('A3310','计算机网络','陈鸣',4, 1)");
    q.exec("INSERT INTO subject VALUES('A3390','操作系统','马洪兵',4, 1)");
    q.exec("INSERT INTO subject VALUES('A3348','计算机组成原理','Daniel Liang', 6,1)");
    q.exec("INSERT INTO subject VALUES('A3319','数据结构','Satrtaj Sanhni',6,1)");
    q.exec("INSERT INTO subject VALUES('A9077','高等数学A','周芳', 6,1)");
    q.exec("INSERT INTO subject VALUES('A9032','概率论','王静', 6,0)");

    q.exec("INSERT INTO grade VALUES('近代史','20170308','张文红', 89, -1, 90, 89.7, 3.2)");
    q.exec("INSERT INTO grade VALUES('近代史','20170301','张豪',86,-1,80,81.8,3.2)");
    q.exec("INSERT INTO grade VALUES('操作系统','20170308','张文红',65,57,77,72.2,3)");
    q.exec("INSERT INTO grade VALUES('操作系统','20170301','张豪',97,87,90,90.6,4)");
    q.exec("INSERT INTO grade VALUES('高等数学A','20170301','张豪',100,82,98,95.9,6)");
    q.exec("INSERT INTO grade VALUES('高等数学A','20170302','陈能宽',94,80,87,87,4.8)");
    q.exec("INSERT INTO grade VALUES('高等数学A','20170303','刘兵',56,80,67,67.3,3.6)");
    q.exec("INSERT INTO grade VALUES('高等数学A','20170304','王晓明',44,70,60,59,0)");
    q.exec("INSERT INTO grade VALUES('概率论','20170301','张豪',99,-1,90,92.7,6)");
    q.exec("INSERT INTO grade VALUES('计算机网络','20170303','刘兵', 80, 82, 88, 87.4, 3.2)");
//    q.exec("INSERT INTO grade VALUES('高等数学A','20170305','孙兴',1,1,1,3,0.5)");
//    q.exec("INSERT INTO grade VALUES('高等数学A','20170306','杨雪',1,1,1,3,0.5)");
//    q.exec("INSERT INTO grade VALUES('高等数学A','20170307','赵一飞',1,1,1,3,0.5)");
//    q.exec("INSERT INTO grade VALUES('高等数学A','20170308','张文红',1,1,1,3,0.5)");

    q.exec("INSERT INTO student VALUES('20170301', '张豪', 'A1221')");
    q.exec("INSERT INTO student VALUES('20170302', '陈能宽', 'A1222')");
    q.exec("INSERT INTO student VALUES('20170303', '刘兵', 'A1223')");
    q.exec("INSERT INTO student VALUES('20170304', '王晓明', 'A1224 ')");
    q.exec("INSERT INTO student VALUES('20170305', '孙兴', 'A1227')");
    q.exec("INSERT INTO student VALUES('20170306', '杨雪', 'A1225')");
    q.exec("INSERT INTO student VALUES('20170307', '赵一飞', 'A1228')");
    q.exec("INSERT INTO student VALUES('20170308', '张文红', 'A1223')");

    return QSqlError();
}


#endif // INITDB_H
