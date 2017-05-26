//--------------------------------------------------------------------------------------
// Copyright (c) No Need Name Dev Teams
// https://www.nnn-team.com/
//
// Desc : 拜见女皇陛下游戏主文件
//--------------------------------------------------------------------------------------

#include "Empress.h"
#include "c_GameSession.h"


/*==============================================================
 * 通用渲染函数
 * Render()
 *==============================================================*/
HRESULT Render(double /*fTime*/, float fElapsedTime, void* /*pUserContext*/)
{
	// Clear render target and the depth stencil
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };

	NNN::Device::DeviceContext::ClearRenderTargetView(ClearColor);
	NNN::Device::DeviceContext::ClearDepthStencilView(D3D11_CLEAR_DEPTH, 1.0f, 0);

	c_GameSession::GetSingleton()->Draw(fElapsedTime);

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	static WCHAR s_title_txt[100] = { 0 };

	WCHAR title_txt[100];
	swprintf_s(title_txt, L"%s [ %s ]", c_TextManager::GetText(1), NNN::DXUTGetFrameStats(true));
	if (wcscmp(s_title_txt, title_txt))
	{
		swprintf_s(s_title_txt, L"%s", title_txt);
		SetWindowText(NNN::DXUTGetHWND(), title_txt);
	}
#endif	// NNN_PLATFORM_WIN32

	return S_OK;
}


/*==============================================================
 * 初始化函数
 * OnCreate_func()
 *==============================================================*/
void OnCreate_func(void* /*pUserContext*/)
{
	// TODO: 初始化代码
	c_GameSession::GetSingleton()->LoadContent();

	// 重置计时器
	NNN::Misc::ResetTimer();
}


/*==============================================================
 * 清理函数
 * OnDestroy_func()
 *==============================================================*/
void OnDestroy_func(void* /*pUserContext*/)
{
	c_GameSession::GetSingleton()->UnloadContent();
}


#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
/*==============================================================
 * OnReset_dx9()	- Reset
 * OnLost_dx9()		- Lost
 *==============================================================*/
HRESULT OnReset_dx9(IDirect3DDevice9* /*pd3dDevice*/, const D3DSURFACE_DESC* /*pBackBufferSurfaceDesc*/, void* /*pUserContext*/)
{
	c_GameSession::GetSingleton()->OnReset_dx9();
	return S_OK;
}
//--------------------------------------------------
void OnLost_dx9(void* /*pUserContext*/)
{
	c_GameSession::GetSingleton()->OnLost_dx9();
}
#endif	// NNN_PLATFORM_WIN32


/*==============================================================
 * 改变分辨率大小
 * ChangeSize()
 *==============================================================*/
void ChangeSize(UINT /*width*/, UINT /*height*/)
{
}


/*==============================================================
 * 处理按键
 * OnKeyboard()
 *
 *		nChar		- 按键（例如：'A'、'a'、VK_LEFT、VK_RIGHT）
 *		bKeyDown	- 是否 WM_KEYDOWN 或 WM_SYSKEYDOWN
 *		bAltDown	- Alt 是否按下
 *==============================================================*/
void CALLBACK OnKeyboard( UINT /*nChar*/, bool /*bKeyDown*/, bool /*bAltDown*/, void* /*pUserContext*/ )
{
}


/*==============================================================
 * 处理鼠标/单触点
 * OnMouse()
 *==============================================================*/
void CALLBACK OnMouse(	bool /*bLeftButtonDown*/, bool /*bRightButtonDown*/, bool /*bMiddleButtonDown*/,
						bool /*bSideButton1Down*/, bool /*bSideButton2Down*/, int /*nMouseWheelDelta*/,
						int /*xPos*/, int /*yPos*/, void* /*pUserContext*/ )
{
}


/*==============================================================
 * 处理多触点
 * OnMultiTouch()
 *==============================================================*/
void CALLBACK OnMultiTouch(	struct NNN::Input::MultiTouch::s_TouchPoint* /*touches*/, int /*touches_count*/,
							NNN::Input::es_InputMessageType /*msg*/, POINT /*point*/, UINT /*touch_id*/,
							void* /*pUserContext*/ )
{
}


