#include "ponto.hpp"
#include <list>
#include <vector>
#ifndef CATMULL_HPP
#define CATMULL_HPP

std::vector<Ponto> getCatmullRomPoint(float t, std::list<Ponto> pontosList);

#endif