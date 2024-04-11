#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include "../utils/bezier.hpp"
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

//Geradores de patches----------------------------------------------------------------------

std::list<Ponto> getPatchPontos(const char* patchFile){
    std::list<Ponto> controlPoints = std::list<Ponto>();
    FILE* patchF = fopen(patchFile, "r");
    if(patchF){
        // Salta as linhas dos patches
        char skipline[BUFSIZ];
        fgets(skipline, BUFSIZ, patchF);
        int numPatches = stoi(skipline);
        for(int i = 0; i < numPatches; i++){
            fgets(skipline, BUFSIZ, patchF);
        }

        // Parse dos pontos
        char firstLine[BUFSIZ];
        fgets(firstLine, BUFSIZ, patchF);
        int numPoints = stoi(firstLine);
        for(int i = 0; i < numPoints; i++){
            char points[BUFSIZ];
            float x, y, z;
            fgets(points, BUFSIZ, patchF);
            sscanf(points, "%f,%f,%f", &x, &y, &z);
            Ponto p = novoPonto(x, y, z);
            controlPoints.push_back(p);
        }
    }
    return controlPoints;
}

std::list<std::list<int>> getPatches(const char* patchFile){
    std::list<std::list<int>> patches = std::list<std::list<int>>();
    FILE* patchF = fopen(patchFile, "r");
    if(patchF){
        char firstLine[BUFSIZ];
        fgets(firstLine, BUFSIZ, patchF); //Salta a primeira linha
        int numPatches = stoi(firstLine);

        for(int i = 1; i <= numPatches; i++){
            std::list<int> indices = std::list<int>();
            char patchLine[BUFSIZ];
            fgets(patchLine, BUFSIZ, patchF);
            for(char* indiceChar = strtok(patchLine, ", "); indiceChar; indiceChar = strtok(NULL, ", ")){
                int indice = atoi(indiceChar);
                indices.push_back(indice);
            }
            patches.push_back(indices);
        }
    }
    else{
        cout << "Erro ao abrir ficheiro de patches!" << endl;
    }    
    return patches;
}

std::list<std::list<Ponto>> getPontosFromPatches(std::list<std::list<int>> patches, std::list<Ponto> controlPoints){
    std::list<std::list<Ponto>> pontos = std::list<std::list<Ponto>>();
    for(std::list<int> patch: patches){
        std::list<Ponto> pontosPatch = std::list<Ponto>();
        for(int i: patch){
            auto it = controlPoints.begin();
            std::advance(it, i);
            pontosPatch.push_back(*it);
        }
        pontos.push_back(pontosPatch);
    }
    return pontos;
}

Figura generateFromPatch(const char* patchFile, int tesselation){
    Figura patch = novaFigura();
    if(!patch){
        cout << "Erro na construção da figura!" << endl;
        return NULL;
    }
    
    std::list<std::list<int>> patches = getPatches(patchFile);
    std::list<Ponto> controlPoints = getPatchPontos(patchFile);

    std::list<std::list<Ponto>> pointsCalculated = getPontosFromPatches(patches, controlPoints);

    for(std::list<Ponto> patchPointsCalculated: pointsCalculated){
        std::vector<Ponto> patchPointsCalculatedVector(patchPointsCalculated.begin(), patchPointsCalculated.end()); // Troca para vector para facilitar o acesso


        float divisionSize = 1.0f/tesselation;
        for(int i = 0; i < tesselation; i++){
            float u0 = (float)i / tesselation;
            for(int j = 0; j < tesselation; j++){
                float v0 = (float)j / tesselation;

                adicionarPonto(patch, calculateBezierPoint(patchPointsCalculatedVector, u0, v0));
                adicionarPonto(patch, calculateBezierPoint(patchPointsCalculatedVector, u0 + divisionSize, v0));
                adicionarPonto(patch, calculateBezierPoint(patchPointsCalculatedVector, u0 + divisionSize, v0 + divisionSize));

                adicionarPonto(patch, calculateBezierPoint(patchPointsCalculatedVector, u0, v0));
                adicionarPonto(patch, calculateBezierPoint(patchPointsCalculatedVector, u0 + divisionSize, v0 + divisionSize));
                adicionarPonto(patch, calculateBezierPoint(patchPointsCalculatedVector, u0, v0 + divisionSize));
            }
        }
    }

    return patch;
}

//Geradores de primitivas----------------------------------------------------------------------

