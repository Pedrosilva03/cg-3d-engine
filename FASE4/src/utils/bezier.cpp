#include "bezier.hpp"
#include "ponto.hpp"
#include <math.h>
#include <iostream>
#include <vector>

Ponto calculateBezierPoint(std::vector<Ponto> pontos, float u, float v){
    Ponto res = novoPonto(0, 0, 0);

    for (int w = 0; w < 4; w++){
        for (int t = 0; t < 4; t++){
            float U, V;

            U = coef((float)3, (float)w, u);
            V = coef((float)3, (float)t, v);

            setX(res, getX(res) + getX(pontos[w * 4 + t]) * U * V);
            setY(res, getY(res) + getY(pontos[w * 4 + t]) * U * V);
            setZ(res, getZ(res) + getZ(pontos[w * 4 + t]) * U * V);
        }

    }
    return res;
}
float coef(float grau, float pos, float dir){
    float bin = binomial(grau, pos);

    float umMenosT = pow(1-dir, grau - pos);

    float tElevadoI = pow(dir, pos);

    return bin * umMenosT * tElevadoI;
}

float binomial(float grau, float pos) {
    // Caso base: se i == 0 ou i == n, o coeficiente binomial é 1
    if (pos == 0 || pos == grau) {
        return 1;
    }
    
    // Caso contrário, calcula o coeficiente binomial usando a fórmula recursiva
    return binomial(grau - 1, pos - 1) + binomial(grau - 1, pos);
}