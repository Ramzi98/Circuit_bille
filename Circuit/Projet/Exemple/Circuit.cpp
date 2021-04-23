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

#include "PNG/ChargePngFile.h"

/* Variables et constantes globales             */
/* pour les angles et les couleurs utilises     */

struct coord_3D {
    GLfloat x = 0.0F;
    GLfloat y = 0.0F;
    GLfloat z = 0.0F;
    GLfloat w = 1.0F;
};

struct polygone {
    int n = 0;
    coord_3D* p = NULL;
};

typedef struct coord_3D coord_3D;
typedef struct polygone polygone;


double hauteur_bord = 7;
double largeur = 20;
double rayonTore = 20;
double rayonBall = 3;
int etage = 3;
bool camera = false;
static int texture = 1;
static unsigned int textureID = 0;
static unsigned char* img1;



static float rx = 0.0F;
static float ry = 0.0F;
static float rz = 0.0F;

static float dx = 0.0F;
static float dy = 0.0F;
static float dz = 0.0F;

static float xball = -(rayonTore + largeur + 20) + rayonBall;
static float yball = 40.0 + rayonBall;
static float zball = -(rayonTore + largeur / 2);

static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float jaune[] = { 1.0F,1.0F,0.0F,1.0F };
static const float rouge[] = { 1.0F,0.0F,0.0F,1.0F };
static const float vert[] = { 0.0F,1.0F,0.0F,1.0F };
static const float bleu[] = { 0.0F,0.0F,1.0F,1.0F };




static GLfloat pts[6][4] = {
  { 80.0F,40.0F,-(rayonTore + largeur / 2), 1.0F },
  { 100.0F,40.0F,-(rayonTore + largeur), 1.0F },
  { 120.0F,40.0F,-(rayonTore + 2 * largeur), 1.0F },
  //{ 80.0F,0.0F,-(rayonTore + largeur/2), 1.0F }
};


static GLfloat pts2[6][4] = {
  { 120.0F,40.0F,-(rayonTore + 2 * largeur), 1.0F },
  { 160.0F,40.0F,-(rayonTore + largeur), 1.0F },
  { 120.0F,40.0F,-(rayonTore + largeur / 2), 1.0F }
};

static GLfloat pts3[6][4] = {
  { 120.0F,40.0F,-(rayonTore + largeur / 2), 1.0F },
  { 80.0F,0.0F,-(rayonTore + largeur / 2), 1.0F },
};


static GLfloat pts4[6][4] = {
  { 80.0F,0.0F,(rayonTore + largeur / 2), 1.0F },
  { 100.0F,0.0F,(rayonTore + largeur), 1.0F },
  { 120.0F,0.0F,(rayonTore + 2 * largeur), 1.0F },
};


static GLfloat pts5[6][4] = {
  { 120.0F,0.0F,(rayonTore + 2 * largeur), 1.0F },
  { 160.0F,0.0F,(rayonTore + largeur), 1.0F },
  { 120.0F,0.0F,(rayonTore + largeur / 2), 1.0F }
};

static GLfloat pts6[6][4] = {
  { 120.0F,0.0F,(rayonTore + largeur / 2), 1.0F },
  { 80.0F,-40.0F,(rayonTore + largeur / 2), 1.0F },
};


static polygone pl;
static int aff = 3;

void bas_relie(float x, float y, float z) {
    glVertex3f(x, y, (z-largeur/2));
    glVertex3f(x, y, (z + largeur / 2));
}

void interieur_relie(float x, float y, float z) {
    glVertex3f(x, y, (z + largeur / 2));
    glVertex3f(x, y + hauteur_bord, (z + largeur / 2));
}

void exterieur_relie(float x, float y, float z) {
    glVertex3f(x, y, (z - largeur / 2));
    glVertex3f(x, y + hauteur_bord, (z - largeur / 2));
}

void bezier(polygone* p, int n, int d) {
    int i, j;
    float t, mt;
    float* cn, x,y,z,fac;
    cn = (float*)calloc(p->n, sizeof(float));
    cn[0] = 1;
    cn[1] = (float)(p->n - 1);
    for (i = 2; i < p->n; i++)
        cn[i] = cn[i - 1] * (p->n - i) / i;
    for (i = 0; i < n; i++) {
        t = (float)i / (n - 1);
        mt = 1 - t;
        x = y = z = 0.0F;
        for (j = 0; j < p->n; j++) {
            fac = cn[j] * (float)pow(t, j) *
                (float)pow(mt, p->n - 1 - j);
            x += fac * p->p[j].x;
            y += fac * p->p[j].y;
            z += fac * p->p[j].z;
        }
        if (d == 1)
        {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, bleu);
            bas_relie(x, y, z);
        }

        if (d == 2)
        {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);

            interieur_relie(x, y, z);
        }

        if (d == 3)
        {
            glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);

            exterieur_relie(x, y, z);
        }
        
        
        
    }
    free(cn);
}




