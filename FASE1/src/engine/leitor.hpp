#ifndef LEITOR
#define LEITOR
#include "../tinyxml/tinyxml.h"
#include <stdlib.h>
#include <list>
#include <string>

typedef struct leitor* Leitor;

Leitor novoLeitor();

Leitor extrair_XML(const char* filePath);

float getXPosCam(Leitor l);

float getYPosCam(Leitor l);

float getZPosCam(Leitor l);

float getXLookAt(Leitor l);

float getYLookAt(Leitor l);

float getZLookAt(Leitor l);

float getXUp(Leitor l);

float getYUp(Leitor l);

float getZUp(Leitor l);

void setPosition(Leitor l, float x, float y, float z);

void setLookAt(Leitor l, float x, float y, float z);

void setUp(Leitor l, float x, float y, float z);

void setProjection(Leitor l, float x, float y, float z);

std::list<std::string> getFiles(Leitor l);

void deleteLeitor(Leitor l);

#endif