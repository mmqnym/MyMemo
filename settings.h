#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();
    void setCurrentComboBox() ;

private slots:
    void on_ok_clicked();

    void on_setting2_currentIndexChanged(int index);

    void on_setting1_currentIndexChanged(int index);

private:
    Ui::Settings *ui;
    bool record_alerm_played ;

};

#endif // SETTINGS_H
