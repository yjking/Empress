//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// SettingsScreen 设置屏幕
//--------------------------------------------------------------------------------------

#include "c_SettingsScreen.h"
#include "c_InputManager.h"
#include "c_TextManager.h"
#include "c_GameSession.h"
#include "c_SaveScreen.h"


c_SettingsScreen::c_SettingsScreen(bool saveEnable)
{
	m_saveEnable = saveEnable;

	m_textureBack = nullptr;
	m_textureSave = nullptr;
	m_textureSoundEnable = nullptr;
	m_textureSoundDisable = nullptr;
	m_textureVolumeIncrease = nullptr;
	m_textureVolumeDecrease = nullptr;

	m_rectBackground = nullptr;
	m_rectBack = nullptr;
	m_rectSave = nullptr;
	m_rectSoundEnable = nullptr;
	m_rectSoundDisable = nullptr;
	m_rectVolumeIncrease = nullptr;
	m_rectVolumeDecrease = nullptr;
	m_rectLine = nullptr;
	m_rectLang = nullptr;

	m_firstFill = true;
	m_volume = nullptr;

	SetTransitionOnTime(0.5);
	SetTransitionOffTime(0.5);
	SetIsPopup(true);
}


c_SettingsScreen::~c_SettingsScreen()
{

}


void c_SettingsScreen::LoadContent(void)
{
	NNN::Texture::Add(L"IconBack", L"Data/IconBack.png");
	NNN::Texture::Add(L"IconSave", L"Data/IconSave.png");
	NNN::Texture::Add(L"IconSoundEnable", L"Data/IconSoundEnable.png");
	NNN::Texture::Add(L"IconSoundDisable", L"Data/IconSoundDisable.png");
	NNN::Texture::Add(L"IconVolumeIncrease", L"Data/IconVolumeIncrease.png");
	NNN::Texture::Add(L"IconVolumeDecrease", L"Data/IconVolumeDecrease.png");
	m_textureBack = NNN::Texture::Find(L"IconBack");
	m_textureSave = NNN::Texture::Find(L"IconSave");
	m_textureSoundEnable = NNN::Texture::Find(L"IconSoundEnable");
	m_textureSoundDisable = NNN::Texture::Find(L"IconSoundDisable");
	m_textureVolumeIncrease = NNN::Texture::Find(L"IconVolumeIncrease");
	m_textureVolumeDecrease = NNN::Texture::Find(L"IconVolumeDecrease");

	LONG width = NNN::Misc::GetClientWidth();
	LONG height = NNN::Misc::GetClientHeight();

	m_clientPosition = make_rect(0, width, 0, height);
	m_backPosition = make_rect(0, 128, 0, 128);
	m_savePosition = make_rect(128, 256, 0, 128);
	m_soundPosition = make_rect(256, 384, 0, 128);
	m_volumePosition = make_rect(512, 640, 0, 128);
	m_volumeIncreasePosition = make_rect(384, 512, 0, 128);
	m_volumeDecreasePosition = make_rect(640, 768, 0, 128);
	m_langPosition = make_rect(0, 200, 128, 384);
	m_zhcnPosition = make_rect(210, 400, 128, 256);
	m_zhhkPosition = make_rect(410, 600, 128, 256);
	m_enusPosition = make_rect(210, 400, 256, 384);
	m_jajpPosition = make_rect(410, 600, 256, 384);

	m_rectBackground = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectBackground->SetColor(0xccffffff, NNN::Geometry::Rect::c_RectOrtho::es_point::All);

	m_rectBack = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectBack->SetTexture(m_textureBack);

	m_rectSave = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectSave->SetTexture(m_textureSave);
	
	m_rectSoundEnable = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectSoundEnable->SetTexture(m_textureSoundEnable);

	m_rectSoundDisable = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectSoundDisable->SetTexture(m_textureSoundDisable);

	m_rectVolumeIncrease = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectVolumeIncrease->SetTexture(m_textureVolumeIncrease);

	m_rectVolumeDecrease = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectVolumeDecrease->SetTexture(m_textureVolumeDecrease);

	m_rectLine = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectLine->SetColor(0xff000000, NNN::Geometry::Rect::c_RectOrtho::es_point::All);

	m_rectLang = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectLang->SetColor(0xff66ccff, NNN::Geometry::Rect::c_RectOrtho::es_point::All);
	
	ReloadVolume();
	ReloadLang();
}


