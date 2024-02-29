#ifndef FIGURA
#define FIGURA
#include "ponto.hpp"

typedef struct Figura* Figura;

Figura novaFigura(Ponto *pontos);

void adicionarPonto(Figura f, Ponto novoPonto);

#endif