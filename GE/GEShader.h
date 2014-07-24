#pragma once
#ifndef _GESHADER_H_
#define _GESHADER_H_

#include <d3d11.h>
#include <d3dx11async.h>
#include "GEManageClass.h"
#include "GEMesh.h"

//-----------------------------------------------------------------------
namespace GE
{
	struct BasicBuffer
	{
		MATRIX worldViewProj;
		MATRIX world;
		MATRIX worldInvTranspose;
		Material material;
	};

	struct FogBuffer
	{
		FLOAT4 fogColor;			//ŒÌ—’…´
		FLOAT fogStart;				//∆ ºæ‡¿Î
		FLOAT fogRange;				//ŒÌ–ß∑∂Œß
		UINT useFog;
		UINT fogClipEnable;
	};

	struct LightBuffer
	{
		DirLight dirLights[3];
	};

	struct PerFrameBuffer
	{
		MATRIX viewInv;
		FLOAT3 eyePos;
		FLOAT deltaTime;
	};

	class ShaderClass : public GEClass
	{
	public:
		ShaderClass();
		ShaderClass(const ShaderClass&);
		~ShaderClass();

		bool Initialize();
		void Shutdown();

		bool SetBasicParameters(const MATRIX& viewProjMatrix);
		bool SetBasicParameters(const MATRIX& worldMatrix, const MATRIX& viewProjMatrix);
		bool SetBasicParameters(const MATRIX& worldMatrix, const MATRIX& viewMatrix, const MATRIX& projectionMatrix);
		bool SetFogParameters(const FLOAT4& fogColor, const FLOAT fogStart, const FLOAT fogRange, const bool useFog, const bool fogClipEnable);
		bool SetLightParameters(const DirLight* dirLights, const UINT dirStar, const UINT dirNum);
		bool SetPerFrameParameters(const MATRIX& viewInv, const FLOAT3& eyePos, const FLOAT deltaTime);

		bool Render(ColorMesh& mesh);
		bool Render(CubeMapMesh& mesh);
		bool Render(TexMesh_File& mesh);
		bool Render(MazeMesh& mesh);
		bool Render(QuadMesh& mesh);
	private:
		bool InitializeShader();
		void ShutdownShader();
		bool InitializeCBuffer();

	private:
		ID3D11VertexShader *m_colorVS;
		ID3D11PixelShader  *m_colorPS;
		ID3D11VertexShader *m_lightVS;
		ID3D11PixelShader  *m_lightPS;
		ID3D11VertexShader *m_texVS;
		ID3D11PixelShader  *m_texPS;
		ID3D11VertexShader *m_cubeMapVS;
		ID3D11PixelShader  *m_cubeMapPS;
		ID3D11VertexShader *m_mazeVS;
		ID3D11PixelShader  *m_mazePS;
		ID3D11VertexShader *m_texMazeVS;
		ID3D11PixelShader  *m_texMazePS;
		ID3D11VertexShader *m_quadVS;
		ID3D11PixelShader  *m_quadPS;

		ID3D11InputLayout *m_colorIL;
		ID3D11InputLayout *m_lightIL;
		ID3D11InputLayout *m_texIL;
		ID3D11InputLayout *m_cubeMapIL;
		ID3D11InputLayout *m_mazeIL;
		ID3D11InputLayout *m_texMazeIL;
		ID3D11InputLayout *m_quadIL;

		ID3D11Buffer *m_basicBuffer;
		ID3D11Buffer *m_fogBuffer;
		ID3D11Buffer *m_lightBuffer;
		ID3D11Buffer *m_PerFrameBuffer;
	};

	extern ShaderClass *g_shaderClass;

	bool GESetBasicParameters(const MATRIX& worldMatrix, const MATRIX& viewProjMatrix);
	bool GESetBasicParameters(const MATRIX& worldMatrix, const MATRIX& viewMatrix, const MATRIX& projectionMatrix);
	bool GESetFogParameters(const FLOAT4& fogColor, const FLOAT fogStart, const FLOAT fogRange, const bool useFog, const bool fogClipEnable);
	bool GESetLightParameters(const DirLight* dirLights, const UINT dirStar, const UINT dirNum);
	bool GESetPerFrameParameters(const MATRIX& viewInv, const FLOAT3& eyePos, const FLOAT deltaTime);

	bool GERender(ColorMesh& mesh);
	bool GERender(CubeMapMesh& mesh);
	bool GERender(TexMesh_File& mesh);
	bool GERender(MazeMesh& mesh);
	bool GERender(QuadMesh& mesh);
}
#endif