/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static void init(void) {
    const GLfloat shininess[] = { 50.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
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
   // initTexture();
    
}

/* Scene dessinee                               */

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950288
#endif

float longeur = 4.0F * (10.0F * 2.0 * M_PI * 5.0F / 4.0F);
float delta = 0.2F;
float distance = 0.0F;




void Circuit_droit(double p1[], double p2[], double p3[], double p4[])
{
    //printf("X = %f , Y = %f , Z = %f \n", p1[0], p1[1], p1[2]);

        glBegin(GL_QUADS);

        glNormal3f(p1[0], p1[1], p1[2]);
        glVertex3f(p1[0], p1[1], p1[2]);

        glNormal3f(p2[0], p2[1], p2[2]);
        glVertex3f(p2[0], p2[1], p2[2]);

        glNormal3f(p3[0], p3[1], p3[2]);
        glVertex3f(p3[0], p3[1], p3[2]);

        glNormal3f(p4[0], p4[1], p4[2]);
        glVertex3f(p4[0], p4[1], p4[2]);


        glEnd();
   
}


void etage1_3(double x, double y, double z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
   
    glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);

    //Bord interieur 1 
    double p1[] = { 0.0, 0.0, -rayonTore };
    double p2[] = { 80.0 + rayonTore + largeur + 20, 0.0, -rayonTore };
    double p3[] = { 80.0 + rayonTore + largeur + 20, hauteur_bord, -rayonTore };
    double p4[] = { 0.0, hauteur_bord, -rayonTore };
    Circuit_droit(p1, p2, p3, p4);


    //Bord exterieur 1
    double p5[] = { 0.0, 0.0, -(rayonTore + largeur) };
    double p6[] = { 80.0 + rayonTore + largeur + 20, 0.0, -(rayonTore + largeur) };
    double p7[] = { 80.0 + rayonTore + largeur + 20, hauteur_bord, -(rayonTore + largeur) };
    double p8[] = { 0.0, hauteur_bord, -(rayonTore + largeur) };
    Circuit_droit(p5, p6, p7, p8);


  
     
    //Fin1
    double pf5[] = { 0.0, 0.0, -rayonTore };
    double pf6[] = { 0.0, 0.0, -(rayonTore + largeur) };
    double pf7[] = { 0.0, hauteur_bord, -(rayonTore + largeur) };
    double pf8[] = { 0.0, hauteur_bord, -rayonTore };
    Circuit_droit(pf5, pf6, pf7, pf8);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, blanc);

    //La Base 1
    double p21[] = { 0.0, 0.0, -rayonTore };
    double p22[] = { 80.0 + rayonTore + largeur + 20, 0.0, -rayonTore };
    double p23[] = { 80.0 + rayonTore + largeur + 20, 0.0, -(rayonTore + largeur) };
    double p24[] = { 0.0, 0.0, -(rayonTore + largeur) };
    Circuit_droit(p21, p22, p23, p24);

    

    glPopMatrix();
}





void virage_bas(double x1, double y1, double z1, double x2, double y2, double z2)
{
    glNormal3f(x1, y1, -z1);
    glVertex3f(x1, y1, z1);

    glNormal3f(x2, y1, -z2);
    glVertex3f(x2, y1, z2);


    glNormal3f(x1, y2, -z1);
    glVertex3f(x1, y2, z1);

    glNormal3f(x2, y2, -z2);
    glVertex3f(x2, y2, z2);
}

void virage_board_interieur(double x1, double y1, double z1, double x2, double y2, double z2)
{
    glNormal3f(x1, y1, -z1);
    glVertex3f(x1, y1, z1);

    glNormal3f(x1, y1, -z2);
    glVertex3f(x2, y1, z2);


    glNormal3f(x1, y2, -z1);
    glVertex3f(x1, y2, z1);

    glNormal3f(x1, y2, -z2);
    glVertex3f(x2, y2, z2);
}

