//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// HistoryScreen 历史记录屏幕
//--------------------------------------------------------------------------------------

#include "c_HistoryScreen.h"
#include "c_InputManager.h"
#include "c_TextManager.h"
#include "c_GameSession.h"


c_HistoryScreen::c_HistoryScreen(const WCHAR *text)
{
	m_text = text;

	m_textureRaise = nullptr;
	m_rectBackground = nullptr;
	m_rectRaise = nullptr;

	SetTransitionOnTime(0.5);
	SetTransitionOffTime(0.5);
	SetIsPopup(true);
}


c_HistoryScreen::~c_HistoryScreen()
{

}


void c_HistoryScreen::LoadContent(void)
{
	NNN::Texture::Add(L"IconRaise", L"Data/IconRaise.png");
	m_textureRaise = NNN::Texture::Find(L"IconRaise");

	LONG width = NNN::Misc::GetClientWidth();
	LONG height = NNN::Misc::GetClientHeight();

	m_clientPosition = make_rect(0, width, 0, height);
	m_textPosition = make_rect(30, width - 60, 0, height);
	m_backPosition = make_rect(0, width, height - 128, height);

	m_rectBackground = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectBackground->SetColor(0xcc000000, NNN::Geometry::Rect::c_RectOrtho::es_point::All);

	m_rectRaise = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectRaise->SetTexture(m_textureRaise);
	
	c_TextManager::DrawString(m_text, 0xffffffff, 0, DT_LEFT | DT_TOP | DT_WORDBREAK | DT_CALCRECT, &m_textPosition);

	if (m_textPosition.bottom > height)
	{
		m_textPosition.top = height - m_textPosition.bottom - 150;
		m_textPosition.bottom = height - 150;
	}
}


void c_HistoryScreen::UnloadContent(void)
{
	SAFE_DELETE(m_rectBackground);
	SAFE_DELETE(m_rectRaise);

	NNN::Texture::Release(L"IconRaise");
	m_textureRaise = nullptr;
}


void c_HistoryScreen::HandleInput(void)
{
	POINT delta = { 0 };

	if (c_InputManager::Pan(&m_clientPosition, &delta))
	{
		if (delta.y > 0)
		{
			if (m_textPosition.top + delta.y < 150)
			{
				m_textPosition.top += delta.y;
				m_textPosition.bottom += delta.y;
			}
		}
		else
		{
			if (m_textPosition.bottom + delta.y > m_clientPosition.bottom - 150)
			{
				m_textPosition.top += delta.y;
				m_textPosition.bottom += delta.y;
			}
		}
	}
	else if (c_InputManager::Tap(&m_backPosition))
	{
		ExitScreen();
	}
}


void c_HistoryScreen::Draw(float fElapsedTime)
{
	if (GetScreenState() == ec_ScreenState::Active)
	{
		if (m_firstFill)
		{
			m_firstFill = false;

			m_rectBackground->SetRect(m_clientPosition);
			m_rectRaise->SetRect(make_rect((m_clientPosition.right - 64) >> 1,
				(m_clientPosition.right + 64) >> 1,
				m_clientPosition.bottom - 64,
				m_clientPosition.bottom));
		}
	}
	else
	{
		LONG detal = GetTransitionPosition() * m_clientPosition.bottom;

		RECT rect = m_clientPosition;
		rect.bottom -= detal;
		m_rectBackground->SetRect(rect);

		rect = make_rect((m_clientPosition.right - 64) >> 1,
			(m_clientPosition.right + 64) >> 1,
			m_clientPosition.bottom - 64,
			m_clientPosition.bottom);
		rect.top -= detal;
		rect.bottom -= detal;
		m_rectRaise->SetRect(rect);
	}

	m_rectBackground->OnRender(fElapsedTime);
	m_rectRaise->OnRender(fElapsedTime);
	
	if (GetScreenState() == ec_ScreenState::Active)
	{
		c_TextManager::DrawString(m_text, 0xffffffff, 0, DT_LEFT | DT_TOP | DT_WORDBREAK, &m_textPosition);
	}
	else
	{
		LONG detal = GetTransitionPosition() * m_clientPosition.bottom;

		RECT position = { 0 };
		position = m_textPosition;
		position.top -= detal;
		position.bottom -= detal;
		c_TextManager::DrawString(m_text, 0xffffffff, 0, DT_LEFT | DT_TOP | DT_WORDBREAK, &position);
	}
}