//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// MainScreen 主屏幕
//--------------------------------------------------------------------------------------

#include "c_MainScreen.h"
#include "c_InputManager.h"
#include "c_TextManager.h"
#include "c_GameSession.h"
#include "c_EndScreen.h"
#include "c_HistoryScreen.h"
#include "c_SettingsScreen.h"


c_MainScreen::c_MainScreen()
{
	m_textureBackground = nullptr;
	m_texturePerson[0] = nullptr;
	m_texturePerson[1] = nullptr;
	m_texturePerson[2] = nullptr;
	m_texturePerson[3] = nullptr;
	m_texturePerson[4] = nullptr;
	m_textureNameBar = nullptr;
	m_textureMusicOn = nullptr;
	m_textureMusicOff = nullptr;
	m_textureRedStrap = nullptr;
	m_textureSoftDisk = nullptr;

	m_rectBackground = nullptr;
	m_rectPerson[0] = nullptr;
	m_rectPerson[1] = nullptr;
	m_rectPerson[2] = nullptr;
	m_rectPerson[3] = nullptr;
	m_rectPerson[4] = nullptr;
	m_rectNameBar = nullptr;
	m_rectLine = nullptr;
	m_rectDialogueBox = nullptr;
	m_rectMusicOn = nullptr;
	m_rectMusicOff = nullptr;
	m_rectTime = nullptr;
	m_rectLocation = nullptr;
	m_rectSoftDisk = nullptr;
	
	m_nodeReader = nullptr;
	m_isSavePoint = false;
	m_timeElapsed = 0;
	m_locationElapsed = 0;
	m_bgmId = 0;
	m_timeId = 0;
	m_currentLocation = 0;
	m_nameId = 0;
	m_dialogueId = 0;
	m_dialogueBoxRoll = 0;
	m_optionText[0] = 0;
	m_optionText[1] = 0;
	m_optionText[2] = 0;
	m_optionSection[0] = 0;
	m_optionSection[1] = 0;
	m_optionSection[2] = 0;

	m_dialogueBoxState = ec_DialogueBoxState::Lay;
}


c_MainScreen::~c_MainScreen()
{

}