void virage_board_exterieur(double x1, double y1, double z1, double x2, double y2, double z2)
{
    glNormal3f(x1, y1, -z1);
    glVertex3f(x1, y1, z1);

    glNormal3f(x2, y1, -z2);
    glVertex3f(x2, y1, z2);


    glNormal3f(x1, y2, -z1);
    glVertex3f(x1, y2, z1);

    glNormal3f(x2, y2, -z2);
    glVertex3f(x2, y2, z2);
}



void Virage(double largeur ,double rayonTore, double angleI, double angleF, int nbCube) {
    

    glBegin(GL_QUAD_STRIP);

    for (int i = 0; i < nbCube; i++) {
        
        float da = angleF - angleI;

        float alphai = angleI + da * i / nbCube;
        float alphaj = alphai + da / nbCube;

        float cosalphai = cos(alphai);
        float sinalphai = sin(alphai);
        float cosalphaj = cos(alphaj);
        float sinalphaj = sin(alphaj);

        
        float x1b, y1b, z1b;
        float x2b, y2b, z2b;

        if (i == nbCube - 1)
        {
            x1b = 0.0;
            y1b = 0.0;
            z1b = -rayonTore * cosalphai;
        }
        else
        {
            x1b = -rayonTore * sinalphai;
            y1b = 0.0;
            z1b = -rayonTore * cosalphai;
        }


        if (i == 0)
        {
            x2b = 0.0;
            y2b = 0.0;
            z2b = -(rayonTore + largeur);
        }
        else
        {
            x2b = -(rayonTore + largeur) * sinalphaj;
            y2b = 0.0;
            z2b = -(rayonTore + largeur) * cosalphaj;
        }

        glMaterialfv(GL_FRONT, GL_DIFFUSE, blanc);

        virage_bas(x1b, y1b, z1b, x2b, y2b, z2b);

    }
    glEnd();

    
    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < nbCube; i++) {
        float da = angleF - angleI;

        float alphai = angleI + da * i / nbCube;
        float alphaj = alphai + da / nbCube;

        float cosalphai = cos(alphai);
        float sinalphai = sin(alphai);
        float cosalphaj = cos(alphaj);
        float sinalphaj = sin(alphaj);


        float x1i = -rayonTore * sinalphai;
        float y1i = 0;
        float z1i = -rayonTore * cosalphai;

        float x2i = -rayonTore * sinalphaj;
        float y2i = hauteur_bord;
        float z2i = -rayonTore * cosalphaj;
        /*
        if (i < 10 )
        {
            printf("X1 = %f ", x1i);
            printf("Y1 = %f ", y1i);
            printf("Z1 = %f ", z1i);

            printf("X2 = %f ", x2i);
            printf("Y2 = %f ", y2i);
            printf("Z2 = %f \n", z2i);
        }
        */
        glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);

        virage_board_interieur(x1i, y1i, z1i, x2i, y2i, z2i);

    }
    glEnd();

    glBegin(GL_QUAD_STRIP);
    for (int i = 0; i < nbCube; i++) {
        float da = angleF - angleI;

        float alphai = angleI + da * i / nbCube;
        float alphaj = alphai + da / nbCube;

        float cosalphai = cos(alphai);
        float sinalphai = sin(alphai);
        float cosalphaj = cos(alphaj);
        float sinalphaj = sin(alphaj);

        float x1e = -(rayonTore + largeur) * sinalphai;
        float y1e = 0;
        float z1e = -(rayonTore + largeur) * cosalphai;

        float x2e = -(rayonTore + largeur) * sinalphaj;
        float y2e = hauteur_bord;
        float z2e = -(rayonTore + largeur) * cosalphaj;

        glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);

        virage_board_exterieur(x1e, y1e, z1e, x2e, y2e, z2e);

    }
    glEnd();
    
    
}



void Sphere(float x, float y, float z)
{
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, bleu);
    glTranslatef(x, y, z);
    glutSolidSphere(rayonBall, 36, 36);
    glPopMatrix();
}

