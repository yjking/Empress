//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// SaveScreen 存档屏幕
//--------------------------------------------------------------------------------------

#include "c_SaveScreen.h"
#include "c_InputManager.h"
#include "c_TextManager.h"
#include "c_GameSession.h"
#include "c_SettingsScreen.h"


c_SaveScreen::c_SaveScreen(bool saveEnable)
{
	m_saveEnable = saveEnable;
	
	m_textureBack = nullptr;
	m_textureSettings = nullptr;
	m_textureAdd = nullptr;
	m_textureSave = nullptr;
	m_textureLoad = nullptr;
	m_textureCopy = nullptr;
	m_textureDelete = nullptr;

	m_rectBackground = nullptr;
	m_rectSelected = nullptr;
	m_rectBar = nullptr;
	m_rectBack = nullptr;
	m_rectSettings = nullptr;
	m_rectAdd = nullptr;
	m_rectSave = nullptr;
	m_rectLoad = nullptr;
	m_rectCopy = nullptr;
	m_rectDelete = nullptr;

	m_saveCount = 0;
	m_col = 0;
	m_offsetY = 0;
	m_selectedIndex = -1;

	SetIsPopup(true);
}


c_SaveScreen::~c_SaveScreen(void)
{

}


void c_SaveScreen::LoadContent(void)
{
	NNN::Texture::Add(L"IconBack", L"Data/IconBack.png");
	NNN::Texture::Add(L"IconSettings", L"Data/IconSettings.png");
	NNN::Texture::Add(L"IconAdd", L"Data/IconAdd.png");
	NNN::Texture::Add(L"IconSaving", L"Data/IconSaving.png");
	NNN::Texture::Add(L"IconLoad", L"Data/IconLoad.png");
	NNN::Texture::Add(L"IconCopy", L"Data/IconCopy.png");
	NNN::Texture::Add(L"IconDelete", L"Data/IconDelete.png");
	m_textureBack = NNN::Texture::Find(L"IconBack");
	m_textureSettings = NNN::Texture::Find(L"IconSettings");
	m_textureAdd = NNN::Texture::Find(L"IconAdd");
	m_textureSave = NNN::Texture::Find(L"IconSaving");
	m_textureLoad = NNN::Texture::Find(L"IconLoad");
	m_textureCopy = NNN::Texture::Find(L"IconCopy");
	m_textureDelete = NNN::Texture::Find(L"IconDelete");

	LONG width = NNN::Misc::GetClientWidth();
	LONG height = NNN::Misc::GetClientHeight();

	m_backPosition = make_rect(0, 128, 0, 128);
	m_settingsPosition = make_rect(128, 256, 0, 128);
	m_addPosition = make_rect(256, 384, 0, 128);
	m_savePosition = make_rect(384, 512, 0, 128);
	m_loadPosition = make_rect(512, 640, 0, 128);
	m_copyPosition = make_rect(640, 768, 0, 128);
	m_deletePosition = make_rect(768, 896, 0, 128);
	m_panPosition = make_rect(0, width, 129, height);

	m_col = width * 0.003125; // 1 / 320 = 0.003125

	m_rectBackground = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectBackground->SetRect(make_rect(0, width, 0, height));
	m_rectBackground->SetColor(0xcc000000, NNN::Geometry::Rect::c_RectOrtho::es_point::All);
	
	m_rectSelected = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectSelected->SetColor(0x6666ccff, NNN::Geometry::Rect::c_RectOrtho::es_point::All);

	m_rectBar = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectBar->SetRect(make_rect(0, width, 0, 128));
	m_rectBar->SetColor(0xccffffff, NNN::Geometry::Rect::c_RectOrtho::es_point::All);
	
	m_rectBack = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectBack->SetRect(m_backPosition);
	m_rectBack->SetTexture(m_textureBack);

	m_rectSettings = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectSettings->SetRect(m_settingsPosition);
	m_rectSettings->SetTexture(m_textureSettings);

	m_rectAdd = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectAdd->SetRect(m_addPosition);
	m_rectAdd->SetTexture(m_textureAdd);

	m_rectSave = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectSave->SetRect(m_savePosition);
	m_rectSave->SetTexture(m_textureSave);

	m_rectLoad = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectLoad->SetRect(m_loadPosition);
	m_rectLoad->SetTexture(m_textureLoad);

	m_rectCopy = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectCopy->SetRect(m_copyPosition);
	m_rectCopy->SetTexture(m_textureCopy);

	m_rectDelete = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectDelete->SetRect(m_deletePosition);
	m_rectDelete->SetTexture(m_textureDelete);

	ReloadSave();
}


