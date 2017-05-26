//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// TitleScreen 标题屏幕
//--------------------------------------------------------------------------------------

#include "c_TitleScreen.h"
#include "c_InputManager.h"
#include "c_TextManager.h"
#include "c_GameSession.h"
#include "c_SettingsScreen.h"
#include "c_SaveScreen.h"


c_TitleScreen::c_TitleScreen()
{
	m_textureTitle = nullptr;
	m_rectTitle = nullptr;
}


c_TitleScreen::~c_TitleScreen()
{

}


void c_TitleScreen::LoadContent(void)
{
	NNN::Texture::Add(L"GameTitle", L"Data/GameTitle.png");
	m_textureTitle = NNN::Texture::Find(L"GameTitle");

	LONG width = NNN::Misc::GetClientWidth();
	double rate = width * 0.0009765625; // 1 / 1024 = 0.0009765625
	m_startPosition = make_rect(600 * rate, 685 * rate, 180 * rate, 250 * rate);
	m_settingsPosition = make_rect(600 * rate, 710 * rate, 270 * rate, 340 * rate);

	m_rectTitle = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectTitle->GetSamplerState()->SetFilter(D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT);
	m_rectTitle->SetRect(make_rect(0, width, 0, 768 * rate));
	m_rectTitle->SetTexture(m_textureTitle);
}


void c_TitleScreen::UnloadContent(void)
{
	SAFE_DELETE(m_rectTitle);

	NNN::Texture::Release(L"GameTitle");
	m_textureTitle = nullptr;
}


void c_TitleScreen::HandleInput(void)
{
	if (c_InputManager::Tap(&m_startPosition))
	{
		c_GameSession::GetSingleton()->GetScreenManager()->AddScreen(new c_SaveScreen(false));
	}
	else if (c_InputManager::Tap(&m_settingsPosition))
	{
		c_GameSession::GetSingleton()->GetScreenManager()->AddScreen(new c_SettingsScreen(false));
	}
}


void c_TitleScreen::Draw(float fElapsedTime)
{
	m_rectTitle->OnRender(fElapsedTime);
	c_TextManager::DrawString(2, 0xffffffff, 0, DT_CENTER | DT_VCENTER, &m_startPosition);
	c_TextManager::DrawString(3, 0xffffffff, 0, DT_CENTER | DT_VCENTER, &m_settingsPosition);
}