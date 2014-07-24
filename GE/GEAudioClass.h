#pragma once
#ifndef _GEAUDIOCLASS_H_
#define _GEAUDIOCLASS_H_

#pragma comment(lib,"Winmm.lib")

#include <C:\Program Files (x86)\Microsoft DirectX SDK (June 2010)\Include\xaudio2.h>
//#include <mmsystem.h>
#include "GEManageClass.h"

namespace GE
{
	struct WaveFile
	{
		IXAudio2SourceVoice *sourceVoice;
		XAUDIO2_BUFFER buffer;

		inline WaveFile() { sourceVoice = NULL; ZeroMemory(&buffer, sizeof(buffer)); }
		inline ~WaveFile() { if(sourceVoice) sourceVoice->DestroyVoice(); SAFE_DELETE_ARRAY(buffer.pAudioData); }
	};

	class AudioClass : public GEClass
	{
	public:
		inline AudioClass()
		{
		}

		inline AudioClass(const AudioClass&)
		{
		}

		inline ~AudioClass()
		{
			Shutdown();
		}

		bool Initialize();
		void Shutdown();

		bool LoadWaveFile(LPWSTR fileName, WaveFile& wave);
		bool PlayWave(WaveFile& wave);

	private:
		IXAudio2 *m_XAudio2;
		IXAudio2MasteringVoice *m_masteringVoice;

	};

	extern AudioClass *g_audioClass;

	bool GELoadWaveFile(LPWSTR fileName, WaveFile& wave);
	bool GEPlayWave(WaveFile& wave);
}

#endif