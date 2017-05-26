//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// GameSession 游戏会话
//--------------------------------------------------------------------------------------

#include "c_GameSession.h"
#include "c_IntroScreen.h"


c_GameSession::c_GameSession(void)
{
	m_screenManager = nullptr;
	m_mainScreen = nullptr;
	m_isActive = true;
	m_recordXml = nullptr;
	m_scriptXml = nullptr;
	m_mapXml = nullptr;
	m_currentSave = nullptr;
	m_recordPath = nullptr;
}


c_GameSession::~c_GameSession(void)
{

}


c_GameSession *c_GameSession::GetSingleton(void)
{
	static c_GameSession s_singleton;
	return &s_singleton;
}


c_ScreenManager *c_GameSession::GetScreenManager(void) const
{
	return m_screenManager;
}


c_MainScreen *c_GameSession::GetMainScreen(void)
{
	if (m_mainScreen == nullptr)
	{
		m_mainScreen = new c_MainScreen();
	}
	return m_mainScreen;
}


bool c_GameSession::GetIsActive(void) const
{
	return m_isActive;
}


void c_GameSession::SetIsActive(bool value)
{
	m_isActive = value;
}


ec_LANG c_GameSession::GetLang(void) const
{
	return m_lang;
}


void c_GameSession::SetLang(ec_LANG value)
{
	m_lang = value;
}


bool c_GameSession::GetSoundEnable(void) const
{
	return m_soundEnable;
}


void c_GameSession::SetSoundEnable(bool value)
{
	m_soundEnable = value;
}


int c_GameSession::GetVolume(void) const
{
	return m_volume;
}


void c_GameSession::SetVolume(int value)
{
	m_volume = value;
}


TiXmlDocument *c_GameSession::GetScriptXml(void) const
{
	return m_scriptXml;
}


TiXmlDocument *c_GameSession::GetMapXml(void) const
{
	return m_mapXml;
}


c_GameSave *c_GameSession::GetCurrentSave(void) const
{
	return m_currentSave;
}


void c_GameSession::SetCurrentSave(c_GameSave *value)
{
	if (m_currentSave != value)
	{
		SAFE_DELETE(m_currentSave)
		m_currentSave = value;
	}
}


const std::vector<c_GameSave*> *c_GameSession::GetSavings(void) const
{
	return &m_savings;
}


void c_GameSession::SaveErase(int index)
{
	c_GameSave *save = m_savings[index];
	m_savings.erase(m_savings.begin() + index);
	SAFE_DELETE(save)
}


void c_GameSession::SavePushBack(c_GameSave* value)
{
	m_savings.push_back(value);
}


void c_GameSession::SaveRecord(void) const
{
	TiXmlElement *rootElement = m_recordXml->RootElement();
	rootElement->Clear();

	TiXmlElement *pElement = new TiXmlElement("Lang");
	TiXmlNode *pChildNode = nullptr;
	char buf[20];
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
	sprintf_s(buf, 20, "%d", m_lang);
#else
	sprintf(buf, "%d", m_lang);
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
	pElement->LinkEndChild(new TiXmlText(buf));
	rootElement->LinkEndChild(pElement);

	pElement = new TiXmlElement("Sound");
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
	sprintf_s(buf, 20, "%d", m_soundEnable);
#else
	sprintf(buf, "%d", m_soundEnable);
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
	pElement->LinkEndChild(new TiXmlText(buf));
	rootElement->LinkEndChild(pElement);

	pElement = new TiXmlElement("Volume");
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
	sprintf_s(buf, 20, "%d", m_volume);
#else
	sprintf(buf, "%d", m_volume);
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
	pElement->LinkEndChild(new TiXmlText(buf));
	rootElement->LinkEndChild(pElement);

	for (std::vector<c_GameSave*>::const_iterator iter = m_savings.begin(); iter != m_savings.end(); ++iter)
	{
		pElement = new TiXmlElement("Save");
		pChildNode = new TiXmlElement("Id");
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
		sprintf_s(buf, 20, "%d", (*iter)->GetId());
#else
		sprintf(buf, "%d", (*iter)->GetId());
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
		pChildNode->LinkEndChild(new TiXmlText(buf));
		pElement->LinkEndChild(pChildNode);

		pChildNode = new TiXmlElement("SavePoint");
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
		sprintf_s(buf, 20, "%d", (*iter)->GetSavePoint());
#else
		sprintf(buf, "%d", (*iter)->GetSavePoint());
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
		pChildNode->LinkEndChild(new TiXmlText(buf));
		pElement->LinkEndChild(pChildNode);

		pChildNode = new TiXmlElement("Time");
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
		sprintf_s(buf, 20, "%ld", (*iter)->GetTime());
#else
		sprintf(buf, "%ld", (*iter)->GetTime());
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
		pChildNode->LinkEndChild(new TiXmlText(buf));
		pElement->LinkEndChild(pChildNode);

		pChildNode = new TiXmlElement("Location");
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
		sprintf_s(buf, 20, "%d", (*iter)->GetLocation());
#else
		sprintf(buf, "%d", (*iter)->GetLocation());
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
		pChildNode->LinkEndChild(new TiXmlText(buf));
		pElement->LinkEndChild(pChildNode);

		for (std::vector<int>::const_iterator it = (*iter)->GetPassSection()->begin(); it != (*iter)->GetPassSection()->end(); ++it)
		{
			pChildNode = new TiXmlElement("Section");
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
			sprintf_s(buf, 20, "%d", (*it));
#else
			sprintf(buf, "%d", (*it));
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
			pChildNode->LinkEndChild(new TiXmlText(buf));
			pElement->LinkEndChild(pChildNode);
		}
		rootElement->LinkEndChild(pElement);
	}

	m_recordXml->SaveFile(m_recordPath);
}


