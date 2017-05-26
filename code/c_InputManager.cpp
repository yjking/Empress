//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// InputManager 输入管理
//--------------------------------------------------------------------------------------

#include "c_InputManager.h"


NNN::Sprite::Scene::c_Scene *c_InputManager::m_scene = nullptr; // 场景
NNN::Sprite::Scene::c_SpriteInst *c_InputManager::m_spriteTouchWave = nullptr; // 波纹
float c_InputManager::m_totalTime = -1; // 波纹动画经历的总时间
std::vector<POINT> c_InputManager::m_touchPoints; // 触点位置
int c_InputManager::m_preTouchesCount = 0; // 上一帧的触点数目


void c_InputManager::LoadContent(void)
{
	m_scene = new NNN::Sprite::Scene::c_Scene();
	m_scene->Init();
	m_scene->GetSamplerState()->SetFilter(D3D11_FILTER_MIN_MAG_LINEAR_MIP_POINT);
	m_spriteTouchWave = NNN::Sprite::create_new_SprInst(L"TouchWave", L"Data/TouchWaveSpr.txt", L"Data/TouchWaveAct.txt");
	m_spriteTouchWave->SetAction(0);
	m_scene->GetRootInst()->AddChild(m_spriteTouchWave);
}


void c_InputManager::UnloadContent(void)
{
	SAFE_DELETE(m_scene);

	m_touchPoints.clear();
}


void c_InputManager::Update(float fElapsedTime)
{
	if (m_totalTime > -1)
	{
		m_totalTime += fElapsedTime;
	}

	if (m_totalTime > 0.25f)
	{
		m_totalTime = -1;
		m_spriteTouchWave->Stop();
	}

	if (NNN::Input::Mouse::wasMouseButtonPressed(0) ||
		(m_preTouchesCount == 0 &&
		NNN::Input::MultiTouch::GetTouchesCount() == 1))
	{
		m_touchPoints.clear();
	}
	
	if (NNN::Input::Mouse::isMouseButtonDown(0))
	{
		m_touchPoints.push_back(make_point(NNN::Input::Mouse::MouseX(), NNN::Input::Mouse::MouseY()));
	}
	else if (NNN::Input::MultiTouch::GetTouchesCount() == 1)
	{
		m_touchPoints.push_back(NNN::Input::MultiTouch::GetData(0)->m_point);
	}
	
	RECT rect = make_rect(0, NNN::Misc::GetClientWidth(), 0, NNN::Misc::GetClientHeight()); 
	if (Tap(&rect))
	{
		m_totalTime = 0;
		m_spriteTouchWave->SetPosition(m_touchPoints[m_touchPoints.size() - 1]);
		m_spriteTouchWave->Stop();
		m_spriteTouchWave->Play();
	}

	m_preTouchesCount = NNN::Input::MultiTouch::GetTouchesCount();

	m_scene->OnFrameMove(fElapsedTime);
}


void c_InputManager::Draw(float fElapsedTime)
{
	if (m_totalTime > -1)
	{
		m_scene->OnRender(fElapsedTime);
	}
}


#if (NNN_PLATFORM == NNN_PLATFORM_WIN32)
HRESULT c_InputManager::OnReset_dx9(void)
{
	return m_scene->OnReset_dx9();
}


HRESULT c_InputManager::OnLost_dx9(void)
{
	return m_scene->OnLost_dx9();
}
#endif	// NNN_PLATFORM_WIN32


bool c_InputManager::Tap(RECT *rect)
{
	bool isTap = false;

	if (NNN::Input::Mouse::wasMouseButtonReleased(0) ||
		(m_preTouchesCount > 0 &&
		NNN::Input::MultiTouch::GetTouchesCount() == 0))
	{
		isTap = m_touchPoints.size() > 0;

		for (std::vector<POINT>::const_iterator iter = m_touchPoints.begin(); iter != m_touchPoints.end(); ++iter)
		{
			if (!PtInRect(rect, (*iter)))
			{
				isTap = false;
				break;
			}
		}
	}
	
	return isTap;
}


bool c_InputManager::Press(RECT *rect)
{
	POINT point = make_point(-1, -1);

	if (NNN::Input::Mouse::isMouseButtonDown(0))
	{
		point = make_point(NNN::Input::Mouse::MouseX(), NNN::Input::Mouse::MouseY());
	}
	else if (NNN::Input::MultiTouch::GetTouchesCount() == 1)
	{
		point = NNN::Input::MultiTouch::GetData(0)->m_point;
	}

	return PtInRect(rect, point) == 1;
}


bool c_InputManager::Pan(RECT *rect, POINT *delta)
{
	bool isPan = false;

	if (m_touchPoints.size() > 1)
	{
		isPan = true;
		for (std::vector<POINT>::const_iterator iter = m_touchPoints.begin(); iter != m_touchPoints.end(); ++iter)
		{
			if (!PtInRect(rect, (*iter)))
			{
				isPan = false;
				break;
			}
		}

		if (isPan)
		{
			POINT last = m_touchPoints[m_touchPoints.size() - 2];
			POINT now = m_touchPoints[m_touchPoints.size() - 1];
			delta->x = now.x - last.x;
			delta->y = now.y - last.y;

			isPan = delta->x > 0 || delta->y > 0;
		}
	}

	return isPan;
}
