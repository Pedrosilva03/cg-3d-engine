#include "lights.hpp"

enum class LightType{
    DIRECTIONAL,
    POINT,
    SPOT
};

struct lights{
    LightType type;
    float posx, posy, posz, dirx, diry, dirz, cutoff;
};

Lights novaLight(){
    Lights l = new struct lights;
    return l;
}

// Getter para o tipo de luz
std::string getType(Lights l) {
    std::string s = std::string();
    if(l->type == LightType::DIRECTIONAL) s = "directional";
    else if(l->type == LightType::POINT) s = "point";
    else if(l->type == LightType::SPOT) s = "spot";
    return s;
}

// Setter para o tipo de luz
void setType(Lights l, std::string type) {
    if(type == "directional") l->type = LightType::DIRECTIONAL;
    else if(type == "point") l->type = LightType::POINT;
    else if(type == "spot") l->type = LightType::SPOT;
}

// Getter para a posição X da luz
float getPosX(Lights l) {
    return l->posx;
}

// Setter para a posição X da luz
void setPosX(Lights l, float posx) {
    l->posx = posx;
}

// Getter para a posição Y da luz
float getPosY(Lights l) {
    return l->posy;
}

// Setter para a posição Y da luz
void setPosY(Lights l, float posy) {
    l->posy = posy;
}

// Getter para a posição Z da luz
float getPosZ(Lights l) {
    return l->posz;
}

// Setter para a posição Z da luz
void setPosZ(Lights l, float posz) {
    l->posz = posz;
}

// Getter para a direção X da luz
float getDirX(Lights l) {
    return l->dirx;
}

// Setter para a direção X da luz
void setDirX(Lights l, float dirx) {
    l->dirx = dirx;
}

// Getter para a direção Y da luz
float getDirY(Lights l) {
    return l->diry;
}

// Setter para a direção Y da luz
void setDirY(Lights l, float diry) {
    l->diry = diry;
}

// Getter para a direção Z da luz
float getDirZ(Lights l) {
    return l->dirz;
}

// Setter para a direção Z da luz
void setDirZ(Lights l, float dirz) {
    l->dirz = dirz;
}

// Getter para o cutoff da luz
float getCutoff(Lights l) {
    return l->cutoff;
}

// Setter para o cutoff da luz
void setCutoff(Lights l, float cutoff) {
    l->cutoff = cutoff;
}