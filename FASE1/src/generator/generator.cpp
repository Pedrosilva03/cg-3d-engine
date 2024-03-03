#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include <string.h>
#include <stdlib.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

using namespace std;

Figura generatePlane(int length, int divisions, char axis1, char axis2, float h = 0.0f, int reverse = 0)
{
    Figura plano = novaFigura();
    if (!plano)
    {
        cout << "Erro na construção da figura!" << endl;
        return NULL;
    }

    float divisionSize = (float)length / divisions;

    // Calculate vertex positions
    for (int row = 0; row < divisions; ++row)
    {
        for (int col = 0; col < divisions; ++col)
        {
            float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;

            // Calculate coordinates for the vertices of the current square based on the specified axes
            if (axis1 == 'x' && axis2 == 'y')
            {
                x1 = -length / 2 + col * divisionSize;
                y1 = -length / 2 + row * divisionSize;
                x2 = x1 + divisionSize;
                y2 = y1;
                x3 = x1;
                y3 = y1 + divisionSize;
                x4 = x2;
                y4 = y3;
                z1 = z2 = z3 = z4 = h;
            }
            else if (axis1 == 'x' && axis2 == 'z')
            {
                x1 = -length / 2 + col * divisionSize;
                z1 = -length / 2 + row * divisionSize;
                x2 = x1 + divisionSize;
                z2 = z1;
                x3 = x1;
                z3 = z1 + divisionSize;
                x4 = x2;
                z4 = z3;
                y1 = y2 = y3 = y4 = h;
            }
            else if (axis1 == 'y' && axis2 == 'z')
            {
                y1 = -length / 2 + col * divisionSize;
                z1 = -length / 2 + row * divisionSize;
                y2 = y1 + divisionSize;
                z2 = z1;
                y3 = y1;
                z3 = z1 + divisionSize;
                y4 = y2;
                z4 = z3;
                x1 = x2 = x3 = x4 = h;
            }

            // Adjust positions if reverse is set
            if (reverse == 1 && axis1 != 'y' && axis2 != 'z')
            {
                swap(y1, y3);
                swap(y2, y4);
            }
            else if (reverse == 1 && axis1 == 'y' && axis2 == 'z')
            {
                swap(x1, x3);
                swap(x2, x4);
            }

            // Add vertices to the figure
            adicionarPonto(plano, novoPonto(x1, y1, z1));
            adicionarPonto(plano, novoPonto(x2, y2, z2));
            adicionarPonto(plano, novoPonto(x3, y3, z3));
            adicionarPonto(plano, novoPonto(x2, y2, z2));
            adicionarPonto(plano, novoPonto(x3, y3, z3));
            adicionarPonto(plano, novoPonto(x4, y4, z4));
        }
    }

    return plano;
}

Figura generateBox(int dim, int div)
{
    Figura box = novaFigura();
    if (!box)
    {
        cout << "Erro na construção da figura!" << endl;
        return NULL;
    }

    Figura planeTopo = generatePlane(dim, div, 'x', 'z', (float)dim / 2, 0);
    Figura planeBaixo = generatePlane(dim, div, 'x', 'z', (float)-dim / 2, 1);
    Figura planeFrente = generatePlane(dim, div, 'x', 'y', (float)dim / 2, 0);
    Figura planeTras = generatePlane(dim, div, 'x', 'y', (float)-dim / 2, 1);
    Figura planeEsquerda = generatePlane(dim, div, 'y', 'z', (float)dim / 2, 0);
    Figura planeDireita = generatePlane(dim, div, 'y', 'z', (float)-dim / 2, 1);

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
            y1 = radius * sin(stackAngle1) * sin(sliceAngle1);
            z1 = radius * cos(stackAngle1);
            x2 = radius * sin(stackAngle1) * cos(sliceAngle2);
            y2 = radius * sin(stackAngle1) * sin(sliceAngle2);
            z2 = radius * cos(stackAngle1);
            x3 = radius * sin(stackAngle2) * cos(sliceAngle1);
            y3 = radius * sin(stackAngle2) * sin(sliceAngle1);
            z3 = radius * cos(stackAngle2);
            x4 = radius * sin(stackAngle2) * cos(sliceAngle2);
            y4 = radius * sin(stackAngle2) * sin(sliceAngle2);
            z4 = radius * cos(stackAngle2);

            // Add vertices to the figure
            adicionarPonto(sphere, novoPonto(x1, y1, z1));
            adicionarPonto(sphere, novoPonto(x2, y2, z2));
            adicionarPonto(sphere, novoPonto(x3, y3, z3));
            adicionarPonto(sphere, novoPonto(x2, y2, z2));
            adicionarPonto(sphere, novoPonto(x3, y3, z3));
            adicionarPonto(sphere, novoPonto(x4, y4, z4));
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
            y1 = radius * (1 - stackHeight1 / height) * sin(sliceAngle1);
            z1 = stackHeight1;
            x2 = radius * (1 - stackHeight1 / height) * cos(sliceAngle2);
            y2 = radius * (1 - stackHeight1 / height) * sin(sliceAngle2);
            z2 = stackHeight1;
            x3 = radius * (1 - stackHeight2 / height) * cos(sliceAngle1);
            y3 = radius * (1 - stackHeight2 / height) * sin(sliceAngle1);
            z3 = stackHeight2;
            x4 = radius * (1 - stackHeight2 / height) * cos(sliceAngle2);
            y4 = radius * (1 - stackHeight2 / height) * sin(sliceAngle2);
            z4 = stackHeight2;

            // Add vertices to the figure
            adicionarPonto(cone, novoPonto(x1, y1, z1));
            adicionarPonto(cone, novoPonto(x2, y2, z2));
            adicionarPonto(cone, novoPonto(x3, y3, z3));
            adicionarPonto(cone, novoPonto(x2, y2, z2));
            adicionarPonto(cone, novoPonto(x3, y3, z3));
            adicionarPonto(cone, novoPonto(x4, y4, z4));
        }
    }

    return cone;
}

int main(int argc, char *argv[])
{
    Figura figura = novaFigura();
    const char* file_path = nullptr;

    if (argc >= 5)
    {
        const char *file_path;
        if (strcmp(argv[1], "plane") == 0)
        {
            int length = atoi(argv[2]);
            int divisions = atoi(argv[3]);
            file_path = argv[4];

            figura = generatePlane(length, divisions, 'x', 'z');
        }

        else if (strcmp(argv[1], "box") == 0)
        {
            int dim = atoi(argv[2]);
            int div = atoi(argv[3]);
            file_path = argv[4];

            figura = generateBox(dim, div);
        }

        else if (strcmp(argv[1], "sphere") == 0)
        {
            float radius = atof(argv[2]);
            int slices = atoi(argv[3]);
            int stacks = atoi(argv[4]);
            file_path = argv[5];

            figura = generateSphere(radius, slices, stacks);
        }

        else if (strcmp(argv[1], "cone") == 0)
        {
            float radius = atof(argv[2]);
            float height = atof(argv[3]);
            int slices = atoi(argv[4]);
            int stacks = atoi(argv[5]);
            file_path = argv[6];

            figura = generateCone(radius, height, slices, stacks);
        }
    }
    else
    {
        printf("Número de argumentos inválido.\n");
        return 1;
    }

    criarFile(figura, file_path);
    apagarFigura(figura);
    return 0;
}
