#include "ponto.hpp"
#include <cmath>

class Ponto {
    float x;
    float y;
    float z;

public:
    Ponto(float x = 0, float y = 0, float z = 0) : x(x), y(y), z(z) {}

    float getX() const {
        return x;
    }

    float getY() const {
        return y;
    }

    float getZ() const {
        return z;
    }

    void setX(float x) {
        this->x = x;
    }

    void setY(float y) {
        this->y = y;
    }

    void setZ(float z) {
        this->z = z;
    }

    float calcularDistanciaOrigem() const {
        return sqrt(x * x + y * y + z * z);
    }

    float calcularDistancia(const Ponto& outroPonto) const {
        float dx = x - outroPonto.x;
        float dy = y - outroPonto.y;
        float dz = z - outroPonto.z;
        return sqrt(dx * dx + dy * dy + dz * dz);
    }
};
