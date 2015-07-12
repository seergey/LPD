#ifndef SETTINGSWINDOWNEW_H
#define SETTINGSWINDOWNEW_H

#include <QMainWindow>
#include <QSpinBox>
#include <QSlider>
#include "enums.hpp"
#include "Settings.hpp"

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
    void createTrayIcon();


private slots:
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
    void animate(int state);
    void animateSpeedChanged(int value);
    void moodLampColorChanged();
    void onPostInit();
    void quit();
    void showSettings();
    void toggleSettings();
    void backlightOn();
    void backlightOff();
    void profileTraySwitch(const QString newProfileName);
    void updateTrayAndActionStates();

signals:
    void backlightStatusChanged(Backlight::Status);
    void switchOffLeds();

private:
    Ui::SettingsWindowNew *ui;
    SysTrayIcon *m_trayIcon;
    int m_backlightMode;

    void synchronizeValues(QSlider* slider, QSpinBox* spinBox, int newValue);
    void initProfilesCombo();

};

#endif // SETTINGSWINDOWNEW_H
