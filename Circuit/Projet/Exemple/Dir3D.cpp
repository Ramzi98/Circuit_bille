#include"Dir3D.h";
#include"Pos3d.h";
#include"CH3D.h";
#include<math.h>;


Dir3D::Dir3D(void) : CH3D(0.0F, 0.0F, 1.0F, 0.0F) {}
Dir3D::Dir3D(float xp, float yp, float zp) : CH3D(xp, yp, zp, 0.0F) {}
Dir3D::Dir3D(Dir3D* d) : CH3D(d) {}
Dir3D::Dir3D(const Pos3D &p1, const Pos3D &p2) : CH3D(p2.x - p1.x, p2.y - p1.y, p2.z - p1.z, 0.0f) {}

float Dir3D::norme(void)
{
	return sqrt(x * x + y * y + z * z);
}

Dir3D Dir3D::normalize(void)
{
	float norm = norme();
	Dir3D res;
	if (norm != 0.0F) {
		res.x = x / norm;
		res.y = y / norm;
		res.z = z / norm;
	}
	return res;
}


float Dir3D::operator*(const Dir3D& dir) {
	return this->x * dir.x + this->y * dir.y + this->z * dir.z;
}
Dir3D Dir3D::operator^(const Dir3D& dir) {// produit vectoriel entre this et dir
	Dir3D res;
	res.x = this->y * dir.z - dir.y * this->z;
	res.y = this->z * dir.x - dir.z * this->x;
	res.z = this->x * dir.y - dir.x * this->y;
	return res;
}

bool isFlat(const Pos3D &p1, const Pos3D &p2, const Pos3D &p3, const Pos3D &p4) {
	Dir3D v1(p1, p2);
	Dir3D v2(p1, p3);
	Dir3D v3(p1, p4);
	float res = (v1 ^ v2) * v3;
	res = (res > 0 ? res : -res);
	return res <= 0.0001f;
}