void c_MainScreen::LoadContent(void)
{
	Reset();

	NNN::Texture::Add(L"NameBar", L"Data/NameBar.png");
	NNN::Texture::Add(L"MusicOn", L"Data/MusicOn.png");
	NNN::Texture::Add(L"MusicOff", L"Data/MusicOff.png");
	NNN::Texture::Add(L"RedStrap", L"Data/RedStrap.png");
	NNN::Texture::Add(L"SoftDisk", L"Data/SoftDisk.png");
	m_textureNameBar = NNN::Texture::Find(L"NameBar");
	m_textureMusicOn = NNN::Texture::Find(L"MusicOn");
	m_textureMusicOff = NNN::Texture::Find(L"MusicOff");
	m_textureRedStrap = NNN::Texture::Find(L"RedStrap");
	m_textureSoftDisk = NNN::Texture::Find(L"SoftDisk");

	LONG width = NNN::Misc::GetClientWidth();
	LONG height = NNN::Misc::GetClientHeight();
	double rate = width * 0.0009765625; // 1 / 1024 = 0.0009765625

	m_nameBarPosition = make_rect(100, 356, height - 300, height - 260);
	m_nameBasePosition = m_nameBarPosition;
	m_nameShadowPosition = make_rect(
		m_nameBasePosition.left + 2,
		m_nameBasePosition.right + 2,
		m_nameBasePosition.top + 2,
		m_nameBasePosition.bottom + 2);
	m_dialogueBoxPosition = make_rect(0, width, height - 250, height);
	m_dialogueBasePosition = make_rect(100, width - 100, height - 240, height);
	m_dialogueShadowPosition = make_rect(
		m_dialogueBasePosition.left + 2,
		m_dialogueBasePosition.right + 2,
		m_dialogueBasePosition.top + 2,
		m_dialogueBasePosition.bottom + 2);
	m_musicPosition = make_rect(0, 128, 0, 128);
	m_bgmPosition = make_rect(128, width, 20, 80);
	m_timeTextPosition = make_rect(width - 436, width, 20, 90);
	m_locationTextPosition = make_rect(width - 336, width, 100, 170);
	m_softDiskPosition = make_rect(width - 128, width, 0, 128);
	m_personPosition[0] = make_rect(256 * rate, 768 * rate, 0, 768 * rate);
	m_personPosition[1] = make_rect(96 * rate, 608 * rate, 0, 768 * rate);
	m_personPosition[2] = make_rect(416 * rate, 928 * rate, 0, 768 * rate);
	m_personPosition[3] = make_rect(-64 * rate, 448 * rate, 0, 768 * rate);
	m_personPosition[4] = make_rect(576 * rate, 1088 * rate, 0, 768 * rate);
	m_clientPosition = make_rect(0, width, 0, height);
	m_panPosition = make_rect(0, width, 0, m_dialogueBoxPosition.top);

	double rateBox = (height - 180) * 0.0021739130434783; // 1 / 460 = 0.0021739130434783
	for (int i = 0; i < 3; ++i)
	{
		m_optionPosition[i] = make_rect(200, width - 200, 300 + i * 130 * rateBox, 400 + i * 130 * rateBox);
	}

	m_rectBackground = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectBackground->GetSamplerState()->SetFilter(D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT);
	m_rectBackground->SetRect(make_rect(0, width, 0, 768 * rate));

	for (int i = 0; i < 5; ++i)
	{
		m_rectPerson[i] = new NNN::Geometry::Rect::c_RectOrtho();
		m_rectPerson[i]->GetSamplerState()->SetFilter(D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT);
		m_rectPerson[i]->SetRect(m_personPosition[i]);
	}

	m_rectNameBar = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectNameBar->SetRect(m_nameBarPosition);
	m_rectNameBar->SetTexture(m_textureNameBar);

	m_rectLine = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectLine->SetColor(0xccff0066, NNN::Geometry::Rect::c_RectOrtho::es_point::All);

	m_rectDialogueBox = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectDialogueBox->SetRect(m_dialogueBoxPosition);
	m_rectDialogueBox->SetColor(0xccffffff, NNN::Geometry::Rect::c_RectOrtho::es_point::LeftTop);
	m_rectDialogueBox->SetColor(0xccffffff, NNN::Geometry::Rect::c_RectOrtho::es_point::RightTop);
	m_rectDialogueBox->SetColor(0x00ffffff, NNN::Geometry::Rect::c_RectOrtho::es_point::LeftBottom);
	m_rectDialogueBox->SetColor(0x00ffffff, NNN::Geometry::Rect::c_RectOrtho::es_point::RightBottom);
	
	m_rectMusicOn = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectMusicOn->SetRect(m_musicPosition);
	m_rectMusicOn->SetTexture(m_textureMusicOn);

	m_rectMusicOff = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectMusicOff->SetRect(m_musicPosition);
	m_rectMusicOff->SetTexture(m_textureMusicOff);

	m_rectTime = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectTime->SetRect(make_rect(width, width + 512, 20, 90));
	m_rectTime->SetTexture(m_textureRedStrap);

	m_rectLocation = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectLocation->SetRect(make_rect(width + 100, width + 612, 100, 170));
	m_rectLocation->SetTexture(m_textureRedStrap);
	
	m_rectSoftDisk = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectSoftDisk->SetRect(m_softDiskPosition);
	m_rectSoftDisk->SetTexture(m_textureSoftDisk);
}


