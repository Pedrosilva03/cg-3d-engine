#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glew.h>
#include <GL/glut.h>
#endif

#include "../utils/figura.hpp"
#include "../utils/normals.hpp"
#include "../utils/ponto.hpp"
#include "../utils/groups.hpp"
#include "../utils/catmull.hpp"
#include "../utils/lights.hpp"
#include "../tinyxml/tinyxml.h"
#include "leitor.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <chrono>
#include <vector>

using namespace std;

float alpha = M_PI / 4;
float beta1 = M_PI / 4;
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
float fov = 60.0f;
float near = 1.0f;
float far = 1000.0f;
int mode = GL_LINE;
Group listafiguras;
list<Figura> figuras;

Leitor leitor = nullptr;

// FPS counter variables
std::chrono::time_point<std::chrono::steady_clock> lastTime;
int frameCount = 0;
float fps = 0.0f;

//VBOs
vector<GLuint> buffers;
vector<vector<float*>> figurasVertices;
bool VBOstate = false;

bool desenhaCurvas = true;
int elapsedTime = 0;
int instantBefore = 0;

void onExit(){
    for(GLuint buffer: buffers){
        glDeleteBuffers(1, &buffer);
    }
    for(vector<float*> vetor: figurasVertices){
        vetor.clear();
    }
    figurasVertices.clear();
    figuras.clear();
    deleteLeitor(leitor);
}

void loadBuffersData(){
    if(elapsedTime == 0){
        vector<GLuint> loader(figuras.size());
        buffers = loader;
        glGenBuffers(buffers.size(), buffers.data());

        std::vector<Figura> figurasVec = std::vector<Figura>(figuras.begin(), figuras.end());
        for(size_t i = 0; i < figuras.size(); i++){
            const auto& figura = figurasVec[i];
            list<Ponto> pontos = getPontos(figura);

            vector<float*> verticesPointer = vector<float*>();
            vector<float> vertices;
            int index = 0;
            for(Ponto p: pontos){
                verticesPointer.push_back(getXPointer(p));
                verticesPointer.push_back(getYPointer(p));
                verticesPointer.push_back(getZPointer(p));

                vertices.push_back(*verticesPointer[index]);
                index++;
                vertices.push_back(*verticesPointer[index]);
                index++;
                vertices.push_back(*verticesPointer[index]);
                index++;
            }
            glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
            figurasVertices.push_back(verticesPointer);
        }
    }
    else{
        int i = 0;
        for(vector<float*> vertices: figurasVertices){
            vector<float> verticess(vertices.size());
            int index = 0;
            for(float* vertice: vertices){
                verticess[index] = *vertice;
                index++;
            }
            glBindBuffer(GL_ARRAY_BUFFER, buffers[i]);
            glBufferData(GL_ARRAY_BUFFER, verticess.size() * sizeof(float), verticess.data(), GL_STATIC_DRAW);
            i++;
        }
    }
}

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
    gluPerspective(fov, ratio, near, far);

    // return to the model view matrix mode
    glMatrixMode(GL_MODELVIEW);
}

void pontosCatmullParaDesenho(Figura f){
    std::list<Ponto> pontos = getPontos(f);
    std::list<Ponto> pontosCat = getPontosControlFigura(f);
    float t = 0.0f;
    for(Ponto p: pontos){
        std::vector<Ponto> pontosCatCalc = getCatmullRomPoint(t, pontosCat);
        setX(p, getX(pontosCatCalc[0]));
        setY(p, getY(pontosCatCalc[0]));
        setZ(p, getZ(pontosCatCalc[0]));
        t+=0.02;
    }
}

void applyColor(Color c) {
    RGB diffuse = get_diffuse(c);
    RGB ambient = get_ambient(c);
    RGB specular = get_specular(c);
    RGB emissive = get_emissive(c);
    int shininess = get_shininess(c);

    GLfloat diffuse_vals[] = { getR(diffuse) / 255.0f, getG(diffuse) / 255.0f, getB(diffuse) / 255.0f, 1.0f };
    GLfloat ambient_vals[] = { getR(ambient) / 255.0f, getG(ambient) / 255.0f, getB(ambient) / 255.0f, 1.0f };
    GLfloat specular_vals[] = { getR(specular) / 255.0f, getG(specular) / 255.0f, getB(specular) / 255.0f, 1.0f };
    GLfloat emissive_vals[] = { getR(emissive) / 255.0f, getG(emissive) / 255.0f, getB(emissive) / 255.0f, 1.0f };
    GLfloat shininess_val = shininess;

    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse_vals);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient_vals);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular_vals);
    glMaterialfv(GL_FRONT, GL_EMISSION, emissive_vals);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess_val);
}

