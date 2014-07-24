#pragma once
#ifndef _GESHADERSTATE_H_
#define _GESHADERSTATE_H_

#include <d3d11.h>
#include "GEManageClass.h"

namespace GE
{
	enum DDState
	{
		DEFAULT_DDS = 0,
		DISABLEDEPTHWRITE_DDS = 1,
		DISABLEDEPTHTEST_DDS = 2,
	};

	enum RState
	{
		DEFAULT_RS = 0,
		DISABLECULL_RS = 1,
		WIREFRAME_RS = 2,
	};

	enum BState
	{
		DEFAULT_BS = 0,
		INTERPOLATE_BS,
		SNOW_BS,
	};


	class ShaderStateClass : public GEClass
	{
	public:
		inline ShaderStateClass()
		{
		}

		inline ShaderStateClass(const ShaderStateClass&)
		{
		}

		inline ~ShaderStateClass()
		{
			Shutdown();
		}

		bool Initialize();
		void Shutdown();

		inline void SetDDState(DDState para) const 
		{
			switch(para)
			{
			case DEFAULT_DDS: m_deviceContext->OMSetDepthStencilState(m_defaultDSS, 1); break;
			case DISABLEDEPTHWRITE_DDS: m_deviceContext->OMSetDepthStencilState(m_disableDWriteDSS, 1); break;
			case DISABLEDEPTHTEST_DDS: m_deviceContext->OMSetDepthStencilState(m_disableDTestDSS, 1); break;
			}
		}

		inline void SetRState(RState para) const 
		{
			switch(para)
			{
			case DEFAULT_RS: m_deviceContext->RSSetState(m_defaultRS); break;
			case DISABLECULL_RS: m_deviceContext->RSSetState(m_disableCullRS); break;
			case WIREFRAME_RS: m_deviceContext->RSSetState(m_wireframeRS); break;
			case DISABLECULL_RS|WIREFRAME_RS: m_deviceContext->RSSetState(m_wireframe_disableCullRS); break;
			}
		}

		inline void SetBState(BState para) const 
		{
			switch(para)
			{
			case DEFAULT_BS: m_deviceContext->OMSetBlendState(m_defaultBS, m_blendFactor, 0xffffffff); break;
			case INTERPOLATE_BS: m_deviceContext->OMSetBlendState(m_interpolateBS, m_blendFactor, 0xffffffff); break;
			case SNOW_BS: m_deviceContext->OMSetBlendState(m_snowBS, m_blendFactor, 0xffffffff); break;
			}
		}

	private:
		float m_blendFactor[4];

		ID3D11DepthStencilState *m_defaultDSS;
		ID3D11DepthStencilState *m_disableDWriteDSS;
		ID3D11DepthStencilState *m_disableDTestDSS;

		ID3D11RasterizerState *m_defaultRS;
		ID3D11RasterizerState *m_disableCullRS;
		ID3D11RasterizerState *m_wireframeRS;
		ID3D11RasterizerState *m_wireframe_disableCullRS;

		ID3D11BlendState *m_defaultBS;
		ID3D11BlendState *m_interpolateBS;
		ID3D11BlendState *m_snowBS;

		ID3D11SamplerState *m_defaultSS;
	};

	extern ShaderStateClass *g_shaderStateClass;

	void GESetDDState(DDState para);
	void GESetRState(RState para);
	void GESetBState(BState para);
}

#endif