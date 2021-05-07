#include "Mafacette.h"
#include "Pos3d.h"
#include <GL/gl.h>

Mafacette::Mafacette(Pos3D* p01, Pos3D* p02, Pos3D* p03, Pos3D* p04) {
	p1 = p01;
	p2 = p02;
	p3 = p03;
	p4 = p04;
}

void Mafacette::dessiner() {
    glBegin(GL_QUADS);

    glNormal3f(p1.x, p1.y, p1.z);
    glVertex3f(p1.x, p1.y, p1.z);
    glTexCoord2f(0.0F, 0.0F);

    glNormal3f(p2.x, p2.y, p2.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glTexCoord2f(0.0F, 1.0F);

    glNormal3f(p3.x, p3.y, p3.z);
    glVertex3f(p3.x, p3.y, p3.z);
    glTexCoord2f(1.0F, 1.0F);

    glNormal3f(p4.x, p4.y, p4.z);
    glVertex3f(p4.x, p4.y, p4.z);
    glTexCoord2f(1.0F, 0.0F);

    glEnd();
}
