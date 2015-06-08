#include "animatecolorlabel.h"
#include <QPainter>
#include <QBrush>
#include <QPen>
#include <QPaintEvent>
#include <QImageWriter>
#include <QColorDialog>


AnimateColorLabel::AnimateColorLabel(QWidget *parent) : QLabel(parent)
{

}

AnimateColorLabel::~AnimateColorLabel()
{

}

void AnimateColorLabel::mousePressEvent(QMouseEvent *ev)
{
    QColorDialog * dialog = new QColorDialog(this);
    dialog->setWindowFlags(Qt::Window
                          | Qt::WindowStaysOnTopHint
                          | Qt::CustomizeWindowHint
                          | Qt::WindowCloseButtonHint);

    QColor result = dialog->getColor(this->color==NULL ? Qt::white : *(this->color));
    if (result.isValid()) {
        delete this->color;
        this->color = new QColor(result);
        update();
    }
    delete dialog;

}

void AnimateColorLabel::currentColorChanged(QColor color)
{
    this->color = new QColor(color);
}


void AnimateColorLabel::mouseMoveEvent(QMouseEvent *ev)
{

}

void AnimateColorLabel::leaveEvent(QEvent *)
{

}

void AnimateColorLabel::paintEvent(QPaintEvent *ev)
{
    QLabel::paintEvent(ev);
    if (color != NULL) {
    QPainter painter(this);
//    painter.setPen(QPen(Qt::red,2, Qt::SolidLine, Qt::FlatCap));
    QRect rect  = ev->rect();
    rect.setBottom(rect.bottom()-1);
    rect.setTop(rect.top()+1);
    rect.setLeft(rect.left()+1);
    rect.setRight(rect.right()-1);
    QBrush brush = QBrush(*color);
    painter.fillRect(rect, brush);
    QList<QByteArray> array = QImageWriter::supportedImageFormats();
    if (isTop || isBottom) {
        painter.setPen(QPen(Qt::black));
        QPoint point1 = rect.bottomLeft();
        QPoint point2 = rect.bottomRight();
        point1.setY(point1.y()/2+1);
        point2.setY(point2.y()/2+1);
        painter.drawLine(point1, point2);
        QImage* image = new QImage(":/icons/settings_button_black.png");
        painter.drawImage(20, 6, *image);
        delete image;

        int y = rect.bottom()*3/4;
        int x = rect.right()/2;
        QPen pen = QPen(Qt::black);
        pen.setWidth(2);
        painter.setPen(pen);
        painter.drawLine(QPoint(x-3, y-3), QPoint(x+4, y+4));
        painter.drawLine(QPoint(x+4, y-3), QPoint(x-3, y+4));


//        size.setHeight(size.height()/2+1);
//        QPoint point1 = rect.topLeft();
//        QRect topRect = QRect(point1, size);
//        painter.fillRect(topRect, QBrush(Qt::red));
//        brush.setColor(QColor::fromHsl(hue, saturation, lightness));
//        QRect bottomRect = QRect(point2, size);
//    painter.setBrush(QPen(Qt::blue,2, Qt::SolidLine, Qt::FlatCap));
//    brush.setColor(QColor::fromHsl(hue+20, saturation, lightness));
//    painter.fillRect(bottomRect, brush);
    } else {
//    painter.drawText(ev->rect(), Qt::AlignCenter, "AAAAA");
//    rect.setBottom(rect.bottom()-30);
//    rect.setTop(rect.top()+30);
//    painter.drawRect(rect);
    }
    }

}


