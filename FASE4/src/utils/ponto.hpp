#ifndef PONTO_HPP
#define PONTO_HPP

#define M_PI 3.14159265358979323846

#include <cmath>

typedef struct ponto* Ponto;

Ponto novoPonto(float x, float y, float z);

float getX(Ponto p);

float getY(Ponto p);

float getZ(Ponto p);

float* getXPointer(Ponto p);

float* getYPointer(Ponto p);

float* getZPointer(Ponto p);

void setX(Ponto p, float x);

void setY(Ponto p, float y);

void setZ(Ponto p, float z);

float calcularDistanciaOrigem(Ponto p);

float calcularDistanciaEntrePontos(Ponto p1, Ponto p2);

void rodarPonto(Ponto p, Ponto centro, float angle, float x = 0.0f, float y = 0.0f, float z = 0.0f);

Ponto normalize(Ponto a);

float innerProduct(Ponto a, Ponto b);

Ponto cross(Ponto a, Ponto b);

void escalarPonto(Ponto p, Ponto centro, float x, float y, float z);

#endif