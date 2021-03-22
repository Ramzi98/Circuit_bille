/* Une animation en OpenGL                      */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Mars 2021                                    */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

/* Variables et constantes globales             */
/* pour les angles et les couleurs utilises     */

static float rx = 0.0F;
static float ry = 0.0F;
static float rz = 0.0F;
static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float jaune[] = { 1.0F,1.0F,0.0F,1.0F };
static const float rouge[] = { 1.0F,0.0F,0.0F,1.0F };
static const float vert[] = { 0.0F,1.0F,0.0F,1.0F };
static const float bleu[] = { 0.0F,0.0F,1.0F,1.0F };

static int obj = 1;




/* Affichage des informations relatives         */
/* a OpenGL                                     */

static void informationsOpenGL(void) {
    printf("GL_VENDOR     = %s\n", (const char*)glGetString(GL_VENDOR));
    printf("GL_VERSION    = %s\n", (const char*)glGetString(GL_VERSION));
    printf("GL_RENDERER   = %s\n", (const char*)glGetString(GL_RENDERER));
    printf("GL_EXTENSIONS = %s\n", (const char*)glGetString(GL_EXTENSIONS));
}

/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
    const GLfloat shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT, GL_SHININESS, shininess);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, rouge);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, jaune);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, bleu);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
}

/* Scene dessinee                               */

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

float longeur = 4.0F * (10.0F * 2.0 * M_PI * 5.0F / 4.0F);
float delta = 0.2F;
float distance = 0.0F;


static void solidCylindre(double rayon, double hauteur, int nbFTube, int nbFHauteur) {
    GLboolean nm = glIsEnabled(GL_NORMALIZE);
    if (!nm)
        glEnable(GL_NORMALIZE);
    float normale[4];
    glGetFloatv(GL_CURRENT_NORMAL, normale);
    glPushMatrix();
    for (int j = 0; j < nbFHauteur; j++) {
        float hi = hauteur / 2 - j * hauteur / nbFHauteur;
        float hf = hi - hauteur / nbFHauteur;
        glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= nbFTube; i++) {
            float a = (2 * M_PI * i) / nbFTube;
            float cs = cos(a);
            float sn = -sin(a);
            glNormal3f(cs, 0.0F, sn);
            float x = rayon * cs;
            float z = rayon * sn;
            glVertex3f(x, hi, z);
            glVertex3f(x, hf, z);
        }
        glEnd();
    }
    glPopMatrix();
    glNormal3f(normale[0], normale[1], normale[2]);
    if (!nm)
        glDisable(GL_NORMALIZE);
}

void solidTore(double rayonTube, double rayonTore, double angleI, double angleF, int nbTube, int nbTore) {
    for (int i = 0; i < nbTore; i++) {
        float da = angleF - angleI;
        float alphai = angleI + da * i / nbTore;
        float alphaj = alphai + da / nbTore;
        float cosalphai = cos(alphai);
        float sinalphai = sin(alphai);
        float cosalphaj = cos(alphaj);
        float sinalphaj = sin(alphaj);
        glBegin(GL_QUAD_STRIP);
        for (int j = 0; j <= nbTube; j++) {
            float beta = 2 * M_PI * j / nbTube;
            float cosbeta = cos(beta);
            float sinbita = sin(beta);
            float x1 = (rayonTore + rayonTube * cosbeta) * cosalphai;
            float y1 = (rayonTore + rayonTube * cosbeta) * sinalphai;
            float z1 = rayonTube * sinbita;
            glNormal3f(cosbeta * cosalphai, cosbeta * sinalphai, sinbita);
            glVertex3f(x1, y1, z1);
            float x2 = (rayonTore + rayonTube * cosbeta) * cosalphaj;
            float y2 = (rayonTore + rayonTube * cosbeta) * sinalphaj;
            float z2 = rayonTube * sinbita;
            glNormal3f(cosbeta * cosalphaj, cosbeta * sinalphaj, sinbita);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
}

void solidTore(double rayonTube, double rayonTore, int nbFTube, int nbFTore) {
    solidTore(rayonTube, rayonTore, 0.0, 2 * M_PI, nbFTube, nbFTore);
}

void Sphere(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glutSolidSphere(1.2, 36, 36);
    glPopMatrix();
}

static void scene1(void) {
    glPushMatrix();
    // Axe du tunnel
    glMaterialfv(GL_FRONT, GL_DIFFUSE, vert);
    Sphere(5 + (2 * M_PI * 5 / 8.0), 0.0, 0.0);

    for (int i = 0; i < 4; i++) {
        glRotatef(90.0F * i, 0.0F, 1.0F, 0.0F);
        glPushMatrix();
        glTranslatef(-5.0F, 0.0F, 5.0F);
        glRotatef(90.0F, 1.0F, 0.0F, 0.0F);
        solidTore(0.05F, 5.0F, M_PI / 2.0, M_PI, 18, 100);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-10.0F, 0.0F, 0.0F);
        glRotatef(90.0F, 1.0F, 0.0F, 0.0F);
        solidCylindre(0.05F, 10.0F, 18, 100);
        glPopMatrix();
    }
    // Tunnel
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blanc);
    for (int i = 0; i < 4; i++) {
        glRotatef(90.0F * i, 0.0F, 1.0F, 0.0F);
        for (int i = 1; i <= 5; i++) {
            glPushMatrix();
            glTranslatef(5.0F, 0.0F, -5.0F);
            glRotatef(i * 180.0F / 12, 0.0F, 1.0F, 0.0F);
            glTranslatef(5.0F, 0.0F, 0.0F);
            solidTore(0.1, 2.0, 18, 72);
            glPopMatrix();
        }
        for (int i = -5; i <= 5; i++) {
            glPushMatrix();
            glTranslatef(10.0F, 0.0F, i);
            solidTore(0.1, 2.0, 18, 72);
            glPopMatrix();
        }
    }
    glPopMatrix();
}

