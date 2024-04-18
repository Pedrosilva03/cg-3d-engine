#include "figura.hpp"
#include "ponto.hpp"
#include "groups.cpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <list>

int instantBefore = 0;

struct figura
{
    std::list<Ponto> pontos;
};

std::list<Ponto> getPontos(Figura f)
{
    return f->pontos; // Retorna a lista de pontos da figura
}

Figura novaFigura()
{
    Figura f = new struct figura;
    return f; // Retorna uma nova instância de Figura vazia
}

void adicionarPonto(Figura f, const Ponto novoPonto)
{
    f->pontos.push_back(novoPonto); // Adiciona o novo ponto à lista de pontos da figura
}

void adicionarVariosPontos(Figura f, Figura f2)
{
    for (const auto &ponto : f2->pontos)
    {
        f->pontos.push_back(ponto); // Adiciona o novo ponto à lista de pontos da figura
    }
}

void criarFile(const Figura f, const char *path)
{
    FILE *file = fopen(path, "w");
    if (file)
    {
        fprintf(file, "%lu\n", static_cast<unsigned long>(f->pontos.size())); // Corrigindo o tipo de dados
        for (const auto &ponto : f->pontos)
        {
            fprintf(file, "%f,%f,%f\n", getX(ponto), getY(ponto), getZ(ponto));
        }
        fclose(file);
    }
}

Figura criarFigura(const char *path)
{
    Figura f = novaFigura();

    FILE *file = fopen(path, "r");
    if (file)
    {
        int vertices;
        if (fscanf(file, "%d", &vertices) != 1)
        {
            std::cout << "Erro ao ler o número de vértices do arquivo: " << path << std::endl;
            fclose(file);
            return f; // Retorna a figura vazia
        }

        float x, y, z;
        for (int i = 0; i < vertices; i++)
        {
            if (fscanf(file, "%f,%f,%f", &x, &y, &z) != 3)
            {
                std::cout << "Erro ao ler o vértice " << i << " do arquivo: " << path << std::endl;
                fclose(file);
                return f; // Retorna a figura vazia
            }
            Ponto p = novoPonto(x, y, z);
            adicionarPonto(f, p);
        }
        fclose(file);
    }
    else
    {
        std::cout << "Erro ao abrir o arquivo: " << path << std::endl;
    }

    return f;
}

void apagarFigura(Figura f)
{
    f->pontos.clear(); // Limpa a lista de pontos da figura
}

std::list<Figura> criarListaFiguras(Group group, int elapsedTime)
{
    std::list<Figura> listaFiguras; // Cria uma lista de figuras vazia
    
    int i = 0;
    for(Group child = getChild(group, i); child; child = getChild(group, i)){
        listaFiguras.splice(listaFiguras.end(), criarListaFiguras(child, elapsedTime));
        i++;
    }
    std::list<Transform> transforms = getTransform(group);
    std::list<void*> files = getFiles(group);

    for (void* f: files)
    {
        listaFiguras.push_back((Figura)f);            // Adiciona a figura à lista
    }
    applyTransforms(listaFiguras, transforms, elapsedTime);
    return listaFiguras;
}

void applyTransforms(std::list<Figura>& figuras, std::list<Transform>& transforms, int elapsedTime){
    for(Figura figura: figuras){
        int rotated = 0; // Marca se a figura foi rodada anteriormente ou não
        Transform rotation; // Rotação feita
        std::list<Ponto> pontos = getPontos(figura);
        for(Transform t: transforms){
            if(t->type == TransformType::SCALE){
                if(elapsedTime == 0 && t->time == 0){ // Escalas estáticas
                    for(Ponto p: pontos){
                        if(rotated == 0){
                            setX(p, getX(p) * t->x);
                            setY(p, getY(p) * t->y);
                            setZ(p, getZ(p) * t->z);
                        }
                        else{
                            Ponto aux = novoPonto(t->x, t->y, t->z);
                            rodarPonto(aux, rotation->angle, rotation->x, rotation->y, rotation->z);
                            setX(p, getX(p) * getX(aux));
                            setY(p, getY(p) * getY(aux));
                            setZ(p, getZ(p) * getZ(aux));
                        }
                    }
                }
            }
            else if(t->type == TransformType::TRANSLATE){
                if(elapsedTime == 0 && t->time == 0){ // Translações estáticas
                    for(Ponto p: pontos){
                        if(rotated == 0){
                            setX(p, getX(p) + t->x);
                            setY(p, getY(p) + t->y);
                            setZ(p, getZ(p) + t->z);
                        }
                        else{
                            Ponto aux = novoPonto(t->x, t->y, t->z);
                            rodarPonto(aux, rotation->angle, rotation->x, rotation->y, rotation->z);
                            setX(p, getX(p) + getX(aux));
                            setY(p, getY(p) + getY(aux));
                            setZ(p, getZ(p) + getZ(aux));
                        }
                    }
                }
            }
            else if(t->type == TransformType::ROTATE){
                if(elapsedTime == 0 && t->time == 0){ // Rotações estáticas
                    rotated = 1;
                    rotation = t;
                    for(Ponto p: pontos){
                        rodarPonto(p, t->angle, t->x, t->y, t->z);
                    }
                }
                else if(t->time != 0 && (float)elapsedTime / 1000.0f < t->time){ // Rotações dinâmicas
                    float angleTime = ((float)(elapsedTime - instantBefore)) * (360.0f / (t->time * 1000.0f));
                    instantBefore = elapsedTime;
                    for(Ponto p: pontos){
                        rodarPonto(p, angleTime, t->x, t->y, t->z);
                    }
                }
            }
        }
    }
}
