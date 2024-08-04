#ifndef MYMEMO_H
#define MYMEMO_H

#include <QMainWindow>
#include <QSystemTrayIcon>

QT_BEGIN_NAMESPACE
namespace Ui { class MyMemo ; }
QT_END_NAMESPACE

class MyMemo : public QMainWindow
{
    Q_OBJECT

public:
    MyMemo(int eff, QWidget *parent = nullptr) ;
    ~MyMemo() ;
    void setGifModel() ;
    void get_autoRun_flag(bool flag) ;
    void set_autoRun_flag() ;
    void showMultipleExec_alert(bool flag) ;

private slots:
    void on_pushButton_clicked() ;

    void on_pushButton_3_clicked() ;

    void on_pushButton_4_clicked() ;

    void on_pushButton_2_clicked() ;

    void checkTime() ;

    void on_pushButton_5_clicked();

    void autoSave() ;

    void openWindow(QSystemTrayIcon::ActivationReason) ;

    void openWindow() ;

private:
    Ui::MyMemo *ui ;
    bool writeF() ;
    void hideEvent(QHideEvent *event) ;
    void closeEvent(QCloseEvent *event) ;

    bool autoRun_exec ;
    QSystemTrayIcon *systemTray ;
    bool tipShowed ;
    QMovie *movie[5] ;
    bool err_close ;


} ;
#endif // MYMEMO_H
