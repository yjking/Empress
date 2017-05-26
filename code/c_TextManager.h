//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// TextManager 文本管理
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_TextManager_H_
#define _Empress___c_TextManager_H_

#include "../../../Src/nnnEngine/nnn.h"

// 区域性名称和标识符(Locale ID)
enum class ec_LANG
{
	zh_TW = 0x0404, // 台湾正体
	en_US = 0x0409, // 美国英文
	ja_JP = 0x0411, // 日本日文
	zh_CN = 0x0804, // 简体中文
	zh_HK = 0x0C04, // 香港繁体
};

// 文本管理
class c_TextManager
{
public:
	// 构造函数
	c_TextManager(void);
	// 析构函数
	~c_TextManager(void);
	// 加载
	static void LoadContent(void);
	// 卸载
	static void UnloadContent(void);
	// 更新文本列表（在切换语言后需要调用该方法进行刷新）
	static void UpdateTextTable(void);
	// 根据索引获取文本
	static const WCHAR *GetText(int index);
	// 绘制文字，参数为文本
	static HRESULT DrawString(const WCHAR *text,
							  D3DCOLOR color = 0xff000000, float z = 0.0f, DWORD format = DT_LEFT | DT_TOP | DT_NOCLIP,
							  LPRECT pRect = nullptr, int txt_len = -1, int add_line_spacing = 0);
	// 绘制文字，参数为文本索引
	static HRESULT DrawString(int index,
							  D3DCOLOR color = 0xff000000, float z = 0.0f, DWORD format = DT_LEFT | DT_TOP | DT_NOCLIP,
							  LPRECT pRect = nullptr, int txt_len = -1, int add_line_spacing = 0);

private:
	static NNN::Font::c_Font2D *m_font; // 字体
	static std::vector<std::wstring> m_vector; // 文本的向量
};

#endif	/* _Empress___c_TextManager_H_ */