//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// GameSession 游戏会话
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_GameSession_H_
#define _Empress___c_GameSession_H_

#include "c_AudioManager.h"
#include "c_InputManager.h"
#include "c_ScreenManager.h"
#include "c_TextManager.h"
#include "c_GameSave.h"
#include "c_MainScreen.h"

// 游戏会话
class c_GameSession
{
public:
	// 析构函数
	~c_GameSession(void);
	// 获取单例
	static c_GameSession *GetSingleton(void);
	// 获取屏幕
	c_ScreenManager *GetScreenManager(void) const;
	// 获取主屏幕
	c_MainScreen *GetMainScreen(void);
	// 获取是否处于活动状态
	bool GetIsActive(void) const;
	// 设置是否处于活动状态
	void SetIsActive(bool value);
	// 获取当前语言
	ec_LANG GetLang(void) const;
	// 设置当前语言
	void SetLang(ec_LANG value);
	// 获取当前是否启用声音
	bool GetSoundEnable(void) const;
	// 设置当前是否启用声音
	void SetSoundEnable(bool value);
	// 获取当前音量
	int GetVolume(void) const;
	// 设置当前音量
	void SetVolume(int value);
	// 获取剧本Xml
	TiXmlDocument *GetScriptXml(void) const;
	// 获取地图Xml
	TiXmlDocument *GetMapXml(void) const;
	// 获取当前存档
	c_GameSave *GetCurrentSave(void) const;
	// 设置当前存档
	void SetCurrentSave(c_GameSave *value);
	// 获取所有存档
	const std::vector<c_GameSave*> *GetSavings(void) const;
	// 清楚指定Index的存档
	void SaveErase(int index);
	// 把存档压入栈
	void SavePushBack(c_GameSave* value);
	// 保存存档到文件
	void SaveRecord(void) const;
	// 查找最大存档Id
	int FindMaxSaveId(void) const;
	// 加载
	void LoadContent(void);
	// 卸载
	void UnloadContent(void);
	// 更新
	void Update(float fElapsedTime) const;
	// 绘制
	void Draw(float fElapsedTime) const;

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	HRESULT OnReset_dx9(void);
	HRESULT OnLost_dx9(void);
#endif	// NNN_PLATFORM_WIN32

private:
	// 构造函数
	c_GameSession(void);

	c_ScreenManager *m_screenManager; // 屏幕管理
	c_MainScreen *m_mainScreen; // 主屏幕
	bool m_isActive; // 是否处于活动状态中（窗口是否失焦）
	ec_LANG m_lang; // 当前语言
	bool m_soundEnable; // 当前是否启用音频
	int m_volume; // 当前音量
	TiXmlDocument *m_recordXml; // 记录Xml
	TiXmlDocument *m_scriptXml; // 剧本Xml
	TiXmlDocument *m_mapXml; // 地图Xml
	c_GameSave *m_currentSave; // 当前存档
	std::vector<c_GameSave*> m_savings; // 所有存档
	char *m_recordPath; //存档路径
};

#endif	/* _Empress___c_GameSession_H_ */