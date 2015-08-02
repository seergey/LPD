#ifndef ANIMATECOLORLABEL_H
#define ANIMATECOLORLABEL_H

#include <QWidget>
#include <QLabel>
#include <QColor>



class AnimateColorLabel : public QLabel
{
    Q_OBJECT
public:
    explicit AnimateColorLabel(QWidget *parent = 0);
    ~AnimateColorLabel();

    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent* ev);
    void leaveEvent(QEvent* );
    void paintEvent(QPaintEvent* ev);
    void currentColorChanged(QColor color);

    QColor getColor();
    void setColor(QColor color);

    bool isTop, isBottom;
    QColor color = QColor();
signals:
    void Set_Color_Clicked();
    void Change_Color_Clicked();
    void Delete_Color_Clicked();
    void Color_Changed(QColor);

};

#endif // ANIMATECOLORLABEL_H
