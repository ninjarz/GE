#ifndef _QUADSHADER_FX_
#define _QUADSHADER_FX_

#include "cbuffer.fx"

Texture2D g_tex : register(ps, t0);

SamplerState samTex
{
	Filter = ANISOTROPIC;
};

struct QuadVIn
{
	float3	pos:	POSITION;
	float2	tex:	TEXCOORD;
};

struct QuadVOut
{
	float4	posH:	SV_POSITION;
	float2	tex:	TEXCOORD;
};

QuadVOut QuadVS(QuadVIn vin)
{
	/*
	return vin;
	*/
	QuadVOut vout;
	vout.posH = float4(vin.pos, 1.0f);
	vout.tex = vin.tex;

	return vout;
}

[earlydepthstencil]
void QuadPS(QuadVOut pin, out float4 finalColor :SV_TARGET)
{
	finalColor = g_tex.Sample(samTex, pin.tex);
}



#endif