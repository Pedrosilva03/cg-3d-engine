#include "groups.hpp"
#include "ponto.hpp"
#include <list>
#include <string>
#include <iostream>

struct group{
    std::list<Transform> transform;
    std::list<Group> childs;
    std::list<void*> files; // void* são Figura para fugir ao problema de incluir o header das figuras que causava muitos erros
};

struct transform{
    TransformType type;
    float time;
    const char* align;
    std::list<Ponto> points; // Pontos usados para catmull só no translate
    float angle;
    float x;
    float y;
    float z;
};

enum class TransformType{
    SCALE,
    TRANSLATE,
    ROTATE
};

Group novoGrupo(){
    Group g = new struct group;

    return g;
}

Group getChild(Group g, int i){
    std::list<Group> children = g->childs;

    std::list<Group>::iterator it = children.begin();
    std::advance(it, i);
    
    if(it != children.end()) return *it;
    else return nullptr;
}

std::list<Transform> getTransform(Group g){
    return g->transform;
}

std::list<void*> getFiles(Group g){
    return g->files;
}

void add_transform(Group node, std::list<Transform> transform_node){
    node->transform = transform_node;
}

void add_node(Group node, Group child_node){
    node->childs.push_back(child_node);
}

void push_file(Group group, void* file){
    group->files.push_back(file);
}

Transform novoTransform(){
    Transform t = new struct transform;

    return t;
}

void add_transformType(Transform t, const char* type){
    if(strcmp(type, "scale") == 0) t->type = TransformType::SCALE;
    else if(strcmp(type, "translate") == 0) t->type = TransformType::TRANSLATE;
    else if(strcmp(type, "rotate") == 0) t->type = TransformType::ROTATE;
}

void add_transformAngle(Transform t, float angle){
    t->angle = angle;
}

void add_transformX(Transform t, float x){
    t->x = x;
}

void add_transformY(Transform t, float y){
    t->y = y;
}

void add_transformZ(Transform t, float z){
    t->z = z;
}

void add_time(Transform t, float time){
    t->time = time;
}

void add_align(Transform t, const char* align){
    t->align = align;
}

float get_time(Transform t){
    return t->time;
}

bool get_align(Transform t){
    return t->align;
}

void add_pontosCat(Transform t, std::list<Ponto> pontos){
    t->points = pontos;
}