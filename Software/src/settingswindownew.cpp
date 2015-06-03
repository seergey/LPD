#include "settingswindownew.h"
#include "ui_settingswindownew.h"
#include "Settings.hpp"

using namespace SettingsScope;

SettingsWindowNew::SettingsWindowNew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SettingsWindowNew)
{
    ui->setupUi(this);
}

SettingsWindowNew::~SettingsWindowNew()
{
    delete ui;
}

void SettingsWindowNew::connectSignalSlots()
{
    //     connect(ui->listWidget, SIGNAL(currentRowChanged(int)), this, SLOT(changePage(int)));

    connect(ui->shutdownButton, SIGNAL(clicked(bool)), this, SLOT(shutdown()));
    connect(ui->grabbing_settings_button, SIGNAL(clicked(bool)), this, SLOT(showGrabbingSettings()));
    connect(ui->commonSettingsButton, SIGNAL(clicked(bool)), this, SLOT(showCommonSettings()));
    connect(ui->backlightSettingsButton, SIGNAL(clicked(bool)), this, SLOT(showBacklightSettings()));
    connect(ui->minimum_brightness_slider, SIGNAL(valueChanged(int)), this, SLOT(minimumBrightnessChanged(int)));
    connect(ui->minimum_brightness_spinbox, SIGNAL(valueChanged(int)), this, SLOT(minimumBrightnessChanged(int)));

    connect(ui->general_brightness_slider, SIGNAL(valueChanged(int)), this, SLOT(generalBrightnessChanged(int)));
    connect(ui->general_brightness_spinbox, SIGNAL(valueChanged(int)), this, SLOT(generalBrightnessChanged(int)));

    connect(ui->screen_capturing_frequency_slider, SIGNAL(valueChanged(int)), this, SLOT(screenCapturingFrequency(int)));
    connect(ui->screen_capturing_frequency_spinbox, SIGNAL(valueChanged(int)), this, SLOT(screenCapturingFrequency(int)));

    connect(ui->smoothness_slider, SIGNAL(valueChanged(int)), this, SLOT(smoothness(int)));
    connect(ui->smoothness_spinbox, SIGNAL(valueChanged(int)), this, SLOT(smoothness(int)));

    connect(ui->gamma_correction_slider, SIGNAL(valueChanged(int)), this, SLOT(gammaCorrectionInt(int)));
    connect(ui->gamma_correction_spinbox, SIGNAL(valueChanged(double)), this, SLOT(gammaCorrectionDouble(double)));

    connect(ui->keep_lights_on_after_lock_checkbox, SIGNAL(stateChanged(int)), this, SLOT(keepLightsOnAfterLock(int)));
    connect(ui->keep_lights_on_after_exit_checkbox, SIGNAL(stateChanged(int)), this, SLOT(keepLightsOnAfterExit(int)));

//    connect(ui->min_brightness_type_dead_zone, SIGNAL(toggled(bool)), this, SLOT(minimumBrightnessModeChanged(bool)));
    connect(ui->min_brightness_type_lumosity, SIGNAL(toggled(bool)), this, SLOT(minimumBrightnessModeChanged(bool)));

    //    connect(ui->)
}

void SettingsWindowNew::initWithDefaultValues()
{
    ui->general_brightness_slider->setValue(Settings::getDeviceBrightness());
    ui->general_brightness_spinbox->setValue(Settings::getDeviceBrightness());

    ui->minimum_brightness_slider->setValue(Settings::getLuminosityThreshold());
    ui->minimum_brightness_spinbox->setValue(Settings::getLuminosityThreshold());

    ui->min_brightness_type_lumosity->setChecked(Settings::isMinimumLuminosityEnabled());
    ui->min_brightness_type_dead_zone->setChecked(!Settings::isMinimumLuminosityEnabled());

    ui->screen_capturing_frequency_slider->setValue(Settings::getGrabSlowdown());
    ui->screen_capturing_frequency_spinbox->setValue(Settings::getGrabSlowdown());

    ui->gamma_correction_slider->setValue(Settings::getDeviceGamma()*20);
    ui->gamma_correction_spinbox->setValue(Settings::getDeviceGamma());

    ui->smoothness_slider->setValue(Settings::getDeviceSmooth());
    ui->smoothness_spinbox->setValue(Settings::getDeviceSmooth());

    ui->keep_lights_on_after_exit_checkbox->setChecked(Settings::isKeepLightsOnAfterExit());
    ui->keep_lights_on_after_lock_checkbox->setChecked(Settings::isKeepLightsOnAfterLock());

    ui->shutdownButton->setButtonMode(0);
    ui->grabbing_settings_button->setButtonMode(1);
    ui->backlightSettingsButton->setButtonMode(2);
}

