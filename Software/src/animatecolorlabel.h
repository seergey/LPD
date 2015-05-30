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

    bool isTop, isBottom;
    QColor* color = NULL;
signals:
    void Set_Color_Clicked();
    void Change_Color_Clicked();
    void Delete_Color_Clicked();

};

#endif // ANIMATECOLORLABEL_H
