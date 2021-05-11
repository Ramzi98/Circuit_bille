#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#define WIDTH 1200
#define HEIGHT 900 
int nFullScreen = 1;


#include "PNG/ChargePngFile.h"
#include "Balle.h"
#include "Pos3d.h"

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
static int f1;
static int f2;

double hauteur_bord = 7;
double largeur = 20;
double rayonTore = 20;
double rayonBall = 3;
int etage = 3;
int camera = 0;
static int texture = 1;
static unsigned int textureID = 0;
static unsigned char* img1;



static float rx = 0.0F;
static float ry = 0.0F;
static float rz = 0.0F;

static float dx = 0.0F;
static float dy = 0.0F;
static float dz = 0.0F;
//Position initiale de la balle
/*static float positionBall.x = -(rayonTore + largeur + 20) + rayonBall;
static float positionBall.y = 40.0 + rayonBall;
static float positionBall.z = -(rayonTore + largeur / 2);*/
Pos3D positionBall(-(rayonTore + largeur + 20) + rayonBall, 40.0 + rayonBall, -(rayonTore + largeur / 2));
//Création balle
Balle laBalle;
bool ligth1 = true, ligth2 = true, ligth3 = true, ligth4 = true, ligth5 = true;
static float spotDir[3] = { 0.0, -1.0,0.0 };
const GLfloat spotCutOff = 20.0;

static const float blanc[] = { 1.0F,1.0F,1.0F,1.0F };
static const float jaune[] = { 1.0F,1.0F,0.0F,1.0F };
static const float rouge[] = { 1.0F,0.0F,0.0F,1.0F };
static const float vert[] = { 0.0F,1.0F,0.0F,1.0F };
static const float bleu[] = { 0.0F,0.0F,1.0F,1.0F };
static const float gris[] = { 0.5F,0.5F,0.5F,1.0F };
static const float noir[] = { 0.0F,0.0F,0.0F,1.0F };
static int cFond = 0;              // Numero de la couleur de fond (0: gris, 1: blanc, 2:noir)



coord_3D cord1[100000];
coord_3D cord2[100000];
int k = 0;
int k1 = 0;
int k2 = 0;
int k3 = 0;
int cmpt1 = 0;
int cmpt2 = 0;

float vitesse1 = 0.5F;
float vitesse2 = 3.0F;
float vitesse3 = 3.0F;

//Variable pour switcher d'affichage entre mode par facette et mode en fil de fer
//static int affS = 1;

float rt = 0;


