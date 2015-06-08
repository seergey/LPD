#include "TogglableCustomButton.h"
#include <QPainter>
#include <QRect>
#include <QPaintEvent>

TogglableCustomButton::TogglableCustomButton(QWidget *parent) : QPushButton(parent)
{

}

void TogglableCustomButton::setButtonMode(int mode)
{
    this->buttonMode = mode;
}

void TogglableCustomButton::setActiveMode(int mode)
{
    this->activeMode = mode;
    update();
}

void TogglableCustomButton::paintEvent(QPaintEvent *paintEvent)
{
    QPushButton::paintEvent(paintEvent);
    if (this->activeMode == this->buttonMode) {
        QPainter painter(this);
    //    painter.setPen(QPen(Qt::red,2, Qt::SolidLine, Qt::FlatCap));
        QRect rect  = paintEvent->rect();
        rect.setBottom(rect.bottom()-1);
        rect.setTop(rect.bottom()-20);
        rect.setLeft(rect.left()+10);
        rect.setRight(rect.right()-10);
        QBrush brush = QBrush(Qt::red);
        painter.fillRect(rect, brush);
    }
}

