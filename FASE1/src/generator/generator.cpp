#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include "../utils/figura.hpp"
#include "../utils/ponto.hpp"
#include <string.h>

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>

using namespace std;

Figura generatePlane(int length, int divisions, char axis1, char axis2, float x = 0.0f, float y = 0.0f, float z = 0.0f, int inverte = 0)
{
    Figura plane = novaFigura();
    if (!plane)
    {
        cout << "Erro na construção da figura!" << endl;
        return NULL;
    }

    float divisionSize = (float)length / divisions;
    float start_x = -(length / 2.0f); // Calculate the starting x-coordinate
    float start_z = -(length / 2.0f); // Calculate the starting z-coordinate
    float start_y = -(length / 2.0f); // Calculate the starting y-coordinate

    // Calculate vertex positions
    for (int linha = 0; linha < divisions; ++linha)
    {
        for (int coluna = 0; coluna < divisions; ++coluna)
        {
            // Calculate coordinates for the vertices of the current square based on the specified axes
            if (axis1 == 'x' && axis2 == 'y')
            {
                float x1 = start_x + coluna * divisionSize; // Calculate x-coordinate of first vertex
                float z1 = start_z + linha * divisionSize; // Calculate z-coordinate of first vertex
                float x2 = x1 + divisionSize; // Calculate x-coordinate of second vertex
                float z2 = z1; // Second vertex shares the same z-coordinate
                float x3 = x1; // Third vertex shares the same x-coordinate
                float z3 = z1 + divisionSize; // Calculate z-coordinate of third vertex

                // If 'inverte' flag is set, swap vertices to inverte triangle orientation
                if (inverte == 1) {
                    float temp_x = x2;
                    float temp_z = z2;
                    x2 = x3;
                    z2 = z3;
                    x3 = temp_x;
                    z3 = temp_z;
                }

                // Add the vertices of the first triangle
                adicionarPonto(plane, novoPonto(x1, z1, z));
                adicionarPonto(plane, novoPonto(x3, z3, z));
                adicionarPonto(plane, novoPonto(x2, z2, z));
                

                // Add the vertices of the second triangle
                adicionarPonto(plane, novoPonto(x2, z2, z));
                adicionarPonto(plane, novoPonto(x3, z3, z));
                adicionarPonto(plane, novoPonto(x1 + divisionSize, z1 + divisionSize, z));
                
            }
            else if (axis1 == 'x' && axis2 == 'z')
            {
                float x1 = start_x + coluna * divisionSize; // Calculate x-coordinate of first vertex
                float z1 = start_z + linha * divisionSize; // Calculate z-coordinate of first vertex
                float x2 = x1 + divisionSize; // Calculate x-coordinate of second vertex
                float z2 = z1; // Second vertex shares the same z-coordinate
                float x3 = x1; // Third vertex shares the same x-coordinate
                float z3 = z1 + divisionSize; // Calculate z-coordinate of third vertex

                // If 'inverte' flag is set, adjust the vertices for the bottom orientation
                if (inverte == 1) {
                    x2 = x1;
                    x3 = x1 + divisionSize;
                    z3 = z1;
                }

                // Add the vertices of the first triangle
                adicionarPonto(plane, novoPonto(x1, y, z1));
                adicionarPonto(plane, novoPonto(x3, y, z3));
                adicionarPonto(plane, novoPonto(x2, y, z2));
                

                // Add the vertices of the second triangle
                adicionarPonto(plane, novoPonto(x2, y, z2));
                adicionarPonto(plane, novoPonto(x3, y, z3));
                adicionarPonto(plane, novoPonto(x1 + divisionSize, y, z1 + divisionSize));
                
            }
            else if (axis1 == 'y' && axis2 == 'z')
            {
                float y1 = start_y + coluna * divisionSize; // Calculate y-coordinate of first vertex
                float z1 = start_z + linha * divisionSize; // Calculate z-coordinate of first vertex
                float y2 = y1; // Second vertex shares the same y-coordinate
                float z2 = z1 + divisionSize; // Calculate z-coordinate of second vertex
                float y3 = y1 + divisionSize; // Calculate y-coordinate of third vertex
                float z3 = z1; // Third vertex shares the same z-coordinate

                // If 'inverte' flag is set, swap vertices to inverte triangle orientation
                if (inverte == 1) {
                    float temp_y = y2;
                    float temp_z = z2;
                    y2 = y3;
                    z2 = z3;
                    y3 = temp_y;
                    z3 = temp_z;
                }

                // Add the vertices of the first triangle
                adicionarPonto(plane, novoPonto(x, y1, z1));
                adicionarPonto(plane, novoPonto(x, y3, z3));
                adicionarPonto(plane, novoPonto(x, y2, z2));
                

                // Add the vertices of the second triangle
                adicionarPonto(plane, novoPonto(x, y2, z2));
                adicionarPonto(plane, novoPonto(x, y3, z3));
                adicionarPonto(plane, novoPonto(x, y1 + divisionSize, z1 + divisionSize));
                
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

        if (strcmp(argv[1], "plane") == 0)
        {
            int length = atoi(argv[2]);
            int divisions = atoi(argv[3]);
            file_path = argv[4];

            figura = generatePlane(length, divisions, 'x', 'z');
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
    }
    else
    {
        printf("Número de argumentos inválido.\n");
        return 1;
    }

    return 0;
}