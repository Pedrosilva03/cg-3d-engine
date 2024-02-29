#include "figura.hpp"
#include <stdlib.h>
#include <iostream>

using namespace std;

struct Figura {
    Ponto* pontos;
    unsigned long length;
    unsigned long capacidade;
};

Figura novaFigura() {
    Figura f = (Figura)malloc(sizeof(struct Figura));

    if (f) { // Check if memory allocation for Figura was successful
        f->pontos = NULL;
        f->length = 0;
        f->capacidade = 0;

        return f;
    } else {
        cout << "Erro na construção da figura!" << endl;
        return NULL;
    }
}

Figura figura(Ponto *pontos, unsigned long length) {
    Figura f = (Figura)malloc(sizeof(struct Figura));

    if (f) {
        f->pontos = (Ponto*)malloc(sizeof(Ponto) * length); // Allocate memory for pontos array
        if (f->pontos) {
            for (unsigned long i = 0; i < length; ++i) {
                f->pontos[i] = pontos[i];
            }
            f->length = length;
            f->capacidade = length;
        } else {
            cout << "Erro na alocação de memória para pontos!" << endl;
            free(f);
            return NULL;
        }
    } else {
        cout << "Erro na alocação de memória para Figura!" << endl;
        return NULL;
    }

    return f;
}

void adicionarPonto(Figura f, Ponto novoPonto) {
    if (f->length < f->capacidade) {
        f->pontos[f->length++] = novoPonto;
    } else {
        f->capacidade *= 2;
        f->pontos = (Ponto*)realloc(f->pontos, sizeof(Ponto) * f->capacidade);
        if (f->pontos) {
            f->pontos[f->length++] = novoPonto;
        } else {
            cout << "Erro ao realocar memória para pontos!" << endl;
        }
    }
}
