#include "addsuccess.h"
#include "ui_addsuccess.h"
#include <QSound>

AddSuccess::AddSuccess(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddSuccess)
{
    ui->setupUi(this);
    QSound::play(":/new/prefix1/media/alert_music.wav") ;

    setWindowFlags(Qt::Window|Qt::FramelessWindowHint|
                     Qt::WindowStaysOnTopHint) ;

    ui->pushButton->setStyleSheet("QPushButton{background-color: rgb(230, 229, 255, 0%);border:none;}"
                                  "QPushButton:hover{background-color: rgb(0, 0, 0, 30%);}") ;

    this->setWindowOpacity(1) ;

}

AddSuccess::~AddSuccess()
{
    delete ui;
}

void AddSuccess::on_pushButton_clicked()
{
    close() ;
}
