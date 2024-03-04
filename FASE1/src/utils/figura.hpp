#include "ponto.hpp"
#include <list>
#include <string> 
#ifndef FIGURA_HPP
#define FIGURA_HPP

using namespace std;

typedef struct figura* Figura;

list<Ponto> getPontos(Figura f);

Figura novaFigura();

void adicionarPonto(Figura f, const Ponto novoPonto);

void adicionarVariosPontos(Figura f, Figura f2);

void criarFile(const Figura f, const char* path);

Figura criarFigura(const char* path);

void apagarFigura(Figura f);

list<Figura> criarListaFiguras(const list<string>& paths);

#endif