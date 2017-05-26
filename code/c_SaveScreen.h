//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// SaveScreen �浵��Ļ
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_SaveScreen_H_
#define _Empress___c_SaveScreen_H_

#include "c_GameScreen.h"

// �浵��Ļ
class c_SaveScreen : public c_GameScreen
{
public:
	// ���캯��
	c_SaveScreen(bool saveEnable);
	// ��������
	virtual ~c_SaveScreen(void);
	// ����
	virtual void LoadContent(void);
	// ж��
	virtual void UnloadContent(void);
	// ����
	virtual void HandleInput(void);
	// ����
	virtual void Draw(float fElapsedTime);
	
private:
	// ���¼��ش浵
	void ReloadSave(void);

	NNN::Texture::c_Texture *m_textureBack; // ��������
	NNN::Texture::c_Texture *m_textureSettings; // ��������
	NNN::Texture::c_Texture *m_textureAdd; // �½�����
	NNN::Texture::c_Texture *m_textureSave; // �浵����
	NNN::Texture::c_Texture *m_textureLoad; // ��������
	NNN::Texture::c_Texture *m_textureCopy; // ��������
	NNN::Texture::c_Texture *m_textureDelete; // ɾ������

	NNN::Geometry::Rect::c_RectOrtho *m_rectBackground; // ��������ɫȫ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectSelected; // ѡ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectBar; // ������λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectBack; // ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectSettings; // ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectAdd; // �½�λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectSave; // �浵λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectLoad; // ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectCopy; // ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectDelete; // ɾ��λ��

	RECT m_backPosition; // ����λ��
	RECT m_settingsPosition; // ����λ��
	RECT m_addPosition; // �½�λ��
	RECT m_savePosition; // �浵λ��
	RECT m_loadPosition; // ����λ��
	RECT m_copyPosition; // ����λ��
	RECT m_deletePosition; // ɾ��λ��
	RECT m_panPosition; // ��ƽ�Ƶ�λ��

	std::vector<NNN::Geometry::Rect::c_RectOrtho*> m_rectPhotoList; // λ�û���
	std::vector<WCHAR*> m_textureNameList; // �������ƻ���
	std::vector<WCHAR*> m_completeList; // ��ɶȻ���
	std::vector<WCHAR*> m_timeList; // ʱ�仺��

	bool m_saveEnable; // �Ƿ�����浵������浵˵�������ڽ�����Ϸ������Ϊ�մӱ��⻭�濪ʼ��
	unsigned m_saveCount; // �浵��
	int m_col; // ����
	int m_offsetY; // ���յ�������
	int m_selectedIndex; // ѡ��������
};

#endif	/* _Empress___c_SaveScreen_H_ */