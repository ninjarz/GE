#pragma once
#ifndef _GEINPUTCLASS_H_
#define _GEINPUTCLASS_H_

#include <windows.h>
#include <WindowsX.h>
#include "GEManageClass.h"

//-----------------------------------------------------------------------
namespace GE
{
	class InputClass : public GEClass
	{
	public:
		InputClass();
		InputClass(const InputClass&);
		~InputClass();

		bool Initialize();
		void Shutdown();

		bool IsKeyDown(UINT);
		LRESULT CALLBACK MessageHandler(HWND, UINT, WPARAM, LPARAM);

		inline int& GetOnDeltaX() { return m_onDeltaX; }
		inline int& GetOnDeltaY() { return m_onDeltaY; }
		inline void ClearOnDelta() { m_onDeltaX = 0; m_onDeltaY = 0; }

	private:
		void KeyDown(unsigned int);
		void KeyUp(unsigned int);

		void MouseDown(WPARAM, int, int);
		void MouseUp(WPARAM, int , int);

		void MouseWheel(WPARAM, int, int);
		void OnMouseMove(WPARAM, int, int);

	private:
		bool m_keys[256];
		POINT m_lastPos;
		int m_onDeltaX;
		int m_onDeltaY;
		int m_deltaM;
		int m_deltaPerLine;//‘› ±√ª”√
	};

	extern InputClass* g_inputClass;

	bool GEIsKeyDown(UINT);
	int& GEGetOnDeltaX();
	int& GEGetOnDeltaY();
	void GEClearOnDelta();
}

#endif