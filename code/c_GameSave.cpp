//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// GameSave 游戏存档
//--------------------------------------------------------------------------------------

#include "c_GameSave.h"


c_GameSave::c_GameSave(void)
{
	m_id = -1;
	m_savePoint = 0;
	m_time = 0;
	m_location = 0;
}


c_GameSave::c_GameSave(int id, int savePoint, time_t time, int location)
{
	m_id = id;
	m_savePoint = savePoint;
	m_time = time;
	m_location = location;
}


c_GameSave::~c_GameSave(void)
{

}


int c_GameSave::GetId(void) const
{
	return m_id;
}


void c_GameSave::SetId(int value)
{
	m_id = value;
}


int c_GameSave::GetSavePoint(void) const
{
	return m_savePoint;
}


void c_GameSave::SetSavePoint(int value)
{
	m_savePoint = value;
}


time_t c_GameSave::GetTime(void) const
{
	return m_time;	
}


void c_GameSave::SetTime(time_t value)
{
	m_time = value;
}


int c_GameSave::GetLocation(void) const
{
	return m_location;
}


void c_GameSave::SetLocation(int value)
{
	m_location = value;
}


void c_GameSave::SectionPushBack(int id)
{
	bool isExist = false;
	for (std::vector<int>::iterator iter = m_passSection.begin(); iter != m_passSection.end(); ++iter)
	{
		if ((*iter) == id)
		{
			isExist = true;
		}
	}
	if (!isExist)
	{
		m_passSection.push_back(id);
	}
}


const std::vector<int> *c_GameSave::GetPassSection(void) const
{
	return &m_passSection;
}


float c_GameSave::Complete(void) const
{
	return m_passSection.size() * 0.1;
}


void c_GameSave::DeepCopy(c_GameSave *target) const
{
	target->m_id = m_id;
	target->m_savePoint = m_savePoint;
	target->m_time = m_time;
	target->m_location = m_location;
	target->m_passSection.clear();
	
	for (std::vector<int>::const_iterator iter = m_passSection.begin(); iter != m_passSection.end(); ++iter)
	{
		target->m_passSection.push_back(*iter);
	}
}