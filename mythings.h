#ifndef MYTHINGS_H
#define MYTHINGS_H

#include <QDialog>
#include <QMenu>
#include <QAction>

namespace Ui {
class MyThings;
}

class MyThings : public QDialog
{
    Q_OBJECT

public:
    explicit MyThings(QWidget *parent = nullptr);
    ~MyThings();

private slots:
    void on_leave_clicked() ;

    void on_search_clicked() ;

    void searchBar_clicked() ;

    void background_clicked() ;

    void on_searchKey_textChanged(const QString &arg1) ;

    void on_modeChoose_currentIndexChanged(int index) ;

    void clicked_rightMenu(QPoint pos) ;

    void clickMenu_1() ;

    void clickMenu_2() ;

    void on_myAlerm_clicked();

private:
    Ui::MyThings *ui;
    void lsMythings() ;
    void search_relative_thing() ;
    void search_priority(int mode) ;
    void setListVisible() ;

    QMenu *rightMenu ;
    QAction *addExtraAttributes ;
    QAction *setTimerReminder ;

};

#endif // MYTHINGS_H