void applyLight(std::vector<Lights> luzes) {
    GLenum light = GL_LIGHT0;
    
    for (Lights l : luzes) { 
        glEnable(light);
        
        float amb[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        float white[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
        glLightfv(light, GL_DIFFUSE, white);
        glLightfv(light, GL_SPECULAR, white);

        GLfloat position[] = {getPosX(l), getPosY(l), getPosZ(l), 1.0f };
        GLfloat direction[] = { getDirX(l), getDirY(l), getDirZ(l), 0.0f };
        normalizeVector(direction);

        if (getType(l) == "directional") {
            glLightfv(light, GL_POSITION, direction);
        } else if (getType(l) == "point") {
            glLightfv(light, GL_POSITION, position);
        } else if (getType(l) == "spot"){
            glLightfv(light, GL_POSITION, position);
            glLightfv(light, GL_SPOT_DIRECTION, direction);
            glLightf(light, GL_SPOT_CUTOFF, getCutoff(l));
            glLightf(light, GL_SPOT_EXPONENT, 0.0);
        }

        light++;
    }
}

void drawFiguras() {
    glColor3f(1.0f, 1.0f, 1.0f);

    if(VBOstate){
        int index = 0;
        for (const auto& figura : figuras) {
            glPushMatrix();
            Color c = get_color(figura);
            if(c != NULL) applyColor(c);
            if(!getCurva(figura)){
                glBindBuffer(GL_ARRAY_BUFFER, buffers[index]);
                glVertexPointer(3, GL_FLOAT, 0, 0);
                glDrawArrays(GL_TRIANGLES, 0, getPontos(figura).size());
            }
            else if(desenhaCurvas){
                pontosCatmullParaDesenho(figura);
                glBindBuffer(GL_ARRAY_BUFFER, buffers[index]);
                glVertexPointer(3, GL_FLOAT, 0, 0);
                glDrawArrays(GL_LINE_LOOP, 0, getPontos(figura).size());
            }
            index++;
            glPopMatrix();
        }
    }
    else{
        for (const auto& figura : figuras) {
            glPushMatrix();
            Color c = get_color(figura);
            if(c != NULL) applyColor(c);
            if(!getCurva(figura)){
                list<Ponto> pontos = getPontos(figura);

                std::vector<Ponto> normais;
                if(getLights(leitor).size() > 0){
                    normais = normalsHandler(getTypeFig(figura), pontos);
                }
                
                glBegin(GL_TRIANGLES);
                int i = 0;
                for (const auto& ponto : pontos) {
                    //cout << "(" << getX(ponto) << "," << getY(ponto) << "," << getZ(ponto) << ")";
                    if(getLights(leitor).size() > 0) glNormal3f(getX(normais[i]), getY(normais[i]), getZ(normais[i]));
                    glVertex3f(getX(ponto), getY(ponto), getZ(ponto));
                    i++;
                }
                glEnd();
            }
            else if(desenhaCurvas){
                pontosCatmullParaDesenho(figura);
                list<Ponto> pontos = getPontos(figura);
                glBegin(GL_LINE_LOOP);
                for (const auto& ponto : pontos) {
                    //cout << "(" << getX(ponto) << "," << getY(ponto) << "," << getZ(ponto) << ")";
                    glVertex3f(getX(ponto), getY(ponto), getZ(ponto));
                }
                glEnd();
            }
            glPopMatrix();
        }
    }
}

void fpsCounter(void){
    frameCount++;
    auto currentTime = std::chrono::steady_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastTime).count() / 1000.0;
    if (elapsedTime >= 1.0) {
        fps = frameCount / elapsedTime;
        frameCount = 0;
        lastTime = currentTime;
    }
}

void drawTexts(const std::string& text, float x, float y, void* font){
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0, glutGet(GLUT_WINDOW_WIDTH), 0, glutGet(GLUT_WINDOW_HEIGHT), -1, 1);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(x, y);
    for (char c: text){
        glutBitmapCharacter(font, c);
    }

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    if(getLights(leitor).size() > 0) glEnable(GL_LIGHTING);
}

void drawStats(){
    std::stringstream ssFPS;
    std::string vbos;
    std::string curves;

    ssFPS << "FPS: " << fps;
    std::string fps = ssFPS.str();

    if(VBOstate) vbos = "VBO: ON";
    else  vbos = "VBO: OFF";

    if(desenhaCurvas) curves = "Curves: ON";
    else curves = "Curves: OFF";

    drawTexts(fps, 10.0f, 10.0f, GLUT_BITMAP_9_BY_15);
    drawTexts(vbos, 10.0f, 30.0f, GLUT_BITMAP_9_BY_15);
    drawTexts(curves, 10.0f, 50.0f, GLUT_BITMAP_9_BY_15);
}

