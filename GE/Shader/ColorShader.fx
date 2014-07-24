#ifndef _COLORSHADER_FX_
#define _COLORSHADER_FX_

#include "cbuffer.fx"

struct ColorVIn
{
	float3	pos 	: POSITION;
	float4	color 	: COLOR;
};

struct ColorVOut
{
	float4	posH	: SV_POSITION;
	float3	posW    : POSITION;
	float4	color	: COLOR;
};

ColorVOut ColorVS(ColorVIn vin)
{
	ColorVOut vout;
	vout.posH = mul(float4(vin.pos,1.f), g_worldViewProj);
	vout.posW = mul(float4(vin.pos,1.f), g_world).xyz;
	vout.color = vin.color;
	
	return vout;
}

[earlydepthstencil]
void ColorPS(ColorVOut pin, out float4 finalColor :SV_TARGET/*, out float depth :SV_DEPTH*/)
{
	finalColor = pin.color;

	finalColor = ComputeFog(finalColor, pin.posW);
}

#endif