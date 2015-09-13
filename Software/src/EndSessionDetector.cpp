#include "EndSessionDetector.hpp"
#include "debug.h"
#include "LightpackApplication.hpp"

#include <exception>

#ifdef Q_OS_WIN
#if !defined NOMINMAX
#define NOMINMAX
#endif

#if !defined WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <WtsApi32.h>
#endif

class register_exception : public std::exception {
  virtual const char* what() const throw()
  {
    return "Failed to register session notification";
  }
};

EndSessionDetector::EndSessionDetector()
	: m_isDestroyed(false)
{
#ifdef Q_OS_WIN
	if (WTSRegisterSessionNotification(getLightpackApp()->getMainWindowHandle(), NOTIFY_FOR_THIS_SESSION) == FALSE)
        throw register_exception();
#endif
}

bool EndSessionDetector::nativeEventFilter(const QByteArray& eventType, void* message, long* result)
{
	Q_UNUSED(result);
	Q_UNUSED(eventType);
	Q_UNUSED(message);

	bool isSessionEnding = false;
	bool isSessionResuming = false;

#ifdef Q_OS_WIN
	MSG* msg = (MSG*)message;

	if (msg->message == WM_QUERYENDSESSION)
	{
       qWarning() << "WM_QUERYENDSESSION";
		if (!SettingsScope::Settings::isKeepLightsOnAfterExit())
		{
			Destroy();
			isSessionEnding = true;
		}
	}
	else if (msg->message == WM_WTSSESSION_CHANGE)
	{
        qWarning() << "WM_WTSSESSION_CHANGE";

		if (!SettingsScope::Settings::isKeepLightsOnAfterLock())
		{
			if (msg->wParam == WTS_SESSION_LOCK)
			{
				isSessionEnding = true;
			}
			else if (msg->wParam == WTS_SESSION_UNLOCK)
			{
				isSessionResuming = true;
			}
		}
    } else if (msg->message == WM_POWERBROADCAST){

        if (!SettingsScope::Settings::isKeepLightsOnAfterLock())
        {
            if (msg->wParam == PBT_APMSTANDBY || msg->wParam == PBT_APMSUSPEND)
            {
                isSessionEnding = true;
            }
            else if (msg->wParam == PBT_APMRESUMESUSPEND
                     || msg->wParam == PBT_APMRESUMESTANDBY)
            {
                isSessionResuming = true;
            }
        }

    }
#endif

	if (isSessionEnding)
		getLightpackApp()->settingsWnd()->switchOffLeds();
	else if (isSessionResuming)
		getLightpackApp()->settingsWnd()->switchOnLeds();

	return false;
}

void EndSessionDetector::Destroy()
{
	if (!m_isDestroyed)
	{
		m_isDestroyed = true;
#ifdef Q_OS_WIN
		WTSUnRegisterSessionNotification(getLightpackApp()->getMainWindowHandle());
#endif
	}
}

EndSessionDetector::~EndSessionDetector()
{
	Destroy();
}
