//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// HistoryScreen 历史记录屏幕
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_HistoryScreen_H_
#define _Empress___c_HistoryScreen_H_

#include "c_GameScreen.h"

// 历史记录屏幕
class c_HistoryScreen : public c_GameScreen
{
public:
	// 构造函数
	c_HistoryScreen(const WCHAR *text);
	// 析构函数
	virtual ~c_HistoryScreen(void);
	// 加载
	virtual void LoadContent(void);
	// 卸载
	virtual void UnloadContent(void);
	// 输入
	virtual void HandleInput(void);
	// 绘制
	virtual void Draw(float fElapsedTime);

private:
	NNN::Texture::c_Texture * m_textureRaise; // 收起点纹理
	NNN::Geometry::Rect::c_RectOrtho *m_rectBackground; // 背景（黑色全屏）位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectRaise; // 收起点位置

	RECT m_clientPosition; // 客户端位置
	RECT m_textPosition; // 历史记录位置
	RECT m_backPosition; // 返回位置
	const WCHAR *m_text; // 历史记录
	bool m_firstFill; // 是否初次填充
};

#endif	/* _Empress___c_HistoryScreen_H_ */