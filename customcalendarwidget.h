#ifndef CUSTOMCALENDARWIDGET_H
#define CUSTOMCALENDARWIDGET_H

#include <QCalendarWidget>
#include <QPainter>

class CustomCalendarWidget : public QCalendarWidget
{
    Q_OBJECT
public:
    explicit CustomCalendarWidget(QWidget *parent = 0) ;
    ~CustomCalendarWidget() ;


protected:
    void paintCell(QPainter *painter, const QRect &rect, const QDate &date) const ;


};

#endif // CUSTOMCALENDARWIDGET_H