Figura generateRing(float innerRadius, float outerRadius, int divisions){
    Figura ring = novaFigura();
    if(!ring){
        cout << "Erro na construção da figura!" << endl;
        return NULL;
    }

    float angle = 2 * M_PI / divisions;

    for (int i = 0; i < divisions; i++){
        float currentAngle = angle * i;

        float x1 = innerRadius * cos(currentAngle);
        float z1 = innerRadius * sin(currentAngle);
        float x2 = outerRadius * cos(currentAngle);
        float z2 = outerRadius * sin(currentAngle);

        currentAngle = (i + 1) * angle;

        // Calcular as coordenadas x e z para o próximo ponto
        float x3 = innerRadius * cos(currentAngle);
        float z3 = innerRadius * sin(currentAngle);
        float x4 = outerRadius * cos(currentAngle);
        float z4 = outerRadius * sin(currentAngle);

        // Adicionar pontos ao vetor de pontos para formar o segmento do anel
        adicionarPonto(ring, novoPonto(x3, 0, z3)); // Ponto interior
        adicionarPonto(ring, novoPonto(x1, 0, z1)); // Ponto interior
        adicionarPonto(ring, novoPonto(x2, 0, z2)); // Ponto exterior

        adicionarPonto(ring, novoPonto(x3, 0, z3)); // Ponto interior
        adicionarPonto(ring, novoPonto(x2, 0, z2)); // Ponto exterior
        adicionarPonto(ring, novoPonto(x4, 0, z4)); // Ponto interior

        adicionarPonto(ring, novoPonto(x2, 0, z2)); // Ponto exterior
        adicionarPonto(ring, novoPonto(x1, 0, z1)); // Ponto interior
        adicionarPonto(ring, novoPonto(x3, 0, z3)); // Ponto interior

        adicionarPonto(ring, novoPonto(x4, 0, z4)); // Ponto interior
        adicionarPonto(ring, novoPonto(x2, 0, z2)); // Ponto exterior
        adicionarPonto(ring, novoPonto(x3, 0, z3)); // Ponto interior
    }
    return ring;
}

Figura generatePlane(int length, int divisions, char axis1, char axis2, float x = 0.0f, float y = 0.0f, float z = 0.0f, int inverte = 0)
{
    Figura plane = novaFigura();
    if (!plane)
    {
        cout << "Erro na construção da figura!" << endl;
        return NULL;
    }

    float startPos = -(length/2);

    float a1, a2;
    float b1, b2;
    float c1, c2;

    float divisionSize = (float)length / divisions;

    for(int linha = 0; linha < divisions; ++linha){
        for(int coluna = 0; coluna < divisions; ++coluna){
            a1 = startPos + coluna * divisionSize;
            a2 = startPos + linha * divisionSize;
            b1 = a1;
            b2 = a2 + divisionSize;
            c1 = a1 + divisionSize;
            c2 = a2;

            if(inverte == 1){
                float temp_1 = b1;
                float temp_2 = b2;
                b1 = c1;
                b2 = c2;
                c1 = temp_1;
                c2 = temp_2;
            }

            if(axis1 == 'x' && axis2 == 'y'){
                adicionarPonto(plane, novoPonto(a1, a2, z));
                adicionarPonto(plane, novoPonto(c1, c2, z));
                adicionarPonto(plane, novoPonto(b1, b2, z));

                adicionarPonto(plane, novoPonto(b1, b2, z));
                adicionarPonto(plane, novoPonto(c1, c2, z));
                adicionarPonto(plane, novoPonto(a1 + divisionSize, a2 + divisionSize, z));
            }
            else if(axis1 == 'x' && axis2 == 'z'){
                adicionarPonto(plane, novoPonto(a1, y, a2));
                adicionarPonto(plane, novoPonto(b1, y, b2));
                adicionarPonto(plane, novoPonto(c1, y, c2));
                
                adicionarPonto(plane, novoPonto(b1, y, b2));
                adicionarPonto(plane, novoPonto(a1 + divisionSize, y, a2 + divisionSize));
                adicionarPonto(plane, novoPonto(c1, y, c2));
            }
            else{
                adicionarPonto(plane, novoPonto(x, a1, a2));
                adicionarPonto(plane, novoPonto(x, c1, c2));
                adicionarPonto(plane, novoPonto(x, b1, b2));

                adicionarPonto(plane, novoPonto(x, b1, b2));
                adicionarPonto(plane, novoPonto(x, c1, c2));
                adicionarPonto(plane, novoPonto(x, a1 + divisionSize, a2 + divisionSize));
            }
        }
    }

    return plane;
}

