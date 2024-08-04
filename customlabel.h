#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QLabel>
#include <QMouseEvent>

class CustomLabel : public QLabel
{
    Q_OBJECT
public:
    explicit CustomLabel(QWidget *parent = 0) ;
    ~CustomLabel() ;

protected:
    virtual void mousePressEvent(QMouseEvent *ev) ;
signals:
    void clicked() ;

};

#endif // CUSTOMLABEL_H
