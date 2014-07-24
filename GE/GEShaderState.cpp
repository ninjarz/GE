#include "GEShaderState.h"

namespace GE
{
	ShaderStateClass *g_shaderStateClass;

	//-----------------------------------------------------------------------
	bool ShaderStateClass::Initialize()
	{
		float m_blendFactor[4] = {0.f,0.f,0.f,0.f};

		HRESULT hr;

		D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
		ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
		depthStencilDesc.DepthEnable                    = true;
		depthStencilDesc.DepthWriteMask                 = D3D11_DEPTH_WRITE_MASK_ALL;
		depthStencilDesc.DepthFunc                      = D3D11_COMPARISON_LESS;
		depthStencilDesc.StencilEnable                  = false;
		depthStencilDesc.StencilReadMask                = 0xFF;
		depthStencilDesc.StencilWriteMask               = 0xFF;
		depthStencilDesc.FrontFace.StencilFailOp        = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilDepthFailOp   = D3D11_STENCIL_OP_INCR;
		depthStencilDesc.FrontFace.StencilPassOp        = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.FrontFace.StencilFunc          = D3D11_COMPARISON_ALWAYS;
		depthStencilDesc.BackFace.StencilFailOp         = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilDepthFailOp    = D3D11_STENCIL_OP_DECR;
		depthStencilDesc.BackFace.StencilPassOp         = D3D11_STENCIL_OP_KEEP;
		depthStencilDesc.BackFace.StencilFunc           = D3D11_COMPARISON_ALWAYS;
		hr = m_device->CreateDepthStencilState(&depthStencilDesc, &m_defaultDSS);
		if( FAILED(hr) )
			return false;

		depthStencilDesc.DepthWriteMask                 = D3D11_DEPTH_WRITE_MASK_ZERO;
		hr = m_device->CreateDepthStencilState(&depthStencilDesc, &m_disableDWriteDSS);
		if( FAILED(hr) )
			return false;

		depthStencilDesc.DepthEnable                    = false;
		hr = m_device->CreateDepthStencilState(&depthStencilDesc, &m_disableDTestDSS);
		if( FAILED(hr) )
			return false;

		D3D11_RASTERIZER_DESC rasterDesc;
		rasterDesc.AntialiasedLineEnable    = false;
		rasterDesc.CullMode                 = D3D11_CULL_BACK;
		rasterDesc.DepthBias                = 0;
		rasterDesc.DepthBiasClamp           = 0.0f;
		rasterDesc.DepthClipEnable          = true;
		rasterDesc.FillMode                 = D3D11_FILL_SOLID;
		rasterDesc.FrontCounterClockwise    = false;
		rasterDesc.MultisampleEnable        = false;
		rasterDesc.ScissorEnable            = false;
		rasterDesc.SlopeScaledDepthBias     = 0.0f;
		m_device->CreateRasterizerState(&rasterDesc, &m_defaultRS);

		rasterDesc.CullMode                 = D3D11_CULL_NONE;
		m_device->CreateRasterizerState(&rasterDesc, &m_disableCullRS);

		rasterDesc.CullMode                 = D3D11_CULL_BACK;
		rasterDesc.FillMode                 = D3D11_FILL_WIREFRAME;
		m_device->CreateRasterizerState(&rasterDesc, &m_wireframeRS);

		rasterDesc.CullMode                 = D3D11_CULL_NONE;
		rasterDesc.FillMode                 = D3D11_FILL_WIREFRAME;
		m_device->CreateRasterizerState(&rasterDesc, &m_wireframe_disableCullRS);

		D3D11_SAMPLER_DESC SamplerDesc;
		ZeroMemory( &SamplerDesc, sizeof(SamplerDesc) );
		SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		m_device->CreateSamplerState( &SamplerDesc, &m_defaultSS);

		D3D11_BLEND_DESC blendDesc;
		blendDesc.AlphaToCoverageEnable = false;
		blendDesc.IndependentBlendEnable = false;
		blendDesc.RenderTarget[0].BlendEnable = false;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		m_device->CreateBlendState(&blendDesc,&m_defaultBS);

		blendDesc.RenderTarget[0].BlendEnable = true;
		m_device->CreateBlendState(&blendDesc,&m_interpolateBS);

		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = 0x0F;
		m_device->CreateBlendState(&blendDesc, &m_snowBS);

		return true;
	}

	//-----------------------------------------------------------------------
	void ShaderStateClass::Shutdown()
	{
	}

	//-----------------------------------------------------------------------
	void GESetDDState(DDState para) { g_shaderStateClass->SetDDState(para); }

	//-----------------------------------------------------------------------
	void GESetRState(RState para) { g_shaderStateClass->SetRState(para); }

	//-----------------------------------------------------------------------
	void GESetBState(BState para) { g_shaderStateClass->SetBState(para); }

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
}