Figura generateBox(int length, int divisions)
{
    Figura box = novaFigura();
    if (!box)
    {
        cout << "Erro na construção da figura!" << endl;
        return NULL;
    }

    Figura planeTopo = generatePlane(length, divisions, 'x', 'z', 0, (float)length / 2, 0, 0);
    Figura planeBaixo = generatePlane(length, divisions, 'x', 'z', 0, -(float)length / 2, 0, 1);
    Figura planeFrente = generatePlane(length, divisions, 'x', 'y', 0, 0, (float)length / 2, 0);
    Figura planeTras = generatePlane(length, divisions, 'x', 'y', 0, 0, -(float)length / 2, 1);
    Figura planeEsquerda = generatePlane(length, divisions, 'y', 'z', (float)length / 2, 0, 0, 0);
    Figura planeDireita = generatePlane(length, divisions, 'y', 'z', -(float)length / 2, 0, 0, 1);

    adicionarVariosPontos(box, planeTopo);
    adicionarVariosPontos(box, planeBaixo);
    adicionarVariosPontos(box, planeFrente);
    adicionarVariosPontos(box, planeTras);
    adicionarVariosPontos(box, planeEsquerda);
    adicionarVariosPontos(box, planeDireita);

    apagarFigura(planeTopo);
    apagarFigura(planeBaixo);
    apagarFigura(planeFrente);
    apagarFigura(planeTras);
    apagarFigura(planeEsquerda);
    apagarFigura(planeDireita);

    return box;
}

Figura generateSphere(float radius, int slices, int stacks)
{
    Figura sphere = novaFigura();
    if (!sphere)
    {
        cout << "Erro na construção da figura!" << endl;
        return NULL;
    }

    float sliceAngle = 2 * M_PI / slices;
    float stackAngle = M_PI / stacks;

    // Calculate vertex positions
    for (int i = 0; i < stacks; ++i)
    {
        float stackAngle1 = i * stackAngle;
        float stackAngle2 = (i + 1) * stackAngle;

        for (int j = 0; j < slices; ++j)
        {
            float sliceAngle1 = j * sliceAngle;
            float sliceAngle2 = (j + 1) * sliceAngle;

            float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

            // Calculate coordinates for the vertices of the current slice
            x1 = radius * sin(stackAngle1) * cos(sliceAngle1);
            y1 = radius * cos(stackAngle1);
            z1 = radius * sin(stackAngle1) * sin(sliceAngle1);

            x2 = radius * sin(stackAngle1) * cos(sliceAngle2);
            y2 = radius * cos(stackAngle1);
            z2 = radius * sin(stackAngle1) * sin(sliceAngle2);

            x3 = radius * sin(stackAngle2) * cos(sliceAngle1);
            y3 = radius * cos(stackAngle2);
            z3 = radius * sin(stackAngle2) * sin(sliceAngle1);

            x4 = radius * sin(stackAngle2) * cos(sliceAngle2);
            y4 = radius * cos(stackAngle2);
            z4 = radius * sin(stackAngle2) * sin(sliceAngle2);

            // Add vertices to the figure
            adicionarPonto(sphere, novoPonto(x1, y1, z1));
            adicionarPonto(sphere, novoPonto(x2, y2, z2));
            adicionarPonto(sphere, novoPonto(x3, y3, z3));

            adicionarPonto(sphere, novoPonto(x2, y2, z2));
            adicionarPonto(sphere, novoPonto(x4, y4, z4));
            adicionarPonto(sphere, novoPonto(x3, y3, z3));
        }
    }

    return sphere;
}



