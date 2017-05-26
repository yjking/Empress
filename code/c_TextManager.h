//--------------------------------------------------------------------------------------
// �ݼ�Ů�ʱ���ͬ�˶�����Ϸ��
// TextManager �ı�����
//--------------------------------------------------------------------------------------

#pragma once
#ifndef _Empress___c_TextManager_H_
#define _Empress___c_TextManager_H_

#include "../../../Src/nnnEngine/nnn.h"

// ���������ƺͱ�ʶ��(Locale ID)
enum class ec_LANG
{
	zh_TW = 0x0404, // ̨������
	en_US = 0x0409, // ����Ӣ��
	ja_JP = 0x0411, // �ձ�����
	zh_CN = 0x0804, // ��������
	zh_HK = 0x0C04, // ��۷���
};

// �ı�����
class c_TextManager
{
public:
	// ���캯��
	c_TextManager(void);
	// ��������
	~c_TextManager(void);
	// ����
	static void LoadContent(void);
	// ж��
	static void UnloadContent(void);
	// �����ı��б����л����Ժ���Ҫ���ø÷�������ˢ�£�
	static void UpdateTextTable(void);
	// ����������ȡ�ı�
	static const WCHAR *GetText(int index);
	// �������֣�����Ϊ�ı�
	static HRESULT DrawString(const WCHAR *text,
							  D3DCOLOR color = 0xff000000, float z = 0.0f, DWORD format = DT_LEFT | DT_TOP | DT_NOCLIP,
							  LPRECT pRect = nullptr, int txt_len = -1, int add_line_spacing = 0);
	// �������֣�����Ϊ�ı�����
	static HRESULT DrawString(int index,
							  D3DCOLOR color = 0xff000000, float z = 0.0f, DWORD format = DT_LEFT | DT_TOP | DT_NOCLIP,
							  LPRECT pRect = nullptr, int txt_len = -1, int add_line_spacing = 0);

private:
	static NNN::Font::c_Font2D *m_font; // ����
	static std::vector<std::wstring> m_vector; // �ı�������
};

#endif	/* _Empress___c_TextManager_H_ */