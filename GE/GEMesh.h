#pragma once
#ifndef _GEMESH_H_
#define _GEMESH_H_

#include <d3d11.h>
#include "GEManageClass.h"
#include "GEMath.h"
#include "GELight.h"
#include "GEMazeClass.h"

namespace GE
{
	struct ColorVertex
	{
		FLOAT3 pos;
		FLOAT4 color;
	};

	struct ColorMesh
	{
		ID3D11Buffer *colorVB;
		ID3D11Buffer *colorIB;
		UINT indexCount;
		MATRIX worldMatrix;

		inline ColorMesh() : colorVB(NULL), colorIB(NULL) {}
		inline ~ColorMesh() { SAFE_RELEASE(colorVB); SAFE_RELEASE(colorIB); }
	};

	struct LightVertex
	{
		FLOAT3 pos;
		FLOAT3 normal;
	};

	struct LightMesh
	{
		ID3D11Buffer *lightVB;
		ID3D11Buffer *lightIB;
		UINT indexCount;
		MATRIX worldMatrix;
		Material material;

		inline LightMesh() : lightVB(NULL), lightIB(NULL) {}
		inline ~LightMesh() { SAFE_RELEASE(lightVB); SAFE_RELEASE(lightIB); }
	};

	struct TexVertex
	{
		FLOAT3 pos;
		FLOAT3 normal;
		FLOAT2 tex;
	};

	struct TexMesh
	{
		ID3D11Buffer *texVB;
		ID3D11Buffer *texIB;
		UINT indexCount;
		MATRIX worldMatrix;
		ID3D11ShaderResourceView *tex;
		Material material;

		inline TexMesh() : texVB(NULL), texIB(NULL) {}
		inline ~TexMesh() { SAFE_RELEASE(texVB); SAFE_RELEASE(texIB); }
	};

	struct CubeMapVertex
	{
		FLOAT3 pos;
	};

	struct CubeMapMesh
	{
		ID3D11Buffer *cubeMapVB;
		ID3D11Buffer *cubeMapIB;
		UINT indexCount;
		ID3D11ShaderResourceView *tex;

		inline CubeMapMesh() : cubeMapVB(NULL), cubeMapIB(NULL) {}
		inline ~CubeMapMesh() { SAFE_RELEASE(cubeMapVB); SAFE_RELEASE(cubeMapIB); }
	};

	struct TexMesh_File
	{
		ID3D11Buffer *texVB;
		UINT vertexCount;
		MATRIX worldMatrix;
		ID3D11ShaderResourceView *tex;
		Material material;

		inline TexMesh_File() : texVB(NULL) {}
		inline ~TexMesh_File() { SAFE_RELEASE(texVB); }
	};

	struct SnowVertex
	{
		FLOAT4 color;
	};

	struct SnowInfo
	{
		FLOAT3 pos;
		FLOAT3 velocity;
	};

	struct SnowMesh
	{
		ID3D11Buffer *snowVB;
		UINT vertexCount;
		ID3D11ShaderResourceView *tex;
		ID3D11ShaderResourceView *snowSRV;
		ID3D11UnorderedAccessView *snowUAV;

		inline SnowMesh() : snowVB(NULL), snowSRV(NULL), snowUAV(NULL) {}
		inline ~SnowMesh() { SAFE_RELEASE(snowVB); SAFE_RELEASE(snowSRV); SAFE_RELEASE(snowUAV); }
	};

	struct MazeVertex
	{
		FLOAT3 pos;
	};
	
	struct MazeInstance
	{
		MATRIX world;
		FLOAT4 color;
	};

	struct MazeMesh
	{
		ID3D11Buffer *mazeVB;
		ID3D11Buffer *mazeIB;
		ID3D11Buffer *mazeInstanceB;
		UINT indexCount;
		UINT instanceCount;

		inline MazeMesh() : mazeVB(NULL), mazeIB(NULL), mazeInstanceB(NULL), indexCount(0), instanceCount(0) {}
		inline ~MazeMesh() { SAFE_RELEASE(mazeVB); SAFE_RELEASE(mazeIB); SAFE_RELEASE(mazeInstanceB); }
	};

	struct TexMazeVertex
	{
		FLOAT3 pos;
		FLOAT3 normal;
		FLOAT2 tex;
	};
	
	struct TexMazeInstance
	{
		MATRIX world;
	};

	struct TexMazeMesh
	{
		ID3D11Buffer *mazeVB;
		ID3D11Buffer *mazeIB;
		ID3D11Buffer *mazeInstanceB;
		UINT indexCount;
		UINT instanceCount;
		ID3D11ShaderResourceView *tex;

		inline TexMazeMesh() : mazeVB(NULL), mazeIB(NULL), mazeInstanceB(NULL), indexCount(0), instanceCount(0) {}
		inline ~TexMazeMesh() { SAFE_RELEASE(mazeVB); SAFE_RELEASE(mazeIB); SAFE_RELEASE(mazeInstanceB); }
	};

	struct QuadVertex
	{
		FLOAT3 pos;
		FLOAT2 tex;
	};

	struct QuadMesh
	{
		ID3D11Buffer *quadVB;
		ID3D11ShaderResourceView *tex;

		inline QuadMesh() : quadVB(NULL) {}
		inline ~QuadMesh() { SAFE_RELEASE(quadVB); }
	};

	bool GECreateBox(FLOAT width, FLOAT height, FLOAT depth, ColorMesh& mesh);
	bool GECreateBox(FLOAT width, FLOAT height, FLOAT depth, const FLOAT4& color, ColorMesh& mesh);
	bool GECreateBox(FLOAT width, FLOAT height, FLOAT depth, LightMesh& mesh);
	bool GECreateBox(FLOAT width, FLOAT height, FLOAT depth, ID3D11ShaderResourceView* tex, TexMesh& mesh);
	//bool GECreateBox(ID3D11ShaderResourceView* tex, CubeMapMesh& mesh);
	bool GECreateBox(FLOAT width, FLOAT height, FLOAT depth, ID3D11ShaderResourceView* tex, CubeMapMesh& mesh);

	bool GECreateSphere(FLOAT radius, int slice, int stack, const FLOAT4& color, ColorMesh& mesh);
	//bool CreateSphere(float radius, int slice, int stack, LightMesh& mesh);
	//bool CreateSphere(float radius, int slice, int stack, ID3D11ShaderResourceView* tex, TexMesh& mesh);
	bool GECreateSphere(FLOAT radius, int slice, int stack, ID3D11ShaderResourceView* tex, CubeMapMesh& mesh);

	bool GELoadMeshFromFile(LPCWSTR fileName, ID3D11ShaderResourceView* tex, TexMesh_File &mesh);

	bool GECreateSnow(const FLOAT3& centre, FLOAT radius, FLOAT height, UINT count, ID3D11ShaderResourceView* tex, SnowMesh& mesh);
	bool GECreateSnow(const FLOAT3& centre, FLOAT radius, FLOAT height, UINT count, const FLOAT4& color, ID3D11ShaderResourceView* tex, SnowMesh& mesh);

	bool GECreateMaze(FLOAT _width, FLOAT _height, FLOAT _depth, const MazeClass& _maze, MazeMesh& _mesh);
	bool GECreateMaze(FLOAT _width, FLOAT _height, FLOAT _depth, ID3D11ShaderResourceView* tex, const MazeClass& _maze, TexMazeMesh& _mesh);

	bool GECreateQuad(FLOAT _posX, FLOAT _posY, FLOAT _width, FLOAT _height, ID3D11ShaderResourceView* tex, QuadMesh& _mesh);
}


#endif