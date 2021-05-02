#include "Pos3d.h";
#include <GL/gl.h>


#ifndef __BALLE__
#define __BALLE__
class Balle
{
private: 
	bool typeAffiche;// false pour fils de fer et true pour plein
	float couleur[4];
public:
	Balle(void);
	void dessiner(Pos3D position, GLdouble radius, GLint slices, GLint stacks);
	void changerAffichage(bool b);
	bool getTypeAffiche();

	/*Pos3D(void);
	Pos3D(float xp, float yp, float zp);
	Pos3D(Pos3D* p);*/
	

	
};

#endif

