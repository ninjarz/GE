#ifndef _CUBEMAPSHADER_FX_
#define _CUBEMAPSHADER_FX_

#include "cbuffer.fx"

TextureCube g_cubeMap : register(ps, t0);

SamplerState samTex
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

struct CubeMapVIn
{
	float3 pos: POSITION;
};

struct CubeMapVOut
{
	float4 posH: SV_POSITION;
	float3 pos: POSITION;
};



CubeMapVOut CubeMapVS(CubeMapVIn vin)
{
	CubeMapVOut vout;
	vout.posH = mul(float4(vin.pos,1.f), g_worldViewProj);
	vout.pos = vin.pos;

	return vout;
}

[earlydepthstencil]
void CubeMapPS(CubeMapVOut pin, out float4 finalColor :SV_TARGET/*, out float depth :SV_DEPTH*/)
{
	if( g_useFog )
	{
		finalColor = g_fogColor;
	}
	else
		finalColor = g_cubeMap.Sample(samTex, pin.pos);
}


#endif