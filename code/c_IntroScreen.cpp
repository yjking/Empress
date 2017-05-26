//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// IntroScreen 入场屏幕
//--------------------------------------------------------------------------------------

#include "c_IntroScreen.h"
#include "c_InputManager.h"
#include "c_TextManager.h"
#include "c_GameSession.h"
#include "c_TitleScreen.h"


c_IntroScreen::c_IntroScreen()
{
	m_textureNewGameLogo = nullptr;
	m_rectNewGameLogo = nullptr;

	m_totalTime = 0;
}


c_IntroScreen::~c_IntroScreen()
{

}


void c_IntroScreen::LoadContent(void)
{
	NNN::Texture::Add(L"NewGameLogo", L"Data/NewGameLogo.png");
	m_textureNewGameLogo = NNN::Texture::Find(L"NewGameLogo");

	LONG width = NNN::Misc::GetClientWidth();
	LONG height = NNN::Misc::GetClientHeight();
	m_clientPosition = make_rect(0, width, 0, height);
	m_zcloudPosition = make_rect(0, width, (height >> 1) - 20, (height >> 1) + 20);

	m_rectNewGameLogo = new NNN::Geometry::Rect::c_RectOrtho();
	UINT imageWidth = m_textureNewGameLogo->GetImageWidth();
	UINT imageHeight = m_textureNewGameLogo->GetImageHeight();
	m_rectNewGameLogo->SetRect(make_rect((m_clientPosition.right - imageWidth) >> 1,
		(m_clientPosition.right + imageWidth) >> 1,
		(m_clientPosition.bottom - imageHeight) >> 1,
		(m_clientPosition.bottom + imageHeight) >> 1));
	m_rectNewGameLogo->SetTexture(m_textureNewGameLogo);
}


void c_IntroScreen::UnloadContent(void)
{
	SAFE_DELETE(m_rectNewGameLogo);

	NNN::Texture::Release(L"NewGameLogo");
	m_textureNewGameLogo = nullptr;
}


void c_IntroScreen::HandleInput(void)
{	
	if (c_InputManager::Tap(&m_clientPosition) || m_totalTime > 8)
	{
		ExitScreen();
		c_GameSession::GetSingleton()->GetScreenManager()->AddScreen(new c_TitleScreen());
	}
}


void c_IntroScreen::Draw(float fElapsedTime)
{
	m_totalTime += fElapsedTime;
	
	if (m_totalTime < 2)
	{
		c_TextManager::DrawString(5, ((int)(m_totalTime * 0x80) << 24) | 0xffffff, 0, DT_CENTER | DT_VCENTER, &m_zcloudPosition);
	}
	else if (m_totalTime < 3)
	{
		c_TextManager::DrawString(5, 0xffffffff, 0, DT_CENTER | DT_VCENTER, &m_zcloudPosition);
	}
	else if (m_totalTime < 4)
	{
		c_TextManager::DrawString(5, ((int)((4 - m_totalTime) * 0xff) << 24) | 0xffffff, 0, DT_CENTER | DT_VCENTER, &m_zcloudPosition);
	}
	else if (m_totalTime < 8)
	{
		D3DCOLOR color = 0;
		if (m_totalTime < 6)
		{
			color = ((int)((m_totalTime - 4) * 0x80) << 24) | 0xffffff;
		}
		else if (m_totalTime < 7)
		{
			color = 0xffffffff;
		}
		else if (m_totalTime < 8)
		{
			color = ((int)((8 - m_totalTime) * 0xff) << 24) | 0xffffff;
		}
		m_rectNewGameLogo->SetColor(color, NNN::Geometry::Rect::c_RectOrtho::es_point::All);
		m_rectNewGameLogo->OnRender(fElapsedTime);
	}
}