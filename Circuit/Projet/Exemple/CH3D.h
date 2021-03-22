#include "TG3D.h";

#ifndef __CH3D__
#define __CH3D__

class CH3D {
public: float x, y, z;
private: float w;
public: CH3D(void);
	  CH3D(float xp, float yp, float zp, float wp);
	  CH3D(CH3D* c);
	  CH3D mult(const TG3D& mat);
};

#endif