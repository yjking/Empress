//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// GameSave 游戏存档
//--------------------------------------------------------------------------------------

#include <time.h>
#include <vector>

#pragma once
#ifndef _Empress___c_GameSave_H_
#define _Empress___c_GameSave_H_

// 游戏存档
class c_GameSave
{
public:
	// 构造函数
	c_GameSave(void);
	// 构造函数（工厂）
	c_GameSave(int id, int savePoint, time_t time, int location);
	// 析构函数
	~c_GameSave(void);
	// 获取Id
	int GetId(void) const;
	// 设置Id
	void SetId(int value);
	// 获取记录点
	int GetSavePoint(void) const;
	// 设置记录点
	void SetSavePoint(int value);
	// 获取时间
	time_t GetTime(void) const;
	// 设置时间
	void SetTime(time_t value);
	// 获取地点
	int GetLocation(void) const;
	// 设置地点
	void SetLocation(int value);
	// 将环节Id压入栈，如果已存在则不添加
	void SectionPushBack(int id);
	// 获取经历过的环节Id
	const std::vector<int> *GetPassSection(void) const;
	// 获取完成度
	float Complete(void) const;
	// 深拷贝，到目标存档
	void DeepCopy(c_GameSave *target) const;

private:
	int m_id; // 存档Id
	int m_savePoint; // 记录点
	time_t m_time; // 存档时间
	int m_location; // 地点
	std::vector<int> m_passSection; // 经历过的环节Id
};

#endif	/* _Empress___c_GameSave_H_ */