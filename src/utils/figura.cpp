#include "figura.hpp"
#include <stdlib.h>
#include <vector>

struct Figura {
    Ponto* pontos;
};

Figura novaFigura(Ponto *pontos) {
    Figura f = (Figura)malloc(sizeof(struct Figura));

    for (int i = 0; i < 4; i++) {
        f->pontos[i] = pontos[i];
    }

    return f;
}

void adicionarPonto(Figura f, Ponto novoPonto) {
    int indiceVazio = -1;
    int i = 0;

    while(f->pontos[i] != nullptr) {
        if (f->pontos[i] == nullptr) {
            indiceVazio = i;
            break;
        }
        i++;
    }

    if (indiceVazio != -1) {
        f->pontos[indiceVazio] = novoPonto;
    }

    else {
        f->pontos = (Ponto*)realloc(f->pontos, sizeof(Ponto) * (2 * i));
        f->pontos[i] = novoPonto;
    }
}
