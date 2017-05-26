//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// GameScreen ��Ϸ��Ļ��������ࣩ
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_GameScreen_H_
#define _Empress___c_GameScreen_H_

#include "../../../Src/nnnEngine/nnn.h"

// ��Ļ״̬
enum class ec_ScreenState
{
	TransitionOn, // ��Ļ����
    Active, // ��Ļ���ڻ
    TransitionOff, // ��Ļ����
    Hidden, // ��Ļ��������
};

// ��Ϸ��Ļ��������ࣩ
class c_GameScreen
{
public:
	// ���캯��
	c_GameScreen(void);
	// ��������
	virtual ~c_GameScreen(void);
	// ��ȡ�Ƿ񵯳�����
	bool GetIsPopup(void) const;
	// ��ȡ����ʱ��
	float GetTransitionOnTime(void) const;
	// ��ȡ����ʱ��
	float GetTransitionOffTime(void) const;
	// ��ȡ����λ�ã�0��1�����䣩
	float GetTransitionPosition(void) const;
	// ��ȡ����λ�ã�255��0�����䣩
	int GetTransitionAlpha(void) const;
	// ��ȡ��Ļ״̬
	ec_ScreenState GetScreenState(void) const;
	// ��ȡ�Ƿ������˳�
	bool GetIsExiting(void) const;
	// �����Ƿ������˳�
	void SetIsExiting(bool value);
	// �����˳�ʱִ�еĺ�����ָ�룩
	void (*Exiting)(c_GameScreen *obj);
	// ��ȡ�Ƿ����ڻ
	bool GetIsActive(void) const;
	// ����
	virtual void LoadContent(void) = 0;
	// ж��
	virtual void UnloadContent(void) = 0;
	// ����
	virtual void Update(float fElapsedTime, bool otherScreenHasFocus, bool coveredByOtherScreen);
	// ����
	virtual void HandleInput(void) = 0;
	// ����
	virtual void Draw(float fElapsedTime) = 0;

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	HRESULT OnReset_dx9(void);
	HRESULT OnLost_dx9(void);
#endif	// NNN_PLATFORM_WIN32

	// �˳�����Ļ
	void ExitScreen(void);

protected:
	// �����Ƿ񵯳�����
	void SetIsPopup(bool value);
	// ���ý���ʱ��
	void SetTransitionOnTime(float value);
	// ���ý���ʱ��
	void SetTransitionOffTime(float value);
	// ���ý���λ�ã�0��1�����䣩
	void SetTransitionPosition(float value);
	// ������Ļ״̬
	void SetScreenState(ec_ScreenState value);
	// ����
	NNN::Sprite::Scene::c_Scene *m_scene;

private:
	bool m_isPopup; // �Ƿ񵯳�����
	float m_transitionOnTime; // ����ʱ��
	float m_transitionOffTime; // ����ʱ��
	float m_transitionPosition; // ����λ�ã�0��1�����䣩
	ec_ScreenState m_screenState; // ��Ļ״̬
	bool m_isExiting; // �Ƿ������˳�
	bool m_otherScreenHasFocus; // �Ƿ񽹵����������ڣ���Windowsƽ̨��
	bool UpdateTransition(float fElapsedTime, float time, int direction); // ���½���
};

#endif	/* _Empress___c_GameScreen_H_ */