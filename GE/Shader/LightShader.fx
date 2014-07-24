#ifndef _LIGHTSHADER_FX_
#define _LIGHTSHADER_FX_

#include "cbuffer.fx"

struct LightVIn
{
	float3	pos		: POSITION;
	float3	normal	: NORMAL;
};

struct LightVOut
{
	float4	posH	 : SV_POSITION;
	float3	posW     : POSITION;
	float3	normal	 : NORMAL;
};

LightVOut LightVS(LightVIn vin)
{
	LightVOut vout;

	vout.posH = mul(float4(vin.pos,1.f),g_worldViewProj);
	vout.posW = mul(float4(vin.pos,1.f),g_world).xyz;
	vout.normal = mul(vin.normal,(float3x3)g_worldInvTranspose);

	return vout;
}

[earlydepthstencil]
void LightPS(LightVOut pin, out float4 finalColor :SV_TARGET)
{
	float3 toEye = normalize(g_eyePos - pin.posW);
	float3 normal = normalize(pin.normal);
	
	float4 A = float4(0.f,0.f,0.f,0.f);
	float4 D = float4(0.f,0.f,0.f,0.f);
	float4 S = float4(0.f,0.f,0.f,0.f);
	
	for(int i=0; i<3; ++i)
	{
		float4 ambient, diff, spec;
		ComputeDirLight(g_material, g_dirLights[i],normal, toEye, ambient, diff, spec);
		A += ambient;
		D += diff;
		S += spec;
	}
	finalColor = A + D + S;
	
	finalColor = ComputeFog(finalColor, pin.posW);
	
	finalColor.a = g_material.diffuse.a;
}


#endif