#include "settingswindownew.h"
#include "ui_settingswindownew.h"
#include "Settings.hpp"
#include <QInputDialog>

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
    connect(ui->minimum_brightness_slider, SIGNAL(sliderReleased()), this, SLOT(minimumBrightnessChanged()));
    connect(ui->minimum_brightness_spinbox, SIGNAL(valueChanged(int)), this, SLOT(minimumBrightnessChanged(int)));

    connect(ui->general_brightness_slider, SIGNAL(sliderReleased()), this, SLOT(generalBrightnessChanged()));
    connect(ui->general_brightness_spinbox, SIGNAL(valueChanged(int)), this, SLOT(generalBrightnessChanged(int)));

    connect(ui->screen_capturing_frequency_slider, SIGNAL(sliderReleased()), this, SLOT(screenCapturingFrequency()));
    connect(ui->screen_capturing_frequency_spinbox, SIGNAL(valueChanged(int)), this, SLOT(screenCapturingFrequency(int)));

    connect(ui->smoothness_slider, SIGNAL(sliderReleased()), this, SLOT(smoothness()));
    connect(ui->smoothness_spinbox, SIGNAL(valueChanged(int)), this, SLOT(smoothness(int)));

    connect(ui->gamma_correction_slider, SIGNAL(sliderReleased()), this, SLOT(gammaCorrectionInt()));
    connect(ui->gamma_correction_spinbox, SIGNAL(valueChanged(double)), this, SLOT(gammaCorrectionDouble(double)));

    connect(ui->keep_lights_on_after_lock_checkbox, SIGNAL(stateChanged(int)), this, SLOT(keepLightsOnAfterLock(int)));
    connect(ui->keep_lights_on_after_exit_checkbox, SIGNAL(stateChanged(int)), this, SLOT(keepLightsOnAfterExit(int)));

//    connect(ui->min_brightness_type_dead_zone, SIGNAL(toggled(bool)), this, SLOT(minimumBrightnessModeChanged(bool)));
    connect(ui->min_brightness_type_lumosity, SIGNAL(toggled(bool)), this, SLOT(minimumBrightnessModeChanged(bool)));

    connect(ui->profile_combobox, SIGNAL(currentIndexChanged(int)), this, SLOT(profileChanged(int)));

    connect(ui->animate_check_box, SIGNAL(stateChanged(int)), this, SLOT(animate(int)));
    connect(ui->animation_speed_slider, SIGNAL(sliderReleased()), this, SLOT(animateSpeedChanged()));
    connect(ui->animate_color_1, SIGNAL(Color_Changed(QColor)), this, SLOT(moodLampColorChanged()));
    connect(ui->animate_color_2, SIGNAL(Color_Changed(QColor)), this, SLOT(moodLampColorChanged()));
    connect(ui->animate_color_3, SIGNAL(Color_Changed(QColor)), this, SLOT(moodLampColorChanged()));
    connect(ui->animate_color_4, SIGNAL(Color_Changed(QColor)), this, SLOT(moodLampColorChanged()));
    connect(ui->animate_color_5, SIGNAL(Color_Changed(QColor)), this, SLOT(moodLampColorChanged()));

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

    if (Settings::isBacklightEnabled()){
        if (Settings::getLightpackMode() == Lightpack::AmbilightMode){
            ui->settingsWidget->setCurrentWidget(ui->screen_capturing_settings);

            setMode(1);
        } else if (Settings::getLightpackMode() == Lightpack::MoodLampMode){
            ui->settingsWidget->setCurrentWidget(ui->backLight_settings);

            setMode(2);
        }
    } else {
        setMode(0);
    }

    ui->animate_check_box->setChecked(Settings::isMoodLampLiquidMode());
    ui->animation_speed_slider->setValue(Settings::getMoodLampSpeed());
    ui->animate_color_1->setColor(Settings::getMoodLampColor1());
    ui->animate_color_2->setColor(Settings::getMoodLampColor2());
    ui->animate_color_3->setColor(Settings::getMoodLampColor3());
    ui->animate_color_4->setColor(Settings::getMoodLampColor4());
    ui->animate_color_5->setColor(Settings::getMoodLampColor5());

    initProfilesCombo();
}



void SettingsWindowNew::showCommonSettings()
{
    ui->commonSettingsButton->setIcon(QIcon(":/icons/settings_icon_white.png"));
    ui->settingsWidget->setCurrentWidget(ui->common_settings);
}

