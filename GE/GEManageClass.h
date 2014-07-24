#pragma once
#ifndef _GEMANAGECLASS_H_
#define _GEMANAGECLASS_H_

#define SAFE_RELEASE(x)      { if(x) { (x)->Release(); (x)=NULL; } }
#define SAFE_DELETE(x)       { if(x) { delete (x);     (x)=NULL; } }
#define SAFE_DELETE_ARRAY(x) { if(x) { delete[] (x);   (x)=NULL; } }

#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")

#include <Windows.h>
#include <d3d11.h>

#include "GEmath.h"

//-----------------------------------------------------------------------
namespace GE
{
	struct GEDesc
	{
		LPCWSTR     applicationName;  //窗口名称  
		bool        isFullScreen;     //是否全屏
		int         width;            //窗口宽度
		int         height;           //窗口高度
		bool        isSSAA;           //是开启抗锯齿
		bool        isVsync;          //是否垂直同步
	};

	class GEClass
	{
	public:
		inline GEClass()
		{
		}

		inline GEClass(const GEClass&)
		{
		}

		inline ~GEClass()
		{
			Shutdown();
		}

		bool Initialize(const GEDesc&); 
		void Shutdown();

		bool SetApplicationName(LPCWSTR para)       { m_applicationName = para;  return true;};
		bool SetIsFullScreen(bool para)             { m_isFullScreen = para;     return true;};
		bool SetWidth(int para)                     { m_width = para;            return true;};
		bool SetHeight(int para)                    { m_height = para;           return true;};
		bool SetIsSSAA(bool para)                   { m_isSSAA = para;           return true;};
		bool SetIsVsync(bool para)                  { m_isVsync = para;          return true;};
		bool SetScreenNear(float para)              { m_screenNear = para;       return true;};
		bool SetScreenDeep(float para)              { m_screenDeep = para;       return true;};
		bool SetHInstance(HINSTANCE para)           { m_hInstance = para;        return true;};
		bool SetHWnd(HWND para)                     { m_hWnd = para;             return true;};
		bool SetDevice(ID3D11Device* para)                       { m_device = para;             return true;};
		bool SetDeviceeContext(ID3D11DeviceContext* para)        { m_deviceContext = para;      return true;};

		inline LPCWSTR      GetApplicationName()             const { return  m_applicationName; };
		inline bool         GetIsFullScreen()                const { return  m_isFullScreen;    };
		inline int          GetWidth()                       const { return  m_width;           };
		inline int          GetHeight()                      const { return  m_height;          };
		inline bool         GetIsSSAA()                      const { return  m_isSSAA;          };
		inline bool         GetIsVsync()                     const { return  m_isVsync;         };
		inline float        GetScreenNear()                  const { return  m_screenNear;      };
		inline float        GetScreenDeep()                  const { return  m_screenDeep;      };
		inline HINSTANCE    GetHInstance()                   const { return  m_hInstance;       };
		inline HWND         GetHWnd()                        const { return  m_hWnd;            };
		inline RECT         GetRect()                        const { return  m_rect;            };
		inline INT2         GetInsideCentre()                const { return  m_insideCentre;    };
		inline INT2         GetOutsideCentre()               const { return  m_outsideCentre;   };
		inline ID3D11Device*          GetDevice()            const { return  m_device;          };
		inline ID3D11DeviceContext*   GetDeviceContext()     const { return  m_deviceContext;   };

	protected:
		static LPCWSTR     m_applicationName;
		static bool        m_isFullScreen;
		static int         m_width;
		static int         m_height;
		static bool        m_isSSAA;
		static bool        m_isVsync;
		static float       m_screenNear;
		static float       m_screenDeep;
		static HINSTANCE   m_hInstance;
		static HWND        m_hWnd;
		static RECT        m_rect;
		static INT2        m_insideCentre;
		static INT2        m_outsideCentre;
		static ID3D11Device          *m_device;
		static ID3D11DeviceContext   *m_deviceContext;
		static int m_videoCardMemory;
		static char m_videoCardDescription[128];
		static UINT m_x4MultiQuality;
		static IDXGISwapChain          *m_swapChain;
		static ID3D11Texture2D         *m_depthStencilBuffer;
		static ID3D11RenderTargetView  *m_renderTargetView;
		static ID3D11DepthStencilView  *m_depthStencilView;
	};

	extern GEClass *g_GEClass;

	bool GEInitialize(const GEDesc&);
	void GEShutdown();

	LPCWSTR GEGetApplicationName();
	bool GEGetIsFullScreen();
	int GEGetWidth();
	int GEGetHeight();
	bool GEGetIsSSAA();
	bool GEGetIsVsync();
	float GEGetScreenNear();
	float GEGetScreenDeep();
	HINSTANCE GEGetHInstance();
	HWND GEGetHWnd();
	RECT GEGetRect();
	INT2 GEGetInsideCentre();
	INT2 GEGetOutsideCentre();
	ID3D11Device* GEGetDevice();
	ID3D11DeviceContext* GEGetDeviceContext();
}

#endif