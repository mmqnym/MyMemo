#include "mythings.h"
#include "ui_mythings.h"
#include <QStandardItemModel>
#include "Records.h"
#include "extrainfowindow.h"
#include "settimerrem.h"
#include "deletewindow.h"

MyThings::MyThings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyThings)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window|Qt::FramelessWindowHint|
                     Qt::WindowStaysOnTopHint) ;
    this->setWindowOpacity(0.97);

    connect(ui->searchKey, SIGNAL(clicked()), this, SLOT(searchBar_clicked())) ; // add mouse clicked event
    connect(ui->background, SIGNAL(clicked()), this, SLOT(background_clicked())) ;

    ui->leave->setStyleSheet("QPushButton{background-color: rgb(255, 251, 183, 0%);border:none;}"
                             "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->search->setStyleSheet("QPushButton{background-color: rgb(255, 251, 183, 0%);border:none;}"
                             "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->myAlerm->setStyleSheet("QPushButton{background-color: rgb(255, 251, 183, 0%);border:none;}"
                             "QPushButton:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->modeChoose->setStyleSheet("QComboBox{color: rgb(175, 19, 21); font: 10pt 'SetoFont'; "
                                  "background-color: rgb(255, 251, 183, 0%);border:none;}"
                             "QComboBox:hover{background-color: rgb(0, 0, 0, 40%);}") ;

    ui->modeChoose->setMaxCount(3) ;
    static_cast<QStandardItemModel*> (ui->modeChoose->view()->model())->item(0)->setTextAlignment(Qt::AlignCenter) ;
    static_cast<QStandardItemModel*> (ui->modeChoose->view()->model())->item(1)->setTextAlignment(Qt::AlignCenter) ;
    static_cast<QStandardItemModel*> (ui->modeChoose->view()->model())->item(2)->setTextAlignment(Qt::AlignCenter) ;

    ui->modeChoose->setEditable(true) ;
    ui->modeChoose->lineEdit()->setReadOnly(true) ;
    ui->modeChoose->lineEdit()->setAlignment(Qt::AlignCenter) ;

    ui->proBar->hide() ;
    ui->proBar->setTextVisible(false) ;
    ui->searchKey->setText(QStringLiteral("請輸入關鍵字..")) ;
    ui->searchKey->setStyleSheet("QLineEdit{color: rgb(181, 181, 181);}") ;

    ui->alert_tip->hide() ;

    lsMythings() ;

}

MyThings::~MyThings()
{
    delete ui;
}

void MyThings::lsMythings()
{
    QStandardItemModel *model = new QStandardItemModel ;
    model->setColumnCount(4) ;

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("序號")) ;
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("優先序")) ;
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("事件")) ;
    model->setHeaderData(3, Qt::Horizontal, QStringLiteral("期限")) ;

    ui->recordsList->setModel(model) ;
    ui->recordsList->horizontalHeader()->setStretchLastSection(true) ;

    ui->recordsList->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter) ;

    for (int i = 0; i < 4; i++)
        ui->recordsList->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed) ;

    ui->recordsList->setColumnWidth(0, 50) ;
    ui->recordsList->setColumnWidth(1, 70) ;
    ui->recordsList->setColumnWidth(2, 440) ;
    ui->recordsList->setColumnWidth(3, 149) ;

    ui->recordsList->setEditTriggers(QAbstractItemView::NoEditTriggers) ;
    ui->recordsList->setContextMenuPolicy(Qt::CustomContextMenu) ;
    ui->recordsList->verticalHeader()->setVisible(false) ;
    ui->recordsList->setSelectionBehavior(QAbstractItemView::SelectRows) ;

    rightMenu = new QMenu() ;
    addExtraAttributes = new QAction(QStringLiteral("編輯詳細資訊 ..."), this) ;
    rightMenu->addAction(addExtraAttributes) ;

    rightMenu->addSeparator() ;

    setTimerReminder = new QAction(QStringLiteral("設定提醒時間 ..."), this) ;
    rightMenu->addAction(setTimerReminder) ;

    connect(ui->recordsList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(clicked_rightMenu(QPoint))) ;
    // connect mouse right-click to menu

    connect(addExtraAttributes, SIGNAL(triggered()), this, SLOT(clickMenu_1())) ;
    // connect click choice(1) to menu

    connect(setTimerReminder, SIGNAL(triggered()), this, SLOT(clickMenu_2())) ;
    // connect click choice(2) to menu


    int file_idx = 0 ;

    for (int i = 0; i < g_records.size(); i++)
    {
        int j = 0 ;
        model->setItem(i, j, new QStandardItem(QString::number(i))) ;
        j++ ;

        QString temp = QString::number(g_records.recs.at(file_idx).priority) ;
        model->setItem(i, j, new QStandardItem(temp)) ;

        j++ ;
        temp = g_records.recs.at(file_idx).thing ;
        model->setItem(i, j, new QStandardItem(temp)) ;

        j++ ;
        temp = g_records.recs.at(file_idx).deadline ;
        model->setItem(i, j, new QStandardItem(temp)) ;

        file_idx++ ;
    }

}

