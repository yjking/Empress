//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// EndScreen 结束屏幕
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_EndScreen_H_
#define _Empress___c_EndScreen_H_

#include "c_GameScreen.h"

// 结束屏幕
class c_EndScreen : public c_GameScreen
{
public:
	// 构造函数
	c_EndScreen(void);
	// 析构函数
	virtual ~c_EndScreen(void);
	// 加载
	virtual void LoadContent(void);
	// 卸载
	virtual void UnloadContent(void);
	// 输入
	virtual void HandleInput(void);
	// 绘制
	virtual void Draw(float fElapsedTime);

private:
	NNN::Texture::c_Texture * m_textureQHua; // Q版小华纹理
	NNN::Geometry::Rect::c_RectOrtho *m_rectQHua; // Q版小华位置

	RECT m_staffPosition; // 人员名单位置
	RECT m_clientPosition; // 客户端位置
	std::wstring m_result; // 人员名单
	const WCHAR *m_staff; // 人员名单
	float m_totalTime; // 经历的总时间
};

#endif	/* _Empress___c_EndScreen_H_ */