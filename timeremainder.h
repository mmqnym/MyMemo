#ifndef TIMEREMAINDER_H
#define TIMEREMAINDER_H

#include <QTime>
#include <QDate>
#include <QVector>
#include <QtMultimedia/QSound>
#include <QtAlgorithms>
#include "alert.h"
#include <QSound>

#define ALERM_NUMBER 12

class TimeRemainder
{
private:
    typedef struct aTimer
    {
        QDate dateInfo ;
        QTime timeInfo ;
        QString thing ;
        bool checked ;
    } aTimerRec ;

    int currentAlermIdx ;
    int prevPlayedIdx ;
    QSound *sound[ALERM_NUMBER] ;

    static bool comp(const aTimerRec &a, const aTimerRec &b) ;
    void playAlermChoose() ;
    void setSound() ;

public:
    TimeRemainder() ;
    int recSize() ;
    void init() ;
    void createTimer(QDate &dateInfo, QTime &timeInfo, QString &thing) ;
    void checkTime() ; // every 20 seconds check once
    void checkLose() ; // The time set for this thing has passed
    QVector<aTimerRec> timerRec ;
    void alermChoose(int idx) ;
    int getCurrentAlermIdx() ;
    void playAlermCurrentChoose(int idx) ;
    void stopPlayed() ;

};

#endif // TIMEREMAINDER_H

extern TimeRemainder timeRemainder ;
