//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// HistoryScreen ��ʷ��¼��Ļ
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_HistoryScreen_H_
#define _Empress___c_HistoryScreen_H_

#include "c_GameScreen.h"

// ��ʷ��¼��Ļ
class c_HistoryScreen : public c_GameScreen
{
public:
	// ���캯��
	c_HistoryScreen(const WCHAR *text);
	// ��������
	virtual ~c_HistoryScreen(void);
	// ����
	virtual void LoadContent(void);
	// ж��
	virtual void UnloadContent(void);
	// ����
	virtual void HandleInput(void);
	// ����
	virtual void Draw(float fElapsedTime);

private:
	NNN::Texture::c_Texture * m_textureRaise; // ���������
	NNN::Geometry::Rect::c_RectOrtho *m_rectBackground; // ��������ɫȫ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectRaise; // �����λ��

	RECT m_clientPosition; // �ͻ���λ��
	RECT m_textPosition; // ��ʷ��¼λ��
	RECT m_backPosition; // ����λ��
	const WCHAR *m_text; // ��ʷ��¼
	bool m_firstFill; // �Ƿ�������
};

#endif	/* _Empress___c_HistoryScreen_H_ */