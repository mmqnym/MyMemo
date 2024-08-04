#ifndef ALERT_H
#define ALERT_H

#include <QDialog>

namespace Ui {
class Alert;
}

class Alert : public QDialog
{
    Q_OBJECT

public:
    explicit Alert(QWidget *parent = nullptr);
    ~Alert();

    static bool endFlag ;
    void setErrMsg(QString &errMsg, int type) ;

private slots:
    void on_yes_clicked();

    void on_cancel_clicked();

private:
    Ui::Alert *ui;
};

#endif // ALERT_H
