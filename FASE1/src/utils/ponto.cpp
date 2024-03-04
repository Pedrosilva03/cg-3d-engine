#include "ponto.hpp"
#include <cmath>

struct ponto {
    float x; 
    float y; 
    float z;
};

Ponto novoPonto(float x, float y, float z) {
    Ponto p = (Ponto)malloc(sizeof(Ponto));

    if (p == NULL) return (0, 0, 0);

    p->x = x;
    p->y = y;
    p->z = z;

    return p;
}

float getX(Ponto p){
    return p->x;
}

float getY(Ponto p){
    return p->y;
}

float getZ(Ponto p){
    return p->z;
}

float calcularDistanciaOrigem(Ponto p) {
    return (float)sqrt(pow(p->x, 2) + pow(p->y, 2) + pow(p->z, 2));
}

float calcularDistanciaEntrePontos(Ponto p1, Ponto p2) {
    return (float)sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2) + pow(p2->z - p1->z, 2));
}