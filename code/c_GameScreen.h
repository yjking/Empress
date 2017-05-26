//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// GameScreen 游戏屏幕（抽象基类）
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_GameScreen_H_
#define _Empress___c_GameScreen_H_

#include "../../../Src/nnnEngine/nnn.h"

// 屏幕状态
enum class ec_ScreenState
{
	TransitionOn, // 屏幕渐入
    Active, // 屏幕正在活动
    TransitionOff, // 屏幕渐出
    Hidden, // 屏幕正在隐藏
};

// 游戏屏幕（抽象基类）
class c_GameScreen
{
public:
	// 构造函数
	c_GameScreen(void);
	// 析构函数
	virtual ~c_GameScreen(void);
	// 获取是否弹出类型
	bool GetIsPopup(void) const;
	// 获取渐入时间
	float GetTransitionOnTime(void) const;
	// 获取渐出时间
	float GetTransitionOffTime(void) const;
	// 获取渐变位置（0到1闭区间）
	float GetTransitionPosition(void) const;
	// 获取渐变位置（255到0闭区间）
	int GetTransitionAlpha(void) const;
	// 获取屏幕状态
	ec_ScreenState GetScreenState(void) const;
	// 获取是否正在退出
	bool GetIsExiting(void) const;
	// 设置是否正在退出
	void SetIsExiting(bool value);
	// 正在退出时执行的函数（指针）
	void (*Exiting)(c_GameScreen *obj);
	// 获取是否正在活动
	bool GetIsActive(void) const;
	// 加载
	virtual void LoadContent(void) = 0;
	// 卸载
	virtual void UnloadContent(void) = 0;
	// 更新
	virtual void Update(float fElapsedTime, bool otherScreenHasFocus, bool coveredByOtherScreen);
	// 输入
	virtual void HandleInput(void) = 0;
	// 绘制
	virtual void Draw(float fElapsedTime) = 0;

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	HRESULT OnReset_dx9(void);
	HRESULT OnLost_dx9(void);
#endif	// NNN_PLATFORM_WIN32

	// 退出该屏幕
	void ExitScreen(void);

protected:
	// 设置是否弹出类型
	void SetIsPopup(bool value);
	// 设置渐入时间
	void SetTransitionOnTime(float value);
	// 设置渐出时间
	void SetTransitionOffTime(float value);
	// 设置渐变位置（0到1闭区间）
	void SetTransitionPosition(float value);
	// 设置屏幕状态
	void SetScreenState(ec_ScreenState value);
	// 场景
	NNN::Sprite::Scene::c_Scene *m_scene;

private:
	bool m_isPopup; // 是否弹出类型
	float m_transitionOnTime; // 渐入时间
	float m_transitionOffTime; // 渐出时间
	float m_transitionPosition; // 渐变位置（0到1闭区间）
	ec_ScreenState m_screenState; // 屏幕状态
	bool m_isExiting; // 是否正在退出
	bool m_otherScreenHasFocus; // 是否焦点在其它窗口（仅Windows平台）
	bool UpdateTransition(float fElapsedTime, float time, int direction); // 更新渐变
};

#endif	/* _Empress___c_GameScreen_H_ */