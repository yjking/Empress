//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// GameSession ��Ϸ�Ự
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_GameSession_H_
#define _Empress___c_GameSession_H_

#include "c_AudioManager.h"
#include "c_InputManager.h"
#include "c_ScreenManager.h"
#include "c_TextManager.h"
#include "c_GameSave.h"
#include "c_MainScreen.h"

// ��Ϸ�Ự
class c_GameSession
{
public:
	// ��������
	~c_GameSession(void);
	// ��ȡ����
	static c_GameSession *GetSingleton(void);
	// ��ȡ��Ļ
	c_ScreenManager *GetScreenManager(void) const;
	// ��ȡ����Ļ
	c_MainScreen *GetMainScreen(void);
	// ��ȡ�Ƿ��ڻ״̬
	bool GetIsActive(void) const;
	// �����Ƿ��ڻ״̬
	void SetIsActive(bool value);
	// ��ȡ��ǰ����
	ec_LANG GetLang(void) const;
	// ���õ�ǰ����
	void SetLang(ec_LANG value);
	// ��ȡ��ǰ�Ƿ���������
	bool GetSoundEnable(void) const;
	// ���õ�ǰ�Ƿ���������
	void SetSoundEnable(bool value);
	// ��ȡ��ǰ����
	int GetVolume(void) const;
	// ���õ�ǰ����
	void SetVolume(int value);
	// ��ȡ�籾Xml
	TiXmlDocument *GetScriptXml(void) const;
	// ��ȡ��ͼXml
	TiXmlDocument *GetMapXml(void) const;
	// ��ȡ��ǰ�浵
	c_GameSave *GetCurrentSave(void) const;
	// ���õ�ǰ�浵
	void SetCurrentSave(c_GameSave *value);
	// ��ȡ���д浵
	const std::vector<c_GameSave*> *GetSavings(void) const;
	// ���ָ��Index�Ĵ浵
	void SaveErase(int index);
	// �Ѵ浵ѹ��ջ
	void SavePushBack(c_GameSave* value);
	// ����浵���ļ�
	void SaveRecord(void) const;
	// �������浵Id
	int FindMaxSaveId(void) const;
	// ����
	void LoadContent(void);
	// ж��
	void UnloadContent(void);
	// ����
	void Update(float fElapsedTime) const;
	// ����
	void Draw(float fElapsedTime) const;

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	HRESULT OnReset_dx9(void);
	HRESULT OnLost_dx9(void);
#endif	// NNN_PLATFORM_WIN32

private:
	// ���캯��
	c_GameSession(void);

	c_ScreenManager *m_screenManager; // ��Ļ����
	c_MainScreen *m_mainScreen; // ����Ļ
	bool m_isActive; // �Ƿ��ڻ״̬�У������Ƿ�ʧ����
	ec_LANG m_lang; // ��ǰ����
	bool m_soundEnable; // ��ǰ�Ƿ�������Ƶ
	int m_volume; // ��ǰ����
	TiXmlDocument *m_recordXml; // ��¼Xml
	TiXmlDocument *m_scriptXml; // �籾Xml
	TiXmlDocument *m_mapXml; // ��ͼXml
	c_GameSave *m_currentSave; // ��ǰ�浵
	std::vector<c_GameSave*> m_savings; // ���д浵
	char *m_recordPath; //�浵·��
};

#endif	/* _Empress___c_GameSession_H_ */