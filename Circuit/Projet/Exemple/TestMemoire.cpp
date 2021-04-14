/* Test allocations/desallocation memoire       */
/*                                              */
/* Auteur: Nicolas JANEY                        */
/* nicolas.janey@univ-fcomte.fr                 */
/* Mars 2019                                    */

#if defined(WIN32) || defined(WIN64)
#define _CRTDBG_MAP_ALLOC
#if defined(_DEBUG)
#define _AFXDLL
#include <afx.h>
#endif
#endif
#include <stdlib.h>
#if defined(WIN32) || defined(WIN64)
#include <crtdbg.h>
#endif

#include <stdio.h>
#include <math.h>

#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

static char** t;

/* Fonction executee lors d'un rafraichissement */
/* de la fenetre de dessin                      */

static void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
    int error = glGetError();
    if (error != GL_NO_ERROR)
        printf("Erreur OpenGL: %d\n", error);
}

/* Fonction executee lors de la frappe          */
/* d'une touche du clavier                      */

static void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 0x1B:
        exit(0);
        break;
    }
}

static void clean() {
    for (int i = 0; i < 100; i++)
        free(t[i]);
    free(t);
}

/* Fonction principale                          */

int main(int argc, char** argv) {
#if defined(WIN32) || defined(WIN64)
#if defined(_DEBUG)
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_crtBreakAlloc = 120;
#endif
#endif

    atexit(clean);

    t = (char**)calloc(100, sizeof(char*));
    for (int i = 0; i < 100; i++)
        t[i] = (char*)malloc(1000);

    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(50, 50);
    glutCreateWindow("Test allocations/désallocation mémoire");
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutInitWindowPosition(250, 100);
    glutMainLoop();
    return(0);
}