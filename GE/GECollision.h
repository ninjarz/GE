#pragma once
#ifndef _GECOLLISION_H_
#define _GECOLLISION_H_

#include "GEmath.h"

namespace GE
{
	struct Frustum
	{
		FLOAT3 Origin;              // Origin of the frustum (and projection).
		FLOAT4 Orientation;         // Unit quaternion representing rotation.

		FLOAT RightSlope;           // Positive X slope (X/Z).
		FLOAT LeftSlope;            // Negative X slope.
		FLOAT TopSlope;             // Positive Y slope (Y/Z).
		FLOAT BottomSlope;          // Negative Y slope.
		FLOAT Near, Far;            // Z of the near plane and far plane.
	};

	void GEComputeFrustumFromProjection(Frustum& _frustum, MATRIX& _matrix);
}

#endif