void c_SaveScreen::UnloadContent(void)
{
	for (unsigned i = 0; i < m_saveCount; ++i)
	{
		WCHAR *wchar_tmp = m_completeList[i];
		SAFE_DELETE_ARRAY(wchar_tmp);

		wchar_tmp = m_timeList[i];
		SAFE_DELETE_ARRAY(wchar_tmp);
		
		NNN::Geometry::Rect::c_RectOrtho *rect = m_rectPhotoList[i];
		SAFE_DELETE(rect);
	}
	m_completeList.clear();
	m_timeList.clear();
	m_rectPhotoList.clear();

	SAFE_DELETE(m_rectBackground);
	SAFE_DELETE(m_rectSelected);
	SAFE_DELETE(m_rectBar);
	SAFE_DELETE(m_rectBack);
	SAFE_DELETE(m_rectSettings);
	SAFE_DELETE(m_rectAdd);
	SAFE_DELETE(m_rectSave);
	SAFE_DELETE(m_rectLoad);
	SAFE_DELETE(m_rectCopy);
	SAFE_DELETE(m_rectDelete);

	unsigned count = m_textureNameList.size();
	for (unsigned i = 0; i < count; ++i)
	{
		WCHAR *wchar_tmp = m_textureNameList[i];
		NNN::Texture::Release(wchar_tmp);
		SAFE_DELETE_ARRAY(wchar_tmp);
	}
	m_textureNameList.clear();

	NNN::Texture::Release(L"IconBack");
	NNN::Texture::Release(L"IconSettings");
	NNN::Texture::Release(L"IconAdd");
	NNN::Texture::Release(L"IconSaving");
	NNN::Texture::Release(L"IconLoad");
	NNN::Texture::Release(L"IconCopy");
	NNN::Texture::Release(L"IconDelete");
	m_textureBack = nullptr;
	m_textureSettings = nullptr;
	m_textureAdd = nullptr;
	m_textureSave = nullptr;
	m_textureLoad = nullptr;
	m_textureCopy = nullptr;
	m_textureDelete = nullptr;
}