void c_MainScreen::UnloadContent(void)
{
	SAFE_DELETE(m_rectBackground);
	SAFE_DELETE(m_rectPerson[0]);
	SAFE_DELETE(m_rectPerson[1]);
	SAFE_DELETE(m_rectPerson[2]);
	SAFE_DELETE(m_rectPerson[3]);
	SAFE_DELETE(m_rectPerson[4]);
	SAFE_DELETE(m_rectNameBar);
	SAFE_DELETE(m_rectLine);
	SAFE_DELETE(m_rectDialogueBox);
	SAFE_DELETE(m_rectMusicOn);
	SAFE_DELETE(m_rectMusicOff);
	SAFE_DELETE(m_rectTime);
	SAFE_DELETE(m_rectLocation);
	SAFE_DELETE(m_rectSoftDisk);

	NNN::Texture::Release(L"NameBar");
	NNN::Texture::Release(L"MusicOn");
	NNN::Texture::Release(L"MusicOff");
	NNN::Texture::Release(L"RedStrap");
	NNN::Texture::Release(L"SoftDisk");
	m_textureNameBar = nullptr;
	m_textureMusicOn = nullptr;
	m_textureMusicOff = nullptr;
	m_textureRedStrap = nullptr;
	m_textureSoftDisk = nullptr;

	unsigned count = m_textureNameList.size();
	for (unsigned i = 0; i < count; ++i)
	{
		WCHAR *wchar_tmp = m_textureNameList[i];
		NNN::Texture::Release(wchar_tmp);
		SAFE_DELETE_ARRAY(wchar_tmp);
	}
	m_textureNameList.clear();
	
	m_nodeReader = nullptr;

	CacheClear();
}


void c_MainScreen::HandleInput(void)
{
	POINT delta = { 0 };

	if (c_InputManager::Tap(&m_musicPosition))
	{
		c_GameSession::GetSingleton()->GetScreenManager()->AddScreen(new c_SettingsScreen(true));
	}
	else if (m_isSavePoint && c_InputManager::Tap(&m_softDiskPosition))
	{
		m_isSavePoint = false;

		const std::vector<c_GameSave*> *savings = c_GameSession::GetSingleton()->GetSavings();
		c_GameSave *currentSave = c_GameSession::GetSingleton()->GetCurrentSave();

		for (std::vector<c_GameSave*>::const_iterator iter = (*savings).begin(); iter != (*savings).end(); ++iter)
		{
			if ((*iter)->GetId() == currentSave->GetId())
			{
				currentSave->DeepCopy(*iter);
				(*iter)->SetTime(time(nullptr));
				c_GameSession::GetSingleton()->SaveRecord();
				break;
			}
		}
	}
	else if (c_InputManager::Pan(&m_panPosition, &delta) && delta.y > 0)
	{
		c_GameSession::GetSingleton()->GetScreenManager()->AddScreen(new c_HistoryScreen(m_history.c_str()));
	}
	else if (m_dialogueBoxState == ec_DialogueBoxState::Lay &&
		c_InputManager::Tap(&m_dialogueBoxPosition))
	{
		m_isReading = true;
		m_isSavePoint = false;
	}
	else if (m_dialogueBoxState == ec_DialogueBoxState::Hang)
	{
		for (int i = 0; i < (m_optionText[2] == 0 ? 2 : 3); ++i)
		{
			if (c_InputManager::Tap(&m_optionPosition[i]))
			{
				m_history += c_TextManager::GetText(m_optionText[i]);
				m_history += L"\n";
				m_dialogueBoxState = ec_DialogueBoxState::RollDown;
				m_isReading = true;
				m_nodeReader = c_GameSession::GetSingleton()->GetScriptXml()->RootElement()->FirstChild()->ToElement();
				while (true)
				{
					while (strcmp(m_nodeReader->Value(), "Section") != 0)
					{
						SafeNextSibling();
					}
					if (atoi(m_nodeReader->Attribute("Id")) != m_optionSection[i])
					{
						SafeNextSibling();
					}
					else
					{
						SafeNextSibling();
						break;
					}
				}
				break;
			}
		}
	}
}


