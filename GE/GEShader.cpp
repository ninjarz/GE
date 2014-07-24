#include "GEShader.h"

#include "GECameraClass.h"
#include "GEColor.h"
#include "GEShaderState.h"

namespace GE
{
	ShaderClass *g_shaderClass;

	//-----------------------------------------------------------------------
	ShaderClass::ShaderClass()
	{
	}

	//-----------------------------------------------------------------------
	ShaderClass::ShaderClass(const ShaderClass& other)
	{
	}

	//-----------------------------------------------------------------------
	ShaderClass::~ShaderClass()
	{
		Shutdown();
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::Initialize()
	{
		if( !InitializeShader() )
			return false;

		if( !InitializeCBuffer() )
			return false;

		return true;
	}

	//-----------------------------------------------------------------------
	void ShaderClass::Shutdown()
	{
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::InitializeShader()
	{
		HRESULT result;
		ID3D10Blob *errorMessage;
		ID3D10Blob *vertexShaderBuffer;
		ID3D10Blob *pixelShaderBuffer;

		result = D3DX11CompileFromFile( L"Shader\\ColorShader.fx", NULL, NULL, "ColorVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
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
		result = D3DX11CompileFromFile( L"Shader\\ColorShader.fx", NULL, NULL, "ColorPS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
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
		result = m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_colorVS);
		if(FAILED(result))
			return false;
		result = m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_colorPS);
		if(FAILED(result))
			return false;
		D3D11_INPUT_ELEMENT_DESC colorInputDesc[2] = 
		{
			//¶¥µã
			//ÓïÒåÃû	ÊäÈë²Û		Êı¾İ¸ñÊ½			 ÓïÒåÃûË÷Òı		Æ«ÒÆ		ÊäÈëÀàĞÍ			´Ë´¦²»ÓÃ£¬Éè0
			{ "POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT,	0,			 0,  D3D11_INPUT_PER_VERTEX_DATA,	0 },
			//ÑÕÉ«
			{ "COLOR",	 0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0,			 12, D3D11_INPUT_PER_VERTEX_DATA,	0 }
		};
		result = m_device->CreateInputLayout(colorInputDesc, 2, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_colorIL);
		if(FAILED(result))
			return false;
		SAFE_RELEASE(vertexShaderBuffer);
		SAFE_RELEASE(pixelShaderBuffer);

		result = D3DX11CompileFromFile( L"Shader\\LightShader.fx", NULL, NULL, "LightVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
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
		result = D3DX11CompileFromFile( L"Shader\\LightShader.fx", NULL, NULL, "LightPS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
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
		result = m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_lightVS);
		if(FAILED(result))
			return false;
		result = m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_lightPS);
		if(FAILED(result))
			return false;
		D3D11_INPUT_ELEMENT_DESC lightInputDesc[2] = 
		{
			{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0, D3D11_INPUT_PER_VERTEX_DATA,0},
			{"NORMAL",  0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0}
		};
		result = m_device->CreateInputLayout(lightInputDesc, 2, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_lightIL);
		if(FAILED(result))
			return false;
		SAFE_RELEASE(vertexShaderBuffer);
		SAFE_RELEASE(pixelShaderBuffer);

		result = D3DX11CompileFromFile( L"Shader\\TexShader.fx", NULL, NULL, "TexVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
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
		result = D3DX11CompileFromFile( L"Shader\\TexShader.fx", NULL, NULL, "TexPS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
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
		result = m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_texVS);
		if(FAILED(result))
			return false;
		result = m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_texPS);
		if(FAILED(result))
			return false;
		D3D11_INPUT_ELEMENT_DESC textureInputDesc[3] = 
		{
			{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0, D3D11_INPUT_PER_VERTEX_DATA,0},
			{"NORMAL",  0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,   0,24,D3D11_INPUT_PER_VERTEX_DATA,0}
		};
		result = m_device->CreateInputLayout(textureInputDesc, 3, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_texIL);
		if(FAILED(result))
			return false;
		SAFE_RELEASE(vertexShaderBuffer);
		SAFE_RELEASE(pixelShaderBuffer);

		result = D3DX11CompileFromFile( L"Shader\\CubeMapShader.fx", NULL, NULL, "CubeMapVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
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
		result = D3DX11CompileFromFile( L"Shader\\CubeMapshader.fx", NULL, NULL, "CubeMapPS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
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
		result = m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_cubeMapVS);
		if(FAILED(result))
			return false;
		result = m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_cubeMapPS);
		if(FAILED(result))
			return false;
		D3D11_INPUT_ELEMENT_DESC cubeMapInputDesc[1] = 
		{
			{"POSITION",0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
		result = m_device->CreateInputLayout(cubeMapInputDesc, 1, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_cubeMapIL);
		if(FAILED(result))
			return false;
		SAFE_RELEASE(vertexShaderBuffer);
		SAFE_RELEASE(pixelShaderBuffer);

		result = D3DX11CompileFromFile( L"Shader\\MazeShader.fx", NULL, NULL, "MazeVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
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
		result = D3DX11CompileFromFile( L"Shader\\MazeShader.fx", NULL, NULL, "MazePS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
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
		result = m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_mazeVS);
		if(FAILED(result))
			return false;
		result = m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_mazePS);
		if(FAILED(result))
			return false;
		D3D11_INPUT_ELEMENT_DESC mazeInputDesc[6] = 
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0      },
			{ "WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1   },
			{ "WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1  },
			{ "WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1  },
			{ "WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1  },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 64,  D3D11_INPUT_PER_INSTANCE_DATA, 1 }
		};
		result = m_device->CreateInputLayout(mazeInputDesc, 6, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_mazeIL);
		if(FAILED(result))
			return false;
		SAFE_RELEASE(vertexShaderBuffer);
		SAFE_RELEASE(pixelShaderBuffer);
		/*
		result = D3DX11CompileFromFile( L"Shader\\TexMazeShader.fx", NULL, NULL, "TexMazeVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
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
		result = D3DX11CompileFromFile( L"Shader\\TexMazeShader.fx", NULL, NULL, "TexMazePS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
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
		result = m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_texMazeVS);
		if(FAILED(result))
			return false;
		result = m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_texMazePS);
		if(FAILED(result))
			return false;
		D3D11_INPUT_ELEMENT_DESC texMazeInputDesc[7] = 
		{
			{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0, D3D11_INPUT_PER_VERTEX_DATA,0},
			{"NORMAL",  0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
			{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,   0,24,D3D11_INPUT_PER_VERTEX_DATA,0},
			{ "WORLD", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_INSTANCE_DATA, 1   },
			{ "WORLD", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 16, D3D11_INPUT_PER_INSTANCE_DATA, 1  },
			{ "WORLD", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 32, D3D11_INPUT_PER_INSTANCE_DATA, 1  },
			{ "WORLD", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 48, D3D11_INPUT_PER_INSTANCE_DATA, 1  },
		};
		result = m_device->CreateInputLayout(texMazeInputDesc, 7, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_texMazeIL);
		SAFE_RELEASE(vertexShaderBuffer);
		SAFE_RELEASE(pixelShaderBuffer);
		*/

		result = D3DX11CompileFromFile( L"Shader\\QuadShader.fx", NULL, NULL, "QuadVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
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
		result = D3DX11CompileFromFile( L"Shader\\QuadShader.fx", NULL, NULL, "QuadPS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
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
		result = m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_quadVS);
		if(FAILED(result))
			return false;
		result = m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_quadPS);
		if(FAILED(result))
			return false;
		D3D11_INPUT_ELEMENT_DESC quadInputDesc[2] = 
		{
			{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0, D3D11_INPUT_PER_VERTEX_DATA,0},
			{"TEXCOORD",0,DXGI_FORMAT_R32G32_FLOAT,   0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		};
		result = m_device->CreateInputLayout(quadInputDesc, 2, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_quadIL);
		if(FAILED(result))
			return false;
		SAFE_RELEASE(vertexShaderBuffer);
		SAFE_RELEASE(pixelShaderBuffer);
		return true;
	}

	//-----------------------------------------------------------------------
	void ShaderClass::ShutdownShader()
	{
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::InitializeCBuffer()
	{
		HRESULT result;
		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth = sizeof(BasicBuffer);
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		result = m_device->CreateBuffer(&bufferDesc, NULL, &m_basicBuffer);
		if(FAILED(result))
			return false;
		bufferDesc.ByteWidth = sizeof(FogBuffer);
		result = m_device->CreateBuffer(&bufferDesc, NULL, &m_fogBuffer);
		if(FAILED(result))
			return false;
		bufferDesc.ByteWidth = sizeof(LightBuffer);
		result = m_device->CreateBuffer(&bufferDesc, NULL, &m_lightBuffer);
		if(FAILED(result))
			return false;
		bufferDesc.ByteWidth = sizeof(PerFrameBuffer);
		result = m_device->CreateBuffer(&bufferDesc, NULL, &m_PerFrameBuffer);
		if(FAILED(result))
			return false;

		if( !SetFogParameters(GE_SILVER, 0.f, 200.f, true, true) )
			return false;

		DirLight directLight[3];
		directLight[0].ambient  =	FLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		directLight[0].diffuse  =	FLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		directLight[0].specular =	FLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
		directLight[0].dir		=	FLOAT3(0.57735f, -0.57735f, 0.57735f);
		directLight[1].ambient  =	FLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		directLight[1].diffuse  =	FLOAT4(0.20f, 0.20f, 0.20f, 1.0f);
		directLight[1].specular =	FLOAT4(0.25f, 0.25f, 0.25f, 1.0f);
		directLight[1].dir		=	FLOAT3(-0.57735f, -0.57735f, 0.57735f);
		directLight[2].ambient  =	FLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		directLight[2].diffuse  =	FLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
		directLight[2].specular =	FLOAT4(0.0f, 0.0f, 0.0f, 1.0f);
		directLight[2].dir	    =	FLOAT3(0.0f, -0.707f, -0.707f);
		if( !SetLightParameters(directLight, 0, 3) )
			return false;

		//if( !SetPerFrameParameters( )
		//	return false;

		return true;
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::SetBasicParameters(const MATRIX& viewProjMatrix)
	{
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		BasicBuffer* dataPtr;

		result = m_deviceContext->Map(m_basicBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if(FAILED(result))
			return false;
		dataPtr = (BasicBuffer*)mappedResource.pData;
		dataPtr->worldViewProj = viewProjMatrix;
		m_deviceContext->Unmap(m_basicBuffer, 0);

		m_deviceContext->VSSetConstantBuffers(0, 1, &m_basicBuffer);
		m_deviceContext->PSSetConstantBuffers(0, 1, &m_basicBuffer);
		m_deviceContext->GSSetConstantBuffers(0, 1, &m_basicBuffer);
		m_deviceContext->CSSetConstantBuffers(0, 1, &m_basicBuffer);
		return true;
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::SetBasicParameters(const MATRIX& worldMatrix, const MATRIX& viewProjMatrix)
	{
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		BasicBuffer* dataPtr;

		result = m_deviceContext->Map(m_basicBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if(FAILED(result))
			return false;
		dataPtr = (BasicBuffer*)mappedResource.pData;
		dataPtr->worldViewProj = worldMatrix * viewProjMatrix;
		dataPtr->world = worldMatrix;
		m_deviceContext->Unmap(m_basicBuffer, 0);

		m_deviceContext->VSSetConstantBuffers(0, 1, &m_basicBuffer);
		m_deviceContext->PSSetConstantBuffers(0, 1, &m_basicBuffer);
		m_deviceContext->GSSetConstantBuffers(0, 1, &m_basicBuffer);
		m_deviceContext->CSSetConstantBuffers(0, 1, &m_basicBuffer);
		return true;
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::SetBasicParameters(const MATRIX& worldMatrix, const MATRIX& viewMatrix, const MATRIX& projectionMatrix)
	{
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		BasicBuffer* dataPtr;

		result = m_deviceContext->Map(m_basicBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if(FAILED(result))
			return false;
		dataPtr = (BasicBuffer*)mappedResource.pData;
		dataPtr->worldViewProj = worldMatrix * viewMatrix * projectionMatrix;
		dataPtr->world = worldMatrix;
		m_deviceContext->Unmap(m_basicBuffer, 0);

		m_deviceContext->VSSetConstantBuffers(0, 1, &m_basicBuffer);
		m_deviceContext->PSSetConstantBuffers(0, 1, &m_basicBuffer);
		m_deviceContext->GSSetConstantBuffers(0, 1, &m_basicBuffer);
		m_deviceContext->CSSetConstantBuffers(0, 1, &m_basicBuffer);

		return true;
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::SetFogParameters(const FLOAT4& fogColor, const FLOAT fogStart, const FLOAT fogRange, const bool useFog, const bool fogClipEnable)
	{
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		FogBuffer *dataPtr;

		result = m_deviceContext->Map(m_fogBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if(FAILED(result))
			return false;
		dataPtr = (FogBuffer*)mappedResource.pData;
		dataPtr->fogStart = fogStart;
		dataPtr->fogRange = fogRange;
		dataPtr->fogColor = fogColor;
		dataPtr->useFog = (UINT)useFog;
		dataPtr->fogClipEnable = (UINT)fogClipEnable;
		m_deviceContext->Unmap(m_fogBuffer, 0);

		m_deviceContext->PSSetConstantBuffers(1, 1, &m_fogBuffer);

		return true;
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::SetLightParameters(const DirLight* dirLights, const UINT dirStar, const UINT dirNum)
	{
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		LightBuffer *dataPtr;

		result = m_deviceContext->Map(m_lightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if(FAILED(result))
			return false;
		dataPtr = (LightBuffer*)mappedResource.pData;
		memcpy(&dataPtr->dirLights[dirStar], dirLights, sizeof(DirLight)*dirNum);
		m_deviceContext->Unmap(m_lightBuffer, 0);

		m_deviceContext->PSSetConstantBuffers(2, 1, &m_lightBuffer);

		return true;
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::SetPerFrameParameters(const MATRIX& viewInv, const FLOAT3& eyePos, const FLOAT deltaTime)
	{
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		PerFrameBuffer *dataPtr;

		result = m_deviceContext->Map(m_PerFrameBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if(FAILED(result))
			return false;
		dataPtr = (PerFrameBuffer*)mappedResource.pData;
		dataPtr->viewInv = viewInv;
		dataPtr->eyePos = eyePos;
		dataPtr->deltaTime = deltaTime;
		m_deviceContext->Unmap(m_PerFrameBuffer, 0);

		m_deviceContext->VSSetConstantBuffers(3, 1, &m_PerFrameBuffer);
		m_deviceContext->PSSetConstantBuffers(3, 1, &m_PerFrameBuffer);
		m_deviceContext->GSSetConstantBuffers(3, 1, &m_PerFrameBuffer);
		m_deviceContext->CSSetConstantBuffers(3, 1, &m_PerFrameBuffer);
		return true;
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::Render(ColorMesh& mesh)
	{
		if( !SetBasicParameters(mesh.worldMatrix, g_cameraClass->GetViewProjMatrix()))
			return false;

		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_deviceContext->IASetInputLayout(m_colorIL);
		UINT stride =  sizeof(ColorVertex); 
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &mesh.colorVB, &stride, &offset);
		m_deviceContext->IASetIndexBuffer(mesh.colorIB, DXGI_FORMAT_R32_UINT, 0);
		m_deviceContext->VSSetShader(m_colorVS, NULL, 0);
		m_deviceContext->PSSetShader(m_colorPS, NULL, 0);

		m_deviceContext->DrawIndexed(mesh.indexCount, 0, 0);

		return true;
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::Render(CubeMapMesh& mesh)
	{
		ID3D11DepthStencilState* depthStencilStateStored = NULL;
		UINT stencilRef;
		m_deviceContext->OMGetDepthStencilState(&depthStencilStateStored, &stencilRef);
		g_shaderStateClass->SetDDState(DISABLEDEPTHTEST_DDS);

		FLOAT3 pos = g_cameraClass->GetPosition();
		if( !SetBasicParameters(MatrixTranslation(pos.x, pos.y, pos.z), g_cameraClass->GetViewProjMatrix()) )
			return false;
		if( mesh.tex )
		{
			m_deviceContext->PSSetShaderResources(0, 1, &mesh.tex);
		}
		//SAFE_RELEASE(mesh.tex);

		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_deviceContext->IASetInputLayout(m_cubeMapIL);
		UINT stride =  sizeof(CubeMapVertex); 
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &mesh.cubeMapVB, &stride, &offset);
		m_deviceContext->IASetIndexBuffer(mesh.cubeMapIB, DXGI_FORMAT_R32_UINT, 0);
		m_deviceContext->VSSetShader(m_cubeMapVS, NULL, 0);
		m_deviceContext->PSSetShader(m_cubeMapPS, NULL, 0);

		m_deviceContext->DrawIndexed(mesh.indexCount, 0, 0);

		m_deviceContext->OMSetDepthStencilState( depthStencilStateStored, stencilRef );
		SAFE_RELEASE(depthStencilStateStored);

		return true;
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::Render(TexMesh_File& mesh)
	{
		if( !SetBasicParameters(mesh.worldMatrix, g_cameraClass->GetViewProjMatrix()))
			return false;
		m_deviceContext->PSSetShaderResources(0, 1, &mesh.tex);

		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_deviceContext->IASetInputLayout(m_texIL);
		UINT stride =  sizeof(TexVertex); 
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &mesh.texVB, &stride, &offset);
		m_deviceContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R32_UINT, 0);
		m_deviceContext->VSSetShader(m_texVS, NULL, 0);
		m_deviceContext->PSSetShader(m_texPS, NULL, 0);

		m_deviceContext->Draw(mesh.vertexCount, 0);

		return true;
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::Render(MazeMesh& mesh)
	{
		if( !SetBasicParameters(g_cameraClass->GetViewProjMatrix()))
			return false;
		//m_deviceContext->PSSetShaderResources(0, 1, &mesh.tex);

		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_deviceContext->IASetInputLayout(m_mazeIL);
		UINT stride[2] = {sizeof(MazeVertex), sizeof(MazeInstance)};
		UINT offset[2] = {0,0};
		ID3D11Buffer* vbs[2] = {mesh.mazeVB, mesh.mazeInstanceB};
		m_deviceContext->IASetVertexBuffers(0, 2, vbs, stride, offset);
		m_deviceContext->IASetIndexBuffer(mesh.mazeIB, DXGI_FORMAT_R32_UINT, 0);
		m_deviceContext->VSSetShader(m_mazeVS, NULL, 0);
		m_deviceContext->PSSetShader(m_mazePS, NULL, 0);

		m_deviceContext->DrawIndexedInstanced(mesh.indexCount, mesh.instanceCount, 0, 0, 0);

		return true;
	}

	//-----------------------------------------------------------------------
	bool ShaderClass::Render(QuadMesh& mesh)
	{
		g_shaderStateClass->SetBState(INTERPOLATE_BS);

		m_deviceContext->PSSetShaderResources(0, 1, &mesh.tex);

		m_deviceContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
		m_deviceContext->IASetInputLayout(m_quadIL);
		UINT stride =  sizeof(QuadVertex); 
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &mesh.quadVB, &stride, &offset);
		m_deviceContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R32_UINT, 0);
		m_deviceContext->VSSetShader(m_quadVS, NULL, 0);
		m_deviceContext->PSSetShader(m_quadPS, NULL, 0);

		m_deviceContext->Draw(4, 0);

		g_shaderStateClass->SetBState(DEFAULT_BS);
		return true;
	}

	//-----------------------------------------------------------------------
	bool GESetFogParameters(const FLOAT4& fogColor, const FLOAT fogStart, const FLOAT fogRange, const bool useFog, const bool fogClipEnable) { return g_shaderClass->SetFogParameters(fogColor, fogStart, fogRange, useFog, fogClipEnable); }

	//-----------------------------------------------------------------------
	bool GESetLightParameters(const DirLight* dirLights, const UINT dirStar, const UINT dirNum) { return g_shaderClass->SetLightParameters(dirLights, dirStar, dirNum); }

	//-----------------------------------------------------------------------
	bool GESetPerFrameParameters(const MATRIX& viewInv, const FLOAT3& eyePos, const FLOAT deltaTime) { return g_shaderClass->SetPerFrameParameters(viewInv, eyePos, deltaTime); }

	//-----------------------------------------------------------------------
	bool GERender(ColorMesh& mesh) { return g_shaderClass->Render(mesh); }

	//-----------------------------------------------------------------------
	bool GERender(CubeMapMesh& mesh) { return g_shaderClass->Render(mesh); }

	//-----------------------------------------------------------------------
	bool GERender(TexMesh_File& mesh) { return g_shaderClass->Render(mesh); }

	//-----------------------------------------------------------------------
	bool GERender(MazeMesh& mesh) { return g_shaderClass->Render(mesh); }

	//-----------------------------------------------------------------------
	bool GERender(QuadMesh& mesh) { return g_shaderClass->Render(mesh); }
	//-----------------------------------------------------------------------
}