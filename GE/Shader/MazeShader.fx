#ifndef _MAZESHADER_FX_
#define _MAZESHADER_FX_

#include "cbuffer.fx"

struct MazeVIn
{
	float3	pos               : POSITION;
	row_major float4x4 world  : WORLD;
	float4 color              : COLOR;
	//uint InstanceId : SV_InstanceID;
};

struct MazeVOut
{
	float4	posH	: SV_POSITION;
	float3	posW    : POSITION;
	float4	color	: COLOR;
};

MazeVOut MazeVS(MazeVIn vin)
{
	MazeVOut vout;
	vout.posW = mul(float4(vin.pos,1.f), vin.world).xyz;
	vout.posH = mul(float4(vout.posW,1.f), g_worldViewProj);
	vout.color = vin.color;

	return vout;
}

[earlydepthstencil]
void MazePS(MazeVOut pin, out float4 finalColor :SV_TARGET/*, out float depth :SV_DEPTH*/)
{
	finalColor = pin.color;

	finalColor = ComputeFog(finalColor, pin.posW);
}

#endif