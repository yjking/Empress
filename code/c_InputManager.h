//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// InputManager 输入管理
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_InputManager_H_
#define _Empress___c_InputManager_H_

#include "../../../Src/nnnEngine/nnn.h"

// 输入管理
class c_InputManager
{
public:
	// 构造函数
	c_InputManager(void);
	// 析构函数
	~c_InputManager(void);
	// 加载
	static void LoadContent(void);
	// 卸载
	static void UnloadContent(void);
	// 更新
	static void Update(float fElapsedTime);
	// 绘制
	static void Draw(float fElapsedTime);

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	static HRESULT OnReset_dx9(void);
	static HRESULT OnLost_dx9(void);
#endif	// NNN_PLATFORM_WIN32

	// 为了与鼠标统一，使用单触点的手势
	// 轻击
	static bool Tap(RECT *rect);
	// 按下
	static bool Press(RECT *rect);
	// 移动
	static bool Pan(RECT *rect, POINT *delta);

private:
	static NNN::Sprite::Scene::c_Scene *m_scene; // 场景
	static NNN::Sprite::Scene::c_SpriteInst *m_spriteTouchWave; // 波纹
	static float m_totalTime; // 波纹动画经历的总时间
	static std::vector<POINT> m_touchPoints; // 触点位置
	static int m_preTouchesCount; // 上一帧的触点数目
};

#endif	/* _Empress___c_InputManager_H_ */