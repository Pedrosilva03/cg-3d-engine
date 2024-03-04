#include "figura.hpp"
#include "ponto.hpp"
#include <iostream>
#include <cstdio>
#include <string> 
#include <list>

using namespace std;

struct figura {
    list<Ponto> pontos;
};

list<Ponto> getPontos(Figura f) {
    return f->pontos; // Retorna a lista de pontos da figura
}

Figura novaFigura() {
    Figura f = new struct figura;
    return f; // Retorna uma nova instância de Figura vazia
}

void adicionarPonto(Figura f, const Ponto novoPonto) {
    f->pontos.push_back(novoPonto); // Adiciona o novo ponto à lista de pontos da figura
}

void adicionarVariosPontos(Figura f, Figura f2) {
    for (const auto& ponto : f2->pontos) {
        f->pontos.push_back(ponto); // Adiciona o novo ponto à lista de pontos da figura
    }
}

void criarFile(const Figura f, const char* path) {
    FILE* file = fopen(path, "w");
    if (file) {
        fprintf(file, "%lu\n", f->pontos.size());
        for (const auto& ponto : f->pontos) {
            fprintf(file, "%g,%g,%g\n", getX(ponto), getY(ponto), getZ(ponto));
        }
        fclose(file);
    }
}

Figura criarFigura(const char* path) {
    Figura f = novaFigura();

    FILE* file = fopen(path, "r");
    if (file) {
        int vertices;
        if (fscanf(file, "%d", &vertices) != 1) {
            cout << "Erro ao ler o número de vértices do arquivo: " << path << endl;
            fclose(file);
            return f; // Retorna a figura vazia
        }

        float x, y, z;
        for (int i = 0; i < vertices; i++) {
            if (fscanf(file, "%f,%f,%f", &x, &y, &z) != 3) {
                cout << "Erro ao ler o vértice " << i << " do arquivo: " << path << endl;
                fclose(file);
                return f; // Retorna a figura vazia
            }
            Ponto p = novoPonto(x, y, z);
            adicionarPonto(f, p);
        }
        fclose(file);
    }
    else {
        cout << "Erro ao abrir o arquivo: " << path << endl;
    }

    return f;
}

void apagarFigura(Figura f) {
    f->pontos.clear(); // Limpa a lista de pontos da figura
}

list<Figura> criarListaFiguras(const list<string>& paths) {
    list<Figura> listaFiguras; // Cria uma lista de figuras vazia

    for (const auto& path : paths) {
        Figura figura = criarFigura(path.c_str()); // Cria uma figura a partir do arquivo
        listaFiguras.push_back(figura); // Adiciona a figura à lista
    }

    return listaFiguras;
}
