#include "normals.hpp"
#include <iostream>

std::vector<Ponto> normalsHandler(std::string type, std::list<Ponto> pontos){
    if (type == "box") {
        return calculateCubeNormals(pontos);
    } else if (type == "plane") {
        return calculatePlaneNormals(pontos);
    } else if (type == "sphere") {
        return calculateSphereNormals(pontos);
    } else if (type == "cone") {
        return calculateConeNormals(pontos);
    } else if (type == "patch") {
        return calculateBezierPatchNormals(pontos);
    } else if (type == "ring") {
        return calculateRingNormals(pontos);
    } else {
        return std::vector<Ponto>();
    }
}

std::vector<Ponto> calculateCubeNormals(std::list<Ponto> vertices) {
    std::list<Ponto> normals = std::list<Ponto>();
    auto it = vertices.begin();
    while (it != vertices.end()) {
        Ponto v0 = *it++;
        Ponto v1 = *it++;
        Ponto v2 = *it++;

        Ponto edge1 = novoPonto(getX(v1) - getX(v0), getY(v1) - getY(v0), getZ(v1) - getZ(v0));
        Ponto edge2 = novoPonto(getX(v2) - getX(v0), getY(v2) - getY(v0), getZ(v2) - getZ(v0));
        Ponto normal = novoPonto(
            getY(edge1) * getZ(edge2) - getZ(edge1) * getY(edge2),
            getZ(edge1) * getX(edge2) - getX(edge1) * getZ(edge2),
            getX(edge1) * getY(edge2) - getY(edge1) * getX(edge2)
        );

        float length = sqrt(getX(normal) * getX(normal) + getY(normal) * getY(normal) + getZ(normal) * getZ(normal));
        setX(normal, getX(normal) / length);
        setY(normal, getY(normal) / length);
        setZ(normal, getZ(normal) / length);

        for (int j = 0; j < 6; ++j) {
            normals.push_back(normal);
        }
    }
    std::vector<Ponto> normalVec(normals.begin(), normals.end());
    return normalVec;
}

std::vector<Ponto> calculatePlaneNormals(std::list<Ponto> vertices) {
    std::list<Ponto> normals = std::list<Ponto>();
    auto it = vertices.begin();
    Ponto v0 = *it++;
    Ponto v1 = *it++;
    Ponto v2 = *it++;

    Ponto edge1 = novoPonto(getX(v1) - getX(v0), getY(v1) - getY(v0), getZ(v1) - getZ(v0));
    Ponto edge2 = novoPonto(getX(v2) - getX(v0), getY(v2) - getY(v0), getZ(v2) - getZ(v0));
    Ponto normal = novoPonto(
        getY(edge1) * getZ(edge2) - getZ(edge1) * getY(edge2),
        getZ(edge1) * getX(edge2) - getX(edge1) * getZ(edge2),
        getX(edge1) * getY(edge2) - getY(edge1) * getX(edge2)
    );

    float length = sqrt(getX(normal) * getX(normal) + getY(normal) * getY(normal) + getZ(normal) * getZ(normal));
    setX(normal, getX(normal) / length);
    setY(normal, getY(normal) / length);
    setZ(normal, getZ(normal) / length);

    for (size_t i = 0; i < vertices.size(); ++i) {
        normals.push_back(normal);
    }
    std::vector<Ponto> normalVec(normals.begin(), normals.end());
    return normalVec;
}

std::vector<Ponto> calculateSphereNormals(std::list<Ponto> vertices) {
    std::vector<Ponto> vertVec(vertices.begin(), vertices.end());
    std::vector<Ponto> normals = std::vector<Ponto>();

    // Calcula o centro da esfera
    float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;
    for (const auto& ponto : vertices) {
        centerX += getX(ponto);
        centerY += getY(ponto);
        centerZ += getZ(ponto);
    }
    centerX /= vertices.size();
    centerY /= vertices.size();
    centerZ /= vertices.size();

    for (const auto& ponto : vertices) {
        float vetorX = getX(ponto) - centerX;
        float vetorY = getY(ponto) - centerY;
        float vetorZ = getZ(ponto) - centerZ;

        float comprimento = std::sqrt(vetorX * vetorX + vetorY * vetorY + vetorZ * vetorZ);

        // Normalize the vector to get the normal
        float normalX = vetorX / comprimento;
        float normalY = vetorY / comprimento;
        float normalZ = vetorZ / comprimento;

        normals.push_back(novoPonto(normalX, normalY, normalZ));
    }
    return normals;
}

