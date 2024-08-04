#include "settings.h"
#include "ui_settings.h"
#include "timeremainder.h"
#include <QStandardItemModel>
#include <QLineEdit>
#include <QAbstractItemView>
#include <QSound>
#include "Records.h"

#define MUSIC_NUMBER 13 // include silent mode

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Window|Qt::FramelessWindowHint|
                         Qt::WindowStaysOnTopHint) ;

    this->setWindowOpacity(0.96) ;

    ui->ok->setStyleSheet("QPushButton{background-color: rgb(255, 251, 183, 0%);border:none;}"
                             "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    //QString fontName = QStringLiteral("²MªQ¤â¼gÅé2") ;

    ui->setting1->setStyleSheet("QComboBox{color: rgb(175, 19, 21); color:rgb(136, 39, 255) ; font: 12pt 'JasonHandwriting2' ; "
                                  "background-color: rgb(255, 251, 183, 0%);border:none;}"
                             "QComboBox:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->setting2->setStyleSheet("QComboBox{color: rgb(175, 19, 21); color:rgb(136, 39, 255) ; font: 12pt 'JasonHandwriting2' ; "
                                  "background-color: rgb(255, 251, 183, 0%);border:none;}"
                             "QComboBox:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->setting1->setMaxCount(3) ;
    static_cast<QStandardItemModel*> (ui->setting1->view()->model())->item(0)->setTextAlignment(Qt::AlignCenter) ;
    static_cast<QStandardItemModel*> (ui->setting1->view()->model())->item(1)->setTextAlignment(Qt::AlignCenter) ;
    static_cast<QStandardItemModel*> (ui->setting1->view()->model())->item(2)->setTextAlignment(Qt::AlignCenter) ;

    ui->setting1->setEditable(true) ;
    ui->setting1->lineEdit()->setReadOnly(true) ;
    ui->setting1->lineEdit()->setAlignment(Qt::AlignCenter) ;

    ui->setting2->setMaxCount(MUSIC_NUMBER) ;

    for (int i = 0; i < MUSIC_NUMBER; i++)
        static_cast<QStandardItemModel*> (ui->setting2->view()->model())->item(i)->setTextAlignment(Qt::AlignCenter) ;


    ui->setting2->setEditable(true) ;
    ui->setting2->lineEdit()->setReadOnly(true) ;
    ui->setting2->lineEdit()->setAlignment(Qt::AlignCenter) ;

    record_alerm_played = false ;

    ui->alert2->hide() ;
}

Settings::~Settings()
{
    delete ui;
}

void Settings::setCurrentComboBox()
{
    ui->setting1->setCurrentIndex(g_records.effect_choose) ;
    ui->setting2->setCurrentIndex(timeRemainder.getCurrentAlermIdx()) ;
}

void Settings::on_ok_clicked()
{
    g_records.effect_choose = ui->setting1->currentIndex() ;
    timeRemainder.alermChoose(ui->setting2->currentIndex()) ;

    if (ui->setting2->currentIndex() != 12) // not slient mode
        timeRemainder.stopPlayed() ;
    close() ;
}

void Settings::on_setting2_currentIndexChanged(int index)
{
    // play current choose alerm
    if (timeRemainder.getCurrentAlermIdx() != ui->setting2->currentIndex())
    {
        timeRemainder.playAlermCurrentChoose(index) ;
        record_alerm_played = true ;
    }
    else if (record_alerm_played)
        timeRemainder.playAlermCurrentChoose(index) ;
}

void Settings::on_setting1_currentIndexChanged(int index)
{
    if (index == 2)
    {
        ui->alert1->hide() ;
        ui->alert2->show() ;
    }
    else
    {
        ui->alert2->hide() ;
        ui->alert1->show() ;
    }
}