void MyThings::setListVisible()
{
    int rowCount = ui->recordsList->model()->rowCount() ;

    for (int i = 0; i < rowCount; i++)
    {
        ui->recordsList->setRowHidden(i, false) ;
    }
}

void MyThings::search_relative_thing()
{
    if (ui->searchKey->text() == "")
    {
        ui->proBar->hide() ;
    }
    else
    {
        QString key = ui->searchKey->text() ;
        key.remove(QRegExp("\\s")) ;
        ui->proBar->show() ;
        int rowCount = ui->recordsList->model()->rowCount() ;

        for (int i = 0; i < rowCount; i++)
        {
            if (i >= 1)
            {
                float fraction = (float) i / rowCount ;
                fraction *= 100 ;
                ui->proBar->setValue(fraction) ;
            }
            else if (i == 0)
                ui->proBar->setValue(0) ;

            ui->recordsList->setRowHidden(i, true) ;
            QString r = "" ;

            QAbstractItemModel *tableMd = ui->recordsList->model() ;
            QModelIndex index ;

            index = tableMd->index(i, 2) ;
            r = tableMd->data(index).toString() ;

            r.remove(QRegExp("\\s")) ;

            if (r.contains(key,Qt::CaseSensitive))
                ui->recordsList->setRowHidden(i, false) ;

        }

        ui->proBar->setValue(100) ;
    }

}

#define PRIORITY_SMALL 0
#define PRIORITY_BIG 1

void MyThings::search_priority(int mode)
{
    if (ui->searchKey->text() == "")
    {
        ui->proBar->hide() ;
    }
    else
    {
        QString key = ui->searchKey->text() ;
        key.remove(QRegExp("\\s")) ;
        ui->proBar->show() ;
        int rowCount = ui->recordsList->model()->rowCount() ;

        for (int i = 0; i < rowCount; i++)
        {
            if (i >= 1)
            {
                float fraction = (float) i / rowCount ;
                fraction *= 100 ;
                ui->proBar->setValue(fraction) ;
            }
            else if (i == 0)
                ui->proBar->setValue(0) ;

            ui->recordsList->setRowHidden(i, true) ;
            QString r = "" ;

            QAbstractItemModel *tableMd = ui->recordsList->model() ;
            QModelIndex index ;

            index = tableMd->index(i, 1) ;
            r = tableMd->data(index).toString() ;

            r.remove(QRegExp("\\s")) ;

            int comp = r.toInt() ;
            int comp_key = key.toInt() ;

            if (mode == PRIORITY_SMALL)
            {
                if (comp <= comp_key)
                   ui->recordsList->setRowHidden(i, false) ;
            }
            else if (mode == PRIORITY_BIG)
            {
                if (comp >= comp_key)
                   ui->recordsList->setRowHidden(i, false) ;
            }
        }

        ui->proBar->setValue(100) ;
    }

}

void MyThings::on_leave_clicked()
{
    close() ;
}

