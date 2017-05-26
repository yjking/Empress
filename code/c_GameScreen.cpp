//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// GameScreen 游戏屏幕（抽象基类）
//--------------------------------------------------------------------------------------

#include "c_GameScreen.h"
#include "c_GameSession.h"


c_GameScreen::c_GameScreen()
{
	m_isPopup = false;
	m_transitionOnTime = 0;
	m_transitionOffTime = 0;
	m_transitionPosition = 1;
	m_screenState = ec_ScreenState::TransitionOn;
	m_isExiting = false;
	m_otherScreenHasFocus = false;
	Exiting = nullptr;
}


c_GameScreen::~c_GameScreen()
{

}


bool c_GameScreen::GetIsPopup(void) const
{
	return m_isPopup;
}


float c_GameScreen::GetTransitionOnTime(void) const
{
	return m_transitionOnTime;
}


float c_GameScreen::GetTransitionOffTime(void) const
{
	return m_transitionOffTime;
}


float c_GameScreen::GetTransitionPosition(void) const
{
	return m_transitionPosition;
}


int c_GameScreen::GetTransitionAlpha(void) const
{
	return (int)(255 - m_transitionPosition * 255);
}


ec_ScreenState c_GameScreen::GetScreenState(void) const
{
	return m_screenState;
}


bool c_GameScreen::GetIsExiting(void) const
{
	return m_isExiting;
}


void c_GameScreen::SetIsExiting(bool value)
{
	bool fireEvent = !m_isExiting && value;
	m_isExiting = value;
	if (fireEvent && (Exiting != nullptr))
	{
		(*Exiting)(this);
	}
}


bool c_GameScreen::GetIsActive(void) const
{
	return !m_otherScreenHasFocus &&
		(m_screenState == ec_ScreenState::TransitionOn ||
		m_screenState == ec_ScreenState::Active);
}


void c_GameScreen::Update(float fElapsedTime, bool otherScreenHasFocus, bool coveredByOtherScreen)
{
	m_otherScreenHasFocus = otherScreenHasFocus;

	if (GetIsExiting())
	{
		// If the screen is going away to die, it should transition off.
		m_screenState = ec_ScreenState::TransitionOff;

		if (!UpdateTransition(fElapsedTime, m_transitionOffTime, 1))
		{
			// When the transition finishes, remove the screen.
			c_GameSession::GetSingleton()->GetScreenManager()->RemoveScreen(this);
		}
	}
	else if (coveredByOtherScreen)
	{
		// If the screen is covered by another, it should transition off.
		if (UpdateTransition(fElapsedTime, m_transitionOffTime, 1))
		{
			// Still busy transitioning.
			m_screenState = ec_ScreenState::TransitionOff;
		}
		else
		{
			// Transition finished!
			m_screenState = ec_ScreenState::Hidden;
		}
	}
	else
	{
		// Otherwise the screen should transition on and become active.
		if (UpdateTransition(fElapsedTime, m_transitionOnTime, -1))
		{
			// Still busy transitioning.
			m_screenState = ec_ScreenState::TransitionOn;
		}
		else
		{
			// Transition finished!
			m_screenState = ec_ScreenState::Active;
		}
	}

	if (m_screenState != ec_ScreenState::Hidden && m_scene != nullptr) {
		m_scene->OnFrameMove(fElapsedTime);
	}
}


#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
HRESULT c_GameScreen::OnReset_dx9(void)
{
	return m_scene != nullptr ? m_scene->OnReset_dx9() : S_OK;
}


HRESULT c_GameScreen::OnLost_dx9(void)
{
	return m_scene != nullptr ? m_scene->OnLost_dx9() : S_OK;
}
#endif	// NNN_PLATFORM_WIN32


void c_GameScreen::ExitScreen(void)
{
	// flag that it should transition off and then exit.
	SetIsExiting(true);
	// If the screen has a zero transition time, remove it immediately.
	if (GetTransitionOffTime() == 0)
	{
		c_GameSession::GetSingleton()->GetScreenManager()->RemoveScreen(this);
	}
}


void c_GameScreen::SetIsPopup(bool value)
{
	m_isPopup = value;
}


void c_GameScreen::SetTransitionOnTime(float value)
{
	m_transitionOnTime = value;
}


void c_GameScreen::SetTransitionOffTime(float value)
{
	m_transitionOffTime = value;
}


void c_GameScreen::SetTransitionPosition(float value)
{
	m_transitionPosition = value;
}


void c_GameScreen::SetScreenState(ec_ScreenState value)
{
	m_screenState = value;
}


bool c_GameScreen::UpdateTransition(float fElapsedTime, float time, int direction)
{
	// How much should we move by?
	float transitionDelta;

	if (time == 0)
	{
		transitionDelta = 1;
	}
	else
	{
		transitionDelta = (float)(fElapsedTime / time);
	}

	// Update the transition position.
	m_transitionPosition += transitionDelta * direction;

	// Did we reach the end of the transition?
	if ((m_transitionPosition <= 0) || (m_transitionPosition >= 1))
	{
		if (m_transitionPosition < 0)
		{
			m_transitionPosition = 0;
		}
		else if (m_transitionPosition > 1)
		{
			m_transitionPosition = 1;
		}
		return false;
	}

	// Otherwise we are still busy transitioning.
	return true;
}