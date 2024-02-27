#ifndef PONTO_HPP
#define PONTO_HPP

#include <cmath>

class Ponto {
    float x;
    float y;
    float z;

public:
    Ponto(float x = 0, float y = 0, float z = 0);

    float getX() const;
    float getY() const;
    float getZ() const;

    void setX(float x);
    void setY(float y);
    void setZ(float z);

    float calcularDistanciaOrigem() const;
    float calcularDistancia(const Ponto& outroPonto) const;
};

#endif