void c_MainScreen::Update(float fElapsedTime, bool otherScreenHasFocus, bool coveredByOtherScreen)
{
	c_GameScreen::Update(fElapsedTime, otherScreenHasFocus, coveredByOtherScreen);

	const char *elementName = nullptr;
	const char *filename = nullptr;
	WCHAR *wchar1 = nullptr;
	WCHAR *wchar2 = nullptr;
	char buf[128] = { 0 };
	LONG width = NNN::Misc::GetClientWidth();
	LONG height = NNN::Misc::GetClientHeight();

	if (m_timeElapsed > 0)
	{
		m_timeElapsed += fElapsedTime;

		if (m_timeElapsed < 0.5)
		{
			m_rectTime->SetRect(make_rect(width - m_timeElapsed * 1024, width - m_timeElapsed * 1024 + 512, 20, 90));
		}
		else if (m_timeElapsed < 8)
		{
			m_rectTime->SetRect(make_rect(width - 512, width, 20, 90));
		}
		else if (m_timeElapsed < 10)
		{
			m_rectTime->SetRect(make_rect(width - 512, width, 20, 90));
			D3DCOLOR color = (((int)((12 - m_timeElapsed) * 0x80)) << 24) | 0xffffff;
			m_rectTime->SetColor(color, NNN::Geometry::Rect::c_RectOrtho::es_point::All);
		}
		else
		{
			m_timeElapsed = 0;
		}
	}

	if (m_locationElapsed > 0)
	{
		m_locationElapsed += fElapsedTime;

		if (m_locationElapsed < 0.5)
		{
			m_rectLocation->SetRect(make_rect(width - m_locationElapsed * 1024 + 100, width - m_locationElapsed * 1024 + 612, 100, 170));
		}
		else if (m_locationElapsed < 8)
		{
			m_rectLocation->SetRect(make_rect(width - 412, width + 100, 100, 170));
		}
		else if (m_locationElapsed < 10)
		{
			m_rectLocation->SetRect(make_rect(width - 412, width + 100, 100, 170));
			D3DCOLOR color = (((int)((12 - m_locationElapsed) * 0x80)) << 24) | 0xffffff;
			m_rectLocation->SetColor(color, NNN::Geometry::Rect::c_RectOrtho::es_point::All);
		}
		else
		{
			m_locationElapsed = 0;
		}
	}

	if (m_dialogueBoxState == ec_DialogueBoxState::RollUp)
	{
		m_dialogueBoxRoll += 15;
	}
	else if (m_dialogueBoxState == ec_DialogueBoxState::RollDown)
	{
		m_dialogueBoxRoll -= 15;
	}

	if (m_dialogueBoxRoll > height - 400)
	{
		m_dialogueBoxState = ec_DialogueBoxState::Hang;
	}
	else if (m_dialogueBoxRoll < 0)
	{
		m_dialogueBoxState = ec_DialogueBoxState::Lay;
	}

	while (m_isReading)
	{
		elementName = m_nodeReader->Value();
		if (strcmp(elementName, "Bgm") == 0)
		{
			m_bgmId = atoi(m_nodeReader->Attribute("Id"));
			if (m_bgmId != 0)
			{
				filename = m_nodeReader->Attribute("File");
				if (m_nodeReader->Attribute("Start") != nullptr && m_nodeReader->Attribute("End") != nullptr)
				{
					c_AudioManager::PlayBgm(filename,
					atof(m_nodeReader->Attribute("Start")), atof(m_nodeReader->Attribute("End")));
				}
				else
				{
					c_AudioManager::PlayBgm(filename);
				}
			}
			else
			{
				c_AudioManager::ReleaseBgm();
			}
		}
		else if (strcmp(elementName, "SavePoint") == 0)
		{
			m_isSavePoint = true;
			c_GameSession::GetSingleton()->GetCurrentSave()->SetSavePoint(atoi(m_nodeReader->Attribute("Id")));
			c_GameSession::GetSingleton()->GetCurrentSave()->SetLocation(m_currentLocation);
		}
		else if (strcmp(elementName, "Section") == 0)
		{
			c_GameSession::GetSingleton()->GetCurrentSave()->SectionPushBack(atoi(m_nodeReader->Attribute("Id")));
		}
		else if (strcmp(elementName, "Background") == 0)
		{
			filename = m_nodeReader->Attribute("File");
			NNN::Text::char2wchar(filename, &wchar1);
			m_textureBackground = NNN::Texture::Find(wchar1);
			if (m_textureBackground == nullptr)
			{
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
				sprintf_s(buf, 128, "Data/%s.png", filename);
#else
				sprintf(buf, "Data/%s.png", filename);
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
				NNN::Text::char2wchar(buf, &wchar2);
				NNN::Texture::Add(wchar1, wchar2);
				SAFE_DELETE_ARRAY(wchar2);
				m_textureNameList.push_back(wchar1);
				m_textureBackground = NNN::Texture::Find(wchar1);
			}
			else
			{
				SAFE_DELETE_ARRAY(wchar1);
			}
			m_rectBackground->SetTexture(m_textureBackground);
		}
		else if (strcmp(elementName, "Person") == 0)
		{
			int location = atoi(m_nodeReader->Attribute("Location"));
			filename = m_nodeReader->Attribute("File");

			if (strlen(filename) > 0)
			{
				NNN::Text::char2wchar(filename, &wchar1);
				m_texturePerson[location] = NNN::Texture::Find(wchar1);
				if (m_texturePerson[location] == nullptr)
				{
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
					sprintf_s(buf, 128, "Data/%s.png", filename);
#else
					sprintf(buf, "Data/%s.png", filename);
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
					NNN::Text::char2wchar(buf, &wchar2);
					NNN::Texture::Add(wchar1, wchar2);
					SAFE_DELETE_ARRAY(wchar2);
					m_textureNameList.push_back(wchar1);
					m_texturePerson[location] = NNN::Texture::Find(wchar1);
				}
				else
				{
					SAFE_DELETE_ARRAY(wchar1);
				}
				m_rectPerson[location]->SetTexture(m_texturePerson[location]);
			}
			else
			{
				m_texturePerson[location] = nullptr;
			}
		}
		else if (strcmp(elementName, "Time") == 0)
		{
			m_timeId = atoi(m_nodeReader->Attribute("Id"));
			m_timeElapsed = 0.01f;
			m_rectTime->SetColor(0xffffffff, NNN::Geometry::Rect::c_RectOrtho::es_point::All);
		}
		else if (strcmp(elementName, "Location") == 0)
		{
			m_currentLocation = atoi(m_nodeReader->Attribute("Id"));
			m_locationElapsed = 0.01f;
			m_rectLocation->SetColor(0xffffffff, NNN::Geometry::Rect::c_RectOrtho::es_point::All);
		}
		else if (strcmp(elementName, "Name") == 0)
		{
			m_nameId = atoi(m_nodeReader->Attribute("Id"));
			m_history += c_TextManager::GetText(m_nameId);
			m_history += L"\n";
		}
		else if (strcmp(elementName, "Dialogue") == 0)
		{
			m_dialogueId = atoi(m_nodeReader->Attribute("Id"));
			m_history += c_TextManager::GetText(m_dialogueId);
			m_history += L"\n";
			m_isReading = false;
		}
		else if (strcmp(elementName, "Option") == 0)
		{
			m_optionText[0] = atoi(m_nodeReader->Attribute("FirstId"));
			m_optionSection[0] = atoi(m_nodeReader->Attribute("FirstSection"));
			m_optionText[1] = atoi(m_nodeReader->Attribute("SecondId"));
			m_optionSection[1] = atoi(m_nodeReader->Attribute("SecondSection"));
			if (m_nodeReader->Attribute("ThirdId") != nullptr)
			{
				m_optionText[2] = atoi(m_nodeReader->Attribute("ThirdId"));
				m_optionSection[2] = atoi(m_nodeReader->Attribute("ThirdSection"));
			}
			m_dialogueBoxState = ec_DialogueBoxState::RollUp;
			m_isReading = false;
		}
		else if (strcmp(elementName, "Goto") == 0)
		{
			int sectionId = atoi(m_nodeReader->Attribute("Id"));
			m_nodeReader = c_GameSession::GetSingleton()->GetScriptXml()->RootElement()->FirstChild()->ToElement();
			while (true)
			{
				while (strcmp(m_nodeReader->Value(),"Section") != 0)
				{
					SafeNextSibling();
				}
				if (atoi(m_nodeReader->Attribute("Id")) != sectionId)
				{
					SafeNextSibling();
				}
				else
				{
					break;
				}
			}
		}
		else if (strcmp(elementName, "End") == 0)
		{
			ExitScreen();
			c_GameSession::GetSingleton()->GetScreenManager()->AddScreen(new c_EndScreen());
			m_isReading = false;
			break;
		}
		SafeNextSibling();
	}
}


