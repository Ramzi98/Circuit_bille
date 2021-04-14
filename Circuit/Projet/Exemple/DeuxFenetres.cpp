/* Gestion de deux fenetres                     */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Mars 2019                                    */

#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Variables et constantes globales             */

static int f1;
static int f2;
static float rx = 0.0F;
static float ry = 0.0F;
static float rz = 0.0F;

/* Fonction de rafraichissement des 2 fenetres  */

static void postRedisplay(void) {
    glutPostWindowRedisplay(f1);
    glutPostWindowRedisplay(f2);
}

/* Fonction executee lors de l'appui            */
/* d'une touche de curseur ou d'une touche      */
/* page up ou page down                         */

static void special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        rx++;
        postRedisplay();
        break;
    case GLUT_KEY_DOWN:
        rx--;
        postRedisplay();
        break;
    case GLUT_KEY_LEFT:
        ry++;
        postRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        ry--;
        postRedisplay();
        break;
    case GLUT_KEY_PAGE_UP:
        rz++;
        postRedisplay();
        break;
    case GLUT_KEY_PAGE_DOWN:
        rz--;
        postRedisplay();
        break;
    }
}

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
}

/* Scene dessinee                               */

static void scene(void) {
    glPushMatrix();
    glutWireCube(7.0);
    glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display1(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(rx, 1.0F, 0.0F, 0.0F);
    glRotatef(ry, 0.0F, 1.0F, 0.0F);
    glRotatef(rz, 0.0F, 0.0F, 1.0F);
    scene();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Erreur OpenGL: %d\n", error);
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */
/* -> Ajustement de la camera de visualisation  */

static void reshape1(int x, int y) {
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-9.0, 9.0, -9.0 * (float)y / x, 9.0 * (float)y / x, -9.0, 9.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display2(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    gluLookAt(0.0, 0.0, 10.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(rx, 1.0F, 0.0F, 0.0F);
    glRotatef(ry, 0.0F, 1.0F, 0.0F);
    glRotatef(rz, 0.0F, 0.0F, 1.0F);
    scene();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Erreur OpenGL: %d\n", error);
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */
/* -> Ajustement de la camera de visualisation  */

static void reshape2(int tx, int ty) {
    glViewport(0, 0, tx, ty);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    double ratio = (double)tx / ty;
    if (ratio >= 1.0)
        gluPerspective(80.0, ratio, 0.01, 20.0);
    else
        gluPerspective(80.0 / ratio, ratio, 0.01, 20.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee en tache de fond           */
/* pour realiser une animation                  */

static void idle(void) {
    rx += 0.1F;
    ry += 0.15F;
    rz += 0.23F;
    postRedisplay();
}

/* Fonction executee lors de la frappe          */
/* d'une touche du clavier                      */

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 0x20: {
        static int animation = 1;
        animation = !animation;
        glutIdleFunc((animation) ? idle : NULL); }
             break;
    case 0x1B:
        exit(0);
        break;
    }
}

/* Fonction principale                          */

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(480, 320);
    glutInitWindowPosition(50, 50);
    f1 = glutCreateWindow("Fenêtre 1");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutReshapeFunc(reshape1);
    glutDisplayFunc(display1);
    glutInitWindowSize(320, 240);
    glutInitWindowPosition(250, 100);
    f2 = glutCreateWindow("Fenêtre 2");
    init();
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutDisplayFunc(display2);
    glutReshapeFunc(reshape2);
    glutIdleFunc(idle);
    glutMainLoop();
    return(0);
}