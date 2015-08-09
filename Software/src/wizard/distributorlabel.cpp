#include "distributorlabel.h"
#include <QPainter>
#include <QStyle>
#include <QVariant>

DistributorLabel::DistributorLabel (QWidget *parent) : QLabel(parent)
{
    this->setMouseTracking(true);
}

DistributorLabel::~DistributorLabel()
{

}

void DistributorLabel::mousePressEvent(QMouseEvent *ev)
{
    this->style()->unpolish(this);
    this->setProperty("selected", true);
    this->style()->polish(this);
    update();
    emit clicked();
}

//    QPainter painter(this);
//    if (this->selected) {
//        painter.setPen(QColor("#6baef7"));
//    } else if (this->entered){
//        painter.setPen(QColor("#8f96a4"));
//    } else {
//        painter.setPen(QColor("#d5d8dd"));
//    }
//    painter.drawRoundedRect(0,0, width()-1, height()-1, 15, 15);


void DistributorLabel::setBasePicture(QString picture)
{
    this->basePicture = picture;
}

void DistributorLabel::setSelectedPicture(QString picture)
{
    this->selectedPicture = picture;
}

void DistributorLabel::unselect()
{
    this->setProperty("selected", false);
    this->style()->unpolish(this);
    this->style()->polish(this);
    update();
}

