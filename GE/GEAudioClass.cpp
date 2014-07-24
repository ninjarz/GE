#include "GEAudioClass.h"

namespace GE
{
	AudioClass *g_audioClass;

	//-----------------------------------------------------------------------
	bool AudioClass::Initialize()
	{
		HRESULT hr;

		CoInitializeEx( NULL, COINIT_MULTITHREADED );

		if( FAILED( hr = XAudio2Create(&m_XAudio2, 0) ) )
		{
			MessageBox(NULL, L"Create XAudio2 failed!", L"ERROR",MB_OK);
			CoUninitialize();
			return 0;
		}

		if( FAILED( hr = m_XAudio2->CreateMasteringVoice(&m_masteringVoice) ) )
		{
			MessageBox(NULL, L"Create mastering voice failed!", L"ERROR",MB_OK);
			SAFE_RELEASE(m_XAudio2);
			CoUninitialize();
			return 0;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	void AudioClass::Shutdown()
	{
		m_masteringVoice->DestroyVoice();
		SAFE_RELEASE( m_XAudio2 );
		CoUninitialize();
	}

	//-----------------------------------------------------------------------
	bool AudioClass::LoadWaveFile(LPWSTR fileName, WaveFile& wave)
	{
		HRESULT hr;
		HMMIO hmmio;
		if( NULL == ( hmmio = mmioOpen( fileName, NULL, MMIO_ALLOCBUF | MMIO_READ ) ) )
			return false;
		MMCKINFO ckRiff;
		if( ( 0 != mmioDescend( hmmio, &ckRiff, NULL, 0 ) ) )
		{
			mmioClose( hmmio, 0 );
			return false;
		}
		if( ( ckRiff.ckid != FOURCC_RIFF ) || ( ckRiff.fccType != mmioFOURCC( 'W', 'A', 'V', 'E' ) ) )
		{
			mmioClose( hmmio, 0 );
			return false;
		}
		MMCKINFO ckIn;
		ckIn.ckid = mmioFOURCC( 'f', 'm', 't', ' ' );
		if( 0 != mmioDescend( hmmio, &ckIn, &ckRiff, MMIO_FINDCHUNK ) )
		{
			mmioClose( hmmio, 0 );
			return false;
		}
		if( ckIn.cksize < ( LONG )sizeof( PCMWAVEFORMAT ) )
		{
			mmioClose( hmmio, 0 );
			return false;
		}
		PCMWAVEFORMAT pcmWaveFormat;
		if( sizeof( pcmWaveFormat ) != mmioRead( hmmio, ( HPSTR )&pcmWaveFormat, sizeof( pcmWaveFormat ) ) )
		{
			mmioClose( hmmio, 0 );
			return false;
		}
		WAVEFORMATEX *waveFormat;
		if( pcmWaveFormat.wf.wFormatTag == WAVE_FORMAT_PCM )
		{
			waveFormat = ( WAVEFORMATEX* )new CHAR[ sizeof( WAVEFORMATEX ) ];
			if( NULL == waveFormat )
			{
				mmioClose( hmmio, 0 );
				return false;
			}
			memcpy( waveFormat, &pcmWaveFormat, sizeof( pcmWaveFormat ) );
			waveFormat->cbSize = 0;
		}
		else
		{
			WORD cbExtraBytes = 0L;
			if( sizeof( WORD ) != mmioRead( hmmio, ( CHAR* )&cbExtraBytes, sizeof( WORD ) ) )
			{
				mmioClose( hmmio, 0 );
				return false;
			}

			waveFormat = ( WAVEFORMATEX* )new CHAR[ sizeof( WAVEFORMATEX ) + cbExtraBytes ];
			if( NULL == waveFormat )
			{
				mmioClose( hmmio, 0 );
				return false;
			}

			memcpy( waveFormat, &pcmWaveFormat, sizeof( pcmWaveFormat ) );
			waveFormat->cbSize = cbExtraBytes;

			if( 0 != mmioRead( hmmio, ( CHAR* )( ( ( BYTE* )&( waveFormat->cbSize ) ) + sizeof( WORD ) ),cbExtraBytes ) )
			{
				delete waveFormat;
				waveFormat = NULL;
				{
					mmioClose( hmmio, 0 );
					return false;
				}
			}
		}
		if( -1 == mmioSeek( hmmio, ckRiff.dwDataOffset + sizeof( FOURCC ), SEEK_SET ) )
			return false;
		MMCKINFO m_ck;
		m_ck.ckid = mmioFOURCC( 'd', 'a', 't', 'a' );
		if( 0 != mmioDescend( hmmio, &m_ck, &ckRiff, MMIO_FINDCHUNK ) )
			return false;
		//º«µ√ Õ∑≈
		BYTE *waveData = new BYTE[ m_ck.cksize ];
		MMIOINFO mmioinfoIn; 
		if( 0 != mmioGetInfo( hmmio, &mmioinfoIn, 0 ) )
			return false;
		for( DWORD cT = 0; cT < m_ck.cksize; cT++ )
		{
			if( mmioinfoIn.pchNext == mmioinfoIn.pchEndRead )
			{
				if( 0 != mmioAdvance( hmmio, &mmioinfoIn, MMIO_READ ) )
					return false;

				if( mmioinfoIn.pchNext == mmioinfoIn.pchEndRead )
					return false;
			}
			*( ( BYTE* )waveData + cT ) = *( ( BYTE* )mmioinfoIn.pchNext );
			mmioinfoIn.pchNext++;
		}

		if( 0 != mmioSetInfo( hmmio, &mmioinfoIn, 0 ) )
			return false;

		if( wave.sourceVoice )
			wave.sourceVoice->DestroyVoice();
		if( FAILED( hr = m_XAudio2->CreateSourceVoice(&wave.sourceVoice, waveFormat) ) )
			return false;

		SAFE_DELETE_ARRAY(wave.buffer.pAudioData);
		ZeroMemory(&wave.buffer, sizeof(wave.buffer));
		wave.buffer.pAudioData = waveData;
		wave.buffer.Flags = XAUDIO2_END_OF_STREAM;
		wave.buffer.AudioBytes = m_ck.cksize;

		if( FAILED( hr = wave.sourceVoice->SubmitSourceBuffer( &wave.buffer ) ) )
		{
			wave.sourceVoice->DestroyVoice();
			if(waveData)
			{
				SAFE_DELETE_ARRAY(wave.buffer.pAudioData);
			}
			return false;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	bool AudioClass::PlayWave(WaveFile& wave)
	{
		if( FAILED(wave.sourceVoice->Start(0)) )
			return false;
		return true;
	}

	//-----------------------------------------------------------------------
	bool GELoadWaveFile(LPWSTR fileName, WaveFile& wave) { return g_audioClass->LoadWaveFile(fileName, wave); }

	//-----------------------------------------------------------------------
	bool GEPlayWave(WaveFile& wave) { return g_audioClass->PlayWave(wave); }

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
}