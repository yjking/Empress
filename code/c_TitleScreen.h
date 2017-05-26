//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// TitleScreen ������Ļ
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_TitleScreen_H_
#define _Empress___c_TitleScreen_H_

#include "c_GameScreen.h"

// ������Ļ
class c_TitleScreen : public c_GameScreen
{
public:
	// ���캯��
	c_TitleScreen(void);
	// ��������
	virtual ~c_TitleScreen(void);
	// ����
	virtual void LoadContent(void);
	// ж��
	virtual void UnloadContent(void);
	// ����
	virtual void HandleInput(void);
	// ����
	virtual void Draw(float fElapsedTime);

private:
	NNN::Texture::c_Texture * m_textureTitle; // ��������
	NNN::Geometry::Rect::c_RectOrtho *m_rectTitle; // ����λ��
	RECT m_startPosition; // ��ʼλ��
	RECT m_settingsPosition; // ����λ��
};

#endif	/* _Empress___c_TitleScreen_H_ */