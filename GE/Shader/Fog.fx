#ifndef _FOG_FX_
#define _FOG_FX_

float4 ComputeFog(float4 color, float3 posW)
{
	float4 result = color;
	if(g_useFog)
	{
		float dist = length(g_eyePos - posW);
		if(g_fogClipEnable)
		{
			clip(g_fogStart + g_fogRange - dist);
		}
		float fogFactor = saturate((dist - g_fogStart) / g_fogRange);
		result = lerp(color, g_fogColor, fogFactor);
	}

	return result;
}

#endif