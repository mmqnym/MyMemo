#ifndef EXTRAINFOWINDOW_H
#define EXTRAINFOWINDOW_H

#include <QDialog>

namespace Ui {
class ExtraInfoWindow;
}

class ExtraInfoWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ExtraInfoWindow(QWidget *parent = nullptr);
    ~ExtraInfoWindow();
    void getText(QString &text) ;
    void selectedRow(int row) ;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ExtraInfoWindow *ui;
    int row ;
};

#endif // EXTRAINFOWINDOW_H
