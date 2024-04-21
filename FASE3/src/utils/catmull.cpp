#include "catmull.hpp"

float newT;

std::vector<Ponto> reorganizeControlPoints(float t, std::vector<Ponto> pontosList){
    newT = t * pontosList.size();
    int index = static_cast<int>(newT) % pontosList.size();
    newT = newT - floor(newT);

    int ind1, ind2, ind3, ind4;
    ind1 = (index + pontosList.size() - 1) % pontosList.size();
    ind2 = (ind1 + 1) % pontosList.size();
    ind3 = (ind2 + 1) % pontosList.size();
    ind4 = (ind3 + 1) % pontosList.size();

    std::vector<Ponto> pontosOrganizados = {pontosList[ind1], pontosList[ind2], pontosList[ind3], pontosList[ind4]};
    return pontosOrganizados;
}

Ponto getCatmullRomPoint(float t, std::list<Ponto> pontosList){
    std::vector<Ponto> pontosControlNotOrganized(pontosList.begin(), pontosList.end());

    std::vector<Ponto> pontosControl = reorganizeControlPoints(t, pontosControlNotOrganized);

    // Fator de interpolação cúbica
    float t2 = newT * newT;
    float t3 = t2 * newT;

    // Coeficientes do polinômio cúbico de Catmull-Rom
    float c0 = -0.5f * t3 + t2 - 0.5f * newT;
    float c1 = 1.5f * t3 - 2.5f * t2 + 1.0f;
    float c2 = -1.5f * t3 + 2.0f * t2 + 0.5f * newT;
    float c3 = 0.5f * t3 - 0.5f * t2;

    // Interpolação dos pontos de controle
    float px = c0 * getX(pontosControl[0]) + c1 * getX(pontosControl[1]) + c2 * getX(pontosControl[2]) + c3 * getX(pontosControl[3]);
    float py = c0 * getY(pontosControl[0]) + c1 * getY(pontosControl[1]) + c2 * getY(pontosControl[2]) + c3 * getY(pontosControl[3]);
    float pz = c0 * getZ(pontosControl[0]) + c1 * getZ(pontosControl[1]) + c2 * getZ(pontosControl[2]) + c3 * getZ(pontosControl[3]);

    return novoPonto(px, py, pz);
}
