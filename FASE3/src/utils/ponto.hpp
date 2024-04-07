#ifndef PONTO_HPP
#define PONTO_HPP

#include <cmath>

typedef struct ponto* Ponto;

Ponto novoPonto(float x, float y, float z);

float getX(Ponto p);

float getY(Ponto p);

float getZ(Ponto p);

void setX(Ponto p, float x);

void setY(Ponto p, float y);

void setZ(Ponto p, float z);

float calcularDistanciaOrigem(Ponto p);

float calcularDistanciaEntrePontos(Ponto p1, Ponto p2);

void rodarPonto(Ponto p, float angle, float x = 0.0f, float y = 0.0f, float z = 0.0f);

#endif