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
    void updateTrayAndActionStates();


private slots:
    void shutdown();
    void showCommonSettings();
    void showGrabbingSettings();
    void showBacklightSettings();
    void generalBrightnessChanged();
    void minimumBrightnessChanged();
    void generalBrightnessChanged(int newValue);
    void minimumBrightnessChanged(int newValue);
    void minimumBrightnessModeChanged(bool);
    void screenCapturingFrequency();
    void screenCapturingFrequency(int newValue);
    void gammaCorrectionInt();
    void gammaCorrectionDouble(double newValue);
    void smoothness();
    void smoothness(int newValue);
    void keepLightsOnAfterExit(int state);
    void keepLightsOnAfterLock(int state);
    void setMode(int mode);
    void profileChanged(int profileId);
    void animate(int state);
    void animateSpeedChanged();
    void moodLampColorChanged();
    void onPostInit();
    void quit();
    void showSettings();
    void toggleSettings();
    void backlightOn();
    void backlightOff();
    void profileTraySwitch(const QString newProfileName);
    void setupWidgetsClicked();
    void runConfigurationWizardClicked();

signals:
    void backlightStatusChanged(Backlight::Status);
    void switchOffLeds();
    void setLedWidgets(bool);

private:
    Ui::SettingsWindowNew *ui;
    SysTrayIcon *m_trayIcon;
    int m_backlightMode;

    void synchronizeValues(QSlider* slider, QSpinBox* spinBox, int newValue);
    void initProfilesCombo();

};

#endif // SETTINGSWINDOWNEW_H
