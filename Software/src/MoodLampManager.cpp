/*
 * MoodLampManager.cpp
 *
 *  Created on: 11.12.2011
 *     Project: Lightpack
 *
 *  Copyright (c) 2011 Mike Shatohin, mikeshatohin [at] gmail.com
 *
 *  Lightpack a USB content-driving ambient lighting system
 *
 *  Lightpack is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  Lightpack is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */


#include "MoodLampManager.hpp"
#include "PrismatikMath.hpp"
#include "Settings.hpp"
#include <QTime>

using namespace SettingsScope;

//int MoodLampManager::m_checkColors[MoodLampManager::ColorsMoodLampCount];
//const QColor MoodLampManager::m_colorsMoodLamp[MoodLampManager::ColorsMoodLampCount] =
//{
//    Qt::white, Qt::black, Qt::red, Qt::yellow, Qt::green, Qt::blue, Qt::magenta, Qt::cyan,
//    Qt::darkRed, Qt::darkGreen, Qt::darkBlue, Qt::darkYellow,
//    qRgb(255,128,0), qRgb(128,255,255), qRgb(128,0,255)
//};

MoodLampManager::MoodLampManager(QObject *parent) : QObject(parent)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

    m_isMoodLampEnabled = false;
//    m_rgbSaved = 0;

    m_isLiquidMode = Settings::isMoodLampLiquidMode();
    m_liquidModeSpeed = Settings::getMoodLampSpeed();
    m_colorsMoodLamp = Settings::getMoodLampColors();
    m_colorsMoodLampCount = Settings::getMoodLampColorsCount();

    m_isSendDataOnlyIfColorsChanged = Settings::isSendDataOnlyIfColorsChanges();

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateColors()));
}

void MoodLampManager::start(bool isEnabled)
{
    DEBUG_LOW_LEVEL << Q_FUNC_INFO << isEnabled;

    m_isMoodLampEnabled = isEnabled;

    if (m_isMoodLampEnabled)
    {
        // Clear saved color for force emit signal after check m_rgbSaved != rgb in updateColors()
        // This is usable if start is called after API unlock, and we should force set current color
//        m_rgbSaved = 0;
        updateColors();
    }
    else
        m_timer.stop();
}

void MoodLampManager::moodLampColorsChanged()
{
    DEBUG_MID_LEVEL << Q_FUNC_INFO;

    m_colorsMoodLamp = Settings::getMoodLampColors();
    m_colorsMoodLampCount = Settings::getMoodLampColorsCount();

    if (m_isMoodLampEnabled && (m_isLiquidMode == false) && m_colorsMoodLampCount > 0)
    {
        fillColors(m_colorsMoodLamp[0].rgb());
        emit updateLedsColors(m_colors);
    }
}

void MoodLampManager::setLiquidMode(bool state)
{
    DEBUG_LOW_LEVEL << Q_FUNC_INFO << state;
    m_isLiquidMode = state;
    if (m_isLiquidMode && m_isMoodLampEnabled)
        m_timer.start();
    else {
        m_timer.stop();
        if (m_isMoodLampEnabled)
            updateColors();
    }
}

void MoodLampManager::setLiquidModeSpeed(int value)
{
    DEBUG_LOW_LEVEL << Q_FUNC_INFO << value;
    m_liquidModeSpeed = value;
    m_delay = generateDelay(m_liquidModeSpeed);
}

void MoodLampManager::setSendDataOnlyIfColorsChanged(bool state)
{
    DEBUG_LOW_LEVEL << Q_FUNC_INFO << state;
    m_isSendDataOnlyIfColorsChanged = state;
}

void MoodLampManager::setNumberOfLeds(int numberOfLeds)
{
    DEBUG_LOW_LEVEL << Q_FUNC_INFO << numberOfLeds;

    initColors(numberOfLeds);
    moodLampColorsChanged();
}

void MoodLampManager::reset()
{
//    m_rgbSaved = 0;
}

void MoodLampManager::settingsProfileChanged(const QString &profileName)
{
    DEBUG_LOW_LEVEL << Q_FUNC_INFO;
    Q_UNUSED(profileName)
    initFromSettings();
}

void MoodLampManager::initFromSettings()
{
    m_liquidModeSpeed = Settings::getMoodLampSpeed();
    m_colorsMoodLamp = Settings::getMoodLampColors();
    setLiquidMode(Settings::isMoodLampLiquidMode());
    m_isSendDataOnlyIfColorsChanged = Settings::isSendDataOnlyIfColorsChanges();

    initColors(Settings::getNumberOfLeds(Settings::getConnectedDevice()));
}

void MoodLampManager::updateColors()
{
    DEBUG_HIGH_LEVEL << Q_FUNC_INFO << m_isLiquidMode << m_liquidModeSpeed;

    QRgb rgb;

    if (m_isLiquidMode && m_colorsMoodLampCount > 1)
    {
        static int red   = 0;
        static int green = 0;
        static int blue  = 0;

        static int redNew   = 0;
        static int greenNew = 0;
        static int blueNew  = 0;

        if (red == redNew && green == greenNew && blue == blueNew)
        {
            m_delay = generateDelay(m_liquidModeSpeed);
            QColor colorNew = generateColor();

            redNew = colorNew.red();
            greenNew = colorNew.green();
            blueNew = colorNew.blue();

            DEBUG_HIGH_LEVEL << Q_FUNC_INFO << colorNew;
        }

        if (redNew   != red)  { if (red   > redNew)   --red;   else ++red;   }
        if (greenNew != green){ if (green > greenNew) --green; else ++green; }
        if (blueNew  != blue) { if (blue  > blueNew)  --blue;  else ++blue;  }

        rgb = qRgb(red, green, blue);
    }
    else
    {
        if (m_colorsMoodLampCount > 0)
            rgb = m_colorsMoodLamp[0].rgb();
    }

//    if (m_isSendDataOnlyIfColorsChanged == false)
//    {
        fillColors(rgb);
        emit updateLedsColors(m_colors);
//    }

    if (m_isMoodLampEnabled && m_isLiquidMode && m_colorsMoodLampCount > 1)
    {
        m_timer.start(m_delay);
    }

//    m_rgbSaved = rgb;
}

int MoodLampManager::generateDelay(int speed)
{
    return 1000 / (speed + PrismatikMath::rand(25) + 1);
}

QColor MoodLampManager::generateColor()
{
    if (m_colorsMoodLampCount == 0){
        return QColor();
    }
    if (m_colorsMoodLampCount == 1){
        return m_colorsMoodLamp[0];
    }

    static QList<QColor> unselectedColors;

    if (unselectedColors.empty())
    {
        for (int i = 0; i < m_colorsMoodLampCount; i++)
            unselectedColors << m_colorsMoodLamp[i];
    }

    int randIndex = PrismatikMath::rand(unselectedColors.size());


    QColor newColor = unselectedColors.takeAt(randIndex);

    DEBUG_LOW_LEVEL << Q_FUNC_INFO << newColor.name();

    return newColor;
}

void MoodLampManager::initColors(int numberOfLeds)
{
    DEBUG_LOW_LEVEL << Q_FUNC_INFO << numberOfLeds;

    m_colors.clear();

    for (int i = 0; i < numberOfLeds; i++)
        m_colors << 0;
}

void MoodLampManager::fillColors(QRgb rgb)
{
    DEBUG_MID_LEVEL << Q_FUNC_INFO << rgb;

    for (int i = 0; i < m_colors.size(); i++)
    {
        if (Settings::isLedEnabled(i))
            m_colors[i] = rgb;
        else
            m_colors[i] = 0;
    }
}
