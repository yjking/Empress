//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// AudioManager ��Ƶ����
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_AudioManager_H_
#define _Empress___c_AudioManager_H_

#include "../../../Src/nnnEngine/nnn.h"

// ��Ƶ����
class c_AudioManager
{
public:
	// ���캯��
	c_AudioManager(void);
	// ��������
	~c_AudioManager(void);
	// ���أ���ʱ�����κβ�����
	static void LoadContent(void);
	// ж��
	static void UnloadContent(void);
	// ����ָ���������֣�����Ѿ��ڲ��ţ��򲻴������δ���뻺�棬����룩
	static void PlayBgm(const char *filename, double startTime = 0, double endTime = 0);
	// �ͷű�������
	static void ReleaseBgm(void);

private:
	static WCHAR *m_bgm; // �����������ƻ���
};

#endif	/* _Empress___c_AudioManager_H_ */