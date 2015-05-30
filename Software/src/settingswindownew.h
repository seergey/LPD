#ifndef SETTINGSWINDOWNEW_H
#define SETTINGSWINDOWNEW_H

#include <QMainWindow>

namespace Ui {
class SettingsWindowNew;
}

class SettingsWindowNew : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsWindowNew(QWidget *parent = 0);
    ~SettingsWindowNew();

private:
    Ui::SettingsWindowNew *ui;
};

#endif // SETTINGSWINDOWNEW_H