Figura generateCone(float radius, float height, int slices, int stacks)
{
    Figura cone = novaFigura();
    if (!cone)
    {
        cout << "Erro na construção da figura!" << endl;
        return NULL;
    }

    float sliceAngle = 2 * M_PI / slices;
    float stackHeight = height / stacks;

    // Calculate vertex positions
    for (int i = 0; i < stacks; ++i)
    {
        float stackHeight1 = i * stackHeight;
        float stackHeight2 = (i + 1) * stackHeight;

        for (int j = 0; j < slices; ++j)
        {
            float sliceAngle1 = j * sliceAngle;
            float sliceAngle2 = (j + 1) * sliceAngle;

            float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

            // Calculate coordinates for the vertices of the current slice
            x1 = radius * (1 - stackHeight1 / height) * cos(sliceAngle1);
            y1 = stackHeight1;
            z1 = radius * (1 - stackHeight1 / height) * sin(sliceAngle1);

            x2 = radius * (1 - stackHeight1 / height) * cos(sliceAngle2);
            y2 = stackHeight1;
            z2 = radius * (1 - stackHeight1 / height) * sin(sliceAngle2);

            x3 = radius * (1 - stackHeight2 / height) * cos(sliceAngle1);
            y3 = stackHeight2;
            z3 = radius * (1 - stackHeight2 / height) * sin(sliceAngle1);

            x4 = radius * (1 - stackHeight2 / height) * cos(sliceAngle2);
            y4 = stackHeight2;
            z4 = radius * (1 - stackHeight2 / height) * sin(sliceAngle2);

            // Add vertices to the figure
            adicionarPonto(cone, novoPonto(x1, y1, z1));
            adicionarPonto(cone, novoPonto(x3, y3, z3));
            adicionarPonto(cone, novoPonto(x2, y2, z2));
            adicionarPonto(cone, novoPonto(x2, y2, z2));
            adicionarPonto(cone, novoPonto(x3, y3, z3));
            adicionarPonto(cone, novoPonto(x4, y4, z4));
        }
    }

         for (int j = 0; j < slices; ++j)
    {
        float sliceAngle1 = j * sliceAngle;
        float sliceAngle2 = (j + 1) * sliceAngle;

        float x1 = 0;
        float y1 = 0;
        float z1 = 0;

        float x2 = radius * cos(sliceAngle1);
        float y2 = 0;
        float z2 = radius * sin(sliceAngle1);

        float x3 = radius * cos(sliceAngle2);
        float y3 = 0;
        float z3 = radius * sin(sliceAngle2);

        // Add vertices to the figure for the base
        adicionarPonto(cone, novoPonto(x1, y1, z1));
        adicionarPonto(cone, novoPonto(x2, y2, z2));
        adicionarPonto(cone, novoPonto(x3, y3, z3));
    }



    return cone;
}

int main(int argc, char *argv[])
{
    if (argc >= 5)
    {
        Figura figura = novaFigura();
        const char *file_path = nullptr;

        if(strcmp(argv[1], "patch") == 0){
            const char* patchFile = argv[2];
            int tesselation = atoi(argv[3]);
            file_path = argv[4];

            figura = generateFromPatch(patchFile, tesselation);
            criarFile(figura, file_path);
            apagarFigura(figura);
        }

        else if(strcmp(argv[1], "ring") == 0){
            float innerRadius = atof(argv[2]);
            float outerRadius = atof(argv[3]);
            float divisions = atof(argv[4]);
            file_path = argv[5];

            figura = generateRing(innerRadius, outerRadius, divisions);
            criarFile(figura, file_path);
            apagarFigura(figura);
        }

        else if (strcmp(argv[1], "plane") == 0)
        {
            int length = atoi(argv[2]);
            int divisions = atoi(argv[3]);
            file_path = argv[4];

            figura = generatePlane(length, divisions, 'x', 'z');
            adicionarVariosPontos(figura, generatePlane(length, divisions, 'x', 'z', 0, 0, 0, 1));
            criarFile(figura, file_path);
            apagarFigura(figura);
        }

        else if (strcmp(argv[1], "box") == 0)
        {
            int length = atoi(argv[2]);
            int divisions = atoi(argv[3]);
            file_path = argv[4];

            figura = generateBox(length, divisions);
            criarFile(figura, file_path);
            apagarFigura(figura);
        }

        else if (strcmp(argv[1], "sphere") == 0)
        {
            float radius = atof(argv[2]);
            int slices = atoi(argv[3]);
            int stacks = atoi(argv[4]);
            file_path = argv[5];

            figura = generateSphere(radius, slices, stacks);
            criarFile(figura, file_path);
            apagarFigura(figura);
        }

        else if (strcmp(argv[1], "cone") == 0)
        {
            float radius = atof(argv[2]);
            float height = atof(argv[3]);
            int slices = atoi(argv[4]);
            int stacks = atoi(argv[5]);
            file_path = argv[6];

            figura = generateCone(radius, height, slices, stacks);
            criarFile(figura, file_path);
            apagarFigura(figura);
        }
        else{
            printf("Modelo pedido inválido. Nada foi gerado.");
            return 1;
        }
    }
    else
    {
        printf("Número de argumentos inválido.\n");
        return 1;
    }

    return 0;
}