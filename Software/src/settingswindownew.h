#ifndef SETTINGSWINDOWNEW_H
#define SETTINGSWINDOWNEW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QSlider>
#include "enums.hpp"

namespace Ui {
class SettingsWindowNew;
}

class SettingsWindowNew : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingsWindowNew(QWidget *parent = 0);
    ~SettingsWindowNew();

    void connectSignalSlots();
    void initWithDefaultValues();

public slots:
    void shutdown();
    void showCommonSettings();
    void showGrabbingSettings();
    void showBacklightSettings();
    void generalBrightnessChanged(int newValue);
    void minimumBrightnessChanged(int newValue);
    void minimumBrightnessModeChanged(bool);
    void screenCapturingFrequency(int newValue);
    void gammaCorrectionInt(int newValue);
    void gammaCorrectionDouble(double newValue);
    void smoothness(int newValue);
    void keepLightsOnAfterExit(int state);
    void keepLightsOnAfterLock(int state);
    void setMode(int mode);
    void profileChanged(int profileId);
    void profileSaved(int profileId);
signals:
    void backlightStatusChanged(Backlight::Status);

private:
    Ui::SettingsWindowNew *ui;
    void synchronizeValues(QSlider* slider, QSpinBox* spinBox, int newValue);

};

#endif // SETTINGSWINDOWNEW_H