void c_SaveScreen::HandleInput(void)
{
	const std::vector<c_GameSave*> *savings = c_GameSession::GetSingleton()->GetSavings();
	POINT delta = { 0 };

	if (c_InputManager::Tap(&m_backPosition))
	{
		ExitScreen();
	}
	else if (m_saveEnable && c_InputManager::Tap(&m_settingsPosition))
	{
		ExitScreen();
		c_GameSession::GetSingleton()->GetScreenManager()->AddScreen(new c_SettingsScreen(true));
	}
	else if (c_InputManager::Tap(&m_addPosition))
	{
		c_GameSession::GetSingleton()->SavePushBack(new c_GameSave(
			c_GameSession::GetSingleton()->FindMaxSaveId() + 1, 0, time(nullptr), 44));
		c_GameSession::GetSingleton()->SaveRecord();
		ReloadSave();
	}
	else if (m_selectedIndex > -1 && m_saveEnable && c_InputManager::Tap(&m_savePosition))
	{
		c_GameSave *save = (*savings)[m_selectedIndex];
		c_GameSession::GetSingleton()->GetCurrentSave()->DeepCopy(save);
		save->SetId(c_GameSession::GetSingleton()->FindMaxSaveId() + 1);
		save->SetTime(time(nullptr));
		c_GameSession::GetSingleton()->SaveRecord();
		c_GameSession::GetSingleton()->GetCurrentSave()->SetId(save->GetId());
		ReloadSave();
	}
	else if (m_selectedIndex > -1 && c_InputManager::Tap(&m_loadPosition))
	{
		ExitScreen();
		c_GameSave *save = new c_GameSave(*((*savings)[m_selectedIndex]));
		c_GameSession::GetSingleton()->SetCurrentSave(save);
		if (!m_saveEnable)
		{
			c_GameSession::GetSingleton()->GetScreenManager()->AddScreen(
				c_GameSession::GetSingleton()->GetMainScreen());
		}
		else
		{
			c_GameSession::GetSingleton()->GetMainScreen()->Reset();
		}
	}
	else if (m_selectedIndex > -1 && c_InputManager::Tap(&m_copyPosition))
	{
		c_GameSave *save = new c_GameSave(*((*savings)[m_selectedIndex]));
		save->SetId(c_GameSession::GetSingleton()->FindMaxSaveId() + 1);
		save->SetTime(time(nullptr));
		c_GameSession::GetSingleton()->SavePushBack(save);
		c_GameSession::GetSingleton()->SaveRecord();
		ReloadSave();
	}
	else if (m_selectedIndex > -1 && c_InputManager::Tap(&m_deletePosition))
	{
		c_GameSession::GetSingleton()->SaveErase(m_selectedIndex);
		c_GameSession::GetSingleton()->SaveRecord();
		m_selectedIndex = -1;
		ReloadSave();
	}
	else if (c_InputManager::Pan(&m_panPosition, &delta))
	{
		m_offsetY -= delta.y;
	}
	else if (c_InputManager::Tap(&m_panPosition))
	{
		for (unsigned i = 0; i < m_saveCount; ++i)
		{
			RECT position = make_rect(i % m_col * 320, (i % m_col + 1) * 320, i / m_col * 200 - m_offsetY + 128, (i / m_col + 1) * 200 - m_offsetY + 128);
			if (c_InputManager::Tap(&position))
			{
				m_selectedIndex = i;
				break;
			}
			m_selectedIndex = -1;
		}
	}

	int offsetMax = (m_saveCount % m_col == 0 ? m_saveCount / m_col : m_saveCount / m_col + 1) * 200 - m_panPosition.bottom + m_panPosition.top;
	if (m_offsetY > offsetMax)
	{
		m_offsetY = offsetMax;
	}
	if (m_offsetY < 0)
	{
		m_offsetY = 0;
	}
}


void c_SaveScreen::Draw(float fElapsedTime)
{
	m_rectBackground->OnRender(fElapsedTime);

	const std::vector<c_GameSave*> *savings = c_GameSession::GetSingleton()->GetSavings();
	POINT point = { 0 };
	RECT position = { 0 };
	NNN::Geometry::Rect::c_RectOrtho *rect = nullptr;

	for (unsigned i = 0; i < m_saveCount; ++i)
	{
		point = make_point(i % m_col * 320, i / m_col * 200 - m_offsetY + 128);

		rect = m_rectPhotoList[i];
		rect->SetRect(make_rect(point.x, point.x + 320, point.y, point.y + 200));
		rect->OnRender(fElapsedTime);

		rect = new NNN::Geometry::Rect::c_RectOrtho();
		rect->SetRect(make_rect(point.x + 5, point.x + 315, point.y + 120, point.y + 200));
		rect->SetColor(0x33999933, NNN::Geometry::Rect::c_RectOrtho::es_point::All);
		rect->OnRender(fElapsedTime);
		SAFE_DELETE(rect);

		if (m_selectedIndex == i)
		{
			m_rectSelected->SetRect(make_rect(point.x, point.x + 320, point.y, point.y + 200));
			m_rectSelected->OnRender(fElapsedTime);
		}

		position = make_rect(point.x + 210, point.x + 320 - 10, point.y + 10, point.y + 200 - 90);
		c_TextManager::DrawString(m_completeList[i], 0xffffffff, 0, DT_CENTER | DT_VCENTER, &position);

		position = make_rect(point.x + 10, point.x + 320, point.y + 120, point.y + 200 - 40);
		c_TextManager::DrawString(m_timeList[i], 0xffffffff, 0, DT_LEFT | DT_VCENTER, &position);
			
		position = make_rect(point.x + 10, point.x + 320, point.y + 160, point.y + 200);
		c_TextManager::DrawString((*savings)[i]->GetLocation(), 0xffffffff, 0, DT_LEFT | DT_VCENTER, &position);
	}

	if (m_saveCount == 0)
	{
		c_TextManager::DrawString(18, 0xffffffff, 0, DT_CENTER | DT_VCENTER, &m_panPosition);
	}

	m_rectBar->OnRender(fElapsedTime);
	m_rectBack->OnRender(fElapsedTime);
	if (m_saveEnable)
	{
		m_rectSettings->OnRender(fElapsedTime);
	}
	m_rectAdd->OnRender(fElapsedTime);
	if (m_selectedIndex > -1)
	{
		if (m_saveEnable)
		{
			m_rectSave->OnRender(fElapsedTime);
		}

		m_rectLoad->OnRender(fElapsedTime);
		m_rectCopy->OnRender(fElapsedTime);
		m_rectDelete->OnRender(fElapsedTime);
	}
}


