#ifndef PONTO_HPP
#define PONTO_HPP

#include <cmath>

typedef struct Ponto* Ponto;

Ponto novoPonto(float x, float y, float z);

float calcularDistanciaOrigem(Ponto p);

float calcularDistanciaEntrePontos(Ponto p1, Ponto p2);

#endif