int c_GameSession::FindMaxSaveId(void) const
{
	int id = 0;
	for (std::vector<c_GameSave*>::const_iterator iter = m_savings.begin(); iter != m_savings.end(); ++iter)
	{
		if ((*iter)->GetId() > id)
		{
			id = (*iter)->GetId();
		}
	}
	return id;
}


void c_GameSession::LoadContent(void)
{

#if NNN_PLATFORM == NNN_PLATFORM_IOS
	m_recordPath = "../Documents/Record.xml";
#elif NNN_PLATFORM == NNN_PLATFORM_ANDROID
	m_recordPath = "/mnt/sdcard/Record.xml";
#else
	m_recordPath = "Record.xml";
#endif
	
	m_recordXml = new TiXmlDocument();

	if (NNN::IO::File::Exists(m_recordPath))
	{
		m_recordXml->LoadFile(m_recordPath);
	}
	else
	{
		UINT32 content_len = 0;
		BYTE *content = NNN::Packet::LoadFileContent(L"Data/Record.xml", &content_len);
		if (content == nullptr)
		{
			return;
		}
		m_recordXml->LoadFile(content, content_len);
		NNN::Packet::UnloadFileContent(L"Data/Record.xml");
	}

	TiXmlNode *pNode = m_recordXml->RootElement()->FirstChild();
	m_lang = (ec_LANG)atoi(pNode->FirstChild()->Value());
	pNode = pNode->NextSibling();
	m_soundEnable = atoi(pNode->FirstChild()->Value()) == 1;
	pNode = pNode->NextSibling();
	m_volume = atoi(pNode->FirstChild()->Value());
	pNode = pNode->NextSibling();
	
	c_GameSave *save = nullptr;
	TiXmlNode *pChildNode = nullptr;
	while (pNode != nullptr)
	{
		save = new c_GameSave();
		pChildNode = pNode->FirstChild();
		save->SetId(atoi(pChildNode->FirstChild()->Value()));
		pChildNode = pChildNode->NextSibling();
		save->SetSavePoint(atoi(pChildNode->FirstChild()->Value()));
		pChildNode = pChildNode->NextSibling();
		save->SetTime(atol(pChildNode->FirstChild()->Value()));
		pChildNode = pChildNode->NextSibling();
		save->SetLocation(atoi(pChildNode->FirstChild()->Value()));
		pChildNode = pChildNode->NextSibling();
		while (pChildNode != nullptr)
		{
			save->SectionPushBack(atoi(pChildNode->FirstChild()->Value()));
			pChildNode = pChildNode->NextSibling();
		}
		m_savings.push_back(save);
		pNode = pNode->NextSibling();
	}

	UINT content_len = 0;
	BYTE *config_file_content = NNN::Packet::LoadFileContent(L"Data/Script.xml", &content_len);
	m_scriptXml = new TiXmlDocument();
	m_scriptXml->LoadFile(config_file_content, content_len);
	NNN::Packet::UnloadFileContent(L"Data/Script.xml");
	config_file_content = NNN::Packet::LoadFileContent(L"Data/Map.xml", &content_len);
	m_mapXml = new TiXmlDocument();
	m_mapXml->LoadFile(config_file_content, content_len);
	NNN::Packet::UnloadFileContent(L"Data/Map.xml");

	c_AudioManager::LoadContent();
	c_TextManager::LoadContent();
	c_InputManager::LoadContent();

	m_screenManager = new c_ScreenManager();
	m_screenManager->AddScreen(new c_IntroScreen());
}


void c_GameSession::UnloadContent(void)
{
	c_AudioManager::UnloadContent();
	c_TextManager::UnloadContent();
	c_InputManager::UnloadContent();
	SAFE_DELETE(m_screenManager);
	SAFE_DELETE(m_mainScreen);
	SAFE_DELETE(m_recordXml);
	SAFE_DELETE(m_scriptXml);
	SAFE_DELETE(m_mapXml);
	SAFE_DELETE(m_currentSave);

	for (std::vector<c_GameSave*>::iterator iter = m_savings.begin(); iter != m_savings.end(); ++iter)
	{
		delete *iter;
	}

	m_savings.clear();
}


void c_GameSession::Update(float fElapsedTime) const
{
	c_InputManager::Update(fElapsedTime);
	m_screenManager->Update(fElapsedTime);
}


void c_GameSession::Draw(float fElapsedTime) const
{
	m_screenManager->Draw(fElapsedTime);
	c_InputManager::Draw(fElapsedTime);
}


#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
HRESULT c_GameSession::OnReset_dx9(void)
{
	c_InputManager::OnReset_dx9();
	m_screenManager->OnReset_dx9();
	return S_OK;
}


HRESULT c_GameSession::OnLost_dx9(void)
{
	c_InputManager::OnLost_dx9();
	m_screenManager->OnLost_dx9();
	return S_OK;
}
#endif	// NNN_PLATFORM_WIN32