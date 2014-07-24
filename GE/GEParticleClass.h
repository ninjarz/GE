#pragma once
#ifndef _GEPARTICLECLASS_H_
#define _GEPARTICLECLASS_H_

#include <d3d11.h>
#include <d3dx11async.h>
#include "GEmath.h"
#include "GEManageClass.h"
#include "GEMesh.h"

//-----------------------------------------------------------------------
namespace GE
{
	class ParticleClass : public GEClass
	{
	public:
		inline ParticleClass()
		{
		}

		inline ParticleClass(const ParticleClass&)
		{
		}

		inline ~ParticleClass()
		{
			Shutdown();
		}

		bool Initialize();
		void Shutdown();

		bool Render(SnowMesh& mesh);

	private:
		ID3D11VertexShader   *m_snowVS;
		ID3D11GeometryShader *m_snowGS;
		ID3D11PixelShader    *m_snowPS;
		ID3D11ComputeShader  *m_snowCS;

		ID3D11InputLayout *m_snowIL;
	};

	extern ParticleClass *g_particleClass;

	bool GERender(SnowMesh& mesh);
}

#endif