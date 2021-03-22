#include "Dir3D.h";
#include "TG3D.h";
#ifndef __TR3D__
#define __TR3D__
class Tr3D : public TG3D
{
	Tr3D(float tx, float ty, float tz);
	Tr3D(const Dir3D& dir);
};
#endif