//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// ScreenManager ��Ļ����
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_ScreenManager_H_
#define _Empress___c_ScreenManager_H_

#include "c_GameScreen.h"

// ��Ļ����
class c_ScreenManager
{
public:
	// ���캯��
	c_ScreenManager(void);
	// ��������
	~c_ScreenManager(void);
	// ����
	void Update(float fElapsedTime);
	// ����
	void Draw(float fElapsedTime) const;

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	HRESULT OnReset_dx9(void);
	HRESULT OnLost_dx9(void);
#endif	// NNN_PLATFORM_WIN32

	// ������Ļ
	void AddScreen(c_GameScreen *screen);
	// �Ƴ���Ļ
	void RemoveScreen(c_GameScreen *screen);
	// �ͷ���Ļ
	void ReleaseScreens(void);

private:
	std::vector<c_GameScreen*> m_screens; // ��Ļջ
	std::vector<c_GameScreen*> m_screensToUpdate; // ׼�����и��µ���Ļջ
	std::vector<c_GameScreen*> m_screensToRelease; // ׼�������ͷŵ���Ļջ
};

#endif	/* _Empress___c_ScreenManager_H_ */