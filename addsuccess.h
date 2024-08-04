#ifndef ADDSUCEESS_H
#define ADDSUCEESS_H

#include <QDialog>

namespace Ui {
class AddSuccess;
}

class AddSuccess : public QDialog
{
    Q_OBJECT

public:
    explicit AddSuccess(QWidget *parent = nullptr);
    ~AddSuccess();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddSuccess *ui;
};

#endif // ADDSUCCESS_H
