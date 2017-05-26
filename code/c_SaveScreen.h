//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// SaveScreen 存档屏幕
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_SaveScreen_H_
#define _Empress___c_SaveScreen_H_

#include "c_GameScreen.h"

// 存档屏幕
class c_SaveScreen : public c_GameScreen
{
public:
	// 构造函数
	c_SaveScreen(bool saveEnable);
	// 析构函数
	virtual ~c_SaveScreen(void);
	// 加载
	virtual void LoadContent(void);
	// 卸载
	virtual void UnloadContent(void);
	// 输入
	virtual void HandleInput(void);
	// 绘制
	virtual void Draw(float fElapsedTime);
	
private:
	// 重新加载存档
	void ReloadSave(void);

	NNN::Texture::c_Texture *m_textureBack; // 返回纹理
	NNN::Texture::c_Texture *m_textureSettings; // 设置纹理
	NNN::Texture::c_Texture *m_textureAdd; // 新建纹理
	NNN::Texture::c_Texture *m_textureSave; // 存档纹理
	NNN::Texture::c_Texture *m_textureLoad; // 读档纹理
	NNN::Texture::c_Texture *m_textureCopy; // 复制纹理
	NNN::Texture::c_Texture *m_textureDelete; // 删除纹理

	NNN::Geometry::Rect::c_RectOrtho *m_rectBackground; // 背景（黑色全屏）位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectSelected; // 选择项位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectBar; // 顶部栏位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectBack; // 返回位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectSettings; // 设置位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectAdd; // 新建位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectSave; // 存档位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectLoad; // 读档位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectCopy; // 复制位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectDelete; // 删除位置

	RECT m_backPosition; // 后退位置
	RECT m_settingsPosition; // 设置位置
	RECT m_addPosition; // 新建位置
	RECT m_savePosition; // 存档位置
	RECT m_loadPosition; // 读档位置
	RECT m_copyPosition; // 复制位置
	RECT m_deletePosition; // 删除位置
	RECT m_panPosition; // 可平移的位置

	std::vector<NNN::Geometry::Rect::c_RectOrtho*> m_rectPhotoList; // 位置缓存
	std::vector<WCHAR*> m_textureNameList; // 纹理名称缓存
	std::vector<WCHAR*> m_completeList; // 完成度缓存
	std::vector<WCHAR*> m_timeList; // 时间缓存

	bool m_saveEnable; // 是否允许存档（允许存档说明已正在进行游戏，否则为刚从标题画面开始）
	unsigned m_saveCount; // 存档数
	int m_col; // 列数
	int m_offsetY; // 参照点纵坐标
	int m_selectedIndex; // 选择项索引
};

#endif	/* _Empress___c_SaveScreen_H_ */