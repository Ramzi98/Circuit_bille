#include "Balle.h"
#include "Pos3d.h"
#include <GL/glut.h>

Balle::Balle(void) : typeAffiche(true) {
    couleur[0] = 0.0F;
    couleur[1] = 0.0F;
    couleur[2] = 1.0F;
    couleur[3] = 1.0F;
}

void Balle::dessiner(Pos3D position, GLdouble radius, GLint slices, GLint stacks) {
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
