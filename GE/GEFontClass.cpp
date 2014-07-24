#include "GEFontClass.h"

//#include <stdarg.h>
#include <fstream>
#include <vector>

namespace GE
{
	FontClass *g_fontClass;

	//-----------------------------------------------------------------------
	bool FontClass::Initialize()
	{
		if (!LoadFontData())
			return false;

		if (FAILED(D3DX11CreateShaderResourceViewFromFile(m_device, L"Font/font.dds", 0, 0, &m_fontTex, 0)))
			return 0;

		HRESULT result;
		ID3D10Blob *errorMessage;
		ID3D10Blob *vertexShaderBuffer;
		ID3D10Blob *pixelShaderBuffer;

		result = D3DX11CompileFromFile(L"Shader/FontShader.fx", NULL, NULL, "FontVS", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &vertexShaderBuffer, &errorMessage, NULL);
		if (FAILED(result))
		{
			if (errorMessage)
			{
				MessageBoxA(NULL, (char*)errorMessage->GetBufferPointer(), "ShaderCompileError", MB_YESNO);
				errorMessage->Release();
				errorMessage = 0;
			}
			else
				MessageBox(NULL, L"CompileShader´íÎó!", L"´íÎó", MB_OK);
			return FALSE;
		}
		result = D3DX11CompileFromFile(L"Shader/FontShader.fx", NULL, NULL, "FontPS", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL, &pixelShaderBuffer, &errorMessage, NULL);
		if (FAILED(result))
		{
			if (errorMessage)
			{
				MessageBoxA(NULL, (char*)errorMessage->GetBufferPointer(), "ShaderCompileError", MB_YESNO);
				errorMessage->Release();
				errorMessage = 0;
			}
			else
				MessageBox(NULL, L"CompileShader´íÎó!", L"´íÎó", MB_OK);
			return FALSE;
		}
		result = m_device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_fontVS);
		if (FAILED(result))
			return false;
		result = m_device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_fontPS);
		if (FAILED(result))
			return false;
		D3D11_INPUT_ELEMENT_DESC fontInputDesc[2] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		result = m_device->CreateInputLayout(fontInputDesc, 2, vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), &m_fontIL);
		if (FAILED(result))
			return false;
		SAFE_RELEASE(vertexShaderBuffer);
		SAFE_RELEASE(pixelShaderBuffer);

		D3D11_BUFFER_DESC bufferDesc;
		bufferDesc.ByteWidth = sizeof(FontBuffer);
		bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		bufferDesc.MiscFlags = 0;
		bufferDesc.StructureByteStride = 0;
		result = m_device->CreateBuffer(&bufferDesc, NULL, &m_fontBuffer);
		if (FAILED(result))
			return false;

		return true;

	}

	//-----------------------------------------------------------------------
	void FontClass::Shutdown()
	{
	}

	//-----------------------------------------------------------------------
	bool FontClass::SetFontParameters(const FLOAT4& _fontColor)
	{
		HRESULT result;
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		FontBuffer* dataPtr;

		result = m_deviceContext->Map(m_fontBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
		if (FAILED(result))
			return false;
		dataPtr = (FontBuffer*)mappedResource.pData;
		dataPtr->fontColor = _fontColor;
		m_deviceContext->Unmap(m_fontBuffer, 0);

		m_deviceContext->PSSetConstantBuffers(7, 1, &m_fontBuffer);
		return true;
	}

	//-----------------------------------------------------------------------
	bool FontClass::LoadFontData()
	{
		std::ifstream fin;

		m_fontData = new FontData[95];
		if (!m_fontData)
		{
			return false;
		}

		fin.open("Font/fontdata.txt");
		if (fin.fail())
		{
			return false;
		}

		char temp;
		for (int i = 0; i<95; i++)
		{
			fin.get(temp);
			while (temp != ' ')
			{
				fin.get(temp);
			}
			fin.get(temp);
			while (temp != ' ')
			{
				fin.get(temp);
			}

			fin >> m_fontData[i].left;
			fin >> m_fontData[i].right;
			fin >> m_fontData[i].size;
		}

		fin.close();
		return true;
	}
	
	//-----------------------------------------------------------------------
	bool FontClass::Print(FLOAT _posX, FLOAT _posY, const FLOAT4& _color, const char* _info)
	{
		float fontPosX = (_posX / (float)m_width) * 2.0f - 1.0f;
		float fontPosY = 1.0f - (_posY / (float)m_height) * 2.0f;
		float deltaX = 2.0f / (float)m_width;
		float deltaY = -32.0f / (float)m_height;
		float fontWidth = 0.0f;
		float fontHeight = fontPosY + deltaY;


		int length = (int)strlen(_info);

		std::vector<FontVertex> vertices(6 * length);

		int index(0), letter(0);
		for (int i = 0; _info[i] != '\0'; ++i)
		{
			letter = ((int)_info[i]) - 32;
			if (letter == 0)
			{
				fontPosX = fontPosX + 3 * deltaX;
			}
			else
			{
				fontWidth = fontPosX + m_fontData[letter].size * deltaX;

				vertices[index].pos = FLOAT3(fontPosX, fontPosY, 0.0f);
				vertices[index].tex = FLOAT2(m_fontData[letter].left, 0.0f);
				index++;
				vertices[index].pos = FLOAT3(fontWidth, fontHeight, 0.0f);
				vertices[index].tex = FLOAT2(m_fontData[letter].right, 1.0f);
				index++;
				vertices[index].pos = FLOAT3(fontPosX, fontHeight, 0.0f);
				vertices[index].tex = FLOAT2(m_fontData[letter].left, 1.0f);
				index++;

				vertices[index].pos = FLOAT3(fontPosX, fontPosY, 0.0f);
				vertices[index].tex = FLOAT2(m_fontData[letter].left, 0.0f);
				index++;
				vertices[index].pos = FLOAT3(fontWidth, fontPosY, 0.0f);
				vertices[index].tex = FLOAT2(m_fontData[letter].right, 0.0f);
				index++;
				vertices[index].pos = FLOAT3(fontWidth, fontHeight, 0.0f);
				vertices[index].tex = FLOAT2(m_fontData[letter].right, 1.0f);
				index++;

				fontPosX = fontPosX + m_fontData[letter].size * deltaX + deltaX;
			}
		}

		ID3D11Buffer *fontVB;

		D3D11_BUFFER_DESC vbDesc = { 0 };
		vbDesc.ByteWidth = sizeof(FontVertex) * vertices.size();
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = &vertices[0];
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if (FAILED(m_device->CreateBuffer(&vbDesc, &vbData, &fontVB)))
		{
			MessageBox(NULL, L"CreateVertexBuffer failed!", L"Error", MB_OK);
			return false;
		}

		SetFontParameters(_color);
		m_deviceContext->PSSetShaderResources(0, 1, &m_fontTex);

		m_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_deviceContext->IASetInputLayout(m_fontIL);
		UINT stride = sizeof(FontVertex);
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &fontVB, &stride, &offset);
		m_deviceContext->IASetIndexBuffer(NULL, DXGI_FORMAT_R32_UINT, 0);
		m_deviceContext->VSSetShader(m_fontVS, NULL, 0);
		m_deviceContext->PSSetShader(m_fontPS, NULL, 0);

		m_deviceContext->Draw(vertices.size(), 0);

		SAFE_RELEASE(fontVB);
		return true;
	}

	//-----------------------------------------------------------------------
	bool FontClass::Printv(FLOAT _posX, FLOAT _posY, const FLOAT4& _color, const char* _info, ...)
	{
		bool flag = false;
		va_list arg_ptr;
		va_start(arg_ptr, _info);
		for (int i = 0; _info[i] != '\0'; ++i)
		{
			if (flag)
			{
				switch (_info[i])
				{
				case 'd':
					//cout << va_arg(arg_ptr, int);
					flag = false;
					break;
				case 's':
					//cout << va_arg(arg_ptr, char*);
					flag = false;
					break;
				case '%':
					//cout << '%';
					break;
				default:;
					//cout << '%' << _info[i];
				}
			}
			else
			{
				switch (_info[i])
				{
				case '%':
					flag = true;
					break;
				default:;
					//cout << _info[i];
				}
			}
		}
		va_end(arg_ptr);

		return true;
	}

	//-----------------------------------------------------------------------
	bool GEPrint(FLOAT _posX, FLOAT _posY, const FLOAT4& _color, const char* _info)
	{
		return g_fontClass->Print(_posX, _posY, _color, _info);
	}

	//-----------------------------------------------------------------------
#define GEPrintv(_posX, _posY, _color, _info, ...) g_fontClass->printv(_posX, _posY, _color, _info, ...)
}