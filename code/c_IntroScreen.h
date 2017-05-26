//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// IntroScreen 入场屏幕
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_IntroScreen_H_
#define _Empress___c_IntroScreen_H_

#include "c_GameScreen.h"

// 入场屏幕
class c_IntroScreen : public c_GameScreen
{
public:
	// 构造函数
	c_IntroScreen(void);
	// 析构函数
	virtual ~c_IntroScreen(void);
	// 加载
	virtual void LoadContent(void);
	// 卸载
	virtual void UnloadContent(void);
	// 输入
	virtual void HandleInput(void);
	// 绘制
	virtual void Draw(float fElapsedTime);

private:
	NNN::Texture::c_Texture * m_textureNewGameLogo; // 新游社标志纹理
	NNN::Geometry::Rect::c_RectOrtho *m_rectNewGameLogo; // 新游社标志位置

	RECT m_zcloudPosition; // ZCloud位置
	RECT m_clientPosition; // 客户端位置
	float m_totalTime; // 经历的总时间
};

#endif	/* _Empress___c_IntroScreen_H_ */