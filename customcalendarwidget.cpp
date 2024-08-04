#include "customcalendarwidget.h"

CustomCalendarWidget::CustomCalendarWidget(QWidget *parent) : QCalendarWidget(parent)
{}

CustomCalendarWidget::~CustomCalendarWidget()
{}

void CustomCalendarWidget::paintCell(QPainter *painter, const QRect &rect, const QDate &date) const
{
    if (date == selectedDate())
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(0, 145, 255, 170));

        painter->drawRoundedRect(rect.x(), rect.y() + 3, rect.width(), rect.height() - 6, 3, 3);
        painter->setPen(QColor(255, 255, 255));

        painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
        painter->restore();
    }
    else if (date == QDate::currentDate())
    {
        painter->save();
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setPen(Qt::NoPen);
        painter->setBrush(QColor(0, 0, 0));
        painter->drawRoundedRect(rect.x(), rect.y() + 3, rect.width(), rect.height() - 6, 0, 0) ;
        painter->setBrush(QColor(142, 0, 189, 127));
        painter->drawRoundedRect(rect.x() + 1, rect.y() + 4, rect.width() - 2, rect.height() - 8, 2, 2);
        painter->setPen(QColor(255, 255, 255));

        painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
        painter->restore();
    }
    else if (date < minimumDate() || date > maximumDate())
    {
        painter->save();

        painter->setPen(QColor(0, 0, 0));
        painter->drawText(rect, Qt::AlignCenter, QString::number(date.day()));
        painter->restore();
    }
    else
    {
        __super::paintCell(painter, rect, date);
    }

}
