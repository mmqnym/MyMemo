#include "timeremainder.h"

#define DEFAULT_SIZE 10
#define ALERM_RANGE_MAX 13 // include slient mode
#define ALERM_RANGE_MIN 1

TimeRemainder timeRemainder ;

TimeRemainder::TimeRemainder()
{
    prevPlayedIdx = currentAlermIdx ;
    sound[0] = new QSound(":/new/prefix1/media/alerm01.wav") ;
    sound[1] = new QSound(":/new/prefix1/media/alerm02.wav") ;
    sound[2] = new QSound(":/new/prefix1/media/alerm03.wav") ;
    sound[3] = new QSound(":/new/prefix1/media/alerm04.wav") ;
    sound[4] = new QSound(":/new/prefix1/media/alerm05.wav") ;
    sound[5] = new QSound(":/new/prefix1/media/alerm06.wav") ;
    sound[6] = new QSound(":/new/prefix1/media/alerm07.wav") ;
    sound[7] = new QSound(":/new/prefix1/media/alerm08.wav") ;
    sound[8] = new QSound(":/new/prefix1/media/alerm09.wav") ;
    sound[9] = new QSound(":/new/prefix1/media/alerm10.wav") ;
    sound[10] = new QSound(":/new/prefix1/media/alerm11.wav") ;
    sound[11] = new QSound(":/new/prefix1/media/alerm12.wav") ;


}

int TimeRemainder::recSize()
{
    return timerRec.size() ;
}

void TimeRemainder::init()
{
    timerRec.reserve(DEFAULT_SIZE) ;
}

void TimeRemainder::stopPlayed()
{
    sound[currentAlermIdx]->stop() ;
}

void TimeRemainder::alermChoose(int idx)
{
    if (idx+1 >= ALERM_RANGE_MIN && idx+1 <= ALERM_RANGE_MAX)
        currentAlermIdx = idx ;
    else
        currentAlermIdx = 0 ;
}

bool TimeRemainder::comp(const aTimerRec &a, const aTimerRec &b)
{
    QDateTime recordDateTime_A ;
    recordDateTime_A.setDate(a.dateInfo) ;
    recordDateTime_A.setTime(a.timeInfo) ;

    QDateTime recordDateTime_B ;
    recordDateTime_B.setDate(b.dateInfo) ;
    recordDateTime_B.setTime(b.timeInfo) ;

    if (recordDateTime_A <= recordDateTime_B)
        return true ;
    else
        return false ;
}

void TimeRemainder::createTimer(QDate &dateInfo, QTime &timeInfo, QString &thing)
{
    aTimerRec temp ;
    temp.dateInfo = dateInfo ;
    temp.timeInfo = timeInfo ;
    temp.thing = thing ;
    temp.checked = false ;
    timerRec.append(temp) ;
    std::sort(timerRec.begin(), timerRec.end(), comp) ;

}

void TimeRemainder::playAlermChoose()
{

    switch (currentAlermIdx + 1)
    {
        case 1:
            sound[0]->play() ;
            break ;

        case 2:
            sound[1]->play() ;
            break ;

        case 3:
            sound[2]->play() ;
            break ;

        case 4:
            sound[3]->play() ;
            break ;

        case 5:
            sound[4]->play() ;
            break ;

        case 6:
            sound[5]->play() ;
            break ;

        case 7:
            sound[6]->play() ;
            break ;

        case 8:
            sound[7]->play() ;
            break ;

        case 9:
            sound[8]->play() ;
            break ;

        case 10:
            sound[9]->play() ;
            break ;

        case 11:
            sound[10]->play() ;
            break ;

        case 12:
            sound[11]->play() ;
            break ;

        case 13:
            break ;

        default:
            sound[0]->play() ;
            break ;
    }

}

void TimeRemainder::playAlermCurrentChoose(int idx)
{
    if (prevPlayedIdx != 12) // not silent mode
        sound[prevPlayedIdx]->stop() ;

    switch (idx + 1)
    {
        case 1:
            sound[0]->play() ;
            prevPlayedIdx = 0 ;
            break ;

        case 2:
            sound[1]->play() ;
            prevPlayedIdx = 1 ;
            break ;

        case 3:
            sound[2]->play() ;
            prevPlayedIdx = 2 ;
            break ;

        case 4:
            sound[3]->play() ;
            prevPlayedIdx = 3 ;
            break ;

        case 5:
            sound[4]->play() ;
            prevPlayedIdx = 4 ;
            break ;

        case 6:
            sound[5]->play() ;
            prevPlayedIdx = 5 ;
            break ;

        case 7:
            sound[6]->play() ;
            prevPlayedIdx = 6 ;
            break ;

        case 8:
            sound[7]->play() ;
            prevPlayedIdx = 7 ;
            break ;

        case 9:
            sound[8]->play() ;
            prevPlayedIdx = 8 ;
            break ;

        case 10:
            sound[9]->play() ;
            prevPlayedIdx = 9 ;
            break ;

        case 11:
            sound[10]->play() ;
            prevPlayedIdx = 10 ;
            break ;

        case 12:
            sound[11]->play() ;
            prevPlayedIdx = 11 ;
            break ;

        case 13:
            prevPlayedIdx = 12 ;
            break ;

        default:
            sound[0]->play() ;
            prevPlayedIdx = 0 ;
            break ;
    }

}

void TimeRemainder::checkTime()
{
    QTime currentTime = QTime::currentTime() ;
    QDate currentDate = QDate::currentDate() ;

    for (int i = 0; i < timerRec.size(); i++)
    {

        if (!timerRec.at(i).checked
            && currentDate == timerRec.at(i).dateInfo
            && currentTime.hour() == timerRec.at(i).timeInfo.hour()
            && currentTime.minute() == timerRec.at(i).timeInfo.minute())
        {
            playAlermChoose() ;

            Alert window ;

            QString msg = QStringLiteral("´£¿ô±z:") + timerRec[i].thing ;
            window.setErrMsg(msg, 0) ;
            window.setModal(true) ;
            window.exec() ;

            if (currentAlermIdx < 12)
                stopPlayed() ; // if alert is checked, stop music
            timerRec[i].checked = true ;
            timerRec.remove(i) ;
        }
        else
            break ;


    }
}

int TimeRemainder::getCurrentAlermIdx()
{
    return timeRemainder.currentAlermIdx ;
}

void TimeRemainder::checkLose() // when open app, do this once
{
    QTime currentTime = QTime::currentTime() ;
    QDate currentDate = QDate::currentDate() ;

    for (int i = 0; i < timerRec.size(); i++)
    {
        QDate recordDate = timerRec.at(i).dateInfo ;
        QTime recordTime = timerRec.at(i).timeInfo ;

        if (recordDate <= currentDate
            && recordTime < currentTime )
        {
            // delete passed thing record
            timerRec.erase(timerRec.begin() + i) ;
        }
    }
}
