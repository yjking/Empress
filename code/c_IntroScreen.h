//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// IntroScreen �볡��Ļ
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_IntroScreen_H_
#define _Empress___c_IntroScreen_H_

#include "c_GameScreen.h"

// �볡��Ļ
class c_IntroScreen : public c_GameScreen
{
public:
	// ���캯��
	c_IntroScreen(void);
	// ��������
	virtual ~c_IntroScreen(void);
	// ����
	virtual void LoadContent(void);
	// ж��
	virtual void UnloadContent(void);
	// ����
	virtual void HandleInput(void);
	// ����
	virtual void Draw(float fElapsedTime);

private:
	NNN::Texture::c_Texture * m_textureNewGameLogo; // �������־����
	NNN::Geometry::Rect::c_RectOrtho *m_rectNewGameLogo; // �������־λ��

	RECT m_zcloudPosition; // ZCloudλ��
	RECT m_clientPosition; // �ͻ���λ��
	float m_totalTime; // ��������ʱ��
};

#endif	/* _Empress___c_IntroScreen_H_ */