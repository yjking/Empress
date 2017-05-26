//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// ScreenManager 屏幕管理
//--------------------------------------------------------------------------------------

#include "c_ScreenManager.h"
#include "c_GameSession.h"


c_ScreenManager::c_ScreenManager(void)
{

}


c_ScreenManager::~c_ScreenManager(void)
{
	unsigned count = m_screens.size();
	for (unsigned i = 0; i < count; ++i)
	{
		RemoveScreen(m_screens[count - i - 1]);
	}
	ReleaseScreens();
}


void c_ScreenManager::Update(float fElapsedTime)
{
	// Make a copy of the master screen list, to avoid confusion if
	// the process of updating one screen adds or removes others.
	ReleaseScreens();
	m_screensToUpdate.clear();

	for (std::vector<c_GameScreen*>::const_iterator iter = m_screens.begin(); iter != m_screens.end(); ++iter)
	{
		m_screensToUpdate.push_back(*iter);
	}

	bool otherScreenHasFocus = !c_GameSession::GetSingleton()->GetIsActive();
	bool coveredByOtherScreen = false;

	// Loop as long as there are screens waiting to be updated.
	while (!m_screensToUpdate.empty())
	{
		// Pop the topmost screen off the waiting list.
		c_GameScreen *screen = m_screensToUpdate.back();
		m_screensToUpdate.pop_back();

		// Update the screen.
		screen->Update(fElapsedTime, otherScreenHasFocus, coveredByOtherScreen);

		if (screen->GetScreenState() == ec_ScreenState::TransitionOn ||
			screen->GetScreenState() == ec_ScreenState::Active)
		{
			// If this is the first active screen we came across,
			// give it a chance to handle input.
			if (!otherScreenHasFocus)
			{
				screen->HandleInput();
				otherScreenHasFocus = true;
			}

			// If this is an active non-popup, inform any subsequent
			// screens that they are covered by it.
			if (!screen->GetIsPopup())
			{
				coveredByOtherScreen = true;
			}
		}
	}
}


void c_ScreenManager::Draw(float fElapsedTime) const
{
	for (std::vector<c_GameScreen*>::const_iterator iter = m_screens.begin(); iter != m_screens.end(); ++iter)
	{
		if ((*iter)->GetScreenState() == ec_ScreenState::Hidden)
		{
			continue;
		}
		(*iter)->Draw(fElapsedTime);
	}
}


#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
HRESULT c_ScreenManager::OnReset_dx9(void)
{
	for (std::vector<c_GameScreen*>::const_iterator iter = m_screens.begin(); iter != m_screens.end(); ++iter)
	{
		(*iter)->OnReset_dx9();
	}
	return S_OK;
}


HRESULT c_ScreenManager::OnLost_dx9(void)
{
	for (std::vector<c_GameScreen*>::const_iterator iter = m_screens.begin(); iter != m_screens.end(); ++iter)
	{
		(*iter)->OnLost_dx9();
	}
	return S_OK;
}
#endif	// NNN_PLATFORM_WIN32


void c_ScreenManager::AddScreen(c_GameScreen *screen)
{
	screen->SetIsExiting(false);
	screen->LoadContent();
	m_screens.push_back(screen);
}


void c_ScreenManager::RemoveScreen(c_GameScreen *screen)
{
	screen->UnloadContent();

	for (unsigned i = 0; i < m_screens.size(); ++i)
	{
		if (m_screens[i] == screen)
		{
			m_screens.erase(m_screens.begin() + i);
			break;
		}
	}

	for (unsigned i = 0; i < m_screensToUpdate.size(); ++i)
	{
		if (m_screensToUpdate[i] == screen)
		{
			m_screensToUpdate.erase(m_screensToUpdate.begin() + i);
			break;
		}
	}

	if (screen != c_GameSession::GetSingleton()->GetMainScreen())
	{
		m_screensToRelease.push_back(screen);
	}
}


void c_ScreenManager::ReleaseScreens(void)
{
	unsigned count = m_screensToRelease.size();
	for (unsigned i = 0; i < count; ++i)
	{
		c_GameScreen *screen = m_screensToRelease.back();
		m_screensToRelease.pop_back();
		SAFE_DELETE(screen);
	}
}