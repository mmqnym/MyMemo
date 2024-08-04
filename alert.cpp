#include "alert.h"
#include "ui_alert.h"

bool Alert::endFlag = true ;

Alert::Alert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Alert)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint|
                     Qt::WindowStaysOnTopHint|Qt::Dialog) ;
    this->setWindowOpacity(0.96);
    ui->cancel->hide() ;
    ui->yes->setStyleSheet("QPushButton{background-color: rgb(127, 127, 127, 0%); border:none;}"
                                    "QPushButton:hover{background-color: rgb(0, 0, 0, 50%); color: rgb(255, 255, 255);}") ;

    ui->cancel->setStyleSheet("QPushButton{background-color: rgb(127, 127, 127, 0%);border:none;}"
                                    "QPushButton:hover{background-color: rgb(0, 0, 0, 50%); color: rgb(255, 255, 255);}") ;
}

Alert::~Alert()
{
    delete ui;
}

void Alert::on_yes_clicked()
{
    Alert::endFlag = true ;
    this->hide() ;
}

void Alert::setErrMsg(QString &errMsg, int type)
{
    ui->alertMsg->setText(errMsg) ;
    ui->cancel->hide() ;

    if (type == 1)
    {

        ui->cancel->show() ;
    }

}

void Alert::on_cancel_clicked()
{
    Alert::endFlag = false ;
    this->close() ;
}