static void etage2(double x ,double y , double z) {

    glPushMatrix();
    glTranslatef(x, y, z);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);
    
    glPushMatrix();
    //Bord interieur 1 
    double p1[] = { 0.0, 0.0, -rayonTore };
    double p2[] = { 80.0, 0.0, -rayonTore };
    double p3[] = { 80.0, hauteur_bord, -rayonTore };
    double p4[] = { 0.0, hauteur_bord, -rayonTore };
    Circuit_droit(p1,p2,p3,p4);


    //Bord exterieur 1
    double p5[] = { 0.0, 0.0, -(rayonTore + largeur) };
    double p6[] = { 80.0, 0.0, -(rayonTore + largeur) };
    double p7[] = { 80.0, hauteur_bord, -(rayonTore + largeur) };
    double p8[] = { 0.0, hauteur_bord, -(rayonTore + largeur) };
    Circuit_droit(p5, p6, p7, p8);

   

    //Fin1
    double pf1[] = { 80.0, 0.0, -rayonTore };
    double pf2[] = { 80.0, 0.0, -(rayonTore+largeur) };
    double pf3[] = { 80.0, hauteur_bord, -(rayonTore + largeur) };
    double pf4[] = { 80.0, hauteur_bord, -rayonTore };
    Circuit_droit(pf1, pf2, pf3, pf4);


    glMaterialfv(GL_FRONT, GL_DIFFUSE, blanc);

    //La Base 1
    double p21[] = { 0.0, 0.0, -rayonTore };
    double p22[] = { 80.0, 0.0, -rayonTore };
    double p23[] = { 80.0, 0.0, -(rayonTore + largeur) };
    double p24[] = { 0.0, 0.0, -(rayonTore + largeur) };
    Circuit_droit(p21, p22, p23, p24);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);

    //Bord interieur 2 
    double p11[] = { 0.0, 0.0, rayonTore };
    double p12[] = { 80.0, 0.0, rayonTore };
    double p13[] = { 80.0, hauteur_bord, rayonTore };
    double p14[] = { 0.0, hauteur_bord, rayonTore };
    Circuit_droit(p11, p12, p13, p14);


    //Bord exterieur 2
    double p15[] = { 0.0, 0.0, (rayonTore + largeur) };
    double p16[] = { 80.0, 0.0, (rayonTore + largeur) };
    double p17[] = { 80.0, hauteur_bord, (rayonTore + largeur) };
    double p18[] = { 0.0, hauteur_bord, (rayonTore + largeur) };
    Circuit_droit(p15, p16, p17, p18);


    //Fin 2
    double pf5[] = { 80.0, 0.0, rayonTore };
    double pf6[] = { 80.0, 0.0, rayonTore + largeur };
    double pf7[] = { 80.0, hauteur_bord, rayonTore + largeur };
    double pf8[] = { 80.0, hauteur_bord, rayonTore };
    Circuit_droit(pf5, pf6, pf7, pf8);


    glMaterialfv(GL_FRONT, GL_DIFFUSE, blanc);

    //La Base 2
    double p25[] = { 0.0, 0.0, rayonTore };
    double p26[] = { 80.0, 0.0, rayonTore };
    double p27[] = { 80.0, 0, rayonTore + largeur };
    double p28[] = { 0.0, 0, rayonTore + largeur };
    Circuit_droit(p25, p26, p27, p28);
   

  
    glPopMatrix();

    //Virage

    glPushMatrix();
    Virage(largeur,rayonTore, 0, M_PI, 30);
    glPopMatrix();



    
    
    glPopMatrix();
}

void relie_etage_3_2(double x, double y, double z)
{
    glPushMatrix();


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

    if (texture)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
    if (camera == false)
    {
        gluLookAt(0.0, 10.0, 10.0, 0.0, 0.0, 0.0, 0.0, 0.0, -20.0);
    }
    else
    {
        gluLookAt(xball - 10, yball + 10, zball, xball, yball, zball, 0.0, 10.0, 0.0);
    }
    
    glRotatef(rz, 0.0F, 0.0F, 1.0F);
    glRotatef(ry, 0.0F, 1.0F, 0.0F);
    glRotatef(rx, 1.0F, 0.0F, 0.0F);

    glTranslatef(dx, dy, dz);

        etage2(0.0,0.0,0.0);

        
        etage1_3(-(rayonTore + largeur + 20), 40.0, 0.0);
        etage1_3(-(rayonTore + largeur + 20), -40.0, rayonTore + 2*largeur);

        Sphere(xball,yball,zball);

        // Relie 3_2
        pl.n = aff;
        pl.p = (coord_3D*)&pts[0][0];
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40,1);
        glEnd();
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40, 2);
        glEnd();
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40, 3);
        glEnd();

       
        pl.p = (coord_3D*)&pts2[0][0];
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40,1);
        glEnd();
     

        pl.n = 2;
        pl.p = (coord_3D*)&pts3[0][0];
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40,1);
        glEnd();
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40, 2);
        glEnd();
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40, 3);
        glEnd();

        //////////////////////////////////////////////////////////


         // Relie 2_1

        pl.n = aff;
        pl.p = (coord_3D*)&pts4[0][0];
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40, 1);
        glEnd();
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40, 2);
        glEnd();
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40, 3);
        glEnd();
        

        pl.p = (coord_3D*)&pts5[0][0];
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40, 1);
        glEnd();

        pl.n = 2;
        pl.p = (coord_3D*)&pts6[0][0];
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40, 1);
        glEnd();
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40, 2);
        glEnd();
        glBegin(GL_QUAD_STRIP);
        bezier(&pl, 40, 3);
        glEnd();
        
      

    glPopMatrix();

 

   


    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);
}

