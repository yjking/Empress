//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// EndScreen 结束屏幕
//--------------------------------------------------------------------------------------

#include "c_EndScreen.h"
#include "c_InputManager.h"
#include "c_TextManager.h"
#include "c_GameSession.h"


c_EndScreen::c_EndScreen()
{
	m_textureQHua = nullptr;
	m_rectQHua = nullptr;

	m_staff = nullptr;
	m_totalTime = 0;
}


c_EndScreen::~c_EndScreen()
{

}


void c_EndScreen::LoadContent(void)
{
	NNN::Texture::Add(L"QHua", L"Data/QHua.png");
	m_textureQHua = NNN::Texture::Find(L"QHua");
	
	LONG width = NNN::Misc::GetClientWidth();
	LONG height = NNN::Misc::GetClientHeight();
	UINT imageWidth = m_textureQHua->GetImageWidth();
	UINT imageHeight = m_textureQHua->GetImageHeight();

	m_rectQHua = new NNN::Geometry::Rect::c_RectOrtho();
	m_rectQHua->GetSamplerState()->SetFilter(D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT);
	double rate = (height - 200.0) / imageHeight;
	POINT point = make_point(width - imageWidth * rate - 30, (LONG)(height - imageHeight * rate) >> 1);
	m_rectQHua->SetRect(make_rect(point.x, point.x + imageWidth * rate, point.y, point.y + imageHeight * rate));
	m_rectQHua->SetTexture(m_textureQHua);
	
	m_staffPosition = make_rect(30, width - imageWidth * rate - 30, height, height + 1);
	m_clientPosition = make_rect(0, width, 0, height);

	UINT content_len = 0;
	BYTE *config_file_content = NNN::Packet::LoadFileContent(L"Data/Staff.txt", &content_len);
	if (config_file_content == nullptr)
	{
		return;
	}
	NNN::IO::File::ReadAllText(config_file_content, content_len, m_result);
	NNN::Packet::UnloadFileContent(L"Data/Staff.txt");
	m_staff = m_result.c_str();
}


void c_EndScreen::UnloadContent(void)
{
	SAFE_DELETE(m_rectQHua);

	NNN::Texture::Release(L"QHua");
	m_textureQHua = nullptr;

	m_staff = nullptr;	
}


void c_EndScreen::HandleInput(void)
{
	if (c_InputManager::Tap(&m_clientPosition) || m_totalTime > 283)
	{
		ExitScreen();
	}
}


void c_EndScreen::Draw(float fElapsedTime)
{
	m_rectQHua->OnRender(fElapsedTime);

	m_totalTime += fElapsedTime;
	RECT staffPosition = m_staffPosition;
	staffPosition.top -= m_totalTime * 30;
	c_TextManager::DrawString(m_staff, 0xffffffff, 0, DT_LEFT | DT_TOP, &staffPosition);
}