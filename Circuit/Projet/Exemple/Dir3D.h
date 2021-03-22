#include "CH3D.h";
#include "Pos3d.h";

#ifndef __DIR3D__
#define __DIR3D__
class Dir3D : public CH3D {
public:
	Dir3D(void);
	Dir3D(float xp, float yp, float zp);
	Dir3D(Dir3D* d);
	Dir3D(const Pos3D &p1, const Pos3D &p2);  // Constructeur pour construire la direction p1 p2

	float norme(void);
	Dir3D normalize(void);

	float operator*(const Dir3D& dir); // produit scalaire entre this et dir
	Dir3D operator^(const Dir3D& dir); // produit vectoriel entre this et dir
};

#endif
