#include "ponto.hpp"
#include <cmath>

#define M_PI 3.14159265358979323846

struct ponto
{
    float x;
    float y;
    float z;
};

Ponto novoPonto(float x, float y, float z)
{
    Ponto p = new struct ponto;
    p->x = x;
    p->y = y;
    p->z = z;

    return p;
}

float getX(Ponto p)
{
    return p->x;
}

float getY(Ponto p)
{
    return p->y;
}

float getZ(Ponto p)
{
    return p->z;
}

void setX(Ponto p, float x)
{
    p->x = x;
}

void setY(Ponto p, float y)
{
    p->y = y;
}

void setZ(Ponto p, float z)
{
    p->z = z;
}

float calcularDistanciaOrigem(Ponto p)
{
    return (float)sqrt(pow(p->x, 2) + pow(p->y, 2) + pow(p->z, 2));
}

float calcularDistanciaEntrePontos(Ponto p1, Ponto p2)
{
    return (float)sqrt(pow(p2->x - p1->x, 2) + pow(p2->y - p1->y, 2) + pow(p2->z - p1->z, 2));
}

void rodarPonto(Ponto p, float angle, float x, float y, float z){
    float rad = angle * M_PI/180;
    float cosA = cos(rad);
    float sinA = sin(rad);

    if(x > 0){
        setY(p, getY(p) * cosA - getZ(p) * sinA);
        setZ(p, getY(p) * sinA - getZ(p) * cosA);
    }
    if(y > 0){
        setX(p, getX(p) * cosA + getZ(p) * sinA);
        setZ(p, -getX(p) * sinA + getZ(p) * cosA);
    }
    if(z > 0){
        setX(p, getX(p) * cosA - getY(p) * sinA);
        setY(p, getX(p) * sinA + getY(p) * cosA);
    }
}