/*==============================================================
 * 处理旋转屏幕
 * OnRotation()
 *==============================================================*/
void CALLBACK OnRotation(	NNN::Input::Rotation::es_Rotation /*rotation*/,
							NNN::Input::Rotation::es_Rotation /*last_rotation*/,
							void* /*pUserContext*/ )
{
}


/*==============================================================
 * 处理加速度计
 * OnAccelerometer()
 *==============================================================*/
void CALLBACK OnAccelerometer( double /*x*/, double /*y*/, double /*z*/, void* /*pUserContext*/ )
{
}


/*==============================================================
 * 处理方向感应器
 * OnOrientation()
 *==============================================================*/
void CALLBACK OnOrientation( float /*x*/, float /*y*/, float /*z*/, void* /*pUserContext*/ )
{
}


/*==============================================================
 * 处理陀螺测试仪
 * OnGyrometer()
 *==============================================================*/
void CALLBACK OnGyrometer(	double /*AngularVelocityX*/, double /*AngularVelocityY*/, double /*AngularVelocityZ*/,
							void* /*pUserContext*/ )
{
}


/*==============================================================
 * 处理测斜仪
 * OnInclinometer()
 *==============================================================*/
void CALLBACK OnInclinometer( float /*PitchDegrees*/, float /*RollDegrees*/, float /*YawDegrees*/, void* /*pUserContext*/ )
{
}


/*==============================================================
 * 处理地磁仪
 * OnMagnetometer()
 *==============================================================*/
void CALLBACK OnMagnetometer( float /*x*/, float /*y*/, float /*z*/, void* /*pUserContext*/ )
{
}


/*==============================================================
 * 处理指南针
 * OnCompass()
 *==============================================================*/
void CALLBACK OnCompass( double /*MagneticNorth*/, double /*TrueNorth*/, void* /*pUserContext*/ )
{
}


#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
/*==============================================================
 * 处理应用程序的消息处理
 * MsgProc()
 *==============================================================*/
LRESULT CALLBACK MsgProc(	HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM /*lParam*/,
							bool *pbNoFurtherProcessing, void* /*pUserContext*/ )
{
	if (uMsg == WM_CLOSE)
	{
		*pbNoFurtherProcessing = true;
		if (MessageBox(hWnd, c_TextManager::GetText(4), c_TextManager::GetText(1), 1) == 1)
		{
			NNN::ExitMainloop();
		}
	}
	else if (uMsg == WM_ACTIVATEAPP)
	{
		c_GameSession::GetSingleton()->SetIsActive(wParam == 1);
	}
	return 0;
}
#endif	// NNN_PLATFORM_WIN32


#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
/*==============================================================
 * 在 D3D9 或 D3D11 设备创建之前，修改设备的设置
 * ModifyDeviceSettings()
 *==============================================================*/
bool CALLBACK ModifyDeviceSettings( NNN::DXUTDeviceSettings* pDeviceSettings, void* /*pUserContext*/ )
{
	UNREFERENCED_PARAMETER(pDeviceSettings);

	// Uncomment this to get debug information from D3D11
	//pDeviceSettings->d3d11.CreateFlags |= D3D11_CREATE_DEVICE_DEBUG;

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)

	// 开启垂直同步。当进入全屏时，强制更改分辨率
	if (NNN::DXUT_D3D11_DEVICE == pDeviceSettings->ver)
	{
		if (!pDeviceSettings->d3d11.sd.Windowed)
		{
			pDeviceSettings->d3d11.sd.BufferDesc.Width = 1280;
			pDeviceSettings->d3d11.sd.BufferDesc.Height = 720;
		}
		pDeviceSettings->d3d11.SyncInterval = 1;
	}
	else if (NNN::DXUT_D3D9_DEVICE == pDeviceSettings->ver)
	{
		if (!pDeviceSettings->d3d9.pp.Windowed)
		{
			pDeviceSettings->d3d9.pp.BackBufferWidth = 1280;
			pDeviceSettings->d3d9.pp.BackBufferHeight = 720;
		}
		pDeviceSettings->d3d9.pp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;
	}

	// For the first device created if its a REF device, optionally display a warning dialog box
	static bool s_bFirstTime = true;
	if( s_bFirstTime )
	{
		s_bFirstTime = false;
		if( ( NNN::DXUT_D3D11_DEVICE == pDeviceSettings->ver &&
			pDeviceSettings->d3d11.DriverType == D3D_DRIVER_TYPE_REFERENCE ) )
		{
			NNN::Optional::DXUTDisplaySwitchingToREFWarning( pDeviceSettings->ver );
		}
	}
