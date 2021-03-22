#include "CH3D.h"
#ifndef __POS3D__
#define __POS3D__
class Pos3D : public CH3D {
public:
	Pos3D(void);
	Pos3D(float xp, float yp, float zp);
	Pos3D(Pos3D* p);

};
#endif