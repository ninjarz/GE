#pragma once
#ifndef _GELIGHT_H_
#define _GELIGHT_H_

#include "GEMath.h"

namespace GE
{
	//平行光
	struct DirLight
	{
		FLOAT4	ambient;	//环境光
		FLOAT4	diffuse;	//漫反射光
		FLOAT4	specular;	//高光

		FLOAT3	dir;		//光照方向
		FLOAT	unused;		//用于与HLSL中"4D向量"对齐规则匹配
	};

	//点光源
	struct PointLight
	{
		FLOAT4	ambient;	//环境光
		FLOAT4	diffuse;	//漫反射光
		FLOAT4	specular;	//高光

		FLOAT3	pos;		//光源位置
		FLOAT	range;		//光照范围

		FLOAT3	att;		//衰减系数
		FLOAT	unused;		//用于与HLSL中"4D向量"对齐规则匹配
	};

	//聚光灯
	struct SpotLight
	{
		FLOAT4	ambient;	//环境光
		FLOAT4	diffuse;	//漫反射光
		FLOAT4	specular;	//高光

		FLOAT3	dir;		//光照方向
		FLOAT	range;		//光照范围

		FLOAT3	pos;		//光源位置
		FLOAT	spot;		//聚光强度系数

		FLOAT3	att;		//衰减系数
		FLOAT	theta;		//最大发散角度
	};

	//材质
	struct Material
	{
		FLOAT4	ambient;
		FLOAT4	diffuse;
		FLOAT4	specular;	//第4个元素为材质的镜面反射系数，即代表材质表面的光滑程度
	};
};

#endif