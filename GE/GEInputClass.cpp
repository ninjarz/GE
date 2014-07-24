#include "GEInputClass.h"

#include "GEManageClass.h"

namespace GE
{
	InputClass* g_inputClass;

	//-----------------------------------------------------------------------
	InputClass::InputClass()
	{
	}

	//-----------------------------------------------------------------------
	InputClass::InputClass(const InputClass& other)
	{
	}

	//-----------------------------------------------------------------------
	InputClass::~InputClass()
	{
		Shutdown();
	}

	//-----------------------------------------------------------------------
	bool InputClass::Initialize()
	{
		ZeroMemory(m_keys,sizeof(m_keys));
		m_onDeltaX = 0;
		m_onDeltaY = 0;
		m_deltaM = 0;
		ULONG scrollLines;
		SystemParametersInfo( SPI_GETWHEELSCROLLLINES, 0, &scrollLines,0);
		if( scrollLines)
			m_deltaPerLine = WHEEL_DELTA / scrollLines;
		else
			m_deltaPerLine = 0;

		return true;
	}

	//-----------------------------------------------------------------------
	void InputClass::Shutdown()
	{
	}

	//-----------------------------------------------------------------------
	void InputClass::KeyDown(UINT input)
	{
		m_keys[input] = true;

		return;
	}

	//-----------------------------------------------------------------------
	void InputClass::KeyUp(UINT input)
	{
		m_keys[input] = false;

		return;
	}

	//-----------------------------------------------------------------------
	bool InputClass::IsKeyDown(UINT key)
	{
		return m_keys[key];
	}

	//-----------------------------------------------------------------------
	void InputClass::MouseDown(WPARAM btnState, int x, int y)
	{
		SetCapture( m_hWnd );
		KeyDown( (unsigned int)btnState );
		m_lastPos.x = x;
		m_lastPos.y = y;
	}

	//-----------------------------------------------------------------------
	void InputClass::MouseUp(WPARAM btnState, int x, int y)
	{
		ReleaseCapture();
		KeyUp( (unsigned int)btnState );
	}

	//-----------------------------------------------------------------------
	void InputClass::MouseWheel(WPARAM btnState, int x, int y)
	{
		m_deltaM += (short)HIWORD(btnState);
	}

	//-----------------------------------------------------------------------
	void InputClass::OnMouseMove(WPARAM btnState, int x, int y)
	{
		if(1)
		{
				m_onDeltaX = x - m_insideCentre.x;
				m_onDeltaY = y - m_insideCentre.y;
		}
		else if(0)
		{
			if(btnState & MK_LBUTTON)
			{
				m_onDeltaX = x - m_lastPos.x;
				m_onDeltaY = y - m_lastPos.y;
			}
			m_lastPos.x = x;
			m_lastPos.y = y;
		}
	}

	//-----------------------------------------------------------------------
	LRESULT CALLBACK InputClass::MessageHandler(HWND hwnd, UINT umsg, WPARAM wparam, LPARAM lparam)
	{
		switch( umsg )
		{
		case WM_LBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_RBUTTONDOWN:
			MouseDown(wparam, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			return 0;

		case WM_LBUTTONUP:
		case WM_MBUTTONUP:
		case WM_RBUTTONUP:
			MouseUp(wparam, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			return 0;

			//case WM_SETTINGCHANGE:

		case WM_MOUSEWHEEL:
			MouseWheel(wparam, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			return 0;
		case WM_MOUSEMOVE:
			OnMouseMove(wparam, GET_X_LPARAM(lparam), GET_Y_LPARAM(lparam));
			return 0;

		case WM_KEYDOWN:
			KeyDown( (unsigned int)wparam );
			return 0;

		case WM_KEYUP:
			KeyUp( (unsigned int)wparam );
			return 0;
		default:
			return DefWindowProc(hwnd, umsg, wparam, lparam);
		}
		//return 0;
	}

	//-----------------------------------------------------------------------
	bool GEIsKeyDown(UINT para) { return g_inputClass->IsKeyDown(para); }

	//-----------------------------------------------------------------------
	int& GEGetOnDeltaX() { return g_inputClass->GetOnDeltaX(); }

	//-----------------------------------------------------------------------
	int& GEGetOnDeltaY() { return g_inputClass->GetOnDeltaY(); }

	//-----------------------------------------------------------------------
	void GEClearOnDelta() { return g_inputClass->ClearOnDelta(); }
}