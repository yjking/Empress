//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// ScreenManager 屏幕管理
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_ScreenManager_H_
#define _Empress___c_ScreenManager_H_

#include "c_GameScreen.h"

// 屏幕管理
class c_ScreenManager
{
public:
	// 构造函数
	c_ScreenManager(void);
	// 析构函数
	~c_ScreenManager(void);
	// 更新
	void Update(float fElapsedTime);
	// 绘制
	void Draw(float fElapsedTime) const;

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	HRESULT OnReset_dx9(void);
	HRESULT OnLost_dx9(void);
#endif	// NNN_PLATFORM_WIN32

	// 增加屏幕
	void AddScreen(c_GameScreen *screen);
	// 移除屏幕
	void RemoveScreen(c_GameScreen *screen);
	// 释放屏幕
	void ReleaseScreens(void);

private:
	std::vector<c_GameScreen*> m_screens; // 屏幕栈
	std::vector<c_GameScreen*> m_screensToUpdate; // 准备进行更新的屏幕栈
	std::vector<c_GameScreen*> m_screensToRelease; // 准备进行释放的屏幕栈
};

#endif	/* _Empress___c_ScreenManager_H_ */