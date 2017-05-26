//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// InputManager �������
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_InputManager_H_
#define _Empress___c_InputManager_H_

#include "../../../Src/nnnEngine/nnn.h"

// �������
class c_InputManager
{
public:
	// ���캯��
	c_InputManager(void);
	// ��������
	~c_InputManager(void);
	// ����
	static void LoadContent(void);
	// ж��
	static void UnloadContent(void);
	// ����
	static void Update(float fElapsedTime);
	// ����
	static void Draw(float fElapsedTime);

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	static HRESULT OnReset_dx9(void);
	static HRESULT OnLost_dx9(void);
#endif	// NNN_PLATFORM_WIN32

	// Ϊ�������ͳһ��ʹ�õ����������
	// ���
	static bool Tap(RECT *rect);
	// ����
	static bool Press(RECT *rect);
	// �ƶ�
	static bool Pan(RECT *rect, POINT *delta);

private:
	static NNN::Sprite::Scene::c_Scene *m_scene; // ����
	static NNN::Sprite::Scene::c_SpriteInst *m_spriteTouchWave; // ����
	static float m_totalTime; // ���ƶ�����������ʱ��
	static std::vector<POINT> m_touchPoints; // ����λ��
	static int m_preTouchesCount; // ��һ֡�Ĵ�����Ŀ
};

#endif	/* _Empress___c_InputManager_H_ */