#ifndef SECDIALOG_H
#define SECDIALOG_H

#include <QDialog>

namespace Ui {
class SecDialog;
}

class SecDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();
    void getText(QString &thing, QString &priority, QString &deadline);

private slots:
    void on_ok_clicked();

    void on_cancel_clicked();

    void on_lineEdit_3_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_cursorPositionChanged();

private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
