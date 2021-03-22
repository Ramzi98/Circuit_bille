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
static int pMode = 1;              // Flag de switch entre modes d'affichage wireframe et fill 
static int mouseActive = 0;        // Flag de d'indication que la souris est active (bouton presse) ou non 
static float sens = 1.0F;          // Sens de rotation de la scene sur elle-meme autour de l'axe x
static int mouseX = 0;

bool mode = false;
int rx = 0;
int ry = 0;
static float rz = 0.0F;            // Angle de rotation de la scene sur elle-meme autour de l'axe z
bool animation = false;


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

void facetteTrouee(void)
{
    glBegin(GL_TRIANGLE_STRIP);
    glVertex3f(1.0F, 1.0F, 0.0F);
    glVertex3f(0.5F, 0.0F, 0.0F);
    glVertex3f(1.0F, -1.0F, 0.0F);
    glVertex3f(0.0F, -0.5F, 0.0F);
    glVertex3f(-1.0F, -1.0F, 0.0F);
    glVertex3f(-0.5F, 0.0F, 0.0F);
    glVertex3f(-1.0F, 1.0F, 0.0F);
    glVertex3f(0.0F, 0.5F, 0.0F);
    glVertex3f(1.0F, 1.0F, 0.0F);
    glVertex3f(0.5F, 0.0F, 0.0F);
    glEnd();
}

void mySolidCubeSansNormales(double c1)
{
    float c = (float)c1 / 2.0F;
    glPushMatrix();
    glBegin(GL_QUADS);
    {
        glVertex3f(c, c, c);    // 1
        glVertex3f(-c, c, c);   // 2
        glVertex3f(-c, -c, c);  // 3
        glVertex3f(c, -c, c);   // 4
    }
    {
        glVertex3f(c, c, c);    // 1
        glVertex3f(c, -c, c);   // 4
        glVertex3f(c, -c, -c);  // 8
        glVertex3f(c, c, -c);   // 5
       
    }
    {
        glVertex3f(c, c, -c);   // 5
        glVertex3f(c, -c, -c);  // 8
        glVertex3f(-c, -c, -c); // 7
        glVertex3f(-c, c, -c);  // 6
    }
    {
        glVertex3f(-c, -c, c);  // 3
        glVertex3f(-c, c, c);   // 2
        glVertex3f(-c, c, -c);  // 6
        glVertex3f(-c, -c, -c); // 7
    }
    {
        glVertex3f(c, c, c);    // 1
        glVertex3f(c, c, -c);   // 5
        glVertex3f(-c, c, -c);  // 6
        glVertex3f(-c, c, c);   // 2
    }
    {
        glVertex3f(c, -c, c);   // 4
        glVertex3f(-c, -c, c);  // 3
        glVertex3f(-c, -c, -c); // 7
        glVertex3f(c, -c, -c);  // 8
    }
    glEnd();
    glPopMatrix();
}

void mySolidCubeAvecNormales(double c1)
{
    float c = (float)c1 / 2.0F;

    glEnable(GL_NORMALIZE);
    glNormal3f(0.0F, 0.0F, 1.0F);
    glEnable(GL_CULL_FACE);
       
    glPushMatrix();
    glBegin(GL_QUADS);
    {
        glNormal3f(0.0F, 0.0F, 1.0F);
        glVertex3f(c, c, c);    // 1
        glVertex3f(-c, c, c);   // 2
        glVertex3f(-c, -c, c);  // 3
        glVertex3f(c, -c, c);   // 4
    }
    {
        glVertex3f(c, c, c);    // 1
        glVertex3f(c, -c, c);   // 4
        glVertex3f(c, -c, -c);  // 8
        glVertex3f(c, c, -c);   // 5

    }
    {
        glVertex3f(c, c, -c);   // 5
        glVertex3f(c, -c, -c);  // 8
        glVertex3f(-c, -c, -c); // 7
        glVertex3f(-c, c, -c);  // 6
    }
    {
        glVertex3f(-c, -c, c);  // 3
        glVertex3f(-c, c, c);   // 2
        glVertex3f(-c, c, -c);  // 6
        glVertex3f(-c, -c, -c); // 7
    }
    {
        glVertex3f(c, c, c);    // 1
        glVertex3f(c, c, -c);   // 5
        glVertex3f(-c, c, -c);  // 6
        glVertex3f(-c, c, c);   // 2
    }
    {
        glVertex3f(c, -c, c);   // 4
        glVertex3f(-c, -c, c);  // 3
        glVertex3f(-c, -c, -c); // 7
        glVertex3f(c, -c, -c);  // 8
    }
    glEnd();
    glPopMatrix();

}

