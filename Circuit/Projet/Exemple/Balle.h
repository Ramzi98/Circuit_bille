#include "Pos3d.h";
#include <GL/gl.h>


#ifndef __BALLE__
#define __BALLE__
class Balle
{
private: 
	bool typeAffiche;// false pour fils de fer et true pour plein
	float couleur[4];
	GLint slices;
	GLint stacks;
public:
	Pos3D positionBall;
	GLdouble radius;
public:
	Balle(void);
	Balle(Pos3D pos, GLdouble r);
	void dessiner(Pos3D position);
	void changerAffichage(bool b);
	bool getTypeAffiche();
	void move(GLdouble rayonBall, int etage);
	

	
};

#endif

