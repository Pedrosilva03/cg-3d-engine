#include "ponto.hpp"
#include <vector>
#ifndef BEZIER_HPP
#define BEZIER_HPP

Ponto calculateBezierPoint(std::vector<Ponto> pontos, float u, float v);
float coef(float grau, float pos, float dir);
float binomial(float grau, float pos);

#endif