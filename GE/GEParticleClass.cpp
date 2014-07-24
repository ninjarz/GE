#include "GEParticleClass.h"

#include "GEShader.h"
#include "GECameraClass.h"
#include "GEShaderState.h"

namespace GE
{
	ParticleClass *g_particleClass;

	//-----------------------------------------------------------------------
	bool ParticleClass::Initialize()
	{
		HRESULT result;
		ID3D10Blob* errorMessage;
		ID3D10Blob* vertexShaderBuffer;
		ID3D10Blob* geometryShaderBuffer;
		ID3D10Blob* pixelShaderBuffer;
		ID3D10Blob* computeShaderBuffer;

		result = D3DX11CompileFromFile( L"Shader\\SnowShader.fx", NULL, NULL, "SnowVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
		if(FAILED(result))
		{
			if(errorMessage)
			{
				MessageBoxA(NULL,(char*)errorMessage->GetBufferPointer(),"ShaderCompileError",MB_YESNO);
				errorMessage->Release();
				errorMessage = 0;
			}
			else
				MessageBox(NULL,L"CompileShader´íÎó!",L"´íÎó",MB_OK);
			return FALSE;
		}
		result = D3DX11CompileFromFile( L"Shader\\SnowShader.fx", NULL, NULL, "SnowGS", "gs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &geometryShaderBuffer, &errorMessage, NULL);
		if(FAILED(result))
		{
			if(errorMessage)
			{
				MessageBoxA(NULL,(char*)errorMessage->GetBufferPointer(),"ShaderCompileError",MB_YESNO);
				errorMessage->Release();
				errorMessage = 0;
			}
			else
				MessageBox(NULL,L"CompileShader´íÎó!",L"´íÎó",MB_OK);
			return FALSE;
		}
		result = D3DX11CompileFromFile( L"Shader\\SnowShader.fx", NULL, NULL, "SnowPS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
		if(FAILED(result))
		{
			if(errorMessage)
			{
				MessageBoxA(NULL,(char*)errorMessage->GetBufferPointer(),"ShaderCompileError",MB_YESNO);
				errorMessage->Release();
				errorMessage = 0;
			}
			else
				MessageBox(NULL,L"CompileShader´íÎó!",L"´íÎó",MB_OK);
			return FALSE;
		}
		result = D3DX11CompileFromFile( L"Shader\\SnowShader.fx", NULL, NULL, "SnowCS", "cs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &computeShaderBuffer, &errorMessage, NULL);
		if(FAILED(result))
		{
			if(errorMessage)
			{
				MessageBoxA(NULL,(char*)errorMessage->GetBufferPointer(),"ShaderCompileError",MB_YESNO);
				errorMessage->Release();
				errorMessage = 0;
			}
			else
				MessageBox(NULL,L"CompileShader´íÎó!",L"´íÎó",MB_OK);
			return FALSE;
		}
		result = m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_snowVS);
		if(FAILED(result))
			return false;
		result = m_device->CreateGeometryShader(geometryShaderBuffer->GetBufferPointer(), geometryShaderBuffer->GetBufferSize(), NULL, &m_snowGS);
		if(FAILED(result))
			return false;
		result = m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_snowPS);
		if(FAILED(result))
			return false;
		result = m_device->CreateComputeShader(computeShaderBuffer->GetBufferPointer(), computeShaderBuffer->GetBufferSize(), NULL, &m_snowCS);
		if(FAILED(result))
			return false;

		D3D11_INPUT_ELEMENT_DESC snowInputDesc[1] = 
	{
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};
	result = m_device->CreateInputLayout(snowInputDesc, 1, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_snowIL);
	if(FAILED(result))
		return false;
	SAFE_RELEASE(vertexShaderBuffer);
	SAFE_RELEASE(geometryShaderBuffer);
	SAFE_RELEASE(pixelShaderBuffer);
	SAFE_RELEASE(computeShaderBuffer);

		return true;
	}

	//-----------------------------------------------------------------------
	void ParticleClass::Shutdown()
	{

	}

	//-----------------------------------------------------------------------
	bool ParticleClass::Render(SnowMesh& mesh)
	{
		ID3D11DepthStencilState* depthStencilStateStored = NULL;
		UINT stencilRef;
		m_deviceContext->OMGetDepthStencilState( &depthStencilStateStored, &stencilRef );
		g_shaderStateClass->SetDDState(DISABLEDEPTHTEST_DDS);
		g_shaderStateClass->SetBState(SNOW_BS);

		m_deviceContext->CSSetUnorderedAccessViews(0, 1, &mesh.snowUAV, NULL);
		m_deviceContext->CSSetShader(m_snowCS, NULL, 0);

		m_deviceContext->Dispatch(mesh.vertexCount, 1, 1);

		ID3D11UnorderedAccessView *UAVNULL[1] = { NULL };
		m_deviceContext->CSSetUnorderedAccessViews(0, 1, UAVNULL, NULL);
		m_deviceContext->CSSetShader(NULL, NULL, 0);

		if( !g_shaderClass->SetBasicParameters(MATRIX::IDENTITY, g_cameraClass->GetViewProjMatrix()) )
			return false;
		m_deviceContext->VSSetShaderResources(0, 1, &mesh.snowSRV);
		m_deviceContext->PSSetShaderResources(0, 1, &mesh.tex);
		UINT stride =sizeof(SnowVertex); 
		UINT offset = 0;
		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		m_deviceContext->IASetInputLayout(m_snowIL);
		m_deviceContext->IASetVertexBuffers(0, 1, &mesh.snowVB, &stride, &offset);
		m_deviceContext->IASetIndexBuffer( NULL, DXGI_FORMAT_R32_UINT, 0);
		m_deviceContext->VSSetShader( m_snowVS, NULL, 0 );
		m_deviceContext->GSSetShader( m_snowGS, NULL, 0 );
		m_deviceContext->PSSetShader( m_snowPS, NULL, 0 );

		m_deviceContext->Draw(mesh.vertexCount, 0);

		ID3D11ShaderResourceView *SRVNULL[] = { NULL };
		m_deviceContext->VSSetShaderResources(0, 1, SRVNULL);
		m_deviceContext->GSSetShader( NULL, NULL, 0 );

		m_deviceContext->OMSetDepthStencilState( depthStencilStateStored, stencilRef );
		SAFE_RELEASE(depthStencilStateStored);
		g_shaderStateClass->SetBState(DEFAULT_BS);

		return true;
	}

	//-----------------------------------------------------------------------
	bool GERender(SnowMesh& mesh) { return g_particleClass->Render(mesh); }

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------
}