void c_MainScreen::Draw(float fElapsedTime)
{
	if (m_textureBackground != nullptr)
	{
		m_rectBackground->OnRender(fElapsedTime);
	}
	
	for (int i = 0; i < 5; ++i)
	{
		if (m_texturePerson[i] != nullptr)
		{
			m_rectPerson[i]->OnRender(fElapsedTime);
		}
	}

	if (m_dialogueBoxState == ec_DialogueBoxState::Lay)
	{
		m_rectDialogueBox->SetRect(m_dialogueBoxPosition);
		m_rectDialogueBox->OnRender(fElapsedTime);

		c_TextManager::DrawString(m_dialogueId, 0xff000000, 0, DT_LEFT | DT_TOP | DT_WORDBREAK, &m_dialogueShadowPosition);
		c_TextManager::DrawString(m_dialogueId, 0xffffffff, 0, DT_LEFT | DT_TOP | DT_WORDBREAK, &m_dialogueBasePosition);

		m_rectLine->SetRect(make_rect(0, m_clientPosition.right, m_nameBarPosition.bottom, m_nameBarPosition.bottom + 5));		
		m_rectLine->OnRender(fElapsedTime);

		m_rectNameBar->SetRect(m_nameBarPosition);
		m_rectNameBar->OnRender(fElapsedTime);

		c_TextManager::DrawString(m_nameId, 0xff000000, 0, DT_CENTER | DT_VCENTER, &m_nameShadowPosition);
		c_TextManager::DrawString(m_nameId, 0xffffffff, 0, DT_CENTER | DT_VCENTER, &m_nameBasePosition);
	}
	else
	{
		RECT dialogueBoxPosition = m_dialogueBoxPosition;
		RECT dialogueBasePosition = m_dialogueBasePosition;
		RECT dialogueShadowPosition = m_dialogueShadowPosition;
		dialogueBoxPosition.top -= m_dialogueBoxRoll;
		dialogueBasePosition.top -= m_dialogueBoxRoll;
		dialogueShadowPosition.top -= m_dialogueBoxRoll;

		m_rectDialogueBox->SetRect(dialogueBoxPosition);
		m_rectDialogueBox->OnRender(fElapsedTime);

		c_TextManager::DrawString(m_dialogueId, 0xff000000, 0, DT_LEFT | DT_TOP | DT_WORDBREAK, &dialogueShadowPosition);
		c_TextManager::DrawString(m_dialogueId, 0xffffffff, 0, DT_LEFT | DT_TOP | DT_WORDBREAK, &dialogueBasePosition);

		RECT nameBarPosition = m_nameBarPosition;
		RECT nameBasePosition = m_nameBasePosition;
		RECT nameShadowPosition = m_nameShadowPosition;
		nameBarPosition.top -= m_dialogueBoxRoll;
		nameBasePosition.top -= m_dialogueBoxRoll;
		nameShadowPosition.top -= m_dialogueBoxRoll;
		nameBarPosition.bottom -= m_dialogueBoxRoll;
		nameBasePosition.bottom -= m_dialogueBoxRoll;
		nameShadowPosition.bottom -= m_dialogueBoxRoll;

		m_rectLine->SetRect(make_rect(0, m_clientPosition.right, nameBarPosition.bottom, nameBarPosition.bottom + 5));
		m_rectLine->OnRender(fElapsedTime);

		m_rectNameBar->SetRect(nameBarPosition);
		m_rectNameBar->OnRender(fElapsedTime);

		c_TextManager::DrawString(m_nameId, 0xff000000, 0, DT_CENTER | DT_VCENTER, &nameShadowPosition);
		c_TextManager::DrawString(m_nameId, 0xffffffff, 0, DT_CENTER | DT_VCENTER, &nameBasePosition);
	}

	if (m_dialogueBoxState == ec_DialogueBoxState::Hang)
	{
		for (int i = 0; i < (m_optionText[2] == 0 ? 2 : 3); ++i)
		{
			c_TextManager::DrawString(m_optionText[i], 0xff66ccff, 0, DT_LEFT | DT_VCENTER, &m_optionPosition[i]);
		}
	}

	if (c_GameSession::GetSingleton()->GetSoundEnable())
	{
		m_rectMusicOn->OnRender(fElapsedTime);
		if (m_bgmId != 0)
		{
			c_TextManager::DrawString(m_bgmId, 0xffffffff, 0, DT_LEFT | DT_VCENTER, &m_bgmPosition);
		}
	}
	else
	{
		m_rectMusicOff->OnRender(fElapsedTime);
	}

	if (m_timeElapsed > 0)
	{
		m_rectTime->OnRender(fElapsedTime);
	}

	if (m_timeElapsed > 0.5 && m_timeElapsed < 1)
	{
		c_TextManager::DrawString(m_timeId, (((int)((m_timeElapsed - 2) * 0x80)) << 24) | 0xffffff,
			0, DT_LEFT | DT_VCENTER, &m_timeTextPosition);
	}
	else if (m_timeElapsed > 8 && m_timeElapsed < 10)
	{
		D3DCOLOR color = (((int)((12 - m_timeElapsed) * 0x80)) << 24) | 0xffffff;
		c_TextManager::DrawString(m_timeId, color, 0, DT_LEFT | DT_VCENTER, &m_timeTextPosition);
	}
	else if (m_timeElapsed >= 1)
	{
		c_TextManager::DrawString(m_timeId, 0xffffffff, 0, DT_LEFT | DT_VCENTER, &m_timeTextPosition);
	}

	if (m_locationElapsed > 0)
	{
		m_rectLocation->OnRender(fElapsedTime);
	}

	if (m_locationElapsed > 0.5 && m_locationElapsed < 1)
	{
		c_TextManager::DrawString(m_currentLocation, (((int)((m_locationElapsed - 2) * 0x80)) << 24) | 0xffffff,
			0, DT_LEFT | DT_VCENTER, &m_locationTextPosition);
	}
	else if (m_locationElapsed > 8 && m_locationElapsed < 10)
	{
		D3DCOLOR color = (((int)((12 - m_locationElapsed) * 0x80)) << 24) | 0xffffff;
		c_TextManager::DrawString(m_currentLocation, color, 0, DT_LEFT | DT_VCENTER, &m_locationTextPosition);
	}
	else if (m_locationElapsed >= 1)
	{
		c_TextManager::DrawString(m_currentLocation, 0xffffffff, 0, DT_LEFT | DT_VCENTER, &m_locationTextPosition);
	}

	if (m_isSavePoint)
	{
		m_rectSoftDisk->OnRender(fElapsedTime);
	}
}


