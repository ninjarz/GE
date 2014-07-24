#pragma once
#ifndef _GESYSTEMCLASS_H_
#define _GESYSTEMCLASS_H_

#include <windows.h>
#include "GEManageClass.h"

//-----------------------------------------------------------------------
namespace GE
{
	class SystemClass : public GEClass
	{
	public:
		SystemClass();
		SystemClass(const SystemClass&);
		~SystemClass();  

		bool Initialize();
		void Shutdown();

	private:  
		void InitWindows();           //创建窗口
		void ShutdownWindows();       //销毁窗口
	};

	LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

	extern SystemClass* g_systemClass;
}

#endif