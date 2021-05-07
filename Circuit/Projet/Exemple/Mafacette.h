#include "Pos3d.h";

#ifndef __MAFACETTE__
#define __MAFACETTE__
class Mafacette
{
private: 
	 Pos3D p1, p2, p3, p4;
public: 
	  Mafacette(Pos3D* p01,Pos3D* p02,Pos3D* p03,Pos3D* p04);
	  void dessiner();
};

#endif