void c_MainScreen::Reset(void)
{
	m_nodeReader = c_GameSession::GetSingleton()->GetScriptXml()->RootElement()->FirstChild()->ToElement();
	while (true)
	{
		while (strcmp(m_nodeReader->Value(), "SavePoint") != 0)
		{
			SafeNextSibling();
		}
		if (atoi(m_nodeReader->Attribute("Id")) != c_GameSession::GetSingleton()->GetCurrentSave()->GetSavePoint())
		{
			SafeNextSibling();
		}
		else
		{
			SafeNextSibling();
			break;
		}
	}

	m_isReading = true;
	m_isSavePoint = false;
	m_timeElapsed = 0;
	m_locationElapsed = 0;
	m_bgmId = 0;
	m_timeId = 0;
	m_currentLocation = c_GameSession::GetSingleton()->GetCurrentSave()->GetLocation();
	m_nameId = 0;
	m_dialogueId = 0;
	m_dialogueBoxRoll = 0;

	for (int i = 0; i < 3; ++i)
	{
		m_optionText[i] = 0;
		m_optionSection[i] = 0;
	}

	m_dialogueBoxState = ec_DialogueBoxState::Lay;
	
	m_textureBackground = nullptr;
	m_texturePerson[0] = nullptr;
	m_texturePerson[1] = nullptr;
	m_texturePerson[2] = nullptr;
	m_texturePerson[3] = nullptr;
	m_texturePerson[4] = nullptr;

	CacheClear();
}


void c_MainScreen::CacheClear(void)
{
	m_history.clear();
	c_AudioManager::ReleaseBgm();
}


void c_MainScreen::SafeNextSibling(void)
{
	if (m_nodeReader->NextSibling() != nullptr)
	{
		m_nodeReader = m_nodeReader->NextSibling()->ToElement();
	}
}