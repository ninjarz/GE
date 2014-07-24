#include "GECollision.h"

namespace GE
{


	//-----------------------------------------------------------------------
	void GEComputeFrustumFromProjection(Frustum& _frustum, MATRIX& _matrix)
	{
		_frustum.Origin = FLOAT3( 0.0f, 0.0f, 0.0f );
		_frustum.Orientation = FLOAT4( 0.0f, 0.0f, 0.0f, 1.0f );
	}
}