//--------------------------------------------------------------------------------------
// 拜见女皇陛下同人动画游戏社
// AudioManager 音频管理
//--------------------------------------------------------------------------------------

#include "c_AudioManager.h"


WCHAR *c_AudioManager::m_bgm = nullptr; // 背景音乐名称缓存


void c_AudioManager::LoadContent(void)
{

}


void c_AudioManager::UnloadContent(void)
{
	ReleaseBgm();
}


void c_AudioManager::PlayBgm(const char *filename, double startTime, double endTime)
{
	WCHAR *wchar1 = nullptr;
	NNN::Text::char2wchar(filename, &wchar1);
	if (!NNN::Sound::isPlaying(wchar1))
	{
		ReleaseBgm();
		
		NNN::Text::char2wchar(filename, &m_bgm);
		WCHAR txt[128] = { 0 };
#if (NNN_PLATFORM == NNN_PLATFORM_WIN32) || (NNN_PLATFORM == NNN_PLATFORM_WP8)
		swprintf_s(txt, L"Data/%s.ogg", m_bgm);
#else
		std::wstring str_txt = L"Data/";
		str_txt += m_bgm;
		str_txt += L".ogg";
		CopyMemory(txt, str_txt.c_str(), (str_txt.size() + 1) * sizeof(WCHAR));
#endif	// NNN_PLATFORM_WIN32 || NNN_PLATFORM_WP8
		NNN::Sound::Add(m_bgm, txt);
		NNN::Sound::Play(m_bgm, true);
		if (startTime > 0 && endTime > 0)
		{
			NNN::Sound::Find(m_bgm)->SetLoopTime(startTime, endTime);
		}
	}
	SAFE_DELETE_ARRAY(wchar1);
}


void c_AudioManager::ReleaseBgm(void)
{
	if (m_bgm != nullptr)
	{
		NNN::Sound::Stop(m_bgm);
		NNN::Sound::Release(m_bgm);
		SAFE_DELETE_ARRAY(m_bgm);
	}
}