#endif	// NNN_PLATFORM_WIN32

	return true;
}


/*==============================================================
 * 当设备被移除时调用。返回 true 时，表示找到一个新设备；false 表示退出
 * OnDeviceRemoved()
 *==============================================================*/
bool CALLBACK OnDeviceRemoved( void* /*pUserContext*/ )
{
	return true;
}
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8


/*==============================================================
 * 处理场景更新。无论使用哪种图形 API，也会调用这个函数。
 * OnFrameMove()
 *==============================================================*/
void CALLBACK OnFrameMove( double /*fTime*/, float fElapsedTime, void* /*pUserContext*/ )
{
	c_GameSession::GetSingleton()->Update(fElapsedTime);
}


/*==============================================================
 * 入口点调用的函数
 * main_func()
 *==============================================================*/
void CALLBACK main_func()
{
	NNN::Init::Step1::DoInit(
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
		NNN::es_GraphAPI::DX9,
#elif (NNN_PLATFORM == NNN_PLATFORM_WP8)
		NNN::es_GraphAPI::DX11,
#else
		NNN::es_GraphAPI::OpenGL,
#endif	// NNN_PLATFORM_WIN32
		nullptr);

#if (NNN_PLATFORM == NNN_PLATFORM_ANDROID)
#if defined(DEBUG) || defined(_DEBUG)
	NNN::Platform::Android::Add_ShowDebugInfoFlag(NNN::Platform::Android::es_DebugInfo::Pointer);
#endif	// DEBUG || _DEBUG
#endif	// NNN_PLATFORM_ANDROID

	// 加载数据包
#if (NNN_PLATFORM == NNN_PLATFORM_ANDROID)
	WCHAR sdcard_path[MAX_PATH] = {0};
	NNN::Text::char2wchar(NNN::Platform::Android::get_sdcard_path(), sdcard_path, _countof(sdcard_path));
#endif	// NNN_PLATFORM_ANDROID

	WCHAR *dir_list[] =
	{
		L"",
		L"Files/",
		L"../Files/",
		L"../../Files/",
		L"../../../Files/",
		L"../../../../Files/",
#if (NNN_PLATFORM == NNN_PLATFORM_ANDROID)
		L"/",
		sdcard_path,
#elif (NNN_PLATFORM == NNN_PLATFORM_IOS)
		L"../Documents/",
#elif (NNN_PLATFORM == NNN_PLATFORM_WP8)
		L"/",
#endif	// NNN_PLATFORM
	};

	WCHAR *file_list[] =
	{
		L"nnnEngine.whp",
		L"Empress.whp",
	};

	std::vector<std::wstring> packet_list;
	for(int dir_idx=0; dir_idx<_countof(dir_list); ++dir_idx)
	{
		for(int file_idx=0; file_idx<_countof(file_list); ++file_idx)
		{
			std::wstring file = dir_list[dir_idx];
			file += file_list[file_idx];

			packet_list.push_back(file);
		}
	}
	NNN::Init::Step2::LoadCustomPacket(&packet_list);

	// 设置回调函数
	NNN::Init::Step2::FrameMove(OnFrameMove);

	NNN::Init::Step2::Keyboard(OnKeyboard);
	NNN::Init::Step2::Mouse(OnMouse);
	NNN::Init::Step2::MultiTouch(OnMultiTouch);
	NNN::Init::Step2::Rotation(OnRotation);
	NNN::Init::Step2::Accelerometer(OnAccelerometer);
	NNN::Init::Step2::Orientation(OnOrientation);
	NNN::Init::Step2::Gyrometer(OnGyrometer);
	NNN::Init::Step2::Inclinometer(OnInclinometer);
	NNN::Init::Step2::Magnetometer(OnMagnetometer);
	NNN::Init::Step2::Compass(OnCompass);

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	NNN::Init::Step2::MsgProc(MsgProc);
#endif	// NNN_PLATFORM_WIN32
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
	NNN::Init::Step2::DeviceChanging(ModifyDeviceSettings);
	NNN::Init::Step2::DeviceRemoved(OnDeviceRemoved);

	// DX11 回调
	NNN::Init::Step2::D3D11DeviceAcceptable(IsD3D11DeviceAcceptable);
	NNN::Init::Step2::D3D11DeviceCreated(OnD3D11CreateDevice);
	NNN::Init::Step2::D3D11SwapChainResized(OnD3D11ResizedSwapChain);
	NNN::Init::Step2::D3D11FrameRender(OnD3D11FrameRender);
	NNN::Init::Step2::D3D11SwapChainReleasing(OnD3D11ReleasingSwapChain);
	NNN::Init::Step2::D3D11DeviceDestroyed(OnD3D11DestroyDevice);
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	// DX9 回调
	NNN::Init::Step2::D3D9DeviceAcceptable(IsD3D9DeviceAcceptable);
	NNN::Init::Step2::D3D9DeviceCreated(OnD3D9CreateDevice);
	NNN::Init::Step2::D3D9DeviceReset(OnD3D9ResetDevice);
	NNN::Init::Step2::D3D9FrameRender(OnD3D9FrameRender);
	NNN::Init::Step2::D3D9DeviceLost(OnD3D9LostDevice);
	NNN::Init::Step2::D3D9DeviceDestroyed(OnD3D9DestroyDevice);
#endif	// NNN_PLATFORM_WIN32

#if (NNN_PLATFORM != NNN_PLATFORM_WP8)
	// OpenGL 回调
	NNN::Init::Step2::OpenglInit(OpenGL_Init);
	NNN::Init::Step2::OpenglFinal(OpenGL_Final);
	NNN::Init::Step2::OpenglChangeSize(OpenGL_ChangeSize);
	NNN::Init::Step2::OpenglFrameRender(OpenGL_OnFrameRender);
#endif	// !NNN_PLATFORM_WP8

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	NNN::Init::Step2::SetCursorSettings(true, true);
	NNN::Init::Step2::SetHotkeyHandling();
#endif	// NNN_PLATFORM_WIN32
	NNN::Init::Step2::Create_Window();

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	HWND winhand = NNN::DXUTGetHWND();
	LONG winstyle = GetWindowLong(winhand, GWL_STYLE);
	winstyle &= ~WS_MAXIMIZEBOX; // 最大化
	winstyle &= ~WS_THICKFRAME;  // 改变窗口大小
	SetWindowLong(winhand, GWL_STYLE, winstyle);
#endif	// NNN_PLATFORM_WIN32

	NNN::Init::Step3::CreateDevice(1280, 720);

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	NNN::es_GraphAPI graph_api = NNN::GetGraphAPI();
	if (graph_api == NNN::es_GraphAPI::OpenGL)
	{
		// 开启垂直同步
		NNN::OpenGL::c_OpenGL_Device *pDevice = NNN::OpenGL::GetDevice();
		wglSwapIntervalEXT(1);
		pDevice->Setinterval(1);
	}
#endif	// NNN_PLATFORM_WIN32

	NNN::Init::Step4::MainLoop();	// Enter into the DXUT render loop
}


/*==============================================================
 * Win32 入口点
 * WinMain()
 *==============================================================*/
#if (NNN_PLATFORM != NNN_PLATFORM_WIN32)
NNN_INIT_FUNC(main_func);
#else
int WINAPI WinMain( HINSTANCE /*hInstance*/, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int /*nCmdShow*/ )
{
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
	// 设置 dump 文件（程序崩溃后记录一些调试信息）
	NNN::Misc::SetDumpFile(L"Empress.dmp");
#endif	// NNN_PLATFORM_WIN32

#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
	// 内存泄漏检测
	NNN::Misc::MemoryLeakCheck();
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8

	main_func();

	return NNN::DXUTGetExitCode();
}
#endif	// !NNN_PLATFORM_WIN32
