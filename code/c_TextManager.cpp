//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// TextManager 文本管理
//--------------------------------------------------------------------------------------

#include "c_TextManager.h"
#include "c_GameSession.h"


NNN::Font::c_Font2D *c_TextManager::m_font = nullptr; // 字体
std::vector<std::wstring> c_TextManager::m_vector; // 文本的向量


c_TextManager::c_TextManager(void)
{
	m_font = nullptr;
}


c_TextManager::~c_TextManager(void)
{

}


void c_TextManager::LoadContent(void)
{
	NNN::Font::Add_CustomFont_ft(L"Data/msyh.ttf");
	NNN::Font::Add_Font2D(L"msyh", NNN::Font::Find_CustomFont(L"Data/msyh.ttf"), 22);
	m_font = NNN::Font::Find_Font2D(L"msyh");

	UpdateTextTable();
}


void c_TextManager::UnloadContent(void)
{
	m_font = nullptr;
}


void c_TextManager::UpdateTextTable(void)
{
	WCHAR *filename = nullptr;
	UINT content_len = 0;
	std::vector<std::wstring> lines;
	std::vector< std::pair<std::wstring, std::wstring> > results;
	m_vector.clear();

	switch (c_GameSession::GetSingleton()->GetLang())
	{
	case ec_LANG::zh_TW:
		filename = L"Data/zh_TW.txt";
		break;
	case ec_LANG::en_US:
		filename = L"Data/en_US.txt";
		break;
	case ec_LANG::ja_JP:
		filename = L"Data/ja_JP.txt";
		break;
	case ec_LANG::zh_CN:
		filename = L"Data/zh_CN.txt";
		break;
	case ec_LANG::zh_HK:
		filename = L"Data/zh_HK.txt";
		break;
	default:
		break;
	}
	
	BYTE *config_file_content = NNN::Packet::LoadFileContent(filename, &content_len);
	if (config_file_content == nullptr)
	{
		return;
	}

	NNN::IO::File::ReadAllLines(config_file_content, content_len, lines);
	NNN::Packet::UnloadFileContent(filename);
	NNN::Config::Read_Config(lines, results);

	for(std::vector< std::pair<std::wstring, std::wstring> >::const_iterator iter = results.begin(); iter != results.end(); ++iter)
	{
		m_vector.push_back((*iter).second);
	}
}


const WCHAR *c_TextManager::GetText(int index)
{
	return m_vector[index].c_str();
}


HRESULT c_TextManager::DrawString(const WCHAR *text,
								  D3DCOLOR color, float z, DWORD format,
								  LPRECT pRect, int txt_len, int add_line_spacing)
{
	return m_font->Draw_Text(text, color, z, false, format, pRect, txt_len, add_line_spacing);
}


HRESULT c_TextManager::DrawString(int index,
								  D3DCOLOR color, float z, DWORD format,
								  LPRECT pRect, int txt_len, int add_line_spacing)
{
	return m_font->Draw_Text(GetText(index), color, z, false, format, pRect, txt_len, add_line_spacing);
}