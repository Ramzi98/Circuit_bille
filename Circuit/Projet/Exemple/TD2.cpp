/* Fonctionnement de GLUt                       */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Janvier 2019                                 */

#include <stdlib.h>
#include <stdio.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Variables globales                           */

static int wTx = 480;              // Resolution horizontale de la fenetre
static int wTy = 480;              // Resolution verticale de la fenetre
static int wPx = 50;               // Position horizontale de la fenetre
static int wPy = 50;               // Position verticale de la fenetre


static float r1 = 10.0F;
static float r2 = -15.0F;

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
}


void brasRobotV1(float ra, float rb)
{
    glPushMatrix();
    glRotatef(ra, 0.0F, 1.0F, 0.0F);
    glTranslatef(1.5F, 0.0F, 0.0F);

    glPushMatrix();
    glScalef(3.0F, 1.0F, 1.0F);
    glutSolidCube(1.0);
    glPopMatrix();


    glTranslatef(1.5F, 0.0F, 0.0F);
    glRotatef(rb, 0.0F, 1.0F, 0.0F);
    glTranslatef(1.5F, 0.0F, 0.0F);

    glPushMatrix();
    glScalef(3.0F, 1.0F, 1.0F);
    glutSolidCube(1.0);
    glPopMatrix();

    glPopMatrix();
}


static void scene(void) {
    glPushMatrix();
    brasRobotV1(r1, r2);
    glPopMatrix();
}

static void display(void) {
    printf("D\n");
   
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    scene();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);
}




/* Fonction principale                          */

int main(int argc, char** argv) {


    glutInit(&argc, argv); // intialiser glut qui va créer la fenetre 
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); //GLUT_RGBA : mode d'affichage RGB c a d en 4 octet A c'est la couleur Aplpha pour la transparance
    //GLUT_DEPTH : dit a open GL de permet l'elimination des partie cacher
    glutInitWindowSize(wTx, wTy);// définit la zone d'affichage en PX de la fenetre
    glutInitWindowPosition(wPx, wPy); // définir la position de la fenetre par rapport a l'écran
    glutCreateWindow("Gestion événementielle de GLUt"); // Créer la fenetre et donner le titre
    init();
    glutDisplayFunc(display);//la fentre qui va etre afficher lorsque en rafrichir
    glutMainLoop();//Ouvrir la fenetre et mettre une boucle infinie 
    return(0);
}