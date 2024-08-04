#ifndef SETTIMERREM_H
#define SETTIMERREM_H

#include <QDialog>
#include "customlabel.h"

namespace Ui {
class SetTimerRem;
}

class SetTimerRem : public QDialog
{
    Q_OBJECT

public:
    explicit SetTimerRem(QWidget *parent = nullptr);
    ~SetTimerRem();
    void getSelectedRowThing(int row) ;

private slots:
    void on_cancel_clicked();

    void on_yes_clicked() ;

    void switchClicked() ;

    void on_timeEdit_editingFinished() ;

private:
    Ui::SetTimerRem *ui ;

};

#endif // SETTIMERREM_H
