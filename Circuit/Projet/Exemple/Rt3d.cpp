#include "Rt3D.h";

Rt3D::Rt3D(float angle, const Dir3D& dir)
	: TG3D()
{
	float c = cos(angle);
	float s = sin(angle);
	Dir3D dirNorm = dir.normalize();
	mat[0][0] = dirNorm.x * dirNorm.x + c * (1.0F - dirNorm.x * dirNorm.x);
	mat[0][1] = dirNorm.x * dirNorm.y * (1.0F - c) - dirNorm.z * s;
	...
}