void MyThings::on_search_clicked()
{
    if (ui->modeChoose->currentIndex() == 1 || ui->modeChoose->currentIndex() == 2)
    {
        std::string againstYuhengMakeTroble = ui->searchKey->text().toStdString() ;
        int yuhenSize = (int) againstYuhengMakeTroble.size() ;

        for (int i = 0; i < yuhenSize; i++)
        {
            if (againstYuhengMakeTroble[i] < '0' || againstYuhengMakeTroble[i] > '9')
            {
                ui->alert_tip->show() ;
                ui->searchKey->clear() ;
                return ;
            }
        }
    }

    if (ui->modeChoose->currentIndex() == 0) // search thing
        search_relative_thing() ;
    else if (ui->modeChoose->currentIndex() == 1) // search priority smaller than x
        search_priority(PRIORITY_SMALL) ;
    else if (ui->modeChoose->currentIndex() == 2) // search priority bigger than x
        search_priority(PRIORITY_BIG) ;
}

void MyThings::searchBar_clicked()
{
    ui->searchKey->clear() ;
    ui->searchKey->setStyleSheet("QLineEdit{color: rgb(0, 0, 0);}") ;
    ui->proBar->hide() ;
    setListVisible() ;
}

void MyThings::background_clicked()
{
    setListVisible() ;
    ui->proBar->hide() ;
}

void MyThings::clicked_rightMenu(QPoint pos)
{
    auto index = ui->recordsList->indexAt(pos) ;

    if (index.isValid())
    {
        rightMenu->exec(QCursor::pos()) ;
    }
}

void MyThings::clickMenu_1()
{

    int selectedRow = ui->recordsList->currentIndex().row() ;

    ExtraInfoWindow extra ;

    extra.setModal(true) ;
    extra.selectedRow(selectedRow) ;
    extra.getText(g_records.recs[selectedRow].expand) ;
    extra.exec() ;

}

void MyThings::clickMenu_2()
{
    int selectedRow = ui->recordsList->currentIndex().row() ;
    SetTimerRem setTimerWindow ;
    setTimerWindow.setModal(true) ;
    setTimerWindow.getSelectedRowThing(selectedRow) ;

    setTimerWindow.exec() ;
}

void MyThings::on_searchKey_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1) ;

    if (ui->modeChoose->currentIndex() == 1 ||
        ui->modeChoose->currentIndex() == 2)
    {
        std::string checkNum = ui->searchKey->text().toStdString() ;

        if (QString::compare(ui->searchKey->text(), "0") == 0)
        {
            ui->alert_tip->show() ;
            ui->searchKey->setText(QStringLiteral("")) ;
        }
        else if (checkNum[checkNum.size()-1] < '0' ||
                 checkNum[checkNum.size()-1] > '9')
        {

            ui->alert_tip->show() ;
            ui->searchKey->backspace() ;
        }
        else
        {
            ui->alert_tip->hide() ;

        }
    }
    else
        ui->alert_tip->hide() ;
}

void MyThings::on_modeChoose_currentIndexChanged(int index)
{
    Q_UNUSED(index) ;
    ui->searchKey->clear() ;
}

void MyThings::on_myAlerm_clicked()
{
    ui->frame->hide() ;
    ui->leave->hide() ;
    ui->search->hide() ;
    ui->frame_2->hide() ;
    ui->myAlerm->hide() ;
    ui->searchKey->hide() ;
    ui->background->hide() ;
    ui->modeChoose->hide() ;
    ui->recordsList->hide() ;
    ui->search_label->hide() ;

    DeleteWindow allThing(2) ;
    allThing.setModal(true) ;
    allThing.lsAllalerm() ;
    allThing.exec() ;

    ui->frame->show() ;
    ui->leave->show() ;
    ui->search->show() ;
    ui->frame_2->show() ;
    ui->myAlerm->show() ;
    ui->searchKey->show() ;
    ui->background->show() ;
    ui->modeChoose->show() ;
    ui->recordsList->show() ;
    ui->search_label->show() ;

}

