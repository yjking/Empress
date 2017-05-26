//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// GameSave ��Ϸ�浵
//--------------------------------------------------------------------------------------

#include <time.h>
#include <vector>

#pragma once
#ifndef _Empress___c_GameSave_H_
#define _Empress___c_GameSave_H_

// ��Ϸ�浵
class c_GameSave
{
public:
	// ���캯��
	c_GameSave(void);
	// ���캯����������
	c_GameSave(int id, int savePoint, time_t time, int location);
	// ��������
	~c_GameSave(void);
	// ��ȡId
	int GetId(void) const;
	// ����Id
	void SetId(int value);
	// ��ȡ��¼��
	int GetSavePoint(void) const;
	// ���ü�¼��
	void SetSavePoint(int value);
	// ��ȡʱ��
	time_t GetTime(void) const;
	// ����ʱ��
	void SetTime(time_t value);
	// ��ȡ�ص�
	int GetLocation(void) const;
	// ���õص�
	void SetLocation(int value);
	// ������Idѹ��ջ������Ѵ��������
	void SectionPushBack(int id);
	// ��ȡ�������Ļ���Id
	const std::vector<int> *GetPassSection(void) const;
	// ��ȡ��ɶ�
	float Complete(void) const;
	// �������Ŀ��浵
	void DeepCopy(c_GameSave *target) const;

private:
	int m_id; // �浵Id
	int m_savePoint; // ��¼��
	time_t m_time; // �浵ʱ��
	int m_location; // �ص�
	std::vector<int> m_passSection; // �������Ļ���Id
};

#endif	/* _Empress___c_GameSave_H_ */