void SettingsWindowNew::showCommonSettings()
{
    ui->settingsWidget->setCurrentWidget(ui->common_settings);
}

void SettingsWindowNew::showGrabbingSettings()
{
    ui->settingsWidget->setCurrentWidget(ui->screen_capturing_settings);
    if (!Settings::isBacklightEnabled()){
        Settings::setIsBacklightEnabled(true);
        Settings::setLightpackMode(Lightpack::AmbilightMode);
    }
    setMode(1);
}

void SettingsWindowNew::showBacklightSettings()
{
    ui->settingsWidget->setCurrentWidget(ui->backLight_settings);
    if (!Settings::isBacklightEnabled()){
        Settings::setIsBacklightEnabled(true);
        Settings::setLightpackMode(Lightpack::MoodLampMode);
    }
    setMode(2);
}

void SettingsWindowNew::generalBrightnessChanged(int newValue)
{
    synchronizeValues(ui->general_brightness_slider,
                      ui->general_brightness_spinbox,
                      newValue);
    Settings::setDeviceBrightness(newValue);
}

void SettingsWindowNew::minimumBrightnessChanged(int newValue)
{
    synchronizeValues(ui->minimum_brightness_slider,
                      ui->minimum_brightness_spinbox,
                      newValue);
    Settings::setLuminosityThreshold(newValue);
}

void SettingsWindowNew::minimumBrightnessModeChanged(bool)
{
    Settings::setMinimumLuminosityEnabled(ui->min_brightness_type_lumosity->isChecked());
}

void SettingsWindowNew::screenCapturingFrequency(int newValue)
{
    synchronizeValues(ui->screen_capturing_frequency_slider,
                      ui->screen_capturing_frequency_spinbox,
                      newValue);
    Settings::setGrabSlowdown(newValue);
}

void SettingsWindowNew::gammaCorrectionInt(int newValue)
{
    int oldIntValue = ui->gamma_correction_spinbox->value() * 20.0;
    if (oldIntValue != newValue){
        double newDoubleValue = newValue/20.0;
        ui->gamma_correction_spinbox->setValue(newDoubleValue);
        Settings::setDeviceGamma(newDoubleValue);
    }
}

void SettingsWindowNew::gammaCorrectionDouble(double newValue)
{
    int newIntValue = newValue*20;
    if (ui->gamma_correction_slider->value() != newIntValue){
        ui->gamma_correction_slider->setValue(newIntValue);
        Settings::setDeviceGamma(newValue);
    }
}

void SettingsWindowNew::smoothness(int newValue)
{
    synchronizeValues(ui->smoothness_slider,
                      ui->smoothness_spinbox,
                      newValue);
    Settings::setDeviceSmooth(newValue);
}

void SettingsWindowNew::keepLightsOnAfterExit(int state)
{
    Settings::setKeepLightsOnAfterExit(state == Qt::Checked);
}

void SettingsWindowNew::keepLightsOnAfterLock(int state)
{
    Settings::setKeepLightsOnAfterLock(state == Qt::Checked);
}

void SettingsWindowNew::setMode(int mode)
{
    // 0 - shutdown
    // 1 - grabbing
    // 2 - backlighting
    ui->shutdownButton->setActiveMode(mode);
    ui->grabbing_settings_button->setActiveMode(mode);
    ui->backlightSettingsButton->setActiveMode(mode);

}

void SettingsWindowNew::profileChanged(int profileId)
{

}

void SettingsWindowNew::profileSaved(int profileId)
{

}

void SettingsWindowNew::shutdown()
{
    setMode(0);
    Settings::setIsBacklightEnabled(false);
//    QApplication::quit();
}

void SettingsWindowNew::synchronizeValues(QSlider* slider, QSpinBox* spinBox, int newValue){
    if (slider->value() != newValue){
        slider->setValue(newValue);
    }
    if (spinBox->value() != newValue){
        spinBox->setValue(newValue);
    }
}