static GLfloat pts[6][4] = {
  { 80.0F,40.0F,-(rayonTore + largeur / 2), 1.0F },
  { 100.0F,40.0F,-(rayonTore + largeur), 1.0F },
  { 120.0F,40.0F,-(rayonTore + 2 * largeur), 1.0F },
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

static double axesElevator[4][3] = {
  { 0, -40, 0 },//1
  { largeur, -40, 0 },//2
  { largeur, -40.0, -20.0 },//3
  { 0.0, -40.0, -20.0 }//4
};

double p1[] = { 0, 0, 0 };//1
double p2[] = { largeur, 0, 0 };//2
double p3[] = { largeur, 0.0, -20.0 };//3
double p4[] = { 0.0, 0.0, -20.0 };//4

static polygone pl;
static int aff = 3;

static void postRedisplay(void) {
    glutPostWindowRedisplay(f1);
    glutPostWindowRedisplay(f2);
}


void bas_relie(float x, float y, float z) {
    glVertex3f(x, y, (z - largeur / 2));
    glTexCoord2f(0.0F, 0.0F);

    glVertex3f(x, y, (z + largeur / 2));
    glTexCoord2f(0.0F, 1.0F);

    if (cmpt1 <= 20)
    {
        cord1[k].x = x;
        cord1[k].y = y;
        cord1[k].z = z;
        k++;
    }


}

void lighting1()
{

    GLfloat pos[4] = { -(rayonTore + largeur + 20), -100.0, -20.0, 1.0 };
    glLightfv(GL_LIGHT3, GL_DIFFUSE, blanc);
    glLightfv(GL_LIGHT3, GL_POSITION, pos);
    glEnable(GL_LIGHT3);
}

void lighting2()
{
    GLfloat pos[4] = { -2.0, 0.0, 4.0, 0.0 };
    // GLfloat pos[4] = { 60.0, 80.0, 0.0, 1.0 };
    glLightfv(GL_LIGHT4, GL_POSITION, pos);
    glLightfv(GL_LIGHT4, GL_DIFFUSE, vert);
    glLightfv(GL_LIGHT4, GL_SPECULAR, blanc);
    glEnable(GL_LIGHT4);
}

void lighting3()
{
    GLfloat pos[4] = { -3.0,-3.0, 15.0, 1.0 };
    glLightfv(GL_LIGHT5, GL_DIFFUSE, vert);
    glLightfv(GL_LIGHT5, GL_POSITION, pos);
    glLightfv(GL_LIGHT5, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT5, GL_SPOT_CUTOFF, spotCutOff);
    glEnable(GL_LIGHT5);
}


void lighting4()
{
    GLfloat pos[4] = { 0.0,0.0,0.0,1.0 };

    glLightfv(GL_LIGHT6, GL_DIFFUSE, vert);
    glLightfv(GL_LIGHT6, GL_POSITION, pos);
    glLightfv(GL_LIGHT6, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT6, GL_SPOT_CUTOFF, spotCutOff);
    glEnable(GL_LIGHT6);
}

void lighting5()
{
    GLfloat pos[4] = { -1.0,1.0,1.0,0.0 };;
    glLightfv(GL_LIGHT7, GL_DIFFUSE, vert);
    glLightfv(GL_LIGHT7, GL_POSITION, pos);
    glLightfv(GL_LIGHT7, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT7, GL_SPOT_CUTOFF, spotCutOff);
    glEnable(GL_LIGHT7);
}

void lighting6()
{
    GLfloat pos[4] = { -1.0,1.0,1.0,0.0 };;
    glLightfv(GL_LIGHT0, GL_DIFFUSE, vert);
    glLightfv(GL_LIGHT0, GL_POSITION, pos);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spotDir);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, spotCutOff);
    glEnable(GL_LIGHT0);
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
    float* cn, x, y, z, fac;
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
    cmpt1++;
    free(cn);
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


/* Fonction d'initialisation des parametres     */
/* OpenGL ne changeant pas au cours de la vie   */
/* du programme                                 */




static void initTexture(void) {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);
    { int rx = 512;
    int ry = 256;



    char* nomFichier = "Testpng/Emoji4.png";
    img1 = chargeImagePng(nomFichier, &rx, &ry);
    if (img1) {
        printf("Resolution en x : %8d\n", rx);
        printf("Resolution en y : %8d\n", ry);
        printf("Adresse         : %p, %d octets\n", img1, 3 * rx * ry);

    }
    else {
        printf("Adresse         : %p\n", img1);
    }



    glTexImage2D(GL_TEXTURE_2D, 0, 3, rx, ry, 0, GL_RGB, GL_UNSIGNED_BYTE, img1);
    free(img1);
    
    }
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    // getchar();
}


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
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
    glEnable(GL_LIGHT5);
    glEnable(GL_LIGHT6);
    glEnable(GL_LIGHT7);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);
    glEnable(GL_AUTO_NORMAL);
    initTexture();
    glEnable(GL_TEXTURE_2D);

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
    glBegin(GL_QUADS);

    glNormal3f(p1[0], p1[1], p1[2]);
    glVertex3f(p1[0], p1[1], p1[2]);
  //  glTexCoord2f(0.0F, 0.0F);

    glNormal3f(p2[0], p2[1], p2[2]);
    glVertex3f(p2[0], p2[1], p2[2]);
  //  glTexCoord2f(0.0F, 1.0F);

    glNormal3f(p3[0], p3[1], p3[2]);
    glVertex3f(p3[0], p3[1], p3[2]);
   // glTexCoord2f(1.0F, 1.0F);

    glNormal3f(p4[0], p4[1], p4[2]);
    glVertex3f(p4[0], p4[1], p4[2]);
    //glTexCoord2f(1.0F, 0.0F);

    glEnd();

}