void c_SettingsScreen::UnloadContent(void)
{
	SAFE_DELETE(m_rectBackground);
	SAFE_DELETE(m_rectBack);
	SAFE_DELETE(m_rectSave);
	SAFE_DELETE(m_rectSoundEnable);
	SAFE_DELETE(m_rectSoundDisable);
	SAFE_DELETE(m_rectVolumeIncrease);
	SAFE_DELETE(m_rectVolumeDecrease);
	SAFE_DELETE(m_rectLine);
	SAFE_DELETE(m_rectLang);

	NNN::Texture::Release(L"IconBack");
	NNN::Texture::Release(L"IconSave");
	NNN::Texture::Release(L"IconSoundEnable");
	NNN::Texture::Release(L"IconSoundDisable");
	NNN::Texture::Release(L"IconVolumeIncrease");
	NNN::Texture::Release(L"IconVolumeDecrease");
	m_textureBack = nullptr;
	m_textureSave = nullptr;
	m_textureSoundEnable = nullptr;
	m_textureSoundDisable = nullptr;
	m_textureVolumeIncrease = nullptr;
	m_textureVolumeDecrease = nullptr;

	SAFE_DELETE_ARRAY(m_volume);
}


void c_SettingsScreen::HandleInput(void)
{
	if (c_InputManager::Tap(&m_zhcnPosition))
	{
		c_GameSession::GetSingleton()->SetLang(ec_LANG::zh_CN);
		ReloadLang();
	}
	else if (c_InputManager::Tap(&m_zhhkPosition))
	{
		c_GameSession::GetSingleton()->SetLang(ec_LANG::zh_HK);
		ReloadLang();
	}
	else if (c_InputManager::Tap(&m_enusPosition))
	{
		c_GameSession::GetSingleton()->SetLang(ec_LANG::en_US);
		ReloadLang();
	}
	else if (c_InputManager::Tap(&m_jajpPosition))
	{
		c_GameSession::GetSingleton()->SetLang(ec_LANG::ja_JP);
		ReloadLang();
	}
	else if (c_InputManager::Tap(&m_soundPosition))
	{
		c_GameSession::GetSingleton()->SetSoundEnable(!c_GameSession::GetSingleton()->GetSoundEnable());
	}
	else if (c_GameSession::GetSingleton()->GetVolume() < 100 && c_InputManager::Tap(&m_volumeIncreasePosition))
	{
		c_GameSession::GetSingleton()->SetVolume(c_GameSession::GetSingleton()->GetVolume() + 1);
		ReloadVolume();
	}
	else if (c_GameSession::GetSingleton()->GetVolume() > 0 && c_InputManager::Tap(&m_volumeDecreasePosition))
	{
		c_GameSession::GetSingleton()->SetVolume(c_GameSession::GetSingleton()->GetVolume() - 1);
		ReloadVolume();
	}
	else if (c_InputManager::Tap(&m_backPosition) || (m_saveEnable && c_InputManager::Tap(&m_savePosition)))
	{
		if (c_GameSession::GetSingleton()->GetSoundEnable())
		{
			NNN::Sound::SetGlobalVolume(c_GameSession::GetSingleton()->GetVolume() * 0.01);
		}
		else
		{
			NNN::Sound::SetGlobalVolume(0); // 关闭声音即为将音量设为0
		}
		
		c_GameSession::GetSingleton()->SaveRecord();
		c_TextManager::UpdateTextTable();

		ExitScreen();

		if (m_saveEnable && c_InputManager::Tap(&m_savePosition))
		{
			c_GameSession::GetSingleton()->GetScreenManager()->AddScreen(new c_SaveScreen(true));
		}
	}
}


