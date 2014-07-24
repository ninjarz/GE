#ifndef _CBUFFER_FX_
#define _CBUFFER_FX_

#include "Struct.fx"

cbuffer BasicBuffer : register( b0 )
{
	row_major matrix  g_worldViewProj     : packoffset( c0 );
	row_major matrix  g_world             : packoffset( c4 );
	row_major matrix  g_worldInvTranspose : packoffset( c8 );
	Material          g_material          : packoffset( c12 );
};

cbuffer FogBuffer : register( b1 )
{
	float4	g_fogColor       : packoffset( c0 );				//ŒÌ—’…´
	float	g_fogStart       : packoffset( c1.x );				//∆ ºæ‡¿Î
	float	g_fogRange       : packoffset( c1.y );				//ŒÌ–ß∑∂Œß
	uint    g_useFog         : packoffset( c1.z );
	uint    g_fogClipEnable  : packoffset( c1.w );
};

cbuffer	LightBuffer : register( b2 )
{
	DirLight	      g_dirLights[3]      : packoffset( c0 );
};

cbuffer PerFrameBuffer : register( b3 )
{
	row_major matrix  g_viewInv     : packoffset( c0 );
	float3            g_eyePos      : packoffset( c4 );
	float             g_deltaTime   : packoffset( c4.w );
}

cbuffer	Quad
{
	static float3 g_positions[4] =
	{
		float3( -1.0f, 1.0f, 0.0f),
		float3( 1.0f, 1.0f, 0.0f),
		float3( -1.0f, -1.0f, 0.0f),
		float3( 1.0f, -1.0f, 0.0f),
	};

	static float2 g_texcoords[4] =
	{
		float2(0,0),
		float2(1,0),
		float2(0,1),
		float2(1,1),
	};
};

#include "Fog.fx"
#include "Lights.fx"

#endif