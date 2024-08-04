#ifndef DELETEWINDOW_H
#define DELETEWINDOW_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class DeleteWindow;
}

class DeleteWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DeleteWindow(int mode, QWidget *parent = nullptr);
    // mode 1: main delete. // mode 2: alerm delete

    ~DeleteWindow();

    void lsAllthings() ;
    void lsAllalerm() ;


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::DeleteWindow *ui;
    QStandardItemModel *model ;
    int mode ;

    void deleteSelectThing() ;
    void deleteAllThing() ;
};

#endif // DELETEWINDOW_H
