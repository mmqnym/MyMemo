#include "customlabel.h"

CustomLabel::CustomLabel(QWidget *parent) : QLabel(parent)
{}

CustomLabel::~CustomLabel()
{}

void CustomLabel::mousePressEvent(QMouseEvent *ev) {

    if (ev->button() == Qt::LeftButton) {
        emit clicked();
    }

}
