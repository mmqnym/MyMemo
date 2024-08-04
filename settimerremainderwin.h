#ifndef SETTIMERREMAINDERWIN_H
#define SETTIMERREMAINDERWIN_H

#include <QDialog>

namespace Ui {
class SetTimerRemainderWin;
}

class SetTimerRemainderWin : public QDialog
{
    Q_OBJECT

public:
    explicit SetTimerRemainderWin(QWidget *parent = nullptr);
    ~SetTimerRemainderWin();

private slots:
    void on_cancel_clicked();

private:
    Ui::SetTimerRemainderWin *ui;
};

#endif // SETTIMERREMAINDERWIN_H
