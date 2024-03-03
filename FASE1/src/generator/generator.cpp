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

// TO DO Generate Box

// TO DO Generate Sphere

// TO DO Generate Cone

//TO DO Completar main
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
