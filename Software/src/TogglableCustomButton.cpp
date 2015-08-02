#include "TogglableCustomButton.h"
#include <QPainter>
#include <QRect>
#include <QPaintEvent>
#include <QStyle>

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

    if (this->buttonMode == 0) {
        if (this->activeMode == this->buttonMode){
            this->setIcon(QIcon(":/icons/shutdown_icon_white.png"));
        } else {
            this->setIcon(QIcon(":/icons/shutdown_icon_gray.png"));
        }
    } else {
        if (this->activeMode == this->buttonMode){
            this->setProperty("selectedOption", true);
        } else {
            this->setProperty("selectedOption", false);
        }
        this->style()->unpolish(this);
        this->style()->polish(this);
    }
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
        rect.setTop(rect.bottom()-4);
        rect.setLeft(rect.left()+10);
        rect.setRight(rect.right()-10);
        QBrush brush = QBrush(QColor(107, 174, 247));
        painter.fillRect(rect, brush);
    }
}

