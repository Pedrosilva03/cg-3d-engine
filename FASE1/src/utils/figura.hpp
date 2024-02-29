#ifndef FIGURA
#define FIGURA
#include "ponto.hpp"

typedef struct Figura* Figura;

Figura novaFigura();

Figura figura(Ponto *pontos, unsigned long length);

void adicionarPonto(Figura f, Ponto novoPonto);

#endif