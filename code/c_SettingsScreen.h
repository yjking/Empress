//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// SettingsScreen 设置屏幕
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_SettingsScreen_H_
#define _Empress___c_SettingsScreen_H_

#include "c_GameScreen.h"

// 设置屏幕
class c_SettingsScreen : public c_GameScreen
{
public:
	// 构造函数
	c_SettingsScreen(bool saveEnable);
	// 析构函数
	virtual ~c_SettingsScreen(void);
	// 加载
	virtual void LoadContent(void);
	// 卸载
	virtual void UnloadContent(void);
	// 输入
	virtual void HandleInput(void);
	// 绘制
	virtual void Draw(float fElapsedTime);

private:
	// 重新加载音量
	void ReloadVolume(void);
	// 重新加载语言位置
	void ReloadLang(void);

	NNN::Texture::c_Texture *m_textureBack; // 返回纹理
	NNN::Texture::c_Texture *m_textureSave; // 保存纹理
	NNN::Texture::c_Texture *m_textureSoundEnable; // 声音启用纹理
	NNN::Texture::c_Texture *m_textureSoundDisable; // 声音禁用纹理
	NNN::Texture::c_Texture *m_textureVolumeIncrease; // 音量增加纹理
	NNN::Texture::c_Texture *m_textureVolumeDecrease; // 音量减小纹理

	NNN::Geometry::Rect::c_RectOrtho *m_rectBackground; // 背景（白色全屏）位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectBack; // 返回位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectSave; // 保存位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectSoundEnable; // 声音启用位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectSoundDisable; // 声音禁用位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectVolumeIncrease; // 音量增加位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectVolumeDecrease; // 音量减小位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectLine; // 一条线位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectLang; // 语言位置

	RECT m_clientPosition; // 客户端位置
	RECT m_backPosition; // 返回位置
	RECT m_savePosition; // 保存位置
	RECT m_soundPosition; // 声音位置
	RECT m_volumePosition; // 音量位置
	RECT m_volumeIncreasePosition; // 音量增加按钮位置
	RECT m_volumeDecreasePosition; // 音量减小按钮位置
	RECT m_langPosition; // 语言位置
	RECT m_zhcnPosition; // 简体中文位置
	RECT m_zhhkPosition; // 香港繁体位置
	RECT m_enusPosition; // 英文位置
	RECT m_jajpPosition; // 日文位置
	RECT m_currentPosition; // 当前语言位置

	bool m_saveEnable; // 是否可以切换到存档屏幕
	bool m_firstFill; // 是否初次填充
	WCHAR *m_volume; // 音量
};

#endif	/* _Empress___c_SettingsScreen_H_ */