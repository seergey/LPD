#ifndef TOGGLABLECUSTOMBUTTON_H
#define TOGGLABLECUSTOMBUTTON_H

#include <QWidget>
#include <QPushButton>

class TogglableCustomButton : public QPushButton
{
    Q_OBJECT
public:
    explicit TogglableCustomButton(QWidget *parent = 0);

    void setButtonMode(int mode);
    void setActiveMode(int mode);

protected:
    void paintEvent(QPaintEvent * paintEvent);

private:
    int buttonMode;
    int activeMode;
    bool isSelected;

signals:

public slots:

};

#endif // TOGGLABLECUSTOMBUTTON_H