void SettingsWindowNew::showGrabbingSettings()
{
    ui->settingsWidget->setCurrentWidget(ui->screen_capturing_settings);
    if (!Settings::isBacklightEnabled()){
        Settings::setIsBacklightEnabled(true);
    }
    Settings::setLightpackMode(Lightpack::AmbilightMode);
    setMode(1);
}

void SettingsWindowNew::showBacklightSettings()
{
    ui->settingsWidget->setCurrentWidget(ui->backLight_settings);
    if (!Settings::isBacklightEnabled()){
        Settings::setIsBacklightEnabled(true);
    }
    Settings::setLightpackMode(Lightpack::MoodLampMode);
    setMode(2);
}
void SettingsWindowNew::generalBrightnessChanged()
{
    generalBrightnessChanged(ui->general_brightness_slider->value());
}

void SettingsWindowNew::minimumBrightnessChanged()
{
    minimumBrightnessChanged(ui->minimum_brightness_slider->value());
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

void SettingsWindowNew::screenCapturingFrequency()
{
    screenCapturingFrequency(ui->screen_capturing_frequency_slider->value());
}

void SettingsWindowNew::screenCapturingFrequency(int newValue)
{
    synchronizeValues(ui->screen_capturing_frequency_slider,
                      ui->screen_capturing_frequency_spinbox,
                      newValue);
    Settings::setGrabSlowdown(newValue);
}

void SettingsWindowNew::gammaCorrectionInt()
{
    int newValue = ui->gamma_correction_slider->value();
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

void SettingsWindowNew::smoothness()
{
    smoothness(ui->smoothness_slider->value());
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
    ui->commonSettingsButton->setIcon(QIcon(":/icons/settings_icon_gray.png"));
    // 0 - shutdown
    // 1 - grabbing
    // 2 - backlighting
    m_backlightMode = mode;
    ui->shutdownButton->setActiveMode(mode);
    ui->grabbing_settings_button->setActiveMode(mode);
    ui->backlightSettingsButton->setActiveMode(mode);
    emit backlightStatusChanged(mode==0 ? Backlight::StatusOff : Backlight::StatusOn);
}

void SettingsWindowNew::profileChanged(int elementId)
{
    if (elementId > 2){
        QString profileName = Settings::findAllProfiles().at(elementId - 3);
        Settings::loadOrCreateProfile(profileName);
        initWithDefaultValues();
    } else {
        if (elementId == 0) { // Create new Profile
            QString newProfileName = QInputDialog::getText(this, tr("Please enter profile name"),
                                                           tr("Profile name:"), QLineEdit::Normal);
            Settings::loadOrCreateProfile(newProfileName);
            initProfilesCombo();
        } else if (elementId == 1) { // Delete current Profile
            if (ui->profile_combobox->count() > 4){
                Settings::removeCurrentProfile();
                QString nextProfileName  = Settings::findAllProfiles().at(0);
                Settings::loadOrCreateProfile(nextProfileName);
                initWithDefaultValues();
            }
            initProfilesCombo();
        }
    }
}

void SettingsWindowNew::animate(int state)
{
    Settings::setMoodLampLiquidMode(state == 2);
}

void SettingsWindowNew::animateSpeedChanged()
{

    Settings::setMoodLampSpeed(ui->animation_speed_slider->value());
}

void SettingsWindowNew::moodLampColorChanged()
{
    Settings::setMoodLampColor(ui->animate_color_1->getColor(),
                               ui->animate_color_2->getColor(),
                               ui->animate_color_3->getColor(),
                               ui->animate_color_4->getColor(),
                               ui->animate_color_5->getColor()
                               );
}


void SettingsWindowNew::onPostInit()
{
    if (m_trayIcon)
        m_trayIcon->checkUpdate();

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

void SettingsWindowNew::initProfilesCombo()
{
    disconnect(ui->profile_combobox, SIGNAL(currentIndexChanged(int)), this, SLOT(profileChanged(int)));

    ui->profile_combobox->clear();

    QStringList profilesList = Settings::findAllProfiles();
    ui->profile_combobox->addItem("Create new Profile");
    ui->profile_combobox->addItem("Delete current Profile");
    ui->profile_combobox->insertSeparator(2);
    for (int i = 0; i < profilesList.count(); i++)
    {
        if (ui->profile_combobox->findText(profilesList.at(i)) == -1) {
            ui->profile_combobox->addItem(profilesList.at(i));
        }
    }
    int idx = ui->profile_combobox->findText(Settings::getCurrentProfileName());
    if (idx < 0){
        idx = 2;
    }
    ui->profile_combobox->setCurrentIndex(idx);
    connect(ui->profile_combobox, SIGNAL(currentIndexChanged(int)), this, SLOT(profileChanged(int)));

}

void SettingsWindowNew::createTrayIcon()
{
    DEBUG_LOW_LEVEL << Q_FUNC_INFO;
    m_trayIcon = new SysTrayIcon();
    connect(m_trayIcon, SIGNAL(quit()), this, SLOT(quit()));
    connect(m_trayIcon, SIGNAL(showSettings()), this, SLOT(showSettings()));
    connect(m_trayIcon, SIGNAL(toggleSettings()), this, SLOT(toggleSettings()));
    connect(m_trayIcon, SIGNAL(backlightOn()), this, SLOT(backlightOn()));
    connect(m_trayIcon, SIGNAL(backlightOff()), this, SLOT(backlightOff()));
    connect(m_trayIcon, SIGNAL(profileSwitched(QString)), this, SLOT(profileTraySwitch(QString)));

    m_trayIcon->init();
    connect(this, SIGNAL(backlightStatusChanged(Backlight::Status)), this, SLOT(updateTrayAndActionStates()));
}

void SettingsWindowNew::quit()
{
    if (!ui->keep_lights_on_after_exit_checkbox->isChecked())
    {
        // Process all currently pending signals (which may include updating the color signals)
        QApplication::processEvents(QEventLoop::AllEvents, 1000);

        emit switchOffLeds();
        QApplication::processEvents(QEventLoop::AllEvents, 1000);
    }

    DEBUG_LOW_LEVEL << Q_FUNC_INFO << "trayIcon->hide();";

    if (m_trayIcon!=NULL) {
        m_trayIcon->hide();
    }

    DEBUG_LOW_LEVEL << Q_FUNC_INFO << "QApplication::quit();";

    QApplication::quit();
}

void SettingsWindowNew::showSettings()
{

}

void SettingsWindowNew::toggleSettings()
{

}

void SettingsWindowNew::backlightOn()
{

}

void SettingsWindowNew::backlightOff()
{

}

void SettingsWindowNew::profileTraySwitch(const QString newProfileName)
{

}

void SettingsWindowNew::updateTrayAndActionStates()
{
    DEBUG_MID_LEVEL << Q_FUNC_INFO;

    if (m_trayIcon== NULL) return;

    switch (m_backlightMode)
    {
    case 1:
    case 2:
//        ui->pushButton_EnableDisableDevice->setIcon(QIcon(*m_pixmapCache["off16"]));
//        ui->pushButton_EnableDisableDevice->setText("  " + tr("Turn lights OFF"));
        m_trayIcon->setStatus(SysTrayIcon::StatusOn);
//        if (m_deviceLockStatus == DeviceLocked::Api)
//        {
////            m_labelStatusIcon->setPixmap(*m_pixmapCache["lock16"]);
//            if (m_trayIcon)
//                m_trayIcon->setStatus(SysTrayIcon::StatusLockedByApi);
//        } else
//            if (m_deviceLockStatus == DeviceLocked::Plugin)
//            {
////                m_labelStatusIcon->setPixmap(*m_pixmapCache["lock16"]);
//                if (m_trayIcon)
//                    m_trayIcon->setStatus(SysTrayIcon::StatusLockedByPlugin, &m_deviceLockModule);
//            } else {
////                m_labelStatusIcon->setPixmap(*m_pixmapCache["on16"]);
//                if (m_trayIcon)
//                    m_trayIcon->setStatus(SysTrayIcon::StatusOn);
//            }
        break;

    case 0:
//        m_labelStatusIcon->setPixmap(*m_pixmapCache["off16"]);
//        ui->pushButton_EnableDisableDevice->setIcon(QIcon(*m_pixmapCache["on16"]));
//        ui->pushButton_EnableDisableDevice->setText("  " + tr("Turn lights ON"));
        if (m_trayIcon)
            m_trayIcon->setStatus(SysTrayIcon::StatusOff);
        break;
    default:
        qWarning() << Q_FUNC_INFO << "m_backlightStatus = " << m_backlightMode;
        break;
    }
//    if (m_trayIcon)
//        m_labelStatusIcon->setToolTip(m_trayIcon->toolTip());
}
