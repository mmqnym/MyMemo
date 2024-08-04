#include "customerLineEdit.h"

CustomerLineEdit::CustomerLineEdit(QWidget *parent):QLineEdit(parent)
{}

CustomerLineEdit::~CustomerLineEdit()
{}

void CustomerLineEdit::mousePressEvent(QMouseEvent *ev) {

    if (ev->button() == Qt::LeftButton) {
        emit clicked();
    }

}
