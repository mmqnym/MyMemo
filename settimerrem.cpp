#include "settimerrem.h"
#include "ui_settimerrem.h"
#include <QTextCharFormat>
#include "customcalendarwidget.h"
#include <QProcess>
#include <QLineEdit>
#include <QToolButton>
#include <QFile>
#include <QTime>
#include <QDate>
#include "Records.h"
#include "timeremainder.h"


SetTimerRem::SetTimerRem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SetTimerRem)
{
    QFile qss(":/new/prefix2/calendar.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    ui->setupUi(this);

    setWindowFlags(Qt::Window|Qt::FramelessWindowHint|
                     Qt::WindowStaysOnTopHint) ;
    this->setWindowOpacity(0.9);

    ui->switch_sup->setStyleSheet("QLabel:hover{background-color: rgb(0, 0, 0, 30%);}") ;

    ui->yes->setStyleSheet("QPushButton{background-color: rgb(127, 127, 127, 0%); border:none;}"
                                    "QPushButton:hover{background-color: rgb(0, 0, 0, 50%); color: rgb(255, 255, 255);}") ;

    ui->cancel->setStyleSheet("QPushButton{background-color: rgb(127, 127, 127, 0%);border:none;}"
                                    "QPushButton:hover{background-color: rgb(0, 0, 0, 50%); color: rgb(255, 255, 255);}") ;

    QProcess::startDetached("hwclock -w") ; // get local host time
    ui->dateEdit->setMinimumDate(QDate::currentDate()) ;
    ui->dateEdit->setCalendarPopup(true) ;
    QString year = QStringLiteral("年") ;
    QString month = QStringLiteral("月") ;
    QString day = QStringLiteral("日") ;
    ui->dateEdit->setDisplayFormat("yyyy" + year + "M" + month + "dd" + day + " " + "ddd") ;
    ui->timeEdit->setTime(QTime::currentTime()) ;
    ui->timeEdit->setButtonSymbols(QAbstractSpinBox::NoButtons) ;
    ui->timeEdit->hide() ;

    ui->sup_View->setButtonSymbols(QAbstractSpinBox::NoButtons) ;
    ui->sup_View->setTime(QTime::currentTime()) ;
    ui->sup_View->setReadOnly(true) ;

    QString space = QStringLiteral(" ") ;
    ui->sup_View->setDisplayFormat(" a hh:mm") ;

    QLineEdit* lEdit = ui->dateEdit->findChild<QLineEdit *>() ;
    lEdit->setReadOnly(true) ;


    // change calendar style
    CustomCalendarWidget *myCalendarWidget = new CustomCalendarWidget ;

    myCalendarWidget->setMinimumSize(330,330) ;
    myCalendarWidget->setBaseSize(330,330) ;
    myCalendarWidget->setMaximumSize(330,330) ;
    QTextCharFormat f = myCalendarWidget->weekdayTextFormat(Qt::Monday) ;
    f.setForeground( QBrush(QColor("#00b7ff")) );
    QTextCharFormat weekdays = f ;
    myCalendarWidget->setWeekdayTextFormat(Qt::Sunday,weekdays) ;
    myCalendarWidget->setWeekdayTextFormat(Qt::Saturday,weekdays) ;
    myCalendarWidget->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader) ;

    ui->dateEdit->setCalendarWidget(myCalendarWidget) ;

    QToolButton *prevBtn = myCalendarWidget->findChild<QToolButton*>(QLatin1String("qt_calendar_prevmonth")) ;
    QToolButton *bextBtn = myCalendarWidget->findChild<QToolButton*>(QLatin1String("qt_calendar_nextmonth")) ;

    prevBtn->setIcon(QIcon(":/new/prefix2/gp_source/previous.png")) ;
    prevBtn->setIconSize(QSize(30, 30)) ;

    bextBtn->setIcon(QIcon(":/new/prefix2/gp_source/next.png")) ;
    bextBtn->setIconSize(QSize(30, 30)) ;
    // end change style

    // connect timeedit to clicked signal
    connect(ui->switch_sup, SIGNAL(clicked()), this, SLOT(switchClicked()));


}

SetTimerRem::~SetTimerRem()
{
    delete ui;
}

void SetTimerRem::on_cancel_clicked()
{
    close() ;
}


void SetTimerRem::on_yes_clicked()
{
    QSound::play(":/new/prefix1/media/alert_music.wav") ;
    // add record
    QString thing = ui->remainder->toPlainText() ;
    QDate date = ui->dateEdit->date() ;
    QTime time = ui->timeEdit->time() ;
    timeRemainder.createTimer(date, time, thing) ;

    Alert errMsg ;
    errMsg.setModal(true) ;
    QString msg = QStringLiteral("提醒設置成功！") ;
    errMsg.setErrMsg(msg, 0) ;
    errMsg.exec() ;

    close() ;
}

void SetTimerRem::switchClicked()
{
    ui->timeEdit->show() ;
    ui->timeEdit->raise() ;
    ui->sup_View->hide() ;
    ui->timeEdit->setFocus() ;
}


void SetTimerRem::on_timeEdit_editingFinished()
{
    QTime time = ui->timeEdit->time() ;

    ui->sup_View->setTime(time) ;

    ui->sup_View->show() ;
    ui->timeEdit->hide() ;
    ui->switch_sup->raise() ;

}

void SetTimerRem::getSelectedRowThing(int row)
{
    QString thing = g_records.recs[row].thing ;
    ui->remainder->setText(thing) ;
    ui->remainder->moveCursor(QTextCursor::End) ;
}
