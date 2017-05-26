//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// SettingsScreen ������Ļ
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_SettingsScreen_H_
#define _Empress___c_SettingsScreen_H_

#include "c_GameScreen.h"

// ������Ļ
class c_SettingsScreen : public c_GameScreen
{
public:
	// ���캯��
	c_SettingsScreen(bool saveEnable);
	// ��������
	virtual ~c_SettingsScreen(void);
	// ����
	virtual void LoadContent(void);
	// ж��
	virtual void UnloadContent(void);
	// ����
	virtual void HandleInput(void);
	// ����
	virtual void Draw(float fElapsedTime);

private:
	// ���¼�������
	void ReloadVolume(void);
	// ���¼�������λ��
	void ReloadLang(void);

	NNN::Texture::c_Texture *m_textureBack; // ��������
	NNN::Texture::c_Texture *m_textureSave; // ��������
	NNN::Texture::c_Texture *m_textureSoundEnable; // ������������
	NNN::Texture::c_Texture *m_textureSoundDisable; // ������������
	NNN::Texture::c_Texture *m_textureVolumeIncrease; // ������������
	NNN::Texture::c_Texture *m_textureVolumeDecrease; // ������С����

	NNN::Geometry::Rect::c_RectOrtho *m_rectBackground; // ��������ɫȫ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectBack; // ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectSave; // ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectSoundEnable; // ��������λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectSoundDisable; // ��������λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectVolumeIncrease; // ��������λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectVolumeDecrease; // ������Сλ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectLine; // һ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectLang; // ����λ��

	RECT m_clientPosition; // �ͻ���λ��
	RECT m_backPosition; // ����λ��
	RECT m_savePosition; // ����λ��
	RECT m_soundPosition; // ����λ��
	RECT m_volumePosition; // ����λ��
	RECT m_volumeIncreasePosition; // �������Ӱ�ťλ��
	RECT m_volumeDecreasePosition; // ������С��ťλ��
	RECT m_langPosition; // ����λ��
	RECT m_zhcnPosition; // ��������λ��
	RECT m_zhhkPosition; // ��۷���λ��
	RECT m_enusPosition; // Ӣ��λ��
	RECT m_jajpPosition; // ����λ��
	RECT m_currentPosition; // ��ǰ����λ��

	bool m_saveEnable; // �Ƿ�����л����浵��Ļ
	bool m_firstFill; // �Ƿ�������
	WCHAR *m_volume; // ����
};

#endif	/* _Empress___c_SettingsScreen_H_ */