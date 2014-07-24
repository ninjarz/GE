#include "GEMesh.h"

#include <vector>
#include <iostream>
#include <fstream>
#include "GEColor.h"

namespace GE
{
	//-----------------------------------------------------------------------
	bool GECreateBox(FLOAT width, FLOAT height, FLOAT depth, ColorMesh &mesh)
	{
		ColorVertex vertices[24];
		UINT indices[36];

		FLOAT halfW = width * 0.5f;
		FLOAT halfH = height * 0.5f;
		FLOAT halfD = depth * 0.5f;

		vertices[0].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[0].color = GE_COLORS[1];
		vertices[1].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[1].color = GE_COLORS[2];
		vertices[2].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[2].color = GE_COLORS[3];
		vertices[3].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[3].color = GE_COLORS[4];

		vertices[4].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[4].color = GE_COLORS[5];
		vertices[5].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[5].color = GE_COLORS[6];
		vertices[6].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[6].color = GE_COLORS[2];
		vertices[7].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[7].color = GE_COLORS[1];

		vertices[8].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[8].color = GE_COLORS[7];
		vertices[9].pos = FLOAT3(halfW,halfH,halfD);
		vertices[9].color = GE_COLORS[8];
		vertices[10].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[10].color = GE_COLORS[6];
		vertices[11].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[11].color = GE_COLORS[5];

		vertices[12].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[12].color = GE_COLORS[4];
		vertices[13].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[13].color = GE_COLORS[3];
		vertices[14].pos = FLOAT3(halfW,halfH,halfD);
		vertices[14].color = GE_COLORS[8];
		vertices[15].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[15].color = GE_COLORS[7];

		vertices[16].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[16].color = GE_COLORS[2];
		vertices[17].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[17].color = GE_COLORS[6];
		vertices[18].pos = FLOAT3(halfW,halfH,halfD);
		vertices[18].color = GE_COLORS[8];
		vertices[19].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[19].color = GE_COLORS[3];

		vertices[20].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[20].color = GE_COLORS[5];
		vertices[21].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[21].color = GE_COLORS[1];
		vertices[22].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[22].color = GE_COLORS[4];
		vertices[23].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[23].color = GE_COLORS[7];

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 0;
		indices[4] = 2;
		indices[5] = 3;

		indices[6] = 4;
		indices[7] = 5;
		indices[8] = 6;
		indices[9] = 4;
		indices[10] = 6;
		indices[11] = 7;

		indices[12] = 8;
		indices[13] = 9;
		indices[14] = 10;
		indices[15] = 8;
		indices[16] = 10;
		indices[17] = 11;

		indices[18] = 12;
		indices[19] = 13;
		indices[20] = 14;
		indices[21] = 12;
		indices[22] = 14;
		indices[23] = 15;

		indices[24] = 16;
		indices[25] = 17;
		indices[26] = 18;
		indices[27] = 16;
		indices[28] = 18;
		indices[29] = 19;

		indices[30] = 20;
		indices[31] = 21;
		indices[32] = 22;
		indices[33] = 20;
		indices[34] = 22;
		indices[35] = 23;

		ID3D11Device *device = g_GEClass->GetDevice();

		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(ColorVertex) * 24;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = vertices;
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &mesh.colorVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		D3D11_BUFFER_DESC ibDesc = {0};
		ibDesc.ByteWidth = sizeof(UINT) * 36;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;
		ibDesc.StructureByteStride = 0;
		ibDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA ibData;
		ibData.pSysMem = indices;
		ibData.SysMemPitch = 0;
		ibData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&ibDesc, &ibData, &mesh.colorIB)))
		{
			MessageBox(NULL,L"CreateIndexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		mesh.indexCount = 36;

		mesh.worldMatrix = MATRIX::IDENTITY;

		return true;
	}

	//-----------------------------------------------------------------------
	bool GECreateBox(FLOAT width, FLOAT height, FLOAT depth, const FLOAT4& color, ColorMesh &mesh)
	{
		ColorVertex vertices[24];
		UINT indices[36];

		FLOAT halfW = width * 0.5f;
		FLOAT halfH = height * 0.5f;
		FLOAT halfD = depth * 0.5f;

		vertices[0].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[0].color = color;
		vertices[1].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[1].color = color;
		vertices[2].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[2].color = color;
		vertices[3].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[3].color = color;

		vertices[4].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[4].color = color;
		vertices[5].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[5].color = color;
		vertices[6].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[6].color = color;
		vertices[7].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[7].color = color;

		vertices[8].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[8].color = color;
		vertices[9].pos = FLOAT3(halfW,halfH,halfD);
		vertices[9].color = color;
		vertices[10].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[10].color = color;
		vertices[11].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[11].color = color;

		vertices[12].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[12].color = color;
		vertices[13].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[13].color = color;
		vertices[14].pos = FLOAT3(halfW,halfH,halfD);
		vertices[14].color = color;
		vertices[15].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[15].color = color;

		vertices[16].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[16].color = color;
		vertices[17].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[17].color = color;
		vertices[18].pos = FLOAT3(halfW,halfH,halfD);
		vertices[18].color = color;
		vertices[19].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[19].color = color;

		vertices[20].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[20].color = color;
		vertices[21].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[21].color = color;
		vertices[22].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[22].color = color;
		vertices[23].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[23].color = color;

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 0;
		indices[4] = 2;
		indices[5] = 3;

		indices[6] = 4;
		indices[7] = 5;
		indices[8] = 6;
		indices[9] = 4;
		indices[10] = 6;
		indices[11] = 7;

		indices[12] = 8;
		indices[13] = 9;
		indices[14] = 10;
		indices[15] = 8;
		indices[16] = 10;
		indices[17] = 11;

		indices[18] = 12;
		indices[19] = 13;
		indices[20] = 14;
		indices[21] = 12;
		indices[22] = 14;
		indices[23] = 15;

		indices[24] = 16;
		indices[25] = 17;
		indices[26] = 18;
		indices[27] = 16;
		indices[28] = 18;
		indices[29] = 19;

		indices[30] = 20;
		indices[31] = 21;
		indices[32] = 22;
		indices[33] = 20;
		indices[34] = 22;
		indices[35] = 23;

		ID3D11Device *device = g_GEClass->GetDevice();

		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(ColorVertex) * 24;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = vertices;
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &mesh.colorVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		D3D11_BUFFER_DESC ibDesc = {0};
		ibDesc.ByteWidth = sizeof(UINT) * 36;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;
		ibDesc.StructureByteStride = 0;
		ibDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA ibData;
		ibData.pSysMem = indices;
		ibData.SysMemPitch = 0;
		ibData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&ibDesc, &ibData, &mesh.colorIB)))
		{
			MessageBox(NULL,L"CreateIndexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		mesh.indexCount = 36;

		mesh.worldMatrix = MATRIX::IDENTITY;

		return true;
	}

	//-----------------------------------------------------------------------
	bool GECreateBox(FLOAT width, FLOAT height, FLOAT depth, LightMesh& mesh)
	{
		LightVertex vertices[24];
		UINT indices[36];

		FLOAT halfW = width * 0.5f;
		FLOAT halfH = height * 0.5f;
		FLOAT halfD = depth * 0.5f;

		vertices[0].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[0].normal = FLOAT3(0.f,0.f,-1.f);
		vertices[1].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[1].normal = FLOAT3(0.f,0.f,-1.f);
		vertices[2].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[2].normal = FLOAT3(0.f,0.f,-1.f);
		vertices[3].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[3].normal = FLOAT3(0.f,0.f,-1.f);

		vertices[4].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[4].normal = FLOAT3(-1.f,0.f,0.f);
		vertices[5].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[5].normal = FLOAT3(-1.f,0.f,0.f);
		vertices[6].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[6].normal = FLOAT3(-1.f,0.f,0.f);
		vertices[7].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[7].normal = FLOAT3(-1.f,0.f,0.f);

		vertices[8].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[8].normal = FLOAT3(0.f,0.f,1.f);
		vertices[9].pos = FLOAT3(halfW,halfH,halfD);
		vertices[9].normal = FLOAT3(0.f,0.f,1.f);
		vertices[10].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[10].normal = FLOAT3(0.f,0.f,1.f);
		vertices[11].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[11].normal = FLOAT3(0.f,0.f,1.f);

		vertices[12].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[12].normal = FLOAT3(1.f,0.f,0.f);
		vertices[13].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[13].normal = FLOAT3(1.f,0.f,0.f);
		vertices[14].pos = FLOAT3(halfW,halfH,halfD);
		vertices[14].normal = FLOAT3(1.f,0.f,0.f);
		vertices[15].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[15].normal = FLOAT3(1.f,0.f,0.f);

		vertices[16].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[16].normal = FLOAT3(0.f,1.f,0.f);
		vertices[17].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[17].normal = FLOAT3(0.f,1.f,0.f);
		vertices[18].pos = FLOAT3(halfW,halfH,halfD);
		vertices[18].normal = FLOAT3(0.f,1.f,0.f);
		vertices[19].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[19].normal = FLOAT3(0.f,1.f,0.f);

		vertices[20].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[20].normal = FLOAT3(0.f,-1.f,0.f);
		vertices[21].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[21].normal = FLOAT3(0.f,-1.f,0.f);
		vertices[22].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[22].normal = FLOAT3(0.f,-1.f,0.f);
		vertices[23].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[23].normal = FLOAT3(0.f,-1.f,0.f);

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 0;
		indices[4] = 2;
		indices[5] = 3;

		indices[6] = 4;
		indices[7] = 5;
		indices[8] = 6;
		indices[9] = 4;
		indices[10] = 6;
		indices[11] = 7;

		indices[12] = 8;
		indices[13] = 9;
		indices[14] = 10;
		indices[15] = 8;
		indices[16] = 10;
		indices[17] = 11;

		indices[18] = 12;
		indices[19] = 13;
		indices[20] = 14;
		indices[21] = 12;
		indices[22] = 14;
		indices[23] = 15;

		indices[24] = 16;
		indices[25] = 17;
		indices[26] = 18;
		indices[27] = 16;
		indices[28] = 18;
		indices[29] = 19;

		indices[30] = 20;
		indices[31] = 21;
		indices[32] = 22;
		indices[33] = 20;
		indices[34] = 22;
		indices[35] = 23;

		ID3D11Device *device = g_GEClass->GetDevice();

		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(LightVertex) * 24;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = vertices;
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &mesh.lightVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		D3D11_BUFFER_DESC ibDesc = {0};
		ibDesc.ByteWidth = sizeof(UINT) * 36;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;
		ibDesc.StructureByteStride = 0;
		ibDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA ibData;
		ibData.pSysMem = indices;
		ibData.SysMemPitch = 0;
		ibData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&ibDesc, &ibData, &mesh.lightIB)))
		{
			MessageBox(NULL,L"CreateIndexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		mesh.indexCount = 36;

		mesh.worldMatrix = MATRIX::IDENTITY;

		return true;
	}

	//-----------------------------------------------------------------------
	bool GECreateBox(FLOAT width, FLOAT height, FLOAT depth, ID3D11ShaderResourceView* tex, TexMesh& mesh)
	{
		TexVertex vertices[24];
		UINT indices[36];

		FLOAT halfW = width * 0.5f;
		FLOAT halfH = height * 0.5f;
		FLOAT halfD = depth * 0.5f;

		vertices[0].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[0].normal = FLOAT3(0.f,0.f,-1.f);
		vertices[0].tex = FLOAT2(0.f,1.f);
		vertices[1].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[1].normal = FLOAT3(0.f,0.f,-1.f);
		vertices[1].tex = FLOAT2(0.f,0.f);
		vertices[2].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[2].normal = FLOAT3(0.f,0.f,-1.f);
		vertices[2].tex = FLOAT2(1.f,0.f);
		vertices[3].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[3].normal = FLOAT3(0.f,0.f,-1.f);
		vertices[3].tex = FLOAT2(1.f,1.f);

		vertices[4].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[4].normal = FLOAT3(-1.f,0.f,0.f);
		vertices[4].tex = FLOAT2(0.f,1.f);
		vertices[5].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[5].normal = FLOAT3(-1.f,0.f,0.f);
		vertices[5].tex = FLOAT2(0.f,0.f);
		vertices[6].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[6].normal = FLOAT3(-1.f,0.f,0.f);
		vertices[6].tex = FLOAT2(1.f,0.f);
		vertices[7].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[7].normal = FLOAT3(-1.f,0.f,0.f);
		vertices[7].tex = FLOAT2(1.f,1.f);

		vertices[8].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[8].normal = FLOAT3(0.f,0.f,1.f);
		vertices[8].tex = FLOAT2(0.f,1.f);
		vertices[9].pos = FLOAT3(halfW,halfH,halfD);
		vertices[9].normal = FLOAT3(0.f,0.f,1.f);
		vertices[9].tex = FLOAT2(0.f,0.f);
		vertices[10].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[10].normal = FLOAT3(0.f,0.f,1.f);
		vertices[10].tex = FLOAT2(1.f,0.f);
		vertices[11].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[11].normal = FLOAT3(0.f,0.f,1.f);
		vertices[11].tex = FLOAT2(1.f,1.f);

		vertices[12].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[12].normal = FLOAT3(1.f,0.f,0.f);
		vertices[12].tex = FLOAT2(0.f,1.f);
		vertices[13].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[13].normal = FLOAT3(1.f,0.f,0.f);
		vertices[13].tex = FLOAT2(0.f,0.f);
		vertices[14].pos = FLOAT3(halfW,halfH,halfD);
		vertices[14].normal = FLOAT3(1.f,0.f,0.f);
		vertices[14].tex = FLOAT2(1.f,0.f);
		vertices[15].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[15].normal = FLOAT3(1.f,0.f,0.f);
		vertices[15].tex = FLOAT2(1.f,1.f);

		vertices[16].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[16].normal = FLOAT3(0.f,1.f,0.f);
		vertices[16].tex = FLOAT2(0.f,1.f);
		vertices[17].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[17].normal = FLOAT3(0.f,1.f,0.f);
		vertices[17].tex = FLOAT2(0.f,0.f);
		vertices[18].pos = FLOAT3(halfW,halfH,halfD);
		vertices[18].normal = FLOAT3(0.f,1.f,0.f);
		vertices[18].tex = FLOAT2(1.f,0.f);
		vertices[19].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[19].normal = FLOAT3(0.f,1.f,0.f);
		vertices[19].tex = FLOAT2(1.f,1.f);

		vertices[20].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[20].normal = FLOAT3(0.f,-1.f,0.f);
		vertices[20].tex = FLOAT2(0.f,1.f);
		vertices[21].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[21].normal = FLOAT3(0.f,-1.f,0.f);
		vertices[21].tex = FLOAT2(0.f,0.f);
		vertices[22].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[22].normal = FLOAT3(0.f,-1.f,0.f);
		vertices[22].tex = FLOAT2(1.f,0.f);
		vertices[23].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[23].normal = FLOAT3(0.f,-1.f,0.f);
		vertices[23].tex = FLOAT2(1.f,1.f);

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 0;
		indices[4] = 2;
		indices[5] = 3;

		indices[6] = 4;
		indices[7] = 5;
		indices[8] = 6;
		indices[9] = 4;
		indices[10] = 6;
		indices[11] = 7;

		indices[12] = 8;
		indices[13] = 9;
		indices[14] = 10;
		indices[15] = 8;
		indices[16] = 10;
		indices[17] = 11;

		indices[18] = 12;
		indices[19] = 13;
		indices[20] = 14;
		indices[21] = 12;
		indices[22] = 14;
		indices[23] = 15;

		indices[24] = 16;
		indices[25] = 17;
		indices[26] = 18;
		indices[27] = 16;
		indices[28] = 18;
		indices[29] = 19;

		indices[30] = 20;
		indices[31] = 21;
		indices[32] = 22;
		indices[33] = 20;
		indices[34] = 22;
		indices[35] = 23;

		ID3D11Device *device = g_GEClass->GetDevice();

		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(TexVertex) * 24;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = vertices;
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &mesh.texVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		D3D11_BUFFER_DESC ibDesc = {0};
		ibDesc.ByteWidth = sizeof(UINT) * 36;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;
		ibDesc.StructureByteStride = 0;
		ibDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA ibData;
		ibData.pSysMem = indices;
		ibData.SysMemPitch = 0;
		ibData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&ibDesc, &ibData, &mesh.texIB)))
		{
			MessageBox(NULL,L"CreateIndexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		mesh.indexCount = 36;

		mesh.worldMatrix = MATRIX::IDENTITY;

		mesh.tex = tex;

		return true;
	}

	//-----------------------------------------------------------------------
	bool GECreateBox(FLOAT width, FLOAT height, FLOAT depth, ID3D11ShaderResourceView* tex, CubeMapMesh& mesh)
	{
		CubeMapVertex vertices[24];
		UINT indices[36];

		FLOAT halfW = width * 0.5f;
		FLOAT halfH = height * 0.5f;
		FLOAT halfD = depth * 0.5f;

		vertices[0].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[1].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[2].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[3].pos = FLOAT3(halfW,-halfH,-halfD);

		vertices[4].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[5].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[6].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[7].pos = FLOAT3(-halfW,-halfH,-halfD);

		vertices[8].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[9].pos = FLOAT3(halfW,halfH,halfD);
		vertices[10].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[11].pos = FLOAT3(-halfW,-halfH,halfD);

		vertices[12].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[13].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[14].pos = FLOAT3(halfW,halfH,halfD);
		vertices[15].pos = FLOAT3(halfW,-halfH,halfD);

		vertices[16].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[17].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[18].pos = FLOAT3(halfW,halfH,halfD);
		vertices[19].pos = FLOAT3(halfW,halfH,-halfD);

		vertices[20].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[21].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[22].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[23].pos = FLOAT3(halfW,-halfH,halfD);

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 0;
		indices[4] = 2;
		indices[5] = 3;

		indices[6] = 4;
		indices[7] = 5;
		indices[8] = 6;
		indices[9] = 4;
		indices[10] = 6;
		indices[11] = 7;

		indices[12] = 8;
		indices[13] = 9;
		indices[14] = 10;
		indices[15] = 8;
		indices[16] = 10;
		indices[17] = 11;

		indices[18] = 12;
		indices[19] = 13;
		indices[20] = 14;
		indices[21] = 12;
		indices[22] = 14;
		indices[23] = 15;

		indices[24] = 16;
		indices[25] = 17;
		indices[26] = 18;
		indices[27] = 16;
		indices[28] = 18;
		indices[29] = 19;

		indices[30] = 20;
		indices[31] = 21;
		indices[32] = 22;
		indices[33] = 20;
		indices[34] = 22;
		indices[35] = 23;

		ID3D11Device *device = g_GEClass->GetDevice();

		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(TexVertex) * 24;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = vertices;
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &mesh.cubeMapVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		D3D11_BUFFER_DESC ibDesc = {0};
		ibDesc.ByteWidth = sizeof(UINT) * 36;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;
		ibDesc.StructureByteStride = 0;
		ibDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA ibData;
		ibData.pSysMem = indices;
		ibData.SysMemPitch = 0;
		ibData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&ibDesc, &ibData, &mesh.cubeMapIB)))
		{
			MessageBox(NULL,L"CreateIndexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		mesh.indexCount = 36;

		mesh.tex = tex;

		return true;
	}

	//-----------------------------------------------------------------------
	bool GECreateSphere(FLOAT radius, int slice, int stack, const FLOAT4& color, ColorMesh& mesh)
	{
		int vertsPerRow = slice + 1;
		int rowCount = stack - 1;

		int vertexCount = vertsPerRow * rowCount + 2;
		int indexCount = (rowCount-1)*slice*6 + slice * 6;

		std::vector<ColorVertex> vertices(vertexCount);
		std::vector<UINT> indices(indexCount);

		for(int i=1; i<=rowCount; ++i)
		{
			float phy = GE_PI * i / stack;
			float tmpRadius = radius * sin(phy);
			for(int j=0; j<vertsPerRow; ++j)
			{
				float theta = GE_2PI * j / slice;
				UINT index = (i-1)*vertsPerRow+j;

				float x = tmpRadius*cos(theta);
				float y = radius*cos(phy);
				float z = tmpRadius*sin(theta);

				vertices[index].pos = FLOAT3(x,y,z);
				vertices[index].color = color;
			}
		}
		int size = vertsPerRow * rowCount;
		vertices[size].pos = FLOAT3(0.f,radius,0.f);
		vertices[size].color = color;
		vertices[size+1].pos = FLOAT3(0.f,-radius,0.f);
		vertices[size+1].color = color;

		UINT tmp(0);
		int start1 = 0;
		int start2 = vertices.size() - vertsPerRow - 2;
		int top = size;
		int bottom = size + 1;
		for(int i=0; i<slice; ++i)
		{
			indices[tmp] = top;
			indices[tmp+1] = start1+i+1;
			indices[tmp+2] = start1+i;

			tmp += 3;
		}

		for(int i=0; i<slice; ++i)
		{
			indices[tmp] = bottom;
			indices[tmp+1] = start2 + i;
			indices[tmp+2] = start2 + i + 1;

			tmp += 3;
		}

		for(int i=0; i<rowCount-1; ++i)
		{
			for(int j=0; j<slice; ++j)
			{
				indices[tmp] = i * vertsPerRow + j;
				indices[tmp+1] = (i + 1) * vertsPerRow + j + 1;
				indices[tmp+2] = (i + 1) * vertsPerRow + j;
				indices[tmp+3] = i * vertsPerRow + j;
				indices[tmp+4] = i * vertsPerRow + j + 1;
				indices[tmp+5] = (i + 1) * vertsPerRow + j + 1;

				tmp += 6;
			}
		}

		ID3D11Device *device = g_GEClass->GetDevice();

		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(TexVertex) * vertexCount;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = &vertices[0];
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &mesh.colorVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		D3D11_BUFFER_DESC ibDesc = {0};
		ibDesc.ByteWidth = sizeof(UINT) * indexCount;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;
		ibDesc.StructureByteStride = 0;
		ibDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA ibData;
		ibData.pSysMem = &indices[0];
		ibData.SysMemPitch = 0;
		ibData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&ibDesc, &ibData, &mesh.colorIB)))
		{
			MessageBox(NULL,L"CreateIndexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		mesh.indexCount = indexCount;

		mesh.worldMatrix = MATRIX::IDENTITY;

		return true;
	}

	//-----------------------------------------------------------------------
	bool GECreateSphere(FLOAT radius, int slice, int stack, ID3D11ShaderResourceView* tex, CubeMapMesh& mesh)
	{
		int vertsPerRow = slice + 1;
		int rowCount = stack - 1;

		int vertexCount = vertsPerRow * rowCount + 2;
		int indexCount = (rowCount-1)*slice*6 + slice * 6;

		std::vector<CubeMapVertex> vertices(vertexCount);
		std::vector<UINT> indices(indexCount);

		for(int i=1; i<=rowCount; ++i)
		{
			float phy = GE_PI * i / stack;
			float tmpRadius = radius * sin(phy);
			for(int j=0; j<vertsPerRow; ++j)
			{
				float theta = GE_2PI * j / slice;
				UINT index = (i-1)*vertsPerRow+j;

				float x = tmpRadius*cos(theta);
				float y = radius*cos(phy);
				float z = tmpRadius*sin(theta);

				vertices[index].pos = FLOAT3(x,y,z);
			}
		}
		int size = vertsPerRow * rowCount;
		vertices[size].pos = FLOAT3(0.f,radius,0.f);
		vertices[size+1].pos = FLOAT3(0.f,-radius,0.f);

		UINT tmp(0);
		int start1 = 0;
		int start2 = vertices.size() - vertsPerRow - 2;
		int top = size;
		int bottom = size + 1;
		for(int i=0; i<slice; ++i)
		{
			indices[tmp] = top;
			indices[tmp+1] = start1+i+1;
			indices[tmp+2] = start1+i;

			tmp += 3;
		}

		for(int i=0; i<slice; ++i)
		{
			indices[tmp] = bottom;
			indices[tmp+1] = start2 + i;
			indices[tmp+2] = start2 + i + 1;

			tmp += 3;
		}

		for(int i=0; i<rowCount-1; ++i)
		{
			for(int j=0; j<slice; ++j)
			{
				indices[tmp] = i * vertsPerRow + j;
				indices[tmp+1] = (i + 1) * vertsPerRow + j + 1;
				indices[tmp+2] = (i + 1) * vertsPerRow + j;
				indices[tmp+3] = i * vertsPerRow + j;
				indices[tmp+4] = i * vertsPerRow + j + 1;
				indices[tmp+5] = (i + 1) * vertsPerRow + j + 1;

				tmp += 6;
			}
		}

		ID3D11Device *device = g_GEClass->GetDevice();

		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(TexVertex) * vertexCount;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = &vertices[0];
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &mesh.cubeMapVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		D3D11_BUFFER_DESC ibDesc = {0};
		ibDesc.ByteWidth = sizeof(UINT) * indexCount;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;
		ibDesc.StructureByteStride = 0;
		ibDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA ibData;
		ibData.pSysMem = &indices[0];
		ibData.SysMemPitch = 0;
		ibData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&ibDesc, &ibData, &mesh.cubeMapIB)))
		{
			MessageBox(NULL,L"CreateIndexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		mesh.indexCount = indexCount;

		mesh.tex = tex;

		return true;
	}

	//-----------------------------------------------------------------------
	bool GELoadMeshFromFile(LPCWSTR fileName, ID3D11ShaderResourceView* tex, TexMesh_File &mesh)
	{
		std::ifstream fin;
		fin.open( fileName );
		if( fin.fail() )
			return false;

		char temp;
		fin.get(temp);
		while(temp != ':')
		{
			fin.get(temp);
		}

		UINT vertexCount;
		fin >> vertexCount;
		std::vector<TexVertex> vertices(vertexCount);

		for(UINT i = 0; i < vertexCount; ++i)
		{
			fin.get(temp);
			fin >> vertices[i].pos.x
				>> vertices[i].pos.y
				>> vertices[i].pos.z
				>> vertices[i].tex.x
				>> vertices[i].tex.y
				>> vertices[i].normal.x
				>> vertices[i].normal.y
				>> vertices[i].normal.z;
		}

		fin.close();

		ID3D11Device *device = g_GEClass->GetDevice();

		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(TexVertex) * vertexCount;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = &vertices[0];
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &mesh.texVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		mesh.vertexCount = vertexCount;

		mesh.worldMatrix = MATRIX::IDENTITY;

		mesh.tex = tex;

		return true;
	}

	//-----------------------------------------------------------------------
	bool GECreateSnow(const FLOAT3& centre, FLOAT radius, FLOAT height, UINT count, ID3D11ShaderResourceView* tex, SnowMesh& mesh)
	{
		ID3D11Device *device = g_GEClass->GetDevice();

		std::vector<SnowVertex> vertices(count);
		for(UINT i = 0; i<count; ++i)
			vertices[i].color = GE_COLORS[rand()%7+2];
		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(SnowVertex) * count;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;
		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = &vertices[0];
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;
		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &mesh.snowVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		mesh.vertexCount = count;

		mesh.tex = tex;

		std::vector<SnowInfo> snowInfo(count);
		for(UINT i = 0; i < count; ++i)
		{
			snowInfo[i].pos = FLOAT3(centre.x-radius+(float)(rand()*1.0/RAND_MAX*2*radius), centre.y-(float)(rand()*1.0/RAND_MAX*height), centre.z-radius+(float)(rand()*1.0/RAND_MAX*2*radius));
			snowInfo[i].velocity = FLOAT3(0.0f, -(float)(rand()*1.0/RAND_MAX * 30.0f) - 10.0f, 0.0f);
		}
		ID3D11Buffer *snowBuffer;
		D3D11_BUFFER_DESC bufDesc = {0};
		bufDesc.ByteWidth = sizeof(SnowInfo) * count;
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
		bufDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
		bufDesc.CPUAccessFlags = 0;
		bufDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bufDesc.StructureByteStride = sizeof(SnowInfo);
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &snowInfo[0];
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;
		device->CreateBuffer(&bufDesc, &initData, &snowBuffer);
		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
		SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		SRVDesc.Buffer.FirstElement = 0;
		SRVDesc.Buffer.NumElements = count;
		device->CreateShaderResourceView(snowBuffer, &SRVDesc, &mesh.snowSRV);
		D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc;
		UAVDesc.Format = DXGI_FORMAT_UNKNOWN;
		UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		UAVDesc.Buffer.FirstElement = 0;
		UAVDesc.Buffer.NumElements =  count;
		UAVDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_COUNTER;
		device->CreateUnorderedAccessView(snowBuffer, &UAVDesc, &mesh.snowUAV);
		SAFE_RELEASE(snowBuffer);

		return true;
	}

	//-----------------------------------------------------------------------
	bool GECreateSnow(const FLOAT3& centre, FLOAT radius, FLOAT height, UINT count, const FLOAT4& color, ID3D11ShaderResourceView* tex, SnowMesh& mesh)
	{
		ID3D11Device *device = g_GEClass->GetDevice();

		std::vector<SnowVertex> vertices(count);
		for(UINT i = 0; i<count; ++i)
			vertices[i].color = color;
		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(SnowVertex) * count;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;
		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = &vertices[0];
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;
		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &mesh.snowVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		mesh.vertexCount = count;

		mesh.tex = tex;

		std::vector<SnowInfo> snowInfo(count);
		for(UINT i = 0; i < count; ++i)
		{
			snowInfo[i].pos = FLOAT3(centre.x-radius+(float)(rand()*1.0/RAND_MAX*2*radius), centre.y-(float)(rand()*1.0/RAND_MAX*height), centre.z-radius+(float)(rand()*1.0/RAND_MAX*2*radius));
			snowInfo[i].velocity = FLOAT3(0.0f, -(float)(rand()*1.0/RAND_MAX * 30.0f) - 10.0f, 0.0f);
		}
		ID3D11Buffer *snowBuffer;
		D3D11_BUFFER_DESC bufDesc = {0};
		bufDesc.ByteWidth = sizeof(SnowInfo) * count;
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
		bufDesc.BindFlags = D3D11_BIND_UNORDERED_ACCESS | D3D11_BIND_SHADER_RESOURCE;
		bufDesc.CPUAccessFlags = 0;
		bufDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		bufDesc.StructureByteStride = sizeof(SnowInfo);
		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &snowInfo[0];
		initData.SysMemPitch = 0;
		initData.SysMemSlicePitch = 0;
		device->CreateBuffer(&bufDesc, &initData, &snowBuffer);
		D3D11_SHADER_RESOURCE_VIEW_DESC SRVDesc;
		SRVDesc.Format = DXGI_FORMAT_UNKNOWN;
		SRVDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		SRVDesc.Buffer.FirstElement = 0;
		SRVDesc.Buffer.NumElements = count;
		device->CreateShaderResourceView(snowBuffer, &SRVDesc, &mesh.snowSRV);
		D3D11_UNORDERED_ACCESS_VIEW_DESC UAVDesc;
		UAVDesc.Format = DXGI_FORMAT_UNKNOWN;
		UAVDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		UAVDesc.Buffer.FirstElement = 0;
		UAVDesc.Buffer.NumElements =  count;
		UAVDesc.Buffer.Flags = D3D11_BUFFER_UAV_FLAG_COUNTER;
		device->CreateUnorderedAccessView(snowBuffer, &UAVDesc, &mesh.snowUAV);
		SAFE_RELEASE(snowBuffer);

		return true;
	}

	//-----------------------------------------------------------------------
	bool GECreateMaze(FLOAT _width, FLOAT _height, FLOAT _depth, const MazeClass& _maze, MazeMesh& _mesh)
	{
		MazeVertex vertices[24];
		UINT indices[36];

		FLOAT halfW = _width * 0.5f;
		FLOAT halfH = _height * 0.5f;
		FLOAT halfD = _depth * 0.5f;

		vertices[0].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[1].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[2].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[3].pos = FLOAT3(halfW,-halfH,-halfD);

		vertices[4].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[5].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[6].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[7].pos = FLOAT3(-halfW,-halfH,-halfD);

		vertices[8].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[9].pos = FLOAT3(halfW,halfH,halfD);
		vertices[10].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[11].pos = FLOAT3(-halfW,-halfH,halfD);

		vertices[12].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[13].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[14].pos = FLOAT3(halfW,halfH,halfD);
		vertices[15].pos = FLOAT3(halfW,-halfH,halfD);

		vertices[16].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[17].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[18].pos = FLOAT3(halfW,halfH,halfD);
		vertices[19].pos = FLOAT3(halfW,halfH,-halfD);

		vertices[20].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[21].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[22].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[23].pos = FLOAT3(halfW,-halfH,halfD);

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 0;
		indices[4] = 2;
		indices[5] = 3;

		indices[6] = 4;
		indices[7] = 5;
		indices[8] = 6;
		indices[9] = 4;
		indices[10] = 6;
		indices[11] = 7;

		indices[12] = 8;
		indices[13] = 9;
		indices[14] = 10;
		indices[15] = 8;
		indices[16] = 10;
		indices[17] = 11;

		indices[18] = 12;
		indices[19] = 13;
		indices[20] = 14;
		indices[21] = 12;
		indices[22] = 14;
		indices[23] = 15;

		indices[24] = 16;
		indices[25] = 17;
		indices[26] = 18;
		indices[27] = 16;
		indices[28] = 18;
		indices[29] = 19;

		indices[30] = 20;
		indices[31] = 21;
		indices[32] = 22;
		indices[33] = 20;
		indices[34] = 22;
		indices[35] = 23;

		ID3D11Device *device = g_GEClass->GetDevice();

		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(MazeVertex) * 24;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = vertices;
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &_mesh.mazeVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		D3D11_BUFFER_DESC ibDesc = {0};
		ibDesc.ByteWidth = sizeof(UINT) * 36;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;
		ibDesc.StructureByteStride = 0;
		ibDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA ibData;
		ibData.pSysMem = indices;
		ibData.SysMemPitch = 0;
		ibData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&ibDesc, &ibData, &_mesh.mazeIB)))
		{
			MessageBox(NULL,L"CreateIndexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		_mesh.indexCount = 36;

		PosType **pos = _maze.GetMaze();
		int mazeWidth = _maze.GetWidth();
		int mazeHeight = _maze.GetHeight();
		_mesh.instanceCount = 0;
		std::vector<MazeInstance> instances(mazeWidth * mazeHeight);
		for(int i = 0; i < mazeWidth; ++i)
		{
			for(int j = 0; j < mazeHeight; ++j)
			{
				switch(pos[i][j])
				{
				case POS_FRAME:
					instances[_mesh.instanceCount].world = MATRIX(
						1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						i * _width + _width/2, 0.0f, j * _depth + _depth/2, 1.0f);
					instances[_mesh.instanceCount].color = FLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
					++_mesh.instanceCount;
					break;

				case POS_WALL:
					instances[_mesh.instanceCount].world = MATRIX(
						1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						i * _width + _width/2, 0.0f, j * _depth + _depth/2, 1.0f);
					instances[_mesh.instanceCount].color = FLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
					++_mesh.instanceCount;
					break;
				default:
					break;
				}
			}
		}
		instances.resize(_mesh.instanceCount);

		D3D11_BUFFER_DESC instanceBDesc;
		instanceBDesc.ByteWidth = sizeof(MazeInstance) * _mesh.instanceCount;
		instanceBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		instanceBDesc.CPUAccessFlags = 0;
		instanceBDesc.MiscFlags = 0;
		instanceBDesc.StructureByteStride = 0;
		instanceBDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA instanceBData;
		instanceBData.pSysMem = &instances[0];
		instanceBData.SysMemPitch = 0;
		instanceBData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&instanceBDesc, &instanceBData, &_mesh.mazeInstanceB)))
		{
			MessageBox(NULL,L"CreateInstanceBuffer failed!",L"Error",MB_OK);
			return false;
		}

		return true;
	}

	//-----------------------------------------------------------------------
	bool GECreateMaze(FLOAT _width, FLOAT _height, FLOAT _depth, ID3D11ShaderResourceView* _tex, const MazeClass& _maze, TexMazeMesh& _mesh)
	{
		TexMazeVertex vertices[24];
		UINT indices[36];

		FLOAT halfW = _width * 0.5f;
		FLOAT halfH = _height * 0.5f;
		FLOAT halfD = _depth * 0.5f;

		vertices[0].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[0].normal = FLOAT3(0.f,0.f,-1.f);
		vertices[0].tex = FLOAT2(0.f,1.f);
		vertices[1].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[1].normal = FLOAT3(0.f,0.f,-1.f);
		vertices[1].tex = FLOAT2(0.f,0.f);
		vertices[2].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[2].normal = FLOAT3(0.f,0.f,-1.f);
		vertices[2].tex = FLOAT2(1.f,0.f);
		vertices[3].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[3].normal = FLOAT3(0.f,0.f,-1.f);
		vertices[3].tex = FLOAT2(1.f,1.f);

		vertices[4].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[4].normal = FLOAT3(-1.f,0.f,0.f);
		vertices[4].tex = FLOAT2(0.f,1.f);
		vertices[5].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[5].normal = FLOAT3(-1.f,0.f,0.f);
		vertices[5].tex = FLOAT2(0.f,0.f);
		vertices[6].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[6].normal = FLOAT3(-1.f,0.f,0.f);
		vertices[6].tex = FLOAT2(1.f,0.f);
		vertices[7].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[7].normal = FLOAT3(-1.f,0.f,0.f);
		vertices[7].tex = FLOAT2(1.f,1.f);

		vertices[8].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[8].normal = FLOAT3(0.f,0.f,1.f);
		vertices[8].tex = FLOAT2(0.f,1.f);
		vertices[9].pos = FLOAT3(halfW,halfH,halfD);
		vertices[9].normal = FLOAT3(0.f,0.f,1.f);
		vertices[9].tex = FLOAT2(0.f,0.f);
		vertices[10].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[10].normal = FLOAT3(0.f,0.f,1.f);
		vertices[10].tex = FLOAT2(1.f,0.f);
		vertices[11].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[11].normal = FLOAT3(0.f,0.f,1.f);
		vertices[11].tex = FLOAT2(1.f,1.f);

		vertices[12].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[12].normal = FLOAT3(1.f,0.f,0.f);
		vertices[12].tex = FLOAT2(0.f,1.f);
		vertices[13].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[13].normal = FLOAT3(1.f,0.f,0.f);
		vertices[13].tex = FLOAT2(0.f,0.f);
		vertices[14].pos = FLOAT3(halfW,halfH,halfD);
		vertices[14].normal = FLOAT3(1.f,0.f,0.f);
		vertices[14].tex = FLOAT2(1.f,0.f);
		vertices[15].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[15].normal = FLOAT3(1.f,0.f,0.f);
		vertices[15].tex = FLOAT2(1.f,1.f);

		vertices[16].pos = FLOAT3(-halfW,halfH,-halfD);
		vertices[16].normal = FLOAT3(0.f,1.f,0.f);
		vertices[16].tex = FLOAT2(0.f,1.f);
		vertices[17].pos = FLOAT3(-halfW,halfH,halfD);
		vertices[17].normal = FLOAT3(0.f,1.f,0.f);
		vertices[17].tex = FLOAT2(0.f,0.f);
		vertices[18].pos = FLOAT3(halfW,halfH,halfD);
		vertices[18].normal = FLOAT3(0.f,1.f,0.f);
		vertices[18].tex = FLOAT2(1.f,0.f);
		vertices[19].pos = FLOAT3(halfW,halfH,-halfD);
		vertices[19].normal = FLOAT3(0.f,1.f,0.f);
		vertices[19].tex = FLOAT2(1.f,1.f);

		vertices[20].pos = FLOAT3(-halfW,-halfH,halfD);
		vertices[20].normal = FLOAT3(0.f,-1.f,0.f);
		vertices[20].tex = FLOAT2(0.f,1.f);
		vertices[21].pos = FLOAT3(-halfW,-halfH,-halfD);
		vertices[21].normal = FLOAT3(0.f,-1.f,0.f);
		vertices[21].tex = FLOAT2(0.f,0.f);
		vertices[22].pos = FLOAT3(halfW,-halfH,-halfD);
		vertices[22].normal = FLOAT3(0.f,-1.f,0.f);
		vertices[22].tex = FLOAT2(1.f,0.f);
		vertices[23].pos = FLOAT3(halfW,-halfH,halfD);
		vertices[23].normal = FLOAT3(0.f,-1.f,0.f);
		vertices[23].tex = FLOAT2(1.f,1.f);

		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 0;
		indices[4] = 2;
		indices[5] = 3;

		indices[6] = 4;
		indices[7] = 5;
		indices[8] = 6;
		indices[9] = 4;
		indices[10] = 6;
		indices[11] = 7;

		indices[12] = 8;
		indices[13] = 9;
		indices[14] = 10;
		indices[15] = 8;
		indices[16] = 10;
		indices[17] = 11;

		indices[18] = 12;
		indices[19] = 13;
		indices[20] = 14;
		indices[21] = 12;
		indices[22] = 14;
		indices[23] = 15;

		indices[24] = 16;
		indices[25] = 17;
		indices[26] = 18;
		indices[27] = 16;
		indices[28] = 18;
		indices[29] = 19;

		indices[30] = 20;
		indices[31] = 21;
		indices[32] = 22;
		indices[33] = 20;
		indices[34] = 22;
		indices[35] = 23;

		ID3D11Device *device = g_GEClass->GetDevice();

		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(TexMazeVertex) * 24;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = vertices;
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &_mesh.mazeVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		D3D11_BUFFER_DESC ibDesc = {0};
		ibDesc.ByteWidth = sizeof(UINT) * 36;
		ibDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibDesc.CPUAccessFlags = 0;
		ibDesc.MiscFlags = 0;
		ibDesc.StructureByteStride = 0;
		ibDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA ibData;
		ibData.pSysMem = indices;
		ibData.SysMemPitch = 0;
		ibData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&ibDesc, &ibData, &_mesh.mazeIB)))
		{
			MessageBox(NULL,L"CreateIndexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		_mesh.indexCount = 36;

		PosType **pos = _maze.GetMaze();
		int mazeWidth = _maze.GetWidth();
		int mazeHeight = _maze.GetHeight();
		_mesh.instanceCount = 0;
		std::vector<TexMazeInstance> instances(mazeWidth * mazeHeight);
		for(int i = 0; i < mazeWidth; ++i)
		{
			for(int j = 0; j < mazeHeight; ++j)
			{
				switch(pos[i][j])
				{
				case POS_FRAME:
					instances[_mesh.instanceCount].world = MATRIX(
						1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						i * _width + _width/2, 0.0f, j * _depth + _depth/2, 1.0f);
					++_mesh.instanceCount;
					break;

				case POS_WALL:
					instances[_mesh.instanceCount].world = MATRIX(
						1.0f, 0.0f, 0.0f, 0.0f,
						0.0f, 1.0f, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f, 0.0f,
						i * _width + _width/2, 0.0f, j * _depth + _depth/2, 1.0f);
					++_mesh.instanceCount;
					break;
				default:
					break;
				}
			}
		}
		instances.resize(_mesh.instanceCount);

		D3D11_BUFFER_DESC instanceBDesc;
		instanceBDesc.ByteWidth = sizeof(TexMazeInstance) * _mesh.instanceCount;
		instanceBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		instanceBDesc.CPUAccessFlags = 0;
		instanceBDesc.MiscFlags = 0;
		instanceBDesc.StructureByteStride = 0;
		instanceBDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA instanceBData;
		instanceBData.pSysMem = &instances[0];
		instanceBData.SysMemPitch = 0;
		instanceBData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&instanceBDesc, &instanceBData, &_mesh.mazeInstanceB)))
		{
			MessageBox(NULL,L"CreateInstanceBuffer failed!",L"Error",MB_OK);
			return false;
		}

		_mesh.tex = _tex;

		return true;
	}
	//-----------------------------------------------------------------------
	bool GECreateQuad(FLOAT _posX, FLOAT _posY, FLOAT _width, FLOAT _height, ID3D11ShaderResourceView* _tex, QuadMesh& _mesh)
	{
		float quadPosX = (_posX / (float)GEGetWidth()) * 2.0f - 1.0f;
		float quadPosY = 1.0f - (_posY / (float)GEGetHeight()) * 2.0f;
		float quadWidth = quadPosX + _width / (float)GEGetWidth() * 2.0f;
		float quadHeight = quadPosY - _height / (float)GEGetHeight() * 2.0f;

		QuadVertex vertices[4];

		vertices[0].pos = FLOAT3( quadPosX, quadPosY, 0.0f);
		vertices[0].tex = FLOAT2(0,0);
		vertices[1].pos = FLOAT3( quadWidth, quadPosY, 0.0f);
		vertices[1].tex = FLOAT2(1,0);
		vertices[2].pos = FLOAT3( quadPosX, quadHeight, 0.0f);
		vertices[2].tex = FLOAT2(0,1);
		vertices[3].pos = FLOAT3( quadWidth, quadHeight, 0.0f);
		vertices[3].tex = FLOAT2(1,1);

		ID3D11Device *device = g_GEClass->GetDevice();

		D3D11_BUFFER_DESC vbDesc = {0};
		vbDesc.ByteWidth = sizeof(QuadVertex) * 4;
		vbDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbDesc.CPUAccessFlags = 0;
		vbDesc.MiscFlags = 0;
		vbDesc.StructureByteStride = 0;
		vbDesc.Usage = D3D11_USAGE_IMMUTABLE;

		D3D11_SUBRESOURCE_DATA vbData;
		vbData.pSysMem = vertices;
		vbData.SysMemPitch = 0;
		vbData.SysMemSlicePitch = 0;

		if(FAILED(device->CreateBuffer(&vbDesc, &vbData, &_mesh.quadVB)))
		{
			MessageBox(NULL,L"CreateVertexBuffer failed!",L"Error",MB_OK);
			return false;
		}

		_mesh.tex = _tex;

		return true;
	}
	//-----------------------------------------------------------------------
}