//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// MainScreen ����Ļ
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_MainScreen_H_
#define _Empress___c_MainScreen_H_

#include "../../../3rdParty/TinyXML/xml.h"
#include "c_GameScreen.h"

// �Ի���״̬
enum class ec_DialogueBoxState
{
	Lay, // �Ի�������
	RollUp, // �Ի�������չ��
	Hang, // �Ի���߹���
	RollDown, // �Ի�����������
};

// ����Ļ
class c_MainScreen : public c_GameScreen
{
public:
	// ���캯��
	c_MainScreen(void);
	// ��������
	virtual ~c_MainScreen(void);
	// ����
	virtual void LoadContent(void);
	// ж��
	virtual void UnloadContent(void);
	// ����
	virtual void HandleInput(void);
	// ����
	virtual void Update(float fElapsedTime, bool otherScreenHasFocus, bool coveredByOtherScreen);
	// ����
	virtual void Draw(float fElapsedTime);
	// ���á�������ʱ����Ҫ������Ļ���и�λ
	void Reset(void);

private:
	// �������
	void CacheClear(void);
	// ��ȫ�ط�����һ���ڵ㡣����nullptr
	void SafeNextSibling(void);

	NNN::Texture::c_Texture *m_textureBackground; // ��������
	NNN::Texture::c_Texture *m_texturePerson[5]; // ��������
	NNN::Texture::c_Texture *m_textureNameBar; // ����������
	NNN::Texture::c_Texture *m_textureMusicOn; // ������������
	NNN::Texture::c_Texture *m_textureMusicOff; // ���ֽ�������
	NNN::Texture::c_Texture *m_textureRedStrap; // ʱ��ص�����
	NNN::Texture::c_Texture *m_textureSoftDisk; // ��������

	NNN::Geometry::Rect::c_RectOrtho *m_rectBackground; // ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectPerson[5]; // ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectNameBar; // ������λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectLine; // һ����λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectDialogueBox; // �Ի���λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectMusicOn; // ��������λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectMusicOff; // ���ֽ���λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectTime; // ʱ��λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectLocation; // �ص�λ��
	NNN::Geometry::Rect::c_RectOrtho *m_rectSoftDisk; // ����λ��
	
	RECT m_nameBarPosition; // ������λ��
	RECT m_nameBasePosition; // ���ƻ�׼λ��
	RECT m_nameShadowPosition; // ������Ӱλ��
	RECT m_dialogueBoxPosition; // �Ի���λ��
	RECT m_dialogueBasePosition; // �Ի����ֻ�׼λ��
	RECT m_dialogueShadowPosition; // �Ի�������Ӱλ��
	RECT m_musicPosition; // ����λ��
	RECT m_bgmPosition; // ������������λ��
	RECT m_timeTextPosition; // ʱ��λ��
	RECT m_locationTextPosition; // �ص�λ��
	RECT m_softDiskPosition; // ����λ��
	RECT m_personPosition[5]; // ����λ��
	RECT m_optionPosition[3]; // ѡ��λ��
	RECT m_clientPosition; // �ͻ���λ��
	RECT m_panPosition; // ��ƽ�Ƶ�λ��

	std::vector<WCHAR*> m_textureNameList; // �������ƻ���
	TiXmlElement *m_nodeReader; // �ڵ��ȡ��
	bool m_isReading; // �Ƿ����ڶ�ȡ
	bool m_isSavePoint; // �Ƿ��ڼ�¼��
	float m_timeElapsed; // ʱ�䶯������ʱ��
	float m_locationElapsed; // �ص㶯������ʱ��
	int m_bgmId; // ������������Id
	int m_timeId; // ʱ��Id
	int m_currentLocation; // ��ǰ�ص�Id
	int m_nameId; // ����Id
	int m_dialogueId; // �Ի�Id
	int m_dialogueBoxRoll; // �Ի����չ��ֵ
	int m_optionText[3]; // ѡ���ı�Id
	int m_optionSection[3]; // ѡ���Ծ���Ļ���Id
	ec_DialogueBoxState m_dialogueBoxState; // �Ի���״̬
	std::wstring m_history; // ��ʷ��¼
};

#endif	/* _Empress___c_MainScreen_H_ */