/* Scene dessinee                               */

static void scene(void) {
    glPushMatrix();

    mySolidCubeSansNormales(1);

    glPopMatrix();
}

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    printf("D\n");

    if (mode == false)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    printf("%d %d %d\n", rx, ry, rz);

    glPushMatrix();

    glRotatef(rz, 0, 0, 1);
    glRotatef(rx, 1, 0, 0);
    glRotatef(ry, 0, 1, 0);

    scene();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int wx, int wy) {
    printf("R\n");
    wTx = wx;
    wTy = wy;
    glViewport(0, 0, wx, wy);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void idle(void) {
    printf("I\n");
    rx++;
    glutPostRedisplay();
}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    printf("K  %4c %4d %4d\n", key, x, y);
    switch (key) {
    case 0x1B:
        exit(0);
        break;
    case 0x20:
        if (mode == false)
        {
            mode = true;
        }
        else
        {
            mode = false;
        }
        glutPostRedisplay();
        break;
    case 0x0d:
        if (animation == false)
        {
            glutIdleFunc(idle);
            animation = true;
        }
        else
        {
            glutIdleFunc(NULL);
            animation = false;
        }
        break;
    }
}

/* Fonction executee lors de l'appui            */
/* d'une touche speciale du clavier :           */
/*   - touches de curseur                       */
/*   - touches de fonction                      */

static void special(int specialKey, int x, int y) {
    printf("S  %4d %4d %4d\n", specialKey, x, y);
    switch (specialKey)
    {
    case GLUT_KEY_DOWN:
        rx--;
        glutPostRedisplay();
        break;
    case GLUT_KEY_UP:
        rx++;
        glutPostRedisplay();
        break;
    case GLUT_KEY_RIGHT:
        ry++;
        glutPostRedisplay();
        break;
    case GLUT_KEY_LEFT:
        ry--;
        glutPostRedisplay();
        break;
    }

}

/* Fonction executee lors de l'utilisation      */
/* de la souris sur la fenetre                  */

static void mouse(int button, int state, int x, int y) {
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {
        mouseX = x;
        mouseActive = 1;
    }
    if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_UP)) {
        mouseActive = 0;
    }
    if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_UP))
        sens *= -1.0F;
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* avec un bouton presse                        */

static void mouseMotion(int x, int y) {
    if (mouseActive) {
        rz += (mouseX - x);
        mouseX = x;
        glutPostRedisplay();
    }
}

/* Fonction executee lors du passage            */
/* de la souris sur la fenetre                  */
/* sans bouton presse                           */

static void passiveMouseMotion(int x, int y) {
    printf("PM %4d %4d\n", x, y);
}

/* Fonction exécutée automatiquement            */
/* lors de l'exécution de la fonction exit()    */

static void clean(void) {
    printf("Bye\n");
}

/* Fonction principale                          */

int main(int argc, char** argv) {

    atexit(clean); //excuter clean aprés la sortie exit

    glutInit(&argc, argv); // intialiser glut qui va créer la fenetre 
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE); //GLUT_RGBA : mode d'affichage RGB c a d en 4 octet A c'est la couleur Aplpha pour la transparance
    //GLUT_DEPTH : dit a open GL de permet l'elimination des partie cacher
    glutInitWindowSize(wTx, wTy);// définit la zone d'affichage en PX de la fenetre
    glutInitWindowPosition(wPx, wPy); // définir la position de la fenetre par rapport a l'écran
    glutCreateWindow("Gestion événementielle de GLUt"); // Créer la fenetre et donner le titre
    init();
    glutKeyboardFunc(keyboard);//Glut mettre en attente le click sur une button alpha numérique
    glutSpecialFunc(special);
    glutMouseFunc(mouse);// fonction pour utiliser la souris 
    glutMotionFunc(mouseMotion);// fonction pour utiliser la souris deplacement
    //glutPassiveMotionFunc(passiveMouseMotion);
    glutReshapeFunc(reshape);//Fonction pour la redimension de la fenetre
    //glutIdleFunc(idle);// la fonction lorsque y'a pas d'autre chose a faire
    //glutIdleFunc(NULL);
    glutDisplayFunc(display);//la fentre qui va etre afficher lorsque en rafrichir
    glutMainLoop();//Ouvrir la fenetre et mettre une boucle infinie 
    return(0);
}