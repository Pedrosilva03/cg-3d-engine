#include "ponto.hpp"
#include <stdlib.h>
#include <cmath>

struct Ponto {
    float x;
    float y;
    float z;
};

Ponto novoPonto(float x, float y, float z) {
    Ponto p = (Ponto)malloc(sizeof(struct Ponto));

    p->x = x;
    p->y = y;
    p->z = z;

    return p;
}

float calcularDistanciaOrigem(Ponto p) {
    return sqrt(pow(p->x, 2) + pow(p->y, 2) + pow(p->z, 2));
}

float calcularDistanciaEntrePontos(Ponto p1, Ponto p2) {
    return sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2) + pow(p2->z - p1->z, 2));
}
