#ifndef PONTO_HPP
#define PONTO_HPP

#include <cmath>

typedef struct ponto* Ponto;

Ponto novoPonto(float x, float y, float z);

float getX(Ponto p);

float getY(Ponto p);

float getZ(Ponto p);

float calcularDistanciaOrigem(Ponto p);

float calcularDistanciaEntrePontos(Ponto p1, Ponto p2);

#endif