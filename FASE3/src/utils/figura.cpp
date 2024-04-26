#include "figura.hpp"
#include "ponto.hpp"
#include "groups.hpp"
#include "catmull.hpp"
#include <iostream>
#include <cstdio>
#include <string>
#include <list>

struct figura
{
    bool curva; // Indica se uma figura é uma curva de Catmull-Rom
    std::list<Ponto> pontosControl; // Se for uma curva, guarda os pontos de control
    std::list<Ponto> pontos;
};

bool getCurva(Figura f){
    return f->curva;
}

void setCurva(Figura f, bool curva){
    f->curva = curva;
}

void addPontosControlFigura(Figura f, std::list<Ponto> pontosControl)
{
    f->pontosControl = pontosControl;
}

std::list<Ponto> getPontosControlFigura(Figura f)
{
    return f->pontosControl; // Retorna a lista de pontos de control da figura
}

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

std::list<Figura> criarListaFiguras(Group group, int elapsedTime, int instantBefore)
{
    std::list<Figura> listaFiguras; // Cria uma lista de figuras vazia
    
    int i = 0;
    for(Group child = getChild(group, i); child; child = getChild(group, i)){
        listaFiguras.splice(listaFiguras.end(), criarListaFiguras(child, elapsedTime, instantBefore));
        i++;
    }
    std::list<Transform> transforms = getTransform(group);
    std::list<void*> files = getFiles(group);

    for (void* f: files)
    {
        listaFiguras.push_back((Figura)f);            // Adiciona a figura à lista
    }
    applyTransforms(listaFiguras, transforms, elapsedTime, instantBefore);
    return listaFiguras;
}

void applyTransforms(std::list<Figura>& figuras, std::list<Transform>& transforms, int elapsedTime, int instantBefore){
    for(Figura figura: figuras){
        int rotated = 0; // Marca se a figura foi rodada anteriormente ou não
        Transform rotation; // Rotação feita
        std::list<Ponto> pontos = getPontos(figura);
        for(Transform t: transforms){
            if(strcmp(get_transformType(t), "scale") == 0){
                if(elapsedTime == 0 && get_time(t) == 0 && !getCurva(figura)){ // Escalas estáticas
                    for(Ponto p: pontos){
                        if(rotated == 0){
                            setX(p, getX(p) * get_transformX(t));
                            setY(p, getY(p) * get_transformY(t));
                            setZ(p, getZ(p) * get_transformZ(t));
                        }
                        else{
                            Ponto aux = novoPonto(get_transformX(t), get_transformY(t), get_transformZ(t));
                            rodarPonto(aux, get_transformAngle(rotation), get_transformX(rotation), get_transformY(rotation), get_transformZ(rotation));
                            setX(p, getX(p) * getX(aux));
                            setY(p, getY(p) * getY(aux));
                            setZ(p, getZ(p) * getZ(aux));
                        }
                    }
                }
            }
            else if(strcmp(get_transformType(t), "translate") == 0){
                if(elapsedTime == 0 && get_time(t) == 0 && !getCurva(figura)){ // Translações estáticas
                    for(Ponto p: pontos){
                        if(rotated == 0){
                            setX(p, getX(p) + get_transformX(t));
                            setY(p, getY(p) + get_transformY(t));
                            setZ(p, getZ(p) + get_transformZ(t));
                        }
                        else{
                            Ponto aux = novoPonto(get_transformX(t), get_transformY(t), get_transformZ(t));
                            rodarPonto(aux, get_transformAngle(rotation), get_transformX(rotation), get_transformY(rotation), get_transformZ(rotation));
                            setX(p, getX(p) + getX(aux));
                            setY(p, getY(p) + getY(aux));
                            setZ(p, getZ(p) + getZ(aux));
                        }
                    }
                }
                else if(get_time(t) != 0 && get_pontosCat(t).size() > 0 /*&& (float)elapsedTime / 1000.0f < get_time(t)*/ && !getCurva(figura)){ // Translações de Catmull-Rom
                    std::list<Ponto> pontosCat = get_pontosCat(t);
                    float tNormalized = ((float)elapsedTime) / (get_time(t) * 1000.0f);

                    std::vector<Ponto> derivInstant = getCatmullRomPoint(tNormalized, get_pontosControlCat(t));

                    // Guarda o primeiro ponto para determinar a direção para ser aplicada aos outros pontos
                    std::list<Ponto>::iterator it = pontos.begin();
                    Ponto pivo = *it;

                    Ponto catmullAtual = derivInstant[0];
                    float difX = getX(catmullAtual) - getX(pivo); 
                    float difY = getY(catmullAtual) - getY(pivo);
                    float difZ = getZ(catmullAtual) - getZ(pivo);
                    
                    float angulo;
                    Ponto rotationAxis;
                    if(get_align(t) && elapsedTime > 0){
                        std::vector<Ponto> derivBefore = getCatmullRomPoint(((float)instantBefore) / (get_time(t) * 1000.0f), get_pontosControlCat(t));

                        Ponto normalizeBefore = normalize(derivBefore[1]);
                        Ponto normalizeInstant = normalize(derivInstant[1]);
                        float produtoInterno = innerProduct(normalizeInstant, normalizeBefore);

                        angulo = acos(produtoInterno) * 180.0f / M_PI;
                        rotationAxis = cross(derivInstant[1], derivBefore[1]);
                    }
                    
                    for(Ponto p: pontos){
                        setX(p, getX(p) + difX);
                        setY(p, getY(p) + difY);
                        setZ(p, getZ(p) + difZ);

                        if(get_align(t) && elapsedTime > 0){
                            rodarPonto(p, angulo, getX(rotationAxis), getY(rotationAxis), getZ(rotationAxis));
                        }
                    }
                }
            }
            else if(strcmp(get_transformType(t), "rotate") == 0){
                if(elapsedTime == 0 && get_time(t) == 0 && !getCurva(figura)){ // Rotações estáticas
                    rotated = 1;
                    rotation = t;
                    for(Ponto p: pontos){
                        rodarPonto(p, get_transformAngle(t), get_transformX(t), get_transformY(t), get_transformZ(t));
                    }
                }
                else if(get_time(t) != 0 /*&& (float)elapsedTime / 1000.0f < get_time(t)*/){ // Rotações dinâmicas
                    float angleTime = ((float)(elapsedTime - instantBefore)) * (360.0f / (get_time(t) * 1000.0f));
                    if(!getCurva(figura)){
                        for(Ponto p: pontos){
                            rodarPonto(p, angleTime, get_transformX(t), get_transformY(t), get_transformZ(t));
                        }
                    }
                    else if(getCurva(figura)){
                        std::list<Ponto> pontosControl = getPontosControlFigura(figura);
                        for(Ponto pp: pontosControl){
                            rodarPonto(pp, angleTime, get_transformX(t), get_transformY(t), get_transformZ(t));
                        }
                    }
                }
            }
        }
    }
}
