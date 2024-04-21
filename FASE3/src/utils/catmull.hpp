#include "ponto.hpp"
#include <list>
#include <vector>
#ifndef CATMULL_HPP
#define CATMULL_HPP

Ponto getCatmullRomPoint(float t, std::list<Ponto> pontosControl);

#endif