void c_SettingsScreen::Draw(float fElapsedTime)
{
	if (GetScreenState() == ec_ScreenState::Active)
	{
		if (m_firstFill)
		{
			m_firstFill = false;

			m_rectBackground->SetRect(m_clientPosition);
			m_rectBack->SetRect(m_backPosition);
			m_rectSave->SetRect(m_savePosition);
			m_rectSoundEnable->SetRect(m_soundPosition);
			m_rectSoundDisable->SetRect(m_soundPosition);
			m_rectVolumeIncrease->SetRect(m_volumeIncreasePosition);
			m_rectVolumeDecrease->SetRect(m_volumeDecreasePosition);
			m_rectLine->SetRect(make_rect(0, m_clientPosition.right, 127, 128));
			m_rectLang->SetRect(m_currentPosition);
		}
	}
	else
	{
		LONG detal = GetTransitionPosition() * m_clientPosition.bottom;
		RECT rect = m_clientPosition;
		rect.top += detal;
		m_rectBackground->SetRect(rect);

		rect = m_backPosition;
		rect.top += detal;
		rect.bottom += detal;
		m_rectBack->SetRect(rect);

		rect = m_savePosition;
		rect.top += detal;
		rect.bottom += detal;
		m_rectSave->SetRect(rect);

		rect = m_soundPosition;
		rect.top += detal;
		rect.bottom += detal;
		m_rectSoundEnable->SetRect(rect);
		m_rectSoundDisable->SetRect(rect);

		rect = m_volumeIncreasePosition;
		rect.top += detal;
		rect.bottom += detal;
		m_rectVolumeIncrease->SetRect(rect);

		rect = m_volumeDecreasePosition;
		rect.top += detal;
		rect.bottom += detal;
		m_rectVolumeDecrease->SetRect(rect);

		m_rectLine->SetRect(make_rect(0, m_clientPosition.right, detal + 127, detal + 128));

		rect = m_currentPosition;
		rect.top += detal;
		rect.bottom += detal;
		m_rectLang->SetRect(rect);
	}

	m_rectBackground->OnRender(fElapsedTime);
	m_rectBack->OnRender(fElapsedTime);
	m_rectSave->OnRender(fElapsedTime);
	if (c_GameSession::GetSingleton()->GetSoundEnable())
	{
		m_rectSoundEnable->OnRender(fElapsedTime);
	}
	else
	{
		m_rectSoundDisable->OnRender(fElapsedTime);
	}
	int volume = c_GameSession::GetSingleton()->GetVolume();
	if (volume < 100)
	{
		m_rectVolumeIncrease->OnRender(fElapsedTime);
	}
	if (volume > 0)
	{
		m_rectVolumeDecrease->OnRender(fElapsedTime);
	}
	m_rectLine->OnRender(fElapsedTime);
	m_rectLang->OnRender(fElapsedTime);

	if (GetScreenState() == ec_ScreenState::Active)
	{
		c_TextManager::DrawString(m_volume, 0xff000000, 0, DT_CENTER | DT_VCENTER, &m_volumePosition);
		c_TextManager::DrawString(10, 0xff526691, 0, DT_CENTER | DT_VCENTER, &m_langPosition);
		c_TextManager::DrawString(11, 0xff000000, 0, DT_CENTER | DT_VCENTER, &m_zhcnPosition);
		c_TextManager::DrawString(12, 0xff000000, 0, DT_CENTER | DT_VCENTER, &m_zhhkPosition);
		c_TextManager::DrawString(13, 0xff000000, 0, DT_CENTER | DT_VCENTER, &m_enusPosition);
		c_TextManager::DrawString(14, 0xff000000, 0, DT_CENTER | DT_VCENTER, &m_jajpPosition);
	}
	else
	{
		LONG detal = GetTransitionPosition() * m_clientPosition.bottom;
		RECT position = m_volumePosition;
		position.top += detal;
		position.bottom += detal;
		c_TextManager::DrawString(m_volume, 0xff000000, 0, DT_CENTER | DT_VCENTER, &position);

		position = m_langPosition;
		position.top += detal;
		position.bottom += detal;
		c_TextManager::DrawString(10, 0xff526691, 0, DT_CENTER | DT_VCENTER, &position);

		position = m_zhcnPosition;
		position.top += detal;
		position.bottom += detal;
		c_TextManager::DrawString(11, 0xff000000, 0, DT_CENTER | DT_VCENTER, &position);

		position = m_zhhkPosition;
		position.top += detal;
		position.bottom += detal;
		c_TextManager::DrawString(12, 0xff000000, 0, DT_CENTER | DT_VCENTER, &position);

		position = m_enusPosition;
		position.top += detal;
		position.bottom += detal;
		c_TextManager::DrawString(13, 0xff000000, 0, DT_CENTER | DT_VCENTER, &position);

		position = m_jajpPosition;
		position.top += detal;
		position.bottom += detal;
		c_TextManager::DrawString(14, 0xff000000, 0, DT_CENTER | DT_VCENTER, &position);
	}
}


void c_SettingsScreen::ReloadVolume(void)
{
	SAFE_DELETE_ARRAY(m_volume);

	char buf[4];
	int volume = c_GameSession::GetSingleton()->GetVolume();

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
	sprintf_s(buf, 4, "%d", volume);
#else
	sprintf(buf, "%d", volume);
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
	NNN::Text::char2wchar(buf, &m_volume);
}


void c_SettingsScreen::ReloadLang(void)
{
	switch (c_GameSession::GetSingleton()->GetLang())
	{
	case ec_LANG::zh_TW:
		//m_currentPosition = m_zhtwPosition; // 暂时不使用台湾正体
		break;
	case ec_LANG::en_US:
		m_currentPosition = m_enusPosition;
		break;
	case ec_LANG::ja_JP:
		m_currentPosition = m_jajpPosition;
		break;
	case ec_LANG::zh_CN:
		m_currentPosition = m_zhcnPosition;
		break;
	case ec_LANG::zh_HK:
		m_currentPosition = m_zhhkPosition;
		break;
	default:
		break;
	}

	m_rectLang->SetRect(m_currentPosition);
}