void cylindre(Pos3D pos, GLUquadricObj* qobj, double h, double r0, int n, int m) {
    glPushMatrix();
    glRotatef(90.0F, 1.0F, 0.0F, 0.0F);
    glTranslatef(0.0F, 0.0F, -h / 2);
    glTranslatef(pos.x, pos.y, pos.z);
    //GLUquadricObj* qobj = q; 
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluCylinder(qobj, r0, r0, h, n, m);
    //gluDeleteQuadric(qobj);
    glPopMatrix();
}


void ascenceur1(double x, double y, double z)
{
    glPushMatrix();

    glTranslatef(x, y, z);

    Pos3D pilier1(0, 0, 0);
    GLUquadricObj* po1 = gluNewQuadric();
    cylindre(pilier1, po1, 80, 3, 15, 15);
    gluDeleteQuadric(po1);

    //Circuit_droit(p1, p2, p3, p4);
    Pos3D pilier2(largeur, 0.0, 0.0);
    GLUquadricObj* po2 = gluNewQuadric();
    cylindre(pilier2, po2, 80, 3, 15, 15);
    gluDeleteQuadric(po2);


    Pos3D pilier3(largeur, -20.0, 0.0);
    GLUquadricObj* po3 = gluNewQuadric();
    cylindre(pilier3, po3, 80, 3, 10, 10);
    gluDeleteQuadric(po3);

    Pos3D pilier4(0.0, -20.0, 0.0);
    GLUquadricObj* po4 = gluNewQuadric();
    cylindre(pilier4, po4, 80, 3, 10, 10);
    gluDeleteQuadric(po4);

    //Base 

    Circuit_droit(axesElevator[0], axesElevator[1], axesElevator[2], axesElevator[3]);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);
    glPopMatrix();

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


void etage3(double x, double y, double z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);




    //Bord interieur 1 
    double p1[] = { 20.0, 0.0, -rayonTore };
    double p2[] = { 80.0 + rayonTore + largeur + 20, 0.0, -rayonTore };
    double p3[] = { 80.0 + rayonTore + largeur + 20, hauteur_bord, -rayonTore };
    double p4[] = { 20.0, hauteur_bord, -rayonTore };
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

void pont(double x, double y, double z) {
    glPushMatrix();
    glRotatef(90.0F, 0.0F, 1.0F, 0.0F);
    glPushMatrix();
    glTranslatef(x, y, z);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);




    //Bord interieur 1 
    double p1[] = { 0.0, 0.0, -rayonTore };
    double p2[] = { 0.0 + rayonTore + largeur + 20, 0.0, -rayonTore };
    double p3[] = { 0.0 + rayonTore + largeur + 20, hauteur_bord, -rayonTore };
    double p4[] = { 0.0, hauteur_bord, -rayonTore };
    Circuit_droit(p1, p2, p3, p4);


    //Bord exterieur 1
    double p5[] = { 0.0, 0.0, -(rayonTore + largeur) };
    double p6[] = { 0.0 + rayonTore + largeur + 20, 0.0, -(rayonTore + largeur) };
    double p7[] = { 0.0 + rayonTore + largeur + 20, hauteur_bord, -(rayonTore + largeur) };
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
    double p21[] = { 20.0, 0.0, -rayonTore };
    double p22[] = { 12.0 + rayonTore + largeur + 20, 0.0, -rayonTore };
    double p23[] = { 12.0 + rayonTore + largeur + 20, 0.0, -(rayonTore + largeur) };
    double p24[] = { 20.0, 0.0, -(rayonTore + largeur) };
    Circuit_droit(p21, p22, p23, p24);



    glPopMatrix();

    glPopMatrix();
}




void virage_bas(double x1, double y1, double z1, double x2, double y2, double z2)
{
    glNormal3f(x1, y1, -z1);
    glVertex3f(x1, y1, z1);
    //glTexCoord2f(0.0F, 0.0F);

    glNormal3f(x2, y1, -z2);
    glVertex3f(x2, y1, z2);
    //glTexCoord2f(0.0F, 1.0F);


    glNormal3f(x1, y2, -z1);
    glVertex3f(x1, y2, z1);
  //  glTexCoord2f(1.0F, 0.0F);

    glNormal3f(x2, y2, -z2);
    glVertex3f(x2, y2, z2);
  //  glTexCoord2f(1.0F, 1.0F);

    if (cmpt2 == 0)
    {
        cord2[k2].x = (x1 + x2) / 2;
        cord2[k2].y = y1;
        cord2[k2].z = (z1 + z2) / 2;
        k2++;
    }
}

void virage_board_interieur(double x1, double y1, double z1, double x2, double y2, double z2)
{
    glNormal3f(x1, y1, -z1);
    glVertex3f(x1, y1, z1);
    glTexCoord2f(0.0F, 0.0F);

    glNormal3f(x1, y1, -z2);
    glVertex3f(x2, y1, z2);
    glTexCoord2f(1.0F, 0.0F);


    glNormal3f(x1, y2, -z1);
    glVertex3f(x1, y2, z1);
    glTexCoord2f(1.0F, 1.0F);

    glNormal3f(x1, y2, -z2);
    glVertex3f(x2, y2, z2);
    glTexCoord2f(0.0F, 1.0F);
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



void Virage(double largeur, double rayonTore, double angleI, double angleF, int nbCube) {


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
    cmpt2++;


}


static void etage2(double x, double y, double z) {

    glPushMatrix();
    glTranslatef(x, y, z);

    glMaterialfv(GL_FRONT, GL_DIFFUSE, rouge);

    glPushMatrix();
    //Bord interieur 1 
    double p1[] = { 0.0, 0.0, -rayonTore };
    double p2[] = { 80.0, 0.0, -rayonTore };
    double p3[] = { 80.0, hauteur_bord, -rayonTore };
    double p4[] = { 0.0, hauteur_bord, -rayonTore };
    Circuit_droit(p1, p2, p3, p4);


    //Bord exterieur 1
    double p5[] = { 0.0, 0.0, -(rayonTore + largeur) };
    double p6[] = { 80.0, 0.0, -(rayonTore + largeur) };
    double p7[] = { 80.0, hauteur_bord, -(rayonTore + largeur) };
    double p8[] = { 0.0, hauteur_bord, -(rayonTore + largeur) };
    Circuit_droit(p5, p6, p7, p8);


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
    Virage(largeur, rayonTore, 0, M_PI, 50 * vitesse3);
    glPopMatrix();





    glPopMatrix();
}

void relie_etage_3_2(double x, double y, double z)
{
    glPushMatrix();


    glPopMatrix();
}

void dessinVirageBizier(GLfloat pts[][4], GLfloat pts1[][4], GLfloat pts2[][4])
{

    pl.n = aff;
    pl.p = (coord_3D*)&pts[0][0];
    glBegin(GL_QUAD_STRIP);
    bezier(&pl, 50 * vitesse2, 1);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    bezier(&pl, 5 * vitesse2, 2);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    bezier(&pl, 5 * vitesse2, 3);
    glEnd();


    pl.p = (coord_3D*)&pts1[0][0];
    glBegin(GL_QUAD_STRIP);
    bezier(&pl, 50 * vitesse2, 1);
    glEnd();


    pl.n = 2;
    pl.p = (coord_3D*)&pts2[0][0];
    glBegin(GL_QUAD_STRIP);
    bezier(&pl, 10 * vitesse2, 1);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    bezier(&pl, 5 * vitesse2, 2);
    glEnd();
    glBegin(GL_QUAD_STRIP);
    bezier(&pl, 5 * vitesse2, 3);
    glEnd();

}








/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {


    const float* fond;
    switch (cFond) {
    case 0:
        fond = gris;
        break;
    case 1:
        fond = blanc;
        break;
    case 2:
        fond = noir;
        break;
    }
    glClearColor(fond[0], fond[1], fond[2], fond[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const GLfloat light0_position[] = { 0.0,0.0,0.0,1.0 };
    const GLfloat light1_position[] = { -1.0,1.0,1.0,0.0 };
    const GLfloat light2_position[] = { 1.0,-1.0,1.0,0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    if (ligth1 == true)
    {
        lighting1();
    }
    else
    {
        glDisable(GL_LIGHT3);
    }

    if (ligth2 == true)
    {
        lighting2();
    }
    else
    {
        glDisable(GL_LIGHT4);
    }

    if (ligth3 == true)
    {
        lighting3();
    }
    else
    {
        glDisable(GL_LIGHT5);
    }
    if (ligth4 == true)
    {
        lighting4();
    }
    else
    {
        glDisable(GL_LIGHT6);
    }
    if (ligth5 == true)
    {
        lighting3();
    }
    else
    {
        glDisable(GL_LIGHT7);
    }


    glPolygonMode(GL_FRONT_AND_BACK, (laBalle.getTypeAffiche()) ? GL_FILL : GL_LINE);// Transformation fil de fer

    glPushMatrix();
    if (texture)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
    if (camera == 0)
    {
        //placer la caméra au dessus du circuit
        gluLookAt(50.0, 120.0, -90.0, 50.0, 0.0, 0.0, 0.0, -40.0, 90.0);
    }
    if (camera == 1)
    {
        if (positionBall.y < 40.0)//Balle dans 2 et 1 étage
        {
            if (positionBall.y == rayonBall && positionBall.z > 2)
            {
                gluLookAt(positionBall.x + 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
            else
            {
                gluLookAt(positionBall.x + 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
        }
        else //3 étage
        {
            if (positionBall.x > 80 && positionBall.x <= 160) {
                gluLookAt(150, 80, positionBall.z - rt, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
            else
            {
                gluLookAt(positionBall.x - 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
        }
    }
    if (camera == 2)
    {
        if (positionBall.y < 40.0)//Balle dans 2 et 1 étage
        {
            if (positionBall.y == rayonBall && positionBall.z > 2)
            {
                //gluLookAt(positionBall.x, positionBall.y, positionBall.z, positionBall.x+10, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
                //gluLookAt(positionBall.x - rayonBall, positionBall.y, positionBall.z, positionBall.x - rayonBall - 3, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
                gluLookAt(positionBall.x + rayonBall, positionBall.y, positionBall.z, positionBall.x + rayonBall + 3, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
            else
            {
                //gluLookAt(positionBall.x, positionBall.y , positionBall.z, positionBall.x+20, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
                gluLookAt(positionBall.x - rayonBall, positionBall.y, positionBall.z, positionBall.x - rayonBall - 3, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
        }
        else //3 étage
        {
            gluLookAt(positionBall.x + rayonBall, positionBall.y, positionBall.z, positionBall.x + rayonBall + 3, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
        }
    }
    glRotatef(rz, 0.0F, 0.0F, 1.0F);
    glRotatef(ry, 0.0F, 1.0F, 0.0F);
    glRotatef(rx, 1.0F, 0.0F, 0.0F);

    glTranslatef(dx, dy, dz);

    etage2(0.0, 0.0, 0.0);


    etage3(-(rayonTore + largeur + 20), 40.0, 0.0); //étage 3
    etage1_3(-(rayonTore + largeur + 20), -40.0, rayonTore + 2 * largeur); //étage 1
    ascenceur1(-(rayonTore + largeur + 20), 0.0, rayonTore + 2 * largeur - 20);// ascenceur1
    pont(-(rayonTore + 20), 40.0, -20.0);

    //Sphere(xball,yball,zball);
    laBalle.dessiner(positionBall, rayonBall, 36, 36);

    // Relie 3_2
    dessinVirageBizier(pts, pts2, pts3);


     // Relie 2_1
    dessinVirageBizier(pts4, pts5, pts6);

    glPopMatrix();




    glFlush();
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Attention erreur %d\n", error);
}
static void display2(void) {


    const float* fond;
    switch (cFond) {
    case 0:
        fond = gris;
        break;
    case 1:
        fond = blanc;
        break;
    case 2:
        fond = noir;
        break;
    }
    glClearColor(fond[0], fond[1], fond[2], fond[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    const GLfloat light0_position[] = { 0.0,0.0,0.0,1.0 };
    const GLfloat light1_position[] = { -1.0,1.0,1.0,0.0 };
    const GLfloat light2_position[] = { 1.0,-1.0,1.0,0.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

    if (ligth1 == true)
    {
        lighting1();
    }
    else
    {
        glDisable(GL_LIGHT3);
    }

    if (ligth2 == true)
    {
        lighting2();
    }
    else
    {
        glDisable(GL_LIGHT4);
    }

    if (ligth3 == true)
    {
        lighting3();
    }
    else
    {
        glDisable(GL_LIGHT5);
    }
    if (ligth4 == true)
    {
        lighting4();
    }
    else
    {
        glDisable(GL_LIGHT6);
    }
    if (ligth5 == true)
    {
        lighting3();
    }
    else
    {
        glDisable(GL_LIGHT7);
    }


    glPolygonMode(GL_FRONT_AND_BACK, (laBalle.getTypeAffiche()) ? GL_FILL : GL_LINE);// Transformation fil de fer

    glPushMatrix();
    //scene5();
    //scene6();
    if (texture)
        glEnable(GL_TEXTURE_2D);
    else
        glDisable(GL_TEXTURE_2D);
    if (camera == 0)
    {
        if (positionBall.y < 40.0)//Balle dans 2 et 1 étage
        {
            if (positionBall.y == rayonBall && positionBall.z > 2)
            {
                gluLookAt(positionBall.x + 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
            else
            {
                gluLookAt(positionBall.x + 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
        }
        else //3 étage
        {
            if (positionBall.x > 80 && positionBall.x <= 160) {
                gluLookAt(150, 80, positionBall.z - rt, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
            else
            {
                gluLookAt(positionBall.x - 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
        }
    }
    if (camera == 1)
    {
        if (positionBall.y < 40.0)//Balle dans 2 et 1 étage
        {
            if (positionBall.y == rayonBall && positionBall.z > 2)
            {
                gluLookAt(positionBall.x + 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
            else
            {
                gluLookAt(positionBall.x + 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
        }
        else //3 étage
        {
            if (positionBall.x > 80 && positionBall.x <= 160) {
                gluLookAt(150, 80, positionBall.z - rt, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);

            }
            else
            {
                if (positionBall.x > 120 && positionBall.x <= 160) {
                    gluLookAt(positionBall.x - 10 + rt, positionBall.y + 10, positionBall.z - rt, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
                    rt += 0.2;
                }
                else {
                    gluLookAt(positionBall.x - 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
                }
            }
        }
    }
    if (camera == 2)
    {
        if (positionBall.y < 40.0)//Balle dans 2 et 1 étage
        {
            if (positionBall.y == rayonBall && positionBall.z > 2)
            {
                gluLookAt(positionBall.x + 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
            else
            {
                gluLookAt(positionBall.x + 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
        }
        else //3 étage
        {
            if (positionBall.x > 80 && positionBall.x <= 160) {
                gluLookAt(150, 80, positionBall.z - rt, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
            }
            else
            {
                gluLookAt(positionBall.x - 10, positionBall.y + 10, positionBall.z, positionBall.x, positionBall.y, positionBall.z, 0.0, 10.0, 0.0);
                
            }
        }
    }
    glRotatef(rz, 0.0F, 0.0F, 1.0F);
    glRotatef(ry, 0.0F, 1.0F, 0.0F);
    glRotatef(rx, 1.0F, 0.0F, 0.0F);

    glTranslatef(dx, dy, dz);

    etage2(0.0, 0.0, 0.0);


    etage3(-(rayonTore + largeur + 20), 40.0, 0.0); //étage 3
    etage1_3(-(rayonTore + largeur + 20), -40.0, rayonTore + 2 * largeur); //étage 1
    ascenceur1(-(rayonTore + largeur + 20), 0.0, rayonTore + 2 * largeur - 20);// ascenceur1
    pont(-(rayonTore + 20), 40.0, -20.0);

    laBalle.dessiner(positionBall, rayonBall, 36, 36);

    // Relie 3_2
    dessinVirageBizier(pts, pts2, pts3);


    // Relie 2_1
    dessinVirageBizier(pts4, pts5, pts6);

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

static void ball(void) {
    if (positionBall.x <= 80.0 && etage == 3)
    {
        positionBall.x += vitesse1 ;
        axesElevator[0][1] = -40;
        axesElevator[1][1] = -40;
        axesElevator[2][1] = -40;
        axesElevator[3][1] = -40;
    }
    else
    {
        if (positionBall.x >= 80.0 - rayonBall && etage == 3)
        {
            etage = 4;
            k1 = 0;
        }
    }

    if (etage == 4 && positionBall.y != rayonBall + 1.0)
    {
        positionBall.x = cord1[k1].x;
        positionBall.y = cord1[k1].y + rayonBall + 1.0;
        positionBall.z = cord1[k1].z;
        k1++;
    }
    else
    {
        if (etage == 4 && positionBall.y == rayonBall + 1.0)
        {
            etage = 2;
            k3 = 0;
        }
    }

    if (etage == 2 && positionBall.x >= 0 && positionBall.z == -(rayonTore + largeur / 2))
    {
        positionBall.x -= vitesse1;
    }
    else
    {
        if (etage == 2 && positionBall.x <= 0 && cord2[k3].z != 0.0)
        {
            positionBall.x = cord2[k3].x;
            positionBall.y = cord2[k3].y + rayonBall;
            positionBall.z = cord2[k3].z;
            k3++;
        }
        else
        {
            if (etage == 2 && positionBall.x <= 80.0)
            {
                positionBall.x += vitesse1;
                
            }
            else
            {

                if (positionBall.x >= 80.0 && etage == 2)
                {
                    etage = 5;
                }
            }

        }


    }

    if (etage == 5 && positionBall.y != -40 + rayonBall + 1.0)
    {
        positionBall.x = cord1[k1].x;
        positionBall.y = cord1[k1].y + rayonBall + 1.0;
        positionBall.z = cord1[k1].z;
        k1++;
    }
    else
    {
        if (etage == 5 && positionBall.y == -40 + rayonBall + 1.0)
        {
            etage = 1;
        }
    }

    if (etage == 1 && positionBall.x >= -(rayonTore + largeur + 20) + rayonBall && positionBall.z == rayonTore + largeur / 2)
    {
        positionBall.x -= vitesse1;
        //Code ascenceur
        if (positionBall.x >= -58.0F && positionBall.x <= -45.0F) {
            etage = 6;
        }
    }
    if (etage == 6) {
        positionBall.y += 1.0F / 10.0;
        axesElevator[0][1] += 1.0F / 10.0;
        axesElevator[1][1] += 1.0F / 10.0;
        axesElevator[2][1] += 1.0F / 10.0;
        axesElevator[3][1] += 1.0F / 10.0;
        if (positionBall.y >= (float)(37.0 + 20 - 2 * hauteur_bord) && positionBall.y <= (float)(37.0 + 20 - 2 * hauteur_bord) + 1) {
            etage = 7;
            printf("x actu %f\n", positionBall.x);
            printf("x init %f\n", rayonBall, -(rayonTore + largeur / 2));
        }
    }
    if (etage == 7) {
        positionBall.z -= vitesse1;
        if (positionBall.z >= -33.0 && positionBall.z <= -30.0) {
            etage = 3;
        }

    }
}


static void balldroite(void) {

    if (positionBall.x <= 80.0 && etage == 3)
    {
        positionBall.x -= vitesse1;
        axesElevator[0][1] = -40;
        axesElevator[1][1] = -40;
        axesElevator[2][1] = -40;
        axesElevator[3][1] = -40;

    }
    else
    {
        if (positionBall.x >= 80.0 - rayonBall && etage == 3)
        {
            etage = 4;
            k1 = 0;
        }
    }




    if (etage == 4 && positionBall.y != rayonBall)
    {
        positionBall.x = cord1[k1].x;
        positionBall.y = cord1[k1].y + rayonBall;
        positionBall.z = cord1[k1].z;
        k1++;
    }
    else
    {
        if (etage == 4 && positionBall.y == rayonBall)
        {
            etage = 2;
            k3 = 0;
        }
    }

    if (etage == 2 && positionBall.x >= 0 && positionBall.z == -(rayonTore + largeur / 2))
    {
        positionBall.x -= vitesse1;
    }
    else
    {
        if (etage == 2 && positionBall.x <= 0 && cord2[k3].z != 0)
        {
            positionBall.x = cord2[k3].x;
            positionBall.y = cord2[k3].y + rayonBall;
            positionBall.z = cord2[k3].z;
            k3++;
        }
        else
        {
            if (etage == 2 && positionBall.x <= 80.0)
            {
                positionBall.x -= vitesse1;
            }
            else
            {
                if (positionBall.x >= 80.0 && etage == 2)
                {
                    etage = 5;
                }
            }

        }


    }

    if (etage == 5 && positionBall.y != -40 + rayonBall)
    {
        positionBall.x = cord1[k1].x;
        positionBall.y = cord1[k1].y + rayonBall;
        positionBall.z = cord1[k1].z;
        k1++;
    }
    else
    {
        if (etage == 5 && positionBall.y == -40 + rayonBall)
        {
            etage = 1;
        }
    }

    if (etage == 1 && positionBall.x >= -(rayonTore + largeur + 20) + rayonBall && positionBall.z == rayonTore + largeur / 2)
    {
        positionBall.x += vitesse1;
        //Code ascenceur
        if (positionBall.x == -45.0) {
            etage = 6;
        }
    }


}



static void idle(void) {
    ball();
    postRedisplay();
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
static void reshape2(int x, int y) {
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
    case GLUT_KEY_F1:
        ligth1 = !ligth1;
        break;

    case GLUT_KEY_F2:
        ligth2 = !ligth2;
        break;

    case GLUT_KEY_F3:
        ligth3 = !ligth3;
        break;


    case GLUT_KEY_F4:
        ligth4 = !ligth4;
        break;

    case GLUT_KEY_F5:
        ligth5 = !ligth5;
        break;
    }


}

/* Fonction executee lors de l'appui            */
/* d'une touche alphanumerique du clavier       */

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'k':
    { cFond = (cFond + 1) % 3;
    glutPostRedisplay(); }
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
        if (camera == 2) {
            camera = 0;
        }
        else {
            camera = camera + 1;
        }

        glutPostRedisplay();
        break;
    case 0x20:
        texture = (texture + 1) % 2;
        glutPostRedisplay();
        break;
    case 'v': //Permet de switcher en mode fils de fer avec la touche "espace"
        //affS = 1 - affS;
        if (laBalle.getTypeAffiche()) {
            laBalle.changerAffichage(false);
        }
        else {
            laBalle.changerAffichage(true);
        }
        glutPostRedisplay();
        break;


    case 'f':
        if (nFullScreen == 0)
        {
            glutFullScreen();
            nFullScreen = 1;
            break;
        }
        if (nFullScreen == 1)
        {
            glutReshapeWindow(WIDTH, HEIGHT);
            glutPositionWindow(50, 50);
            nFullScreen = 0;
            break;
        }
        //K
    case 75:
        balldroite();
        break;
        //m
    case 77:
        ball();

        break;

    case 'l':
        if (glIsEnabled(GL_LIGHTING) == true)
        {
            glDisable(GL_LIGHTING);
        }
        else
        {
            glEnable(GL_LIGHTING);
        }
        break;


    }




}



/* Fonction principale                          */

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(50, 50);
    f1 = glutCreateWindow("Un circuit à bille");
    init();
    glutKeyboardFunc(keyboard);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutSpecialFunc(special);
    glutDisplayFunc(display);
    glutInitWindowSize(360, 340);
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