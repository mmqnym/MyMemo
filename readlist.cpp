#include "readlist.h"
#include "ui_readlist.h"
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include "Records.h"
#include "alert.h"
#include "timeremainder.h"

ReadList::ReadList()
{}

ReadList::~ReadList()
{}

void ReadList::readF()
{
    QFile *file = new QFile ;
    QFile *expand = new QFile ;
    QFile *timer = new QFile ;

    file->setFileName("./notes/record.bin") ;
    expand->setFileName("./notes/expand.bin") ;
    timer->setFileName("./notes/timer.bin") ;

    bool ok = file->open(QIODevice::ReadOnly) ;
    bool ok2 = expand->open(QIODevice::ReadOnly) ;
    bool ok3 = timer->open(QIODevice::ReadOnly) ;

    if(ok)
    {
        QString temp ;
        QTextStream in(file) ;
        temp = in.readAll() ;
        QList<QString> data = temp.split(",") ;

        importData(data) ;

        file->close() ;
        delete file ;
    }
    else
    {
        Alert errMsg ;
        errMsg.setWindowTitle("Error!") ;
        errMsg.setModal(true) ;
        QString msg = "Error:(0x01) missing record.bin, can not load file." ;
        errMsg.setErrMsg(msg, 0) ;
        errMsg.exec() ;
    }

    if(ok2)
    {
        QString temp ;
        QTextStream in(expand) ;
        temp = in.readAll() ;

        QList<QString> data = temp.split("\n") ;

        setExpand(data) ;

        expand->close() ;
        delete expand ;
    }
    else
    {
        Alert errMsg ;
        errMsg.setWindowTitle("Error!") ;
        errMsg.setModal(true) ;
        QString msg = "Error:(0x04) missing expand.bin, can not load file." ;
        errMsg.setErrMsg(msg, 0) ;
        errMsg.exec() ;
    }

    if (ok3)
    {
        QString temp ;
        QTextStream in(timer) ;
        temp = in.readAll() ;

        QList<QString> data = temp.split(",") ;

        setTimer(data) ;

        timer->close() ;
        delete timer ;

    }
    else
    {
        Alert errMsg ;
        errMsg.setWindowTitle("Error!") ;
        errMsg.setModal(true) ;
        QString msg = "Error:(0x05) missing timer.bin, can not load file." ;
        errMsg.setErrMsg(msg, 0) ;
        errMsg.exec() ;
    }
}

void ReadList::importData(QList<QString> &data)
{
    int file_idx = 0 ;
    for (int i = 0; i < data.size()/3; i++)
    {
        int j = 0 ;
        j++ ;

        QString temp = data[file_idx] ;
        int t_priority = temp.toInt() ;

        j++ ;
        file_idx++ ;
        temp = data[file_idx] ;
        QString t_thing = temp ;

        j++ ;
        file_idx++ ;
        temp = data[file_idx] ;
        QString t_deadline = temp ;
        QString t_expand = "" ;

        g_records.add(t_thing, t_priority, t_deadline, t_expand) ;

        file_idx++ ;
    }

}

void ReadList::setExpand(QList<QString> &data)
{

    for (int i = 0; i < data.size() - 1; i++ )
    {
        int idx = data[i].toInt() ;
        i++ ;

        QString addExpand = data[i] ;

        g_records.recs[idx].expand = addExpand ;
    }
}

void ReadList::setTimer(QList<QString> &data)
{
    for (int i = 0; i < data.size()-1; i++ )
    {
        QString thing = data[i] ;
        i++ ;

        QString date_str = data[i] ;
        QDate date = QDate::fromString(date_str, "yyyy-MM-dd") ;
        i++ ;

        QString time_str = data[i] ;
        QTime time = QTime::fromString(time_str, "hh:mm") ;

        timeRemainder.createTimer(date, time, thing) ;
    }

    timeRemainder.checkLose() ;
}

