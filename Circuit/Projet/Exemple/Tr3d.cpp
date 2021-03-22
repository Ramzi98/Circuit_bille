#include "Tr3d.h";
Tr3D::Tr3D(float tx, float ty, float tz)
	: TG3D()
{
	mat[0][3] = tx;
	mat[1][3] = ty;
	mat[2][3] = tz;
}

Tr3D::Tr3D(const Dir3D& dir)
	: Tr3D(dir.x, dir.y, dir.z)
{
}

