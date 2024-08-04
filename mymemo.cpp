#include "mymemo.h"
#include "ui_mymemo.h"
#include <QMovie>
#include <QLabel>
#include "secdialog.h"
#include "readlist.h"
#include "mythings.h"
#include "Records.h"
#include "deletewindow.h"
#include <QFile>
#include <QTextStream>
#include "alert.h"
#include <QTimer>
#include "timeremainder.h"
#include <QHideEvent>
#include <QCloseEvent>
#include "settings.h"

MyMemo::MyMemo(int eff, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyMemo)
{
    ui->setupUi(this);
    this->resize(QSize(820, 510 ));
    setMinimumSize(820, 510);
    setMaximumSize(820, 510);

    setGifModel() ;

    QIcon stsIcon(":/new/prefix1/gp_source/icon.png") ;
    systemTray = new QSystemTrayIcon(this) ;
    systemTray->setIcon(stsIcon) ;
    QMenu *menu = new QMenu(this) ;
    QAction *open = new QAction(QStringLiteral("開啟視窗"), this) ;
    connect(open, SIGNAL(triggered()), this, SLOT(openWindow()));

    menu->addAction(open) ;
    systemTray->setContextMenu(menu) ;
    systemTray->show() ;
    systemTray->connect(systemTray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
                        this, SLOT(openWindow(QSystemTrayIcon::ActivationReason))) ;
    tipShowed = false ;
    err_close = true ;

    QPalette mainPal = ui->pushButton->palette() ;
    mainPal.setColor(QPalette::Button,Qt::blue) ;

    ui->pushButton->setPalette(mainPal);

    ui->pushButton->setStyleSheet("QPushButton{background-color: rgb(182, 204, 159, 70%);}"
                                  "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->pushButton_2->setStyleSheet("QPushButton{background-color: rgb(209, 113, 113, 70%);}"
                                  "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->pushButton_3->setStyleSheet("QPushButton{background-color: rgb(255, 246, 206, 70%);}"
                                  "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->pushButton_4->setStyleSheet("QPushButton{background-color: rgb(233, 210, 255, 70%);}"
                                  "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->pushButton_5->setStyleSheet("QPushButton{background-color: rgb(209, 189, 184, 90%);}"
                                  "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->proBar->hide() ;
    ui->proBar->setTextVisible(false) ;

    // create permanent timer for check thing's time
    QTimer *execTimer = new QTimer(this) ;
    connect(execTimer, SIGNAL(timeout()), this, SLOT(checkTime())) ;
    execTimer->start(eff) ;

    // create permanent timer for auto save
    QTimer *autoSaveTimer = new QTimer(this) ;
    connect(autoSaveTimer, SIGNAL(timeout()), this, SLOT(autoSave())) ;
    autoSaveTimer->start(60000 * 20) ; // every 20 minutes save file once
}

void MyMemo::openWindow()
{
    for (int i = 0; i < 5; i++)
        movie[i]->setPaused(false) ;
    showNormal() ;
    activateWindow() ;

}

void MyMemo::openWindow(QSystemTrayIcon::ActivationReason reop)
{
    if (reop == QSystemTrayIcon::DoubleClick)
    {
        for (int i = 0; i < 5; i++)
            movie[i]->setPaused(false) ;
        showNormal() ;
        activateWindow() ;
    }
}

void MyMemo::showMultipleExec_alert(bool flag)
{
    if (flag)
    {
        systemTray->showMessage("tips", QStringLiteral("程式已於工作列執行!")) ;

    }

}

void MyMemo::set_autoRun_flag()
{
    if (autoRun_exec)
        this->hide() ;

}

void MyMemo::get_autoRun_flag(bool flag)
{
    autoRun_exec = flag ;
}

void MyMemo::checkTime()
{
    timeRemainder.checkTime() ;
}

void MyMemo::autoSave()
{
    writeF() ;
}

void MyMemo::setGifModel()
{
    movie[0] = new QMovie(":/new/prefix1/gp_source/write.gif");
    ui->label_6->setFixedSize(110,70);
    ui->label_6->setScaledContents(true);
    movie[0]->setSpeed(130) ;
    ui->label_6->setMovie(movie[0]);
    movie[0]->start();

    movie[1] = new QMovie(":/new/prefix1/gp_source/remove.gif");
    ui->label_7->setFixedSize(111,71);
    ui->label_7->setScaledContents(true);
    ui->label_7->setMovie(movie[1]);
    movie[1]->start();

    movie[2] = new QMovie(":/new/prefix1/gp_source/lsAll.gif");
    ui->lsAll->setFixedSize(150,120);
    ui->lsAll->setScaledContents(true);
    ui->lsAll->setMovie(movie[2]);
    movie[2]->start();

    movie[3] = new QMovie(":/new/prefix1/gp_source/bye.gif");
    ui->saveAndLeave->setFixedSize(120,100);
    ui->saveAndLeave->setScaledContents(true);
    ui->saveAndLeave->setMovie(movie[3]);
    movie[3]->start();

    movie[4] = new QMovie(":/new/prefix1/gp_source/settings.gif");
    ui->settings->setFixedSize(90,90);
    ui->settings->setScaledContents(true);
    ui->settings->setMovie(movie[4]);
    movie[4]->start();
}

MyMemo::~MyMemo()
{
    delete ui ;
}

bool MyMemo::writeF()
{
    ui->proBar->show() ;
    QFile outF("./notes/record.bin") ;
    QFile outExpand("./notes/expand.bin") ;
    QFile outTimer("./notes/timer.bin") ;
    QFile outSettings("./notes/settings.bin") ;

    bool ok = outF.open(QIODevice::WriteOnly) ;
    bool ok_exp = outExpand.open(QIODevice::WriteOnly) ;
    bool ok_timer = outTimer.open(QIODevice::WriteOnly) ;
    bool ok_settings = outSettings.open(QIODevice::WriteOnly) ;

    if(ok && ok_exp && ok_timer && ok_settings)
    {
        QTextStream txtOutput(&outF) ;
        QTextStream txtExOutput(&outExpand) ;
        QTextStream txtTmOutput(&outTimer) ;
        QTextStream txtStOutput(&outSettings) ;

        for (int i = 0; i < g_records.size(); i++)
        {
            txtOutput << quint32(g_records.recs.at(i).priority) << "," ;
            txtOutput << g_records.recs.at(i).thing << "," ;
            txtOutput << g_records.recs.at(i).deadline << "," ;

            txtExOutput << i << "\n" << g_records.recs.at(i).expand << "\n" ;

            if (i == 0)
            {
                ui->proBar->setValue(0) ;
            }
            else if (i > 0)
            {
                float fraction = (float) i / g_records.size() ;
                fraction *= 100 ;
                ui->proBar->setValue(fraction) ;
            }
        }

        outF.close() ;
        outExpand.close() ;

        for (int i = 0; i < timeRemainder.recSize(); i++)
        {
            txtTmOutput << timeRemainder.timerRec.at(i).thing << "," ;
            txtTmOutput << timeRemainder.timerRec.at(i).dateInfo.toString("yyyy-MM-dd") << "," ;
            txtTmOutput << timeRemainder.timerRec.at(i).timeInfo.toString("hh:mm") << "," ;

        }

        outTimer.close() ;

        txtStOutput << g_records.effect_choose << "," << timeRemainder.getCurrentAlermIdx() << "," ;

        ui->proBar->setValue(100) ;
        ui->proBar->hide() ;
        return true ;
    }
    else
    {
        ui->proBar->hide() ;
        Alert errMsg ;
        errMsg.setWindowTitle("Error!") ;
        errMsg.setModal(true) ;
        QString msg = "Error:(0x02) Can not create save file." ;
        errMsg.setErrMsg(msg, 0) ;
        errMsg.exec() ;
        return false ;
    }

}

void MyMemo::on_pushButton_clicked()
{
    for (int i = 0; i < 5; i++)
        movie[i]->setPaused(true) ;

    tipShowed = true ;
    this->hide() ;

    SecDialog getThing ;
    getThing.setWindowTitle("Add thing") ;
    getThing.setModal(true) ;
    getThing.exec() ;

    if (getThing.close())
    {
        for (int i = 0; i < 5; i++)
            movie[i]->setPaused(false) ;
        this->show() ;
    }

    tipShowed = false ;

}

void MyMemo::on_pushButton_3_clicked()
{
    for (int i = 0; i < 5; i++)
        movie[i]->setPaused(true) ;

    tipShowed = true ;
    this->hide() ;

    MyThings allThing ;
    allThing.setWindowTitle("My things(List)") ;
    allThing.setModal(true) ;
    allThing.exec() ;

    if (allThing.close())
    {
        for (int i = 0; i < 5; i++)
            movie[i]->setPaused(false) ;
        this->show() ;
    }

    tipShowed = false ;
}

void MyMemo::on_pushButton_4_clicked()
{
    err_close = false ;
    for (int i = 0; i < 5; i++)
        movie[i]->setPaused(true) ;
    // write file
    bool wF_flag = writeF() ;
    // end write

    if (wF_flag)
    {
        Alert errMsg ;
        errMsg.setWindowTitle("Quit") ;
        errMsg.setModal(true) ;
        QString msg = QStringLiteral("\t存檔成功！！ 是否要結束程式?") ;
        errMsg.setErrMsg(msg, 1) ;
        errMsg.exec() ;
    }

    if (Alert::endFlag)
        close() ;
    else
    {
        for (int i = 0; i < 5; i++)
            movie[i]->setPaused(false) ;
        return ;
    }
}

void MyMemo::on_pushButton_2_clicked()
{
    for (int i = 0; i < 5; i++)
        movie[i]->setPaused(true) ;

    tipShowed = true ;
    this->hide() ;

    DeleteWindow allThing(1) ;
    allThing.setWindowTitle("My things(Delete)") ;
    allThing.setModal(true) ;
    allThing.lsAllthings() ;
    allThing.exec() ;

    if (allThing.close())
    {
        for (int i = 0; i < 5; i++)
            movie[i]->setPaused(false) ;
        this->show() ;
    }

    tipShowed = false ;
}

void MyMemo::hideEvent(QHideEvent *event)
{
    Q_UNUSED(event) ;

    if (systemTray->isVisible() && !tipShowed)
    {
        this->hide() ;
        systemTray->showMessage("tips", QStringLiteral("已縮小至工作列!")) ;

        for (int i = 0; i < 5; i++)
            movie[i]->setPaused(true) ;

        tipShowed = true ;
    }
    else
        this->hide() ;

}

void MyMemo::closeEvent(QCloseEvent *event)
{
    tipShowed = true ;

    if (err_close)
    {
        systemTray->showMessage("tips", QStringLiteral("請使用選單列結束程式!")) ;
        event->ignore() ;
    }
    else
    {
        event->accept() ;
    }

}

void MyMemo::on_pushButton_5_clicked()
{
    for (int i = 0; i < 5; i++)
        movie[i]->setPaused(true) ;

    tipShowed = true ;
    this->hide() ;

    Settings settingWin ;
    settingWin.setCurrentComboBox() ;
    settingWin.setModal(true) ;
    settingWin.exec() ;

    if (settingWin.close())
    {
        for (int i = 0; i < 5; i++)
            movie[i]->setPaused(false) ;
        this->show() ;
    }

    tipShowed = false ;
}
