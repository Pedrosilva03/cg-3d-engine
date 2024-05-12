#ifndef COLORS_HPP
#define COLORS_HPP

typedef struct rgb *RGB;

typedef struct colors *Color;

Color novaColor();

void add_diffuse(Color c, int R, int G, int B);
void add_ambient(Color c, int R, int G, int B);
void add_specular(Color c, int R, int G, int B);
void add_emissive(Color c, int R, int G, int B);
void add_shininess(Color c, int value);

#endif