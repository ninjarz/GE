#ifndef _SNOWSHADER_FX_
#define _SNOWSHADER_FX_

#include "cbuffer.fx"

struct SnowInfo
{
	float3 pos;
	float3 velocity;
};

Texture2D g_snowAlpha : register(ps, t0);
StructuredBuffer<SnowInfo>   g_snowSRV : register(vs, t0);
RWStructuredBuffer<SnowInfo> g_snowUAV : register(cs, u0);

SamplerState samTex : register( s0 )
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Clamp;
	AddressV = Clamp;
};

struct SnowVIn
{
	float4  color   : COLOR;
	uint    id      : SV_VERTEXID;
};

struct SnowVOut
{
	float3 pos			: POSITION;
	float4 color		: COLOR;
};

struct SnowGOut
{
	float4 color		: COLOR;
	float2 tex			: TEXCOORD0;
	float4 posH			: SV_POSITION;
};

SnowVOut SnowVS(SnowVIn vin)
{
	SnowVOut vout;

	vout.pos = g_snowSRV[vin.id].pos;
	vout.color = vin.color;

	return vout;
}


[maxvertexcount(4)]
void SnowGS(point SnowVOut gin[1], inout TriangleStream<SnowGOut> SpriteStream)
{
	SnowGOut gout;
	[unroll]
	for(int i = 0; i < 4; ++i)
	{
		float3 position = g_positions[i];
			position = mul( position, (float3x3)g_viewInv ) + gin[0].pos;
		gout.posH = mul( float4(position,1.0), g_worldViewProj ); 
		gout.color = gin[0].color;
		gout.tex = g_texcoords[i];

		SpriteStream.Append(gout);
	}
	SpriteStream.RestartStrip();
}


float4 SnowPS(SnowGOut pin) : SV_Target
{   
	float4 finalColor = g_snowAlpha.Sample(samTex, pin.tex) * pin.color;
	if(finalColor.a == 0.0f)
		clip(-1);
	return finalColor;
}

[numthreads(1, 1, 1)]
void SnowCS( uint3 Gid : SV_GroupID, uint3 DTid : SV_DispatchThreadID, uint3 GTid : SV_GroupThreadID, uint GI : SV_GroupIndex )
{
	g_snowUAV[DTid.x].pos += g_snowUAV[DTid.x].velocity * g_deltaTime;
	if( g_snowUAV[DTid.x].pos.y < -50.0f )
		g_snowUAV[DTid.x].pos.y = 70.0f;
}

#endif