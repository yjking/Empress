//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// AudioManager 音频管理
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_AudioManager_H_
#define _Empress___c_AudioManager_H_

#include "../../../Src/nnnEngine/nnn.h"

// 音频管理
class c_AudioManager
{
public:
	// 构造函数
	c_AudioManager(void);
	// 析构函数
	~c_AudioManager(void);
	// 加载（暂时不做任何操作）
	static void LoadContent(void);
	// 卸载
	static void UnloadContent(void);
	// 播放指定背景音乐（如果已经在播放，则不处理；如果未加入缓存，则加入）
	static void PlayBgm(const char *filename, double startTime = 0, double endTime = 0);
	// 释放背景音乐
	static void ReleaseBgm(void);

private:
	static WCHAR *m_bgm; // 背景音乐名称缓存
};

#endif	/* _Empress___c_AudioManager_H_ */