std::vector<Ponto> calculateConeNormals(std::list<Ponto> vertices) {
    std::list<Ponto> normals = std::list<Ponto>();
    auto it = vertices.begin();
    while (it != vertices.end()) {
        Ponto v0 = *it++;
        Ponto v1 = *it++;
        Ponto v2 = *it++;

        Ponto edge1 = novoPonto(getX(v1) - getX(v0), getY(v1) - getY(v0), getZ(v1) - getZ(v0));
        Ponto edge2 = novoPonto(getX(v2) - getX(v0), getY(v2) - getY(v0), getZ(v2) - getZ(v0));
        Ponto normal = novoPonto(
            getY(edge1) * getZ(edge2) - getZ(edge1) * getY(edge2),
            getZ(edge1) * getX(edge2) - getX(edge1) * getZ(edge2),
            getX(edge1) * getY(edge2) - getY(edge1) * getX(edge2)
        );

        float length = sqrt(getX(normal) * getX(normal) + getY(normal) * getY(normal) + getZ(normal) * getZ(normal));
        setX(normal, getX(normal) / length);
        setY(normal, getY(normal) / length);
        setZ(normal, getZ(normal) / length);

        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
    }
    std::vector<Ponto> normalVec(normals.begin(), normals.end());
    return normalVec;
}

std::vector<Ponto> calculateBezierPatchNormals(std::list<Ponto> vertices) {
    std::vector<Ponto> vertVec(vertices.begin(), vertices.end());
    std::vector<Ponto> normals = std::vector<Ponto>();

    float centerX = 0.0f, centerY = 0.0f, centerZ = 0.0f;
    for (const auto& ponto : vertices) {
        centerX += getX(ponto);
        centerY += getY(ponto);
        centerZ += getZ(ponto);
    }
    centerX /= vertices.size();
    centerY /= vertices.size();
    centerZ /= vertices.size();

    for (const auto& ponto : vertices) {
        float vetorX = getX(ponto) - centerX;
        float vetorY = getY(ponto) - centerY;
        float vetorZ = getZ(ponto) - centerZ;

        float comprimento = std::sqrt(vetorX * vetorX + vetorY * vetorY + vetorZ * vetorZ);

        // Normalize the vector to get the normal
        float normalX = vetorX / comprimento;
        float normalY = vetorY / comprimento;
        float normalZ = vetorZ / comprimento;

        normals.push_back(novoPonto(normalX, normalY, normalZ));
    }
    return normals;
}

std::vector<Ponto> calculateRingNormals(std::list<Ponto> vertices) {
    std::list<Ponto> normals = std::list<Ponto>();
    auto it = vertices.begin();
    while (it != vertices.end()) {
        Ponto v0 = *it++;
        Ponto v1 = *it++;
        Ponto v2 = *it++;

        Ponto edge1 = novoPonto(getX(v1) - getX(v0), getY(v1) - getY(v0), getZ(v1) - getZ(v0));
        Ponto edge2 = novoPonto(getX(v2) - getX(v0), getY(v2) - getY(v0), getZ(v2) - getZ(v0));
        Ponto normal = novoPonto(
            getY(edge1) * getZ(edge2) - getZ(edge1) * getY(edge2),
            getZ(edge1) * getX(edge2) - getX(edge1) * getZ(edge2),
            getX(edge1) * getY(edge2) - getY(edge1) * getX(edge2)
        );

        float length = sqrt(getX(normal) * getX(normal) + getY(normal) * getY(normal) + getZ(normal) * getZ(normal));
        setX(normal, getX(normal) / length);
        setY(normal, getY(normal) / length);
        setZ(normal, getZ(normal) / length);

        normals.push_back(normal);
        normals.push_back(normal);
        normals.push_back(normal);
    }
    std::vector<Ponto> normalVec(normals.begin(), normals.end());
    return normalVec;
}

