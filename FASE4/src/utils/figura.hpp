#include "ponto.hpp"
#include "groups.hpp"
#include <list>
#include <string> 
#ifndef FIGURA_HPP
#define FIGURA_HPP

typedef struct figura* Figura;

bool getCurva(Figura f);

void setCurva(Figura f, bool curva);

void addPontosControlFigura(Figura f, std::list<Ponto> pontosControl);

std::list<Ponto> getPontosControlFigura(Figura f);

std::list<Ponto> getPontos(Figura f);

Figura novaFigura();

void adicionarPonto(Figura f, const Ponto novoPonto);

void adicionarVariosPontos(Figura f, Figura f2);

void criarFile(const Figura f, const char* path);

Figura criarFigura(const char* path);

void apagarFigura(Figura f);

std::list<Figura> criarListaFiguras(Group group, int elapsedTime, int instantBefore);

void applyTransforms(std::list<Figura>& figuras, std::list<Transform>& transforms, int elapsedTime, int instantBefore);

void applyScalesToTransforms(std::list<Transform>& transforms);

#endif