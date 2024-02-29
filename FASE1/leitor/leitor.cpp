#include "leitor.hpp"
#include <iostream>
#include <list>
#include <string>

struct leitor {
    // DADOS A RETIRAR DO XML//
    float posicao[3];
    float lookAt[3];
    float up[3];
    float projection[3]; // fov, near, far
    std::list<std::string> file;
};

Leitor novoLeitor() {
    Leitor l = (Leitor)malloc(sizeof(struct leitor));

    if (l) {
        for (int i = 0; i < 3; ++i) {
            l->posicao[i] = 0.0f;
            l->lookAt[i] = 0.0f;
            l->up[i] = 0.0f;
            l->projection[i] = 0.0f;
        }

        l->file = std::list<std::string>();
    } else {
        std::cout << "Erro na construção do leitor!" << std::endl;
    }

    return l;
}

Leitor extrair_XML(const char* filePath) {
    Leitor l = novoLeitor();

    if (l) {
        TiXmlDocument doc;
        if (doc.LoadFile(filePath)) {
            TiXmlElement* root = doc.FirstChildElement("world");
            TiXmlElement* camera = root->FirstChildElement("camera");

            // Extrair dados da câmera
            l->posicao[0] = atof(camera->FirstChildElement("position")->Attribute("x"));
            l->posicao[1] = atof(camera->FirstChildElement("position")->Attribute("y"));
            l->posicao[2] = atof(camera->FirstChildElement("position")->Attribute("z"));

            l->lookAt[0] = atof(camera->FirstChildElement("lookAt")->Attribute("x"));
            l->lookAt[1] = atof(camera->FirstChildElement("lookAt")->Attribute("y"));
            l->lookAt[2] = atof(camera->FirstChildElement("lookAt")->Attribute("z"));

            l->up[0] = atof(camera->FirstChildElement("up")->Attribute("x"));
            l->up[1] = atof(camera->FirstChildElement("up")->Attribute("y"));
            l->up[2] = atof(camera->FirstChildElement("up")->Attribute("z"));

            l->projection[0] = atof(camera->FirstChildElement("projection")->Attribute("fov"));
            l->projection[1] = atof(camera->FirstChildElement("projection")->Attribute("near"));
            l->projection[2] = atof(camera->FirstChildElement("projection")->Attribute("far"));

            // Extrair o nome do arquivo do modelo
            TiXmlElement* model_node = root->FirstChildElement("group")->FirstChildElement("models")->FirstChildElement("model");
            std::string file_name = model_node->Attribute("file");
            l->file.push_back(file_name);
        } else {
            std::cout << "Erro ao carregar o arquivo XML." << std::endl;
        }
    }

    return l;
}

float getXPosCam(Leitor l){
    return l->posicao[0];
}

float getYPosCam(Leitor l){
    return l->posicao[1];
}

float getZPosCam(Leitor l){
    return l->posicao[2];
}

float getXLookAt(Leitor l){
    return l->lookAt[0];
}

float getYLookAt(Leitor l){
    return l->lookAt[1];
}

float getZLookAt(Leitor l){
    return l->lookAt[2];
}

float getXUp(Leitor l){
    return l->up[0];
}

float getYUp(Leitor l){
    return l->up[1];
}

float getZUp(Leitor l){
    return l->up[2];
}

void setPosition(Leitor l, float x, float y, float z){
    if(l){
        l->posicao[0] = x;
        l->posicao[1] = y;
        l->posicao[2] = z;
    }
}

void setLookAt(Leitor l, float x, float y, float z){
    if(l){
        l->lookAt[0] = x;
        l->lookAt[1] = y;
        l->lookAt[2] = z;
    }
}

void setUp(Leitor l, float x, float y, float z){
    if(l){
        l->up[0] = x;
        l->up[1] = y;
        l->up[2] = z;
    }
}

void setProjection(Leitor l, float x, float y, float z){
    if(l){
        l->projection[0] = x;
        l->projection[1] = y;
        l->projection[2] = z;
    }
}

std::list<std::string> getFiles(Leitor l) {
    if (l) {
        std::list<std::string> files = l->file;
        return files;
    } else {
        std::cout << "Leitor inválido!" << std::endl;
        return std::list<std::string>(); // Retorna uma lista vazia se o leitor for inválido
    }
}

void deleteLeitor(Leitor l){
    if(l){
        free(l);
    }
}