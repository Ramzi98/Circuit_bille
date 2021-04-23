/* Auteur: Nicolas JANEY            */
/* nicolas.janey@univ-fcomte.fr     */
/* Septembre 2005                   */
/* Gestion des menus                */

#include <stdlib.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

static void (*cleanUp)(void) = NULL;

static void select(int selection) {
  switch (selection) {
    case 0  : if ( cleanUp )
                cleanUp();
              exit(0); }
  glutPostRedisplay();
}

void creationMenuBasique(void) {
  glutCreateMenu(select);
  glutAddMenuEntry("Quitter",0);
  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void setMenuCleanUp(void (*func)(void)) {
  cleanUp = func;
}
