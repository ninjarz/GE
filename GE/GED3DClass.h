#pragma once
#ifndef _GED3DCLASS_H_
#define _GED3DCLASS_H_

#include <d3d11.h>
#include "GEManageClass.h"
#include "GEmath.h"

//-----------------------------------------------------------------------
namespace GE
{
	class D3DClass : public GEClass
	{
	public:
		inline D3DClass()
		{
		}

		inline D3DClass(const D3DClass&)
		{
		}

		inline ~D3DClass()
		{
			Shutdown();
		}

		bool Initialize();
		void Shutdown();

		void BeginScene(float, float, float, float);
		void BeginScene(const FLOAT4&);
		void EndScene();

		ID3D11Device* GetDevice()                        const {return m_device;};
		ID3D11DeviceContext* GetDeviceContext()          const {return m_deviceContext;};
		ID3D11RenderTargetView* GetRenderTargetView()    const {return m_renderTargetView;};
		ID3D11DepthStencilView* GetDepthStencilView()    const {return m_depthStencilView;};

		void GetVideoCardInfo(char*, int&);
	};

	extern D3DClass *g_D3DClass;

	void GEBeginScene(float, float, float, float);
	void GEBeginScene(const FLOAT4&);
	void GEEndScene();
}

#endif