/* Fonction executee lorsqu'aucun evenement     */
/* n'est en file d'attente                      */

static void clean(void) {
    if (textureID != 0)
        glDeleteTextures(1, &textureID);
}


static void idle(void) {
    printf("I\n");

    if (xball < 80.0-rayonBall && etage == 3)
    {
        xball += 1.0F / 50.0;
        /*
        if (xball == (80.0 - rayonBall + (1.0F / 50.0)))
        {
            etage = 2;
        }
        */
    }

    printf("etage : %d\n", etage);
    glutPostRedisplay();
}

/* Fonction executee lors d'un changement       */
/* de la taille de la fenetre OpenGL            */

static void reshape(int x, int y) {
    glViewport(0, 0, x, y);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(100.0F, (float)x / y, 1.0, 1000.0);
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
    case 0x1B:
        exit(0);
        break;
    case 'z':
        dy -= 1.0;
        glutPostRedisplay();
        break;
    case 's':
        dy += 1.0;
        glutPostRedisplay();
        break;
    case 'd':
        dx -= 1.0;
        glutPostRedisplay();
        break;
    case 'q':
        dx += 1.0;
        glutPostRedisplay();
        break;
    case 'a':
        dz -= 1.0;
        glutPostRedisplay();
        break;
    case 'e':
        dz += 1.0;
        glutPostRedisplay();
        break;
    case 'c':
        camera = !camera;
        glutPostRedisplay();
        break;
    case 0x20:
        texture = (texture + 1) % 2;
        glutPostRedisplay();
        break;
    }
    
        

    
}




//texture
/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */

static unsigned char* image(int nc, int nl) {
    unsigned char* img = (unsigned char*)calloc(3 * nc * nl, sizeof(unsigned char));
    if (!img)
        return NULL;
    unsigned char* p = img;
    for (int l = 0; l < nl; l++)
        for (int c = 0; c < nc; c++) {
            if (l % 2 == 0) {
                if (c % 2 == 0) {
                    p[0] = 0x00;
                    p[1] = 0x00;
                    p[2] = 0x00;
                }
                else {
                    p[0] = 0xFF;
                    p[1] = 0x00;
                    p[2] = 0x00;
                }
            }
            else {
                if (c % 2 == 0) {
                    p[0] = 0x00;
                    p[1] = 0xFF;
                    p[2] = 0x00;
                }
                else {
                    p[0] = 0x00;
                    p[1] = 0x00;
                    p[2] = 0xFF;
                }
            }
            p += 3;
        }
    return img;
}


static void initTexture(void) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    { int rx = 16;
    int ry = 16;
    /*unsigned char* img = image(rx, ry);
    if (img) {
        glTexImage2D(GL_TEXTURE_2D, 0, 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
        free(img);
        printf("Texture chargee %d\n", textureID);
    }
    else {
        glDeleteTextures(1, &textureID);
        textureID = 0;
        printf("Texture non chargee\n");
    }*/


    char* nomFichier = "Test.png/Emoji4.png";
    img1 = chargeImagePng(nomFichier, &rx, &ry);
    if (img1) {
        printf("Resolution en x : %8d\n", rx);
        printf("Resolution en y : %8d\n", ry);
        printf("Adresse         : %p, %d octets\n", img1, 3 * rx * ry);
        free(img1);
    }
    else {
        printf("Adresse         : %p\n", img1);
    }



    glTexImage2D(GL_TEXTURE_2D, 0 , 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
    // free(img1   );
    printf("Texture chargee %d\n", textureID); }
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

/* Fonction principale                          */

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(1200, 840);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Un circuit à bille");
    init();
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutSpecialFunc(special);
    glutDisplayFunc(display);
    glutMainLoop();
    return(0);
}