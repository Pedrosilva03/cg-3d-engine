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
    float angleRad = angle * M_PI/180;
    float pontox = getX(p);
    float pontoy = getY(p);
    float pontoz = getZ(p);

    float pontoRotX = 0;
    float pontoRotY = 0;
    float pontoRotZ = 0;

    if(x > 0){
        pontoRotX = x;
    }
    if(y > 0){
        pontoRotY = y;
    }
    if(z > 0){
        pontoRotZ = z;
    }

    float vecX = pontox - pontoRotX;
    float vecY = pontoy - pontoRotY;
    float vecZ = pontoz - pontoRotZ;

    float vecRotX, vecRotY, vecRotZ;

    if(x > 0){
        vecRotX = vecX;
        vecRotY = vecY * cos(angleRad) - vecZ * sin(angleRad);
        vecRotZ = vecY * sin(angleRad) + vecZ * cos(angleRad);
    } 
    else if(y > 0){
        vecRotX = vecX * cos(angleRad) + vecZ * sin(angleRad);
        vecRotY = vecY;
        vecRotZ = -vecX * sin(angleRad) + vecZ * cos(angleRad);
    }
    else if(z > 0){
        vecRotX = vecX * cos(angleRad) - vecY * sin(angleRad);
        vecRotY = vecX * sin(angleRad) + vecY * cos(angleRad);
        vecRotZ = vecZ;
    }

    float newPontoX, newPontoY, newPontoZ;

    newPontoX = vecRotX + pontoRotX;
    newPontoY = vecRotY + pontoRotY;
    newPontoZ = vecRotZ + pontoRotZ;

    setX(p, newPontoX);
    setY(p, newPontoY);
    setZ(p, newPontoZ);
}