static void scene2(void) {
    glPushMatrix();
    // Axe du tunnel
    glMaterialfv(GL_FRONT, GL_DIFFUSE, vert);
    glPushMatrix();
    glTranslatef(8.0F, 0.0F, 0.0F);
    glRotatef(90.0F, 1.0F, 0.0F, 0.0F);
    solidTore(0.05, 8.0, 18, 180);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-8.0F, 0.0F, 0.0F);
    glRotatef(90.0F, 1.0F, 0.0F, 0.0F);
    solidTore(0.05, 8.0, 18, 180);
    glPopMatrix();
    // Tunnel
    glMaterialfv(GL_FRONT, GL_DIFFUSE, blanc);
    for (int i = 0; i <= 36; i++) {
        glPushMatrix();
        glTranslatef(8.0F, 0.0F, 0.0F);
        glRotatef(i * 180.0F / 18, 0.0F, 1.0F, 0.0F);
        glTranslatef(8.0F, 0.0F, 0.0F);
        solidTore(0.1, 2.0, 18, 72);
        glPopMatrix();
        glPushMatrix();
        glTranslatef(-8.0F, 0.0F, 0.0F);
        glRotatef(i * 180.0F / 18, 0.0F, 1.0F, 0.0F);
        glTranslatef(-8.0F, 0.0F, 0.0F);
        solidTore(0.1, 2.0, 18, 72);
        glPopMatrix();
    }
    glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    printf("D\n");
    glClearColor(0.5F, 0.5F, 0.5F, 0.5F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const GLfloat light0_position[] = { 0.0,0.0,0.0,1.0 };
    const GLfloat light1_position[] = { -1.0,1.0,1.0,0.0 };
    const GLfloat light2_position[] = { 1.0,-1.0,1.0,0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glPushMatrix();
    gluLookAt(5.0, 10.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotatef(rz, 0.0F, 0.0F, 1.0F);
    glRotatef(ry, 0.0F, 1.0F, 0.0F);
    glRotatef(rx, 1.0F, 0.0F, 0.0F);
    if (obj) {
        scene1();
    }
    else {
        scene2();
    }
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
    printf("I\n");
    /*
    if (x1 == 10 && 21 < 10)
    {
        z1++;
        //printf("X = %f", X);
        //printf("Z = %f", Z);
    }
    
    */
    

    glutPostRedisplay();
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int x, int y) {
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0F, (float)x / y, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee lors de l'appui            */
/* d'une touche non alphanumerique du clavier   */

static void special(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        rx += 1.0F;
        glutPostRedisplay();
        break;
    case GLUT_KEY_DOWN:
        rx -= 1.0F;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        ry += 1.0F;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        ry -= 1.0F;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_UP:
        rz += 1.0F;
        glutPostRedisplay();
        break;
    case GLUT_KEY_PAGE_DOWN:
        rz -= 1.0F;
        glutPostRedisplay();
        break;
    }
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'f':
    case 'F':
    { static int fullScreen = 0;
    static int tx;
    static int ty;
    static int px;
    static int py;
    fullScreen = !fullScreen;
    if (fullScreen) {
        px = glutGet(GLUT_WINDOW_X);
        py = glutGet(GLUT_WINDOW_Y);
        tx = glutGet(GLUT_WINDOW_WIDTH);
        ty = glutGet(GLUT_WINDOW_HEIGHT);
        glutFullScreen();
    }
    else
        glutPositionWindow(px, py);
    glutReshapeWindow(tx, ty); }
    break;
    case 0x0D:
    { static int anim = 0;
    anim = !anim;
    glutIdleFunc((anim) ? idle : NULL); }
    break;
    case ' ':
    { informationsOpenGL(); }
    break;
    case 'o':
    case 'O':
        obj = !obj;
        glutPostRedisplay();
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
    glutCreateWindow("Un circuit matérialisé par des anneaux");
    init();
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    glutDisplayFunc(display);
    glutMainLoop();
    return(0);
}