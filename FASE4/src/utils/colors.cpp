#include "colors.hpp"

struct rgb{
    int R;
    int G;
    int B;
};

struct colors{
    RGB diffuse;
    RGB ambient;
    RGB specular;
    RGB emissive;
    int shininess;
};

Color novaColor(){
    return new struct colors;
}

void add_diffuse(Color c, int R, int G, int B){
    RGB diffuse = new struct rgb;
    diffuse->R = R;
    diffuse->G = G;
    diffuse->B = B;
}

void add_ambient(Color c, int R, int G, int B){
    RGB ambient = new struct rgb;
    ambient->R = R;
    ambient->G = G;
    ambient->B = B;
}

void add_specular(Color c, int R, int G, int B){
    RGB specular = new struct rgb;
    specular->R = R;
    specular->G = G;
    specular->B = B;
}

void add_emissive(Color c, int R, int G, int B){
    RGB emissive = new struct rgb;
    emissive->R = R;
    emissive->G = G;
    emissive->B = B;
}

void add_shininess(Color c, int value){
    c->shininess = value;
}