void renderScene(void)
{
    elapsedTime = glutGet(GLUT_ELAPSED_TIME);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(radius * cos(beta1) * sin(alpha), radius * sin(beta1), radius * cos(beta1) * cos(alpha), lookAtX, lookAtY, lookAtZ, upX, upY, upZ);

    glDisable(GL_LIGHTING);
    glBegin(GL_LINES);
    glColor3f(1.0f, 0.0f, 0.0f);
    glVertex3f(-100.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -100.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.0f, 0.0f, -100.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
    if(getLights(leitor).size() > 0) glEnable(GL_LIGHTING);

    glPolygonMode(GL_FRONT_AND_BACK, mode);

    figuras = criarListaFiguras(listafiguras, elapsedTime, instantBefore);
    instantBefore = elapsedTime;

    if(getLights(leitor).size() > 0) applyLight(getLights(leitor));

    drawFiguras();

    fpsCounter();
    drawStats();

    if(VBOstate) loadBuffersData();

    glutSwapBuffers();
}

void processSpecialKeys(int key, int x, int y)
{
    switch (key)
    {
        case GLUT_KEY_UP:
            beta1 -= 1.0f;
            break;
            
        case GLUT_KEY_DOWN:
            beta1 += 1.0f;
            break;

        case GLUT_KEY_LEFT:
            alpha -= 1.0f;
            break;

        case GLUT_KEY_RIGHT:
            alpha += 1.0f;
            break;

        default:
            break;
    }

    glutPostRedisplay();
}

void processKeys(unsigned char key, int x, int y)
{
    switch (key) 
    {
        case 'w':
            beta1 -= 1.0f; // Move the camera forward
            break;

        case 's':
            beta1 += 1.0f; // Move the camera backward
            break;

        case 'a':
            alpha -= 1.0f; // Move the camera left (along the x-axis)
            break;

        case 'd':
            alpha += 1.0f; // Move the camera right (along the x-axis)
            break;

        case 'f':
            mode = GL_FILL;
            break;
            
        case 'l':
            mode = GL_LINE;
            break;

        case 'p':
            mode = GL_POINT;
            break;
        
        case '+':
            radius -= 1.0f; // Zoom in
            break;

        case '-':
            radius += 1.0f; // Zoom out
            break;

        case 'v':
            VBOstate = !VBOstate;
            loadBuffersData();
            break;
        
        case 'c':
            desenhaCurvas = !desenhaCurvas;
            break;
    }

    // Request redraw
    glutPostRedisplay();
}

/*void setupLights(std::vector<Lights> luzes){
    int i = GL_LIGHT0;
    for(Lights l: luzes){
        glEnable(i);

        GLfloat pos[4] = {getPosX(l), getPosY(l), getPosZ(l), 1.0f};
        glLightfv(i, GL_POSITION, pos);

        GLfloat dir[4] = {getDirX(l), getDirY(l), getDirZ(l), 1.0f};
        glLightfv(i, GL_POSITION, dir);

        GLfloat cutoff = getCutoff(l);
        glLightfv(i, GL_SPOT_CUTOFF, &cutoff);

        i++;
    }
}*/


int main(int argc, char **argv)
{
    leitor = extrair_XML(argv[1]);
    listafiguras = getNode(leitor);
    
    if(listafiguras) figuras = criarListaFiguras(listafiguras, 0, instantBefore);

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
    beta1 = asin(cameraPosY / radius);
    fov = getFov(leitor);
    near = getNear(leitor);
    far = getFar(leitor);

    // init GLUT and the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Fase 4 - Texturas e normais");

    // Required callback registry
    glutDisplayFunc(renderScene);
    glutReshapeFunc(changeSize);
    glutIdleFunc(renderScene);

    // Callback registration for keyboard processing
    glutKeyboardFunc(processKeys);
    glutSpecialFunc(processSpecialKeys);

    //  OpenGL settings
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    if(getLights(leitor).size() > 0) glEnable(GL_LIGHTING);

    glEnable(GL_RESCALE_NORMAL);
    glPolygonMode(GL_FRONT, GL_LINE);

    glewInit();
    glEnableClientState(GL_VERTEX_ARRAY);

    loadBuffersData();

    atexit(onExit);

    // enter GLUT's main cycle
    glutMainLoop();

    return 1;
}