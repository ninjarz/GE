#include "GEManageClass.h"

#include <time.h> 
#include "GESystemClass.h"
#include "GEInputClass.h"
#include "GETimerClass.h"
#include "GED3DClass.h"
#include "GEAudioClass.h"
#include "GECameraClass.h"
#include "GEShader.h"
#include "GEShaderState.h"
#include "GEParticleClass.h"
#include "GEFontClass.h"

namespace GE
{
	GEClass *g_GEClass;

	LPCWSTR GEClass::m_applicationName;
	bool GEClass::m_isFullScreen;
	int GEClass::m_width;
	int GEClass::m_height;
	bool GEClass::m_isSSAA;
	bool GEClass::m_isVsync;
	float GEClass::m_screenNear;
	float GEClass::m_screenDeep;
	HINSTANCE GEClass::m_hInstance;
	HWND GEClass::m_hWnd;
	RECT GEClass::m_rect;
	INT2 GEClass::m_insideCentre;
	INT2 GEClass::m_outsideCentre;
	ID3D11Device* GEClass::m_device;
	ID3D11DeviceContext* GEClass::m_deviceContext;
	int GEClass::m_videoCardMemory;
	char GEClass::m_videoCardDescription[128];
	UINT GEClass::m_x4MultiQuality;
	IDXGISwapChain* GEClass::m_swapChain;
	ID3D11Texture2D* GEClass::m_depthStencilBuffer;
	ID3D11RenderTargetView* GEClass::m_renderTargetView;
	ID3D11DepthStencilView* GEClass::m_depthStencilView;

	//-----------------------------------------------------------------------
	bool GEClass::Initialize(const GEDesc& desc)
	{
		m_applicationName = desc.applicationName;
		m_isFullScreen = desc.isFullScreen;
		m_width = desc.width;
		m_height = desc.height;
		m_isSSAA = desc.isSSAA;
		m_isVsync = desc.isVsync;

		return true;
	}

	//-----------------------------------------------------------------------
	void GEClass::Shutdown()
	{
	}

	//-----------------------------------------------------------------------
	bool GEInitialize(const GEDesc& desc)
	{
		srand((unsigned)time(NULL));

		g_GEClass = new GEClass;
		if (!g_GEClass->Initialize(desc))
			return false;

		g_systemClass = new SystemClass;
		if (!g_systemClass->Initialize())
			return false;

		g_inputClass = new InputClass;
		if (!g_inputClass->Initialize())
			return false;

		g_timerClass = new TimerClass;
		if (!g_timerClass->Initialize())
			return false;

		g_D3DClass = new D3DClass;
		if (!g_D3DClass->Initialize())
			return false;

		g_audioClass = new AudioClass;
		if (!g_audioClass->Initialize())
			return false;

		g_cameraClass = new CameraClass;
		if (!g_cameraClass->Initialize())
			return false;

		g_shaderClass = new ShaderClass;
		if (!g_shaderClass->Initialize())
			return false;

		g_shaderStateClass = new ShaderStateClass;
		if (!g_shaderStateClass->Initialize())
			return false;

		g_particleClass = new ParticleClass;
		if (!g_particleClass->Initialize())
			return false;

		g_fontClass = new FontClass;
		if (!g_fontClass->Initialize())
			return false;

		return true;
	}

	//-----------------------------------------------------------------------
	void GEShutdown()
	{
	}

	//-----------------------------------------------------------------------
	LPCWSTR GEGetApplicationName() { return g_GEClass->GetApplicationName(); }

	//-----------------------------------------------------------------------
	bool GEGetIsFullScreen() { return g_GEClass->GetIsFullScreen(); }

	//-----------------------------------------------------------------------
	int GEGetWidth() { return g_GEClass->GetWidth(); }

	//-----------------------------------------------------------------------
	int GEGetHeight() { return g_GEClass->GetHeight(); }

	//-----------------------------------------------------------------------
	bool GEGetIsSSAA() { return g_GEClass->GetIsSSAA(); }

	//-----------------------------------------------------------------------
	bool GEGetIsVsync() { return g_GEClass->GetIsVsync(); }

	//-----------------------------------------------------------------------
	float GEGetScreenNear() { return g_GEClass->GetScreenNear(); }

	//-----------------------------------------------------------------------
	float GEGetScreenDeep() { return g_GEClass->GetScreenDeep(); }

	//-----------------------------------------------------------------------
	HINSTANCE GEGetHInstance() { return g_GEClass->GetHInstance(); }

	//-----------------------------------------------------------------------
	HWND GEGetHWnd() { return g_GEClass->GetHWnd(); }

	//-----------------------------------------------------------------------
	RECT GEGetRect() { return g_GEClass->GetRect(); }

	//-----------------------------------------------------------------------
	INT2 GEGetInsideCentre() { return g_GEClass->GetInsideCentre(); }

	//-----------------------------------------------------------------------
	INT2 GEGetOutsideCentre() { return g_GEClass->GetOutsideCentre(); }

	//-----------------------------------------------------------------------
	ID3D11Device* GEGetDevice() { return g_GEClass->GetDevice(); }

	//-----------------------------------------------------------------------
	ID3D11DeviceContext* GEGetDeviceContext() { return g_GEClass->GetDeviceContext(); }
}