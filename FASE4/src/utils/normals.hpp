#include <stdlib.h>
#include <list>
#include <string>
#include <vector>
#include "ponto.hpp"
#ifndef NORMALS_HPP
#define NORMALS_HPP

std::vector<Ponto> normalsHandler(std::string type, std::list<Ponto> pontos);

std::vector<Ponto> calculateCubeNormals(std::list<Ponto> vertices);
std::vector<Ponto> calculatePlaneNormals(std::list<Ponto> vertices);
std::vector<Ponto> calculateSphereNormals(std::list<Ponto> vertices);
std::vector<Ponto> calculateConeNormals(std::list<Ponto> vertices);
std::vector<Ponto> calculateBezierPatchNormals(std::list<Ponto> vertices);
std::vector<Ponto> calculateRingNormals(std::list<Ponto> vertices);

#endif