#ifndef DISTRIBUTORLABEL_H
#define DISTRIBUTORLABEL_H
#include <QLabel>


class DistributorLabel : public QLabel
{
    Q_OBJECT
public:
    DistributorLabel(QWidget *parent);
    ~DistributorLabel();

    void mousePressEvent(QMouseEvent *ev);
//    void paintEvent(QPaintEvent* ev);

    void setBasePicture(QString picture);
    void setSelectedPicture(QString picture);
    void unselect();

signals:
    void clicked();

private:
    QString basePicture;
    QString selectedPicture;
    bool selected = false;
    bool entered = false;

};

#endif // DISTRIBUTORLABEL_H
