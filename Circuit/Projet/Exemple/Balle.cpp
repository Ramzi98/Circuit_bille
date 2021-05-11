#include "Balle.h"
#include "Pos3d.h"
#include <GL/glut.h>

Balle::Balle(Pos3D pos, GLdouble r) : typeAffiche(true) {
    couleur[0] = 0.0F;
    couleur[1] = 0.0F;
    couleur[2] = 1.0F;
    couleur[3] = 1.0F;
    positionBall.x = pos.x;
    positionBall.y = pos.y;
    positionBall.z = pos.z;
    slices = 36;
    stacks = 36;
    radius = r;
}

void Balle::dessiner(Pos3D position) {
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, couleur);
    glTranslatef(position.x, position.y, position.z);
    if (typeAffiche) {
        glutSolidSphere(radius, slices, stacks);
    }
    else {
        glutWireSphere(radius, slices, stacks);
    }
    glPopMatrix();
}
void Balle::changerAffichage(bool b) {
    typeAffiche = b;
}
bool Balle::getTypeAffiche() {
    return typeAffiche;
}
