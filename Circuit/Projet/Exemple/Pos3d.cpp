#include"Pos3d.h";

Pos3D::Pos3D(void)
	: CH3D() {}
Pos3D::Pos3D(float xp, float yp, float zp)
	: CH3D(xp, yp, zp, 1.0F) {}
Pos3D::Pos3D(Pos3D* p)
	: CH3D(p) {}
