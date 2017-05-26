//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// MainScreen 主屏幕
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_MainScreen_H_
#define _Empress___c_MainScreen_H_

#include "../../../3rdParty/TinyXML/xml.h"
#include "c_GameScreen.h"

// 对话框状态
enum class ec_DialogueBoxState
{
	Lay, // 对话框躺着
	RollUp, // 对话框向上展开
	Hang, // 对话框高挂着
	RollDown, // 对话框向下收起
};

// 主屏幕
class c_MainScreen : public c_GameScreen
{
public:
	// 构造函数
	c_MainScreen(void);
	// 析构函数
	virtual ~c_MainScreen(void);
	// 加载
	virtual void LoadContent(void);
	// 卸载
	virtual void UnloadContent(void);
	// 输入
	virtual void HandleInput(void);
	// 更新
	virtual void Update(float fElapsedTime, bool otherScreenHasFocus, bool coveredByOtherScreen);
	// 绘制
	virtual void Draw(float fElapsedTime);
	// 重置。当读档时，需要对主屏幕进行复位
	void Reset(void);

private:
	// 清除缓存
	void CacheClear(void);
	// 安全地访问下一个节点。避免nullptr
	void SafeNextSibling(void);

	NNN::Texture::c_Texture *m_textureBackground; // 背景纹理
	NNN::Texture::c_Texture *m_texturePerson[5]; // 人物纹理
	NNN::Texture::c_Texture *m_textureNameBar; // 名称栏纹理
	NNN::Texture::c_Texture *m_textureMusicOn; // 音乐启用纹理
	NNN::Texture::c_Texture *m_textureMusicOff; // 音乐禁用纹理
	NNN::Texture::c_Texture *m_textureRedStrap; // 时间地点纹理
	NNN::Texture::c_Texture *m_textureSoftDisk; // 软盘纹理

	NNN::Geometry::Rect::c_RectOrtho *m_rectBackground; // 背景位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectPerson[5]; // 人物位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectNameBar; // 名称栏位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectLine; // 一条线位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectDialogueBox; // 对话框位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectMusicOn; // 音乐启用位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectMusicOff; // 音乐禁用位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectTime; // 时间位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectLocation; // 地点位置
	NNN::Geometry::Rect::c_RectOrtho *m_rectSoftDisk; // 软盘位置
	
	RECT m_nameBarPosition; // 名称栏位置
	RECT m_nameBasePosition; // 名称基准位置
	RECT m_nameShadowPosition; // 名称阴影位置
	RECT m_dialogueBoxPosition; // 对话框位置
	RECT m_dialogueBasePosition; // 对话文字基准位置
	RECT m_dialogueShadowPosition; // 对话文字阴影位置
	RECT m_musicPosition; // 音符位置
	RECT m_bgmPosition; // 背景音乐名称位置
	RECT m_timeTextPosition; // 时间位置
	RECT m_locationTextPosition; // 地点位置
	RECT m_softDiskPosition; // 软盘位置
	RECT m_personPosition[5]; // 人物位置
	RECT m_optionPosition[3]; // 选项位置
	RECT m_clientPosition; // 客户端位置
	RECT m_panPosition; // 可平移的位置

	std::vector<WCHAR*> m_textureNameList; // 纹理名称缓存
	TiXmlElement *m_nodeReader; // 节点读取器
	bool m_isReading; // 是否正在读取
	bool m_isSavePoint; // 是否处于记录点
	float m_timeElapsed; // 时间动画经历时间
	float m_locationElapsed; // 地点动画经历时间
	int m_bgmId; // 背景音乐名称Id
	int m_timeId; // 时间Id
	int m_currentLocation; // 当前地点Id
	int m_nameId; // 名称Id
	int m_dialogueId; // 对话Id
	int m_dialogueBoxRoll; // 对话框卷展数值
	int m_optionText[3]; // 选项文本Id
	int m_optionSection[3]; // 选项将跳跃到的环节Id
	ec_DialogueBoxState m_dialogueBoxState; // 对话框状态
	std::wstring m_history; // 历史记录
};

#endif	/* _Empress___c_MainScreen_H_ */