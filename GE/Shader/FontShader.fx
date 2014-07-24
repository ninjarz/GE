#ifndef _FONTSHADER_FX_
#define _FONTSHADER_FX_

#include "cbuffer.fx"

cbuffer FontBuffer : register(b7)
{
	float4 g_fontColor : packoffset(c0);
}

Texture2D g_tex : register(ps, t0);

SamplerState samTex
{
	Filter = ANISOTROPIC;
};

struct FontVIn
{
	float3	pos:	POSITION;
	float2	tex:	TEXCOORD;
};

struct FontVOut
{
	float4	posH:	SV_POSITION;
	float2	tex:	TEXCOORD;
};

FontVOut FontVS(FontVIn vin)
{
	FontVOut vout;
	vout.posH = float4(vin.pos, 1.0f);
	vout.tex = vin.tex;

	return vout;
}

[earlydepthstencil]
void FontPS(FontVOut pin, out float4 finalColor :SV_TARGET)
{
	finalColor = g_tex.Sample(samTex, pin.tex);

	if (finalColor.r == 0.0f)
		clip(-1);
	else
		finalColor = g_fontColor;
}

#endif