#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include "../tinyxml/tinyxml.h"
#include "leitor.hpp"
#include "math.h"

using namespace std;

float alpha = M_PI / 4;
float beta = M_PI / 4;
float radius = 5.0f;
float cameraPosX = 5.0f;
float cameraPosY = 5.0f;
float cameraPosZ = 5.0f;
float lookAtX = 0.0f;
float lookAtY = 0.0f;
float lookAtZ = 0.0f;
float upX = 0.0f;
float upY = 0.0f;
float upZ = 0.0f;
int mode = GL_LINE;

Leitor leitor = NULL;

void changeSize(int w, int h)
{

    // Prevent a divide by zero, when window is too short
    // (you cant make a window with zero width).
    if (h == 0)
        h = 1;

    // compute window's aspect ratio
    float ratio = w * 1.0 / h;

    // Set the projection matrix as current
    glMatrixMode(GL_PROJECTION);
    // Load Identity Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set perspective
    gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void drawFiguras(Leitor leitor)
{
    // TO DO usar std::list<std::string> file;
}

void renderScenes(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    // gluLookAt(radius*cos(beta_)*sin(alpha), radius*sin(beta_), radius*cos(beta_)*cos(alpha),lookAtx,lookAty,lookAtz,upx,upy,upz); COPIAMOS?

    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-10.0f, 0.0f, 0.0f);
    glVertex3f(10.0f, 0.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, -10.0f, 0.0f);
    glVertex3f(0.0f, 10.0f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -10.0f);
    glVertex3f(0.0f, 0.0f, 10.0f);
    glEnd();

    // Tratar das figuras aqui

    glutSwapBuffers();
}

void processSpecialKeys(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_UP:
        cameraPosY += 1.0f;
        break;
    case GLUT_KEY_DOWN:
        cameraPosY -= 1.0f;
        break;
    default:
        break;
    }

    // ver melhor isto
    gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    glutPostRedisplay();
}

void processKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27: // Escape key
        exit(0);
        break;
    case 'w':
    case 'W':
        cameraPosZ -= 1.0f; // Move the camera forward
        break;
    case 's':
    case 'S':
        cameraPosZ += 1.0f; // Move the camera backward
        break;
    case 'a':
    case 'A':
        cameraPosX -= 1.0f; // Move the camera left (along the x-axis)
        break;
    case 'd':
    case 'D':
        cameraPosX += 1.0f; // Move the camera right (along the x-axis)
        break;
    case 'q':
    case 'Q':
        cameraPosY += 1.0f; // Move the camera up (along the y-axis)
        break;
    case 'z':
    case 'Z':
        cameraPosY -= 1.0f; // Move the camera down (along the y-axis)
        break;
    case 'f':
    case 'F':
        mode = GL_FILL;
        break;
    case 'l':
    case 'L':
        mode = GL_LINE;
        break;
    case 'p':
    case 'P':
        mode = GL_POINT;
        break;
    }

    // Ver melhor isto
    gluLookAt(cameraPosX, cameraPosY, cameraPosZ,
              0.0, 0.0, 0.0,
              0.0, 1.0, 0.0);

    // Request redraw
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    leitor = extrair_XML(argv[1]);
    std::list<std::string> figuras = getFiles(leitor)
        // n sei se é isto

        cameraPosX = getXPosCam(leitor);
    cameraPosY = getYPosCam(leitor);
    cameraPosZ = getZPosCam(leitor);
    radius = sqrt(cameraPosX * cameraPosX + cameraPosY * cameraPosY + cameraPosZ * cameraPosZ);
    lookAtX = getXLookAt(leitor);
    lookAtY = getYLookAt(leitor);
    lookAtZ = getZLookAt(leitor);
    upX = getXUp(leitor);
    upY = getYUp(leitor);
    upZ = getZUp(leitor);
    alpha = acos(cameraPosZ / sqrt(cameraPosX * cameraPosX + cameraPosZ * cameraPosZ));
    beta = asin(cameraPosY / radius);

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Fase 1");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}