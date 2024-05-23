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
    c->diffuse = diffuse;
}

void add_ambient(Color c, int R, int G, int B){
    RGB ambient = new struct rgb;
    ambient->R = R;
    ambient->G = G;
    ambient->B = B;
    c->ambient = ambient;
}

void add_specular(Color c, int R, int G, int B){
    RGB specular = new struct rgb;
    specular->R = R;
    specular->G = G;
    specular->B = B;
    c->specular = specular;
}

void add_emissive(Color c, int R, int G, int B){
    RGB emissive = new struct rgb;
    emissive->R = R;
    emissive->G = G;
    emissive->B = B;
    c->emissive = emissive;
}

void add_shininess(Color c, int value){
    c->shininess = value;
}

RGB get_diffuse(Color c){
    return c->diffuse;
}

RGB get_ambient(Color c){
    return c->ambient;
}

RGB get_specular(Color c){
    return c->specular;
}

RGB get_emissive(Color c){
    return c->emissive;
}

int get_shininess(Color c){
    return c->shininess;
}

int getR(RGB rgb){
    return rgb->R;
}

int getG(RGB rgb){
    return rgb->G;
}

int getB(RGB rgb){
    return rgb->B;
}