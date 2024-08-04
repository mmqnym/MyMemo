#include "extrainfowindow.h"
#include "ui_extrainfowindow.h"
#include "Records.h"
#include <QSound>

ExtraInfoWindow::ExtraInfoWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExtraInfoWindow)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint|
                     Qt::WindowStaysOnTopHint) ;
    this->setWindowOpacity(0.97);

    ui->pushButton->setStyleSheet("QPushButton{background-color: rgb(170, 255, 127, 0%);border:none;}"
                             "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->pushButton_2->setStyleSheet("QPushButton{background-color: rgb(170, 255, 127, 0%);border:none;}"
                             "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;
}

ExtraInfoWindow::~ExtraInfoWindow()
{
    delete ui;
}

void ExtraInfoWindow::getText(QString &text)
{
    ui->textEdit->setText(text.toStdString().c_str()) ;
}

void ExtraInfoWindow::selectedRow(int got_row)
{
    row = got_row ;
}

void ExtraInfoWindow::on_pushButton_clicked()
{
    QSound::play(":/new/prefix1/media/alert_music.wav") ;
    g_records.recs[row].expand = ui->textEdit->toPlainText() ;
    close() ;
}

void ExtraInfoWindow::on_pushButton_2_clicked()
{
    close() ;
}
