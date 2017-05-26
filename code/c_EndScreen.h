//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// EndScreen ������Ļ
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_EndScreen_H_
#define _Empress___c_EndScreen_H_

#include "c_GameScreen.h"

// ������Ļ
class c_EndScreen : public c_GameScreen
{
public:
	// ���캯��
	c_EndScreen(void);
	// ��������
	virtual ~c_EndScreen(void);
	// ����
	virtual void LoadContent(void);
	// ж��
	virtual void UnloadContent(void);
	// ����
	virtual void HandleInput(void);
	// ����
	virtual void Draw(float fElapsedTime);

private:
	NNN::Texture::c_Texture * m_textureQHua; // Q��С������
	NNN::Geometry::Rect::c_RectOrtho *m_rectQHua; // Q��С��λ��

	RECT m_staffPosition; // ��Ա����λ��
	RECT m_clientPosition; // �ͻ���λ��
	std::wstring m_result; // ��Ա����
	const WCHAR *m_staff; // ��Ա����
	float m_totalTime; // ��������ʱ��
};

#endif	/* _Empress___c_EndScreen_H_ */