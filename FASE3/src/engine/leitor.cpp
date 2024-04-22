#include "leitor.hpp"
#include "../utils/groups.hpp"
#include "../utils/figura.hpp"
#include "../utils/catmull.hpp"
#include "../tinyxml/tinyxml.h"
#include <iostream>
#include <list>
#include <string>

struct leitor {
    // DADOS A RETIRAR DO XML//
    float posicao[3];
    float lookAt[3];
    float up[3];
    float projection[3]; // fov, near, far
    Group group;
};

Leitor novoLeitor() {
    Leitor l = new struct leitor;

    if (l) {
        for (int i = 0; i < 3; ++i) {
            l->posicao[i] = 0.0f;
            l->lookAt[i] = 0.0f;
            l->up[i] = 0.0f;
            l->projection[i] = 0.0f;
        }

        l->group = novoGrupo();
    } else {
        std::cout << "Erro na construção do leitor!" << std::endl;
    }

    return l;
}

void extrair_transform(Group node, TiXmlElement* transform_element, std::list<Transform>& transform_node){
    for(TiXmlElement* transform_attribute = transform_element->FirstChildElement(); transform_attribute; transform_attribute = transform_attribute->NextSiblingElement()){
        Transform t = novoTransform();
        add_time(t, 0.0f);
        if(strcmp(transform_attribute->Value(), "scale") == 0){
            add_transformType(t, "scale");
            add_transformX(t, atof(transform_attribute->Attribute("x")));
            add_transformY(t, atof(transform_attribute->Attribute("y")));
            add_transformZ(t, atof(transform_attribute->Attribute("z")));
        }
        else if(strcmp(transform_attribute->Value(), "translate") == 0){
            add_transformType(t, "translate");
            const char* atTime = transform_attribute->Attribute("time");
            if(atTime){ // Sabemos que é uma curva de catmull-rom
                add_time(t, atof(atTime));
                add_align(t, transform_attribute->Attribute("align"));
                std::list<Ponto> pontos = std::list<Ponto>();
                for(TiXmlElement* pointElement = transform_attribute->FirstChildElement("point"); pointElement; pointElement = pointElement->NextSiblingElement("point")){
                    Ponto p = novoPonto(atof(pointElement->Attribute("x")), atof(pointElement->Attribute("y")), atof(pointElement->Attribute("z")));
                    pontos.push_back(p);
                }
                // Calcula os pontos de Catmull-Rom previamente no parse como uma figura para poder aplicar transforms
                std::list<Ponto> pontosCatCalc = std::list<Ponto>();
                float tt = 0.0f;
                for(int i = 0; i < 1000; i++, tt+=0.001){
                    Ponto pCat = getCatmullRomPoint(tt, pontos);
                    pontosCatCalc.push_back(pCat);
                }
                Figura f = novaFigura();
                setCurva(f, true);
                for(Ponto p: pontosCatCalc){
                    adicionarPonto(f, p);
                }
                push_file(node, f);
                add_pontosCat(t, pontosCatCalc);
            }
            else{
                add_transformX(t, atof(transform_attribute->Attribute("x")));
                add_transformY(t, atof(transform_attribute->Attribute("y")));
                add_transformZ(t, atof(transform_attribute->Attribute("z")));
            }
        }
        else if(strcmp(transform_attribute->Value(), "rotate") == 0){
            add_transformType(t, "rotate");
            const char* rotationTime = transform_attribute->Attribute("time");
            if(!rotationTime){
                add_transformAngle(t, atof(transform_attribute->Attribute("angle")));
            }
            else{
                add_time(t, atof(rotationTime));
            }
            add_transformX(t, atof(transform_attribute->Attribute("x")));
            add_transformY(t, atof(transform_attribute->Attribute("y")));
            add_transformZ(t, atof(transform_attribute->Attribute("z")));
        }
        transform_node.push_back(t);
    }
}

void extrair_grupo(TiXmlElement* group_element, Group node){
    for(TiXmlElement* group_child_element = group_element->FirstChildElement("group"); group_child_element; group_child_element = group_child_element->NextSiblingElement("group")){
        Group child_node = novoGrupo();
        extrair_grupo(group_child_element, child_node);
        add_node(node, child_node);
    }

    TiXmlElement* transform_element = group_element->FirstChildElement("transform");
    if(transform_element){
        std::list<Transform> transform_node = std::list<Transform>();
        extrair_transform(node, transform_element, transform_node);
        add_transform(node, transform_node);
    }

    TiXmlElement* model_element = group_element->FirstChildElement("models");
    if(model_element){
        for(TiXmlElement* models = model_element->FirstChildElement(); models; models = models->NextSiblingElement()){
            const char* file_name = models->Attribute("file");
            Figura f = criarFigura(file_name);
            setCurva(f, false);
            push_file(node, (void*)f);
        }
    }
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
            TiXmlElement* main_node = root->FirstChildElement("group");
            extrair_grupo(main_node, l->group);
            
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

float getFov(Leitor l){
    return l->projection[0];
}

float getNear(Leitor l){
    return l->projection[1];
}

float getFar(Leitor l){
    return l->projection[2];
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

Group getNode(Leitor l) {
    if (l) {
        Group files = l->group;
        return files;
    } else {
        std::cout << "Leitor inválido!" << std::endl;
        return nullptr; // Retorna uma lista vazia se o leitor for inválido
    }
}

void deleteLeitor(Leitor l){
    if(l){
        free(l);
    }
}