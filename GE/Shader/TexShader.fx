#ifndef _TEXSHADER_FX_
#define _TEXSHADER_FX_

#include "cbuffer.fx"

Texture2D g_tex : register(ps, t0);

SamplerState samTex
{
	Filter = ANISOTROPIC;
};

struct TexVIn
{
	float3	pos:	POSITION;
	float3	normal:	NORMAL;
	float2	tex:	TEXCOORD;
};

struct TexVOut
{
	float4	posH:	SV_POSITION;
	float3	posW:	POSITION;
	float3	normal:	NORMAL;
	float2	tex:	TEXCOORD;
};

TexVOut TexVS(TexVIn vin)
{
	TexVOut vout;
	vout.posH = mul(float4(vin.pos,1.f),g_worldViewProj);
	vout.posW = mul(float4(vin.pos,1.f),g_world).xyz;
	vout.normal = mul(vin.normal,(float3x3)g_worldInvTranspose);
	vout.tex = vin.tex;

	return vout;
}

[earlydepthstencil]
void TexPS(TexVOut pin, out float4 finalColor :SV_TARGET)
{
	finalColor = g_tex.Sample(samTex,pin.tex);

	finalColor = ComputeFog(finalColor, pin.posW);
}


#endif