void c_SaveScreen::ReloadSave(void)
{
	for (unsigned i = 0; i < m_saveCount; ++i)
	{
		WCHAR *wchar_tmp = m_completeList[i];
		SAFE_DELETE_ARRAY(wchar_tmp);

		wchar_tmp = m_timeList[i];
		SAFE_DELETE_ARRAY(wchar_tmp);

		NNN::Geometry::Rect::c_RectOrtho *rect = m_rectPhotoList[i];
		SAFE_DELETE(rect);
	}
	m_completeList.clear();
	m_timeList.clear();
	m_rectPhotoList.clear();
	
	const std::vector<c_GameSave*> *savings = c_GameSession::GetSingleton()->GetSavings();
	m_saveCount = (*savings).size();
	char buf[32] = { 0 };
	time_t t = 0;
	WCHAR *wchar1 = nullptr;
	WCHAR *wchar2 = nullptr;
	c_GameSave *save = nullptr;
	NNN::Texture::c_Texture *texture = nullptr;
	NNN::Geometry::Rect::c_RectOrtho *rect = nullptr;

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
	struct tm local;
#else
	struct tm *plocal = nullptr;
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8

	for (unsigned i = 0; i < m_saveCount; ++i)
	{
		save = (*savings)[i];

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
		sprintf_s(buf, 32, "Location%d", save->GetLocation());
#else
		sprintf(buf, "Location%d", save->GetLocation());
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
		NNN::Text::char2wchar(buf, &wchar1);

		texture = NNN::Texture::Find(wchar1);
		if (texture == nullptr)
		{
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
			sprintf_s(buf, 32, "Data/Location%d.png", save->GetLocation());
#else
			sprintf(buf, "Data/Location%d.png", save->GetLocation());
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
			NNN::Text::char2wchar(buf, &wchar2);
			NNN::Texture::Add(wchar1, wchar2);
			SAFE_DELETE_ARRAY(wchar2);
			m_textureNameList.push_back(wchar1);
			texture = NNN::Texture::Find(wchar1);
		}
		else
		{
			SAFE_DELETE_ARRAY(wchar1);
		}

		rect = new NNN::Geometry::Rect::c_RectOrtho();
		rect->SetTexture(texture);
		m_rectPhotoList.push_back(rect);

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
		sprintf_s(buf, 32, "%.1f%%", (*savings)[i]->Complete());
#else
		sprintf(buf, "%.1f%%", (*savings)[i]->Complete());
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
		NNN::Text::char2wchar(buf, &wchar1);
		m_completeList.push_back(wchar1);

		t = (*savings)[i]->GetTime();
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
		localtime_s(&local, &t);
		sprintf_s(buf, 32, "%d/%02d/%02d %02d:%02d:%02d", local.tm_year + 1900, local.tm_mon + 1, local.tm_mday, local.tm_hour, local.tm_min, local.tm_sec);
#else
		plocal = localtime(&t);
		sprintf(buf, "%d/%02d/%02d %02d:%02d:%02d", plocal->tm_year + 1900, plocal->tm_mon + 1, plocal->tm_mday, plocal->tm_hour, plocal->tm_min, plocal->tm_sec);
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
		NNN::Text::char2wchar(buf, &wchar1);
		m_timeList.push_back(wchar1);
	}
}