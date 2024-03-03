#ifndef FIGURA
#define FIGURA
#include "ponto.hpp"

typedef struct Figura* Figura;

Figura novaFigura();

Figura figura(Ponto *pontos, unsigned long length);

Figura criarFigura(const char* path);

void criarFile(Figura f, const char* path);

void adicionarPonto(Figura f, Ponto novoPonto);

void apagarFigura(Figura f);

#endif