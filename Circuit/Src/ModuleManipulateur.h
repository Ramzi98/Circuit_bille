/* Auteur: Nicolas JANEY              */
/* nicolas.janey@univ-fcomte.fr       */
/* Septembre 2005                     */
/* Un manipulateur souris et clavier  */

#ifndef MODULEMANIPULATEUR
#define MODULEMANIPULATEUR

int sourisManipulateur(int bouton,int etat,int x,int y) ;
int motionManipulateur(int x,int y) ;
void manipulateurSouris() ;
void setManipulateurDistance(float d) ;
int keyManipulateur(unsigned char key,int x,int y) ;
int specialManipulateur(int k, int x, int y) ;
void setManipulateurClavierAngle(float ax,float ay,float az) ;
void setManipulateurSourisAngle(float ax,float ay,float az) ;
void manipulateurClavier() ;
void sourisBasique(int bouton,int etat,int x,int y) ;
void motionBasique(int x,int y) ;
void keyBasique(unsigned char key,int x,int y) ;
void specialBasique(int k, int x, int y) ;
void setIdleWindow(int w) ;
void idleBasique(void) ;
void setManipulateurCleanUp(void (*func)(void));

typedef void (*fonctionVoid) (void);

void setManipulateurParametre0(float *param,float min,float max,float fct);
void setManipulateurParametre1(float *param,float min,float max,float fct);
void setManipulateurParametreFonction(fonctionVoid fonction);
void setManipulateurRefresh(fonctionVoid fonct);

#endif
