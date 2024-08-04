#ifndef CUSTOMERLINEEDIT_H
#define CUSTOMERLINEEDIT_H

#include <QLineEdit>
#include <QMouseEvent>

class CustomerLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit CustomerLineEdit(QWidget *parent = 0) ;
     ~CustomerLineEdit() ;

protected:
    virtual void mousePressEvent(QMouseEvent *ev) ;
signals:
    void clicked() ;
} ;


#endif // CUSTOMERLINEEDIT_H
