//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// TitleScreen 标题屏幕
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_TitleScreen_H_
#define _Empress___c_TitleScreen_H_

#include "c_GameScreen.h"

// 标题屏幕
class c_TitleScreen : public c_GameScreen
{
public:
	// 构造函数
	c_TitleScreen(void);
	// 析构函数
	virtual ~c_TitleScreen(void);
	// 加载
	virtual void LoadContent(void);
	// 卸载
	virtual void UnloadContent(void);
	// 输入
	virtual void HandleInput(void);
	// 绘制
	virtual void Draw(float fElapsedTime);

private:
	NNN::Texture::c_Texture * m_textureTitle; // 标题纹理
	NNN::Geometry::Rect::c_RectOrtho *m_rectTitle; // 标题位置
	RECT m_startPosition; // 开始位置
	RECT m_settingsPosition; // 设置位置
};

#endif	/* _Empress___c_TitleScreen_H_ */