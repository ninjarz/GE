#include "GESystemClass.h"

#include "GEInputClass.h"

namespace GE
{
	SystemClass* g_systemClass;

	//-----------------------------------------------------------------------
	SystemClass::SystemClass()
	{
	}

	//-----------------------------------------------------------------------
	SystemClass::SystemClass(const SystemClass&)
	{
	}

	//-----------------------------------------------------------------------
	SystemClass::~SystemClass()
	{
	}

	//-----------------------------------------------------------------------
	bool SystemClass::Initialize()
	{
		m_hInstance = GetModuleHandle(NULL);
		InitWindows();
		return true;
	}

	//-----------------------------------------------------------------------
	void SystemClass::Shutdown()
	{
		ShutdownWindows();
	}

	//-----------------------------------------------------------------------
	void SystemClass::InitWindows()
	{
		WNDCLASSEX wc;
		wc.cbSize         = sizeof(WNDCLASSEXW);                         //窗口类的大小
		wc.style          = CS_HREDRAW | CS_VREDRAW | CS_OWNDC ;         //窗口的风格
		wc.lpfnWndProc    = WndProc;                                     //指向处理函数的指针，WndProc函数用于处理系统消息
		wc.cbClsExtra     = 0;                                           //紧跟窗口类结构后的附加字节数
		wc.cbWndExtra     = 0;                                           //紧跟窗口实例后的附加字节数
		wc.hInstance      = m_hInstance;                                 //本模块的实例句柄
		wc.hIcon          = LoadIcon(NULL, IDI_WINLOGO);                 //图标的句柄
		wc.hCursor        = LoadCursor(NULL, IDC_ARROW);                 //光标的句柄
		wc.hbrBackground  = (HBRUSH)GetStockObject(WHITE_BRUSH);         //背景画刷的句柄
		wc.lpszMenuName   = NULL;                                        //指向菜单的指针
		wc.lpszClassName  = m_applicationName;                           //指向类名称的指针
		wc.hIconSm        = wc.hIcon;                                    //指向窗口左上小图标的句柄

		RegisterClassEx(&wc);

		//设备初始化(全屏与否）
		int         posX;               //窗口左上角的位置X
		int         posY;               //窗口左上角的位置Y

		if( m_isFullScreen )
		{
			DEVMODE dmScreenSettings;
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));

			dmScreenSettings.dmSize       = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth  = (unsigned long)m_width;
			dmScreenSettings.dmPelsHeight = (unsigned long)m_height;
			dmScreenSettings.dmBitsPerPel = 32;			
			dmScreenSettings.dmFields     = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN);

			posX = posY = 0;
		}
		else
		{
			posX = (GetSystemMetrics(SM_CXSCREEN) - m_width) / 2;
			posY = (GetSystemMetrics(SM_CYSCREEN) - m_height) / 2;
		}

		//创建窗口
		m_hWnd = CreateWindowEx(WS_EX_APPWINDOW,                  //窗口的扩展风格
			m_applicationName,                                    //指向窗口类名字的指针
			m_applicationName,                                    //指向窗口名字的指针
			WS_OVERLAPPEDWINDOW,                                  //窗口的风格
			posX, posY,                                           //窗口在屏幕上显示的起始位置
			m_width, m_height,                                    //窗口的宽度和高度
			NULL,                                                 //指向被创建窗口的的父窗口的句柄
			NULL,                                                 //菜单的句柄
			m_hInstance,                                          //与窗口相关联的模块的实例句柄
			NULL);                                                //指向一个值的指针，该值传递给窗口WM_CREATE消息


		ShowWindow(m_hWnd, SW_SHOW);
		SetForegroundWindow(m_hWnd);
		SetFocus(m_hWnd);


		//以下这段代码用于限制鼠标光标移动区域
		POINT lt,rb;
		GetClientRect(m_hWnd,&m_rect);  //取得窗口内部矩形
		//将矩形左上点坐标存入lt中
		lt.x = m_rect.left;
		lt.y = m_rect.top;
		//将矩形右下坐标存入rb中
		rb.x = m_rect.right;
		rb.y = m_rect.bottom;
		//将lt和rb的窗口坐标转换为屏幕坐标
		ClientToScreen(m_hWnd,&lt);
		ClientToScreen(m_hWnd,&rb);
		//以屏幕坐标重新设定矩形区域
		m_rect.left = lt.x;
		m_rect.top = lt.y;
		m_rect.right = rb.x;
		m_rect.bottom = rb.y;
		//限制鼠标光标移动区域
		//ClipCursor(&m_rect);

		m_insideCentre.x = (m_rect.right - m_rect.left) / 2;
		m_insideCentre.y = (m_rect.bottom - m_rect.top) / 2;
		m_outsideCentre.x = m_rect.left + m_insideCentre.x;
		m_outsideCentre.y = m_rect.top + m_insideCentre.y;
		ShowCursor(false);		//隐藏鼠标光标

		return;
	}

	//-----------------------------------------------------------------------
	void SystemClass::ShutdownWindows()
	{
		//ShowCursor(true);     //显示光标

		if( m_isFullScreen )
		{
			ChangeDisplaySettings(NULL, 0);
		}

		DestroyWindow(m_hWnd);
		m_hWnd = NULL;

		UnregisterClass(m_applicationName, m_hInstance);
		m_hInstance = NULL;

		return;
	}

	//-----------------------------------------------------------------------
	LRESULT CALLBACK WndProc(HWND hwnd, UINT umessage, WPARAM wparam, LPARAM lparam)
	{
		switch(umessage)
		{
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				return 0;
			}
		case WM_CLOSE:
			{
				PostQuitMessage(0);
				return 0;
			}
		default:
			{
				return g_inputClass->MessageHandler(hwnd, umessage, wparam, lparam);
			}
		}
	}
}