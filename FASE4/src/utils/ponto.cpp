#include "ponto.hpp"
#include <cmath>
#include <iostream>

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

float* getXPointer(Ponto p)
{
    return &(p->x);
}

float* getYPointer(Ponto p)
{
    return &(p->y);
}

float* getZPointer(Ponto p)
{
    return &(p->z);
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

void rodarPonto(Ponto p, Ponto centro, float angle, float x, float y, float z){
    float angleRad = angle * M_PI/180;
    float pontox = getX(p);
    float pontoy = getY(p);
    float pontoz = getZ(p);

    float pontoRotX = x + getX(centro);
    float pontoRotY = y + getY(centro);
    float pontoRotZ = z + getZ(centro);

    float vecX = pontox - pontoRotX;
    float vecY = pontoy - pontoRotY;
    float vecZ = pontoz - pontoRotZ;

    float vecRotX, vecRotY, vecRotZ;

    if(x != 0){
        vecRotX = vecX;
        vecRotY = vecY * cos(angleRad) - vecZ * sin(angleRad);
        vecRotZ = vecY * sin(angleRad) + vecZ * cos(angleRad);
        x = 0;
    } 
    else if(y != 0){
        vecRotX = vecX * cos(angleRad) + vecZ * sin(angleRad);
        vecRotY = vecY;
        vecRotZ = -vecX * sin(angleRad) + vecZ * cos(angleRad);
        y = 0;
    }
    else if(z != 0){
        vecRotX = vecX * cos(angleRad) - vecY * sin(angleRad);
        vecRotY = vecX * sin(angleRad) + vecY * cos(angleRad);
        vecRotZ = vecZ;
        z = 0;
    }

    float newPontoX, newPontoY, newPontoZ;

    newPontoX = vecRotX + pontoRotX;
    newPontoY = vecRotY + pontoRotY;
    newPontoZ = vecRotZ + pontoRotZ;

    setX(p, newPontoX);
    setY(p, newPontoY);
    setZ(p, newPontoZ);

    if(x != 0 || y != 0 || z != 0){
        rodarPonto(p, centro, angle, x, y, z);
    }
}

Ponto normalize(Ponto a){
    float length = sqrt(a->x * a->x + a->y * a->y + a->z * a->z);
    return novoPonto(a->x / length, a->y / length, a->z / length);
}

float innerProduct(Ponto a, Ponto b){
    return a->x * b->x + a->y * b->y + a->z * b->z;
}

Ponto cross(Ponto a, Ponto b){
    //vec1.y * vec2.z - vec1.z * vec2.y, vec1.z * vec2.x - vec1.x * vec2.z, vec1.x * vec2.y - vec1.y * vec2.x
    return novoPonto(a->y * b->z - a->z * b->y, a->z * b->x - a->x * b->z, a->x * b->y - a->y * b->x);
} 

void escalarPonto(Ponto p, Ponto centro, float x, float y, float z){
    float px = getX(p);
    float cx = getX(centro);
    float py = getY(p);
    float cy = getY(centro);
    float pz = getZ(p);
    float cz = getZ(centro);

    px -= cx;
    py -= cy;
    pz -= cz;

    px *= x;
    py *= y;
    pz *= z;

    px += cx;
    py += cy;
    pz += cz;

    setX(p, px);
    setY(p, py);
    setZ(p, pz);
}