#include "deletewindow.h"
#include "ui_deletewindow.h"
#include <QStandardItemModel>
#include "Records.h"
#include <QMap>
#include "timeremainder.h"

DeleteWindow::DeleteWindow(int mode, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeleteWindow)
{
    ui->setupUi(this);
    this->setWindowOpacity(0.9);

    setWindowFlags(Qt::Window|Qt::FramelessWindowHint|
                     Qt::WindowStaysOnTopHint) ;

    ui->pushButton->setStyleSheet("QPushButton{background-color: rgb(230, 229, 255, 0%);border:none;}"
                                  "QPushButton:hover{background-color: rgb(0, 0, 0, 30%);}") ;

    ui->pushButton_2->setStyleSheet("QPushButton{background-color: rgb(230, 229, 255, 0%);border:none;}"
                                  "QPushButton:hover{background-color: rgb(0, 0, 0, 30%);}") ;

    ui->pushButton_3->setStyleSheet("QPushButton{background-color: rgb(230, 229, 255, 0%);border:none;}"
                                  "QPushButton:hover{background-color: rgb(0, 0, 0, 30%);}") ;

    if (mode == 1 || mode == 2)
        this->mode = mode ;
    else
        this->mode = 0 ;
}

DeleteWindow::~DeleteWindow()
{
    delete ui;
}

void DeleteWindow::lsAllalerm()
{
    model = new QStandardItemModel ;
    model->setColumnCount(3) ;

    model->setHeaderData(0, Qt::Horizontal, QStringLiteral("提醒內容")) ;
    model->setHeaderData(1, Qt::Horizontal, QStringLiteral("日期")) ;
    model->setHeaderData(2, Qt::Horizontal, QStringLiteral("時間")) ;


    ui->recordsList->setModel(model) ;
    ui->recordsList->horizontalHeader()->setStretchLastSection(true) ;
    ui->recordsList->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter) ;

    for (int i = 0; i < 3; i++)
        ui->recordsList->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Fixed) ;

    ui->recordsList->setColumnWidth(0, 440) ;
    ui->recordsList->setColumnWidth(1, 150) ;
    ui->recordsList->setColumnWidth(2, 120) ;

    ui->recordsList->verticalHeader()->setVisible(false) ;
    ui->recordsList->setSelectionBehavior(QAbstractItemView::SelectRows) ;
    ui->recordsList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->recordsList->setEditTriggers(QAbstractItemView::NoEditTriggers) ;

    int file_idx = 0 ;

    for (int i = 0; i < timeRemainder.recSize(); i++)
    {
        int j = 0 ;

        QString temp = timeRemainder.timerRec.at(file_idx).thing ;
        model->setItem(i, j, new QStandardItem(temp)) ;

        j++ ;
        temp = timeRemainder.timerRec.at(file_idx).dateInfo.toString("yyyy-MM-dd") ;
        model->setItem(i, j, new QStandardItem(temp)) ;

        j++ ;
        temp = timeRemainder.timerRec.at(file_idx).timeInfo.toString("a hh:mm") ;
        model->setItem(i, j, new QStandardItem(temp)) ;

        file_idx++ ;
    }
}

void DeleteWindow::lsAllthings()
{
    model = new QStandardItemModel ;
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

    ui->recordsList->verticalHeader()->setVisible(false) ;
    ui->recordsList->setSelectionBehavior(QAbstractItemView::SelectRows) ;
    ui->recordsList->setSelectionMode(QAbstractItemView::ExtendedSelection);
    ui->recordsList->setEditTriggers(QAbstractItemView::NoEditTriggers) ;

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

void DeleteWindow::deleteSelectThing()
{
    QItemSelectionModel *selections = ui->recordsList->selectionModel() ;
    QModelIndexList selected = selections->selectedIndexes() ;
    QMap<int, int> rowMap ;
    foreach (QModelIndex index, selected)
    {

        rowMap.insert(index.row(), 0) ;
    }

    int rowToDel;
    QMapIterator<int, int> rowMapIterator(rowMap) ;
    rowMapIterator.toBack() ;
    while (rowMapIterator.hasPrevious())
    {
        rowMapIterator.previous() ;
        rowToDel = rowMapIterator.key() ;
        model->removeRow(rowToDel) ;

        if (mode == 1)
            g_records.remove(rowToDel) ;
        else if (mode == 2)
            timeRemainder.timerRec.remove(rowToDel) ;
        else
            ;
    }
}

void DeleteWindow::deleteAllThing()
{
    int rowNum = ui->recordsList->model()->rowCount() ;

    for(int i = rowNum -1; i >= 0 ; i--)
    {
        model->removeRow(i) ;

        if (mode == 1)
            g_records.remove(i) ;
        else if (mode == 2)
            timeRemainder.timerRec.remove(i) ;
        else
            ;
    }
}

void DeleteWindow::on_pushButton_clicked()
{
    deleteSelectThing() ;

    if (mode == 1)
    {
        for (int i = 0; i < g_records.size(); i++)
        {
            model->setItem(i, 0, new QStandardItem(QString::number(i))) ;
        }

        ui->recordsList->setColumnWidth(0, 50) ;
    }
    else if (mode == 2)
    {
        for (int i = 0; i < timeRemainder.recSize(); i++)
        {
            model->setItem(i, 1, new QStandardItem(QString::number(i))) ;
        }

        ui->recordsList->setColumnWidth(0, 440) ;
    }
    else
        ;

}

void DeleteWindow::on_pushButton_2_clicked() // leave
{
    close() ;
}

void DeleteWindow::on_pushButton_3_clicked()
{
    deleteAllThing() ;

    if (mode == 1)
    {
        for (int i = 0; i < g_records.size(); i++)
        {
            model->setItem(i, 0, new QStandardItem(QString::number(i))) ;
        }

        ui->recordsList->setColumnWidth(0, 50) ;
    }
    else if (mode == 2)
    {
        for (int i = 0; i < timeRemainder.recSize(); i++)
        {
            model->setItem(i, 1, new QStandardItem(QString::number(i))) ;
        }

        ui->recordsList->setColumnWidth(0, 440) ;
    }
    else
        ;

}
