#include "secdialog.h"
#include "ui_secdialog.h"
#include "addsuccess.h"
#include "Records.h"

SecDialog::SecDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint|
                     Qt::WindowStaysOnTopHint) ;

    this->setWindowOpacity(0.9) ;

    activateWindow() ;
    ui->alert_tip->hide() ;
    ui->alert_tip_thing->hide() ;
    ui->alert_tip_date->hide() ;

    ui->ok->setStyleSheet("QPushButton{background-color: rgb(230, 229, 255, 0%);border:none;}"
                          "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->cancel->setStyleSheet("QPushButton{background-color: rgb(230, 229, 255, 0%);border:none;}"
                          "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->ok->setToolTip(QStringLiteral("確認添加")) ;
    ui->cancel->setToolTip(QStringLiteral("取消")) ;

    ui->lineEdit->setFocus() ;
}

SecDialog::~SecDialog()
{
    delete ui;
}

void SecDialog::getText(QString &thing, QString &priority, QString &deadline)
{
    thing = ui->lineEdit->toPlainText();
    priority = ui->lineEdit_2->text();
    deadline = ui->lineEdit_3->text();
}

void SecDialog::on_ok_clicked()
{
    QString thing, priority, deadline;
    int priorityValue = -1 ;
    bool checkAllin = true ;
    getText(thing, priority, deadline) ;

    if (QString::compare(thing, "") == 0)
    {
        ui->alert_tip_thing->setText(QStringLiteral("請輸入事項")) ;
        ui->alert_tip_thing->show() ;
        checkAllin = false ;
    }

    if (QString::compare(priority, "") == 0)
    {
        ui->alert_tip->setText(QStringLiteral("請輸入優先序")) ;
        ui->alert_tip->show() ;
        checkAllin = false ;
    }

    if (QString::compare(deadline, "") == 0)
    {
        ui->alert_tip_date->setText(QStringLiteral("請輸入期限")) ;
        ui->alert_tip_date->show() ;
        checkAllin = false ;
    }

    std::string checkNum = ui->lineEdit_2->text().toStdString() ;
    bool hasStr = false ;

    for (int idx = 0; checkNum[idx] != '\0'; idx++)
    {
        if (checkNum[idx] < '0' || checkNum[idx] > '9')
        {
            hasStr = true ;
            break ;
        }
    }

    if (!checkAllin)
        return ;

    if (hasStr)
    {
        ui->alert_tip->setText(QStringLiteral("請輸入數字1~xxx")) ;
        ui->lineEdit_2->setText(QStringLiteral("")) ;
        return ;
    }

    priorityValue = priority.toUInt() ;

    QString t_expand = "" ;
    g_records.add(thing, priorityValue, deadline, t_expand) ;

    AddSuccess msg;
    msg.setWindowTitle("success!");
    msg.setModal(true);
    msg.exec();
    close();
}

void SecDialog::on_cancel_clicked()
{
    close();
}

void SecDialog::on_lineEdit_cursorPositionChanged()
{
    ui->alert_tip_thing->hide() ;
}

void SecDialog::on_lineEdit_3_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1) ;
    Q_UNUSED(arg2) ;
    ui->alert_tip_date->hide() ;
}

void SecDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1) ;
    std::string checkNum = ui->lineEdit_2->text().toStdString() ;

    if (QString::compare(ui->lineEdit_2->text(), "0") == 0)
    {
        ui->alert_tip->setText(QStringLiteral("請輸入數字1~xxx")) ;
        ui->alert_tip->show() ;
        ui->lineEdit_2->setText(QStringLiteral("")) ;
    }
    else if (checkNum[checkNum.size()-1] < '0' ||
             checkNum[checkNum.size()-1] > '9')
    {
        ui->alert_tip->setText(QStringLiteral("請輸入數字1~xxx")) ;
        ui->alert_tip->show() ;

        ui->lineEdit_2->backspace() ;
    }
    else
    {
        ui->alert_tip->hide() ;

    }

}

