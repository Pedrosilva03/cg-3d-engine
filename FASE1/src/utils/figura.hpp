#ifndef FIGURA
#define FIGURA
#include "ponto.hpp"

using namespace std;

typedef struct Figura* Figura;

#include "figura.hpp"
#include "ponto.hpp"
#include <iostream>
#include <list>

using namespace std;

list<Ponto> getPontos(Figura f);

Figura novaFigura();

void adicionarPonto(Figura f, const Ponto novoPonto);

void adicionarVariosPontos(Figura f, Figura f2);

void criarFile(const Figura f, const char* path);

Figura criarFigura(const char* path);

void apagarFigura(Figura f);

list<Figura> criarListaFiguras(const list<string>& paths);

#endif