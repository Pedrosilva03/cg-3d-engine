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

/*std::vector<Ponto> calculateSphereNormals(std::list<Ponto> vertices) {
    std::vector<Ponto> vertVec(vertices.begin(), vertices.end());
    std::vector<Ponto> normals(vertVec.size());

    for (size_t i = 0; i < vertVec.size(); i += 3) {
        Ponto p1 = vertVec[i];
        Ponto p2 = vertVec[i + 1];
        Ponto p3 = vertVec[i + 2];

        Ponto v1 = novoPonto(getX(p2) - getX(p1), getY(p2) - getY(p1), getZ(p2) - getZ(p1));
        Ponto v2 = novoPonto(getX(p3) - getX(p1), getY(p3) - getY(p1), getZ(p3) - getZ(p1));
        Ponto normal = cross(v1, v2);
        normal = normalize(normal);

        std::cout << i << "\n";

        normals[i] = normalize(novoPonto(getX(p1) + getX(normal), getY(p1) + getY(normal), getZ(p1) + getZ(normal)));
        normals[i + 1] = normalize(novoPonto(getX(p2) + getX(normal), getY(p2) + getY(normal), getZ(p2) + getZ(normal)));
        normals[i + 2] = normalize(novoPonto(getX(p3) + getX(normal), getY(p3) + getY(normal), getZ(p3) + getZ(normal)));
    }

    return normals;
}*/

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

    for(size_t i = 0; i < vertices.size(); i += 6){
        Ponto p1 = vertVec[i];
        Ponto p2 = vertVec[i+1];
        Ponto p3 = vertVec[i+2];
        Ponto p4 = vertVec[i+3];

        float vetorX1 = getX(p1) - centerX;
        float vetorY1 = getY(p1) - centerY;
        float vetorZ1 = getZ(p1) - centerZ;

        float comprimento1 = std::sqrt(vetorX1 * vetorX1 + vetorY1 * vetorY1 + vetorZ1 * vetorZ1);

        float vetorX2 = getX(p2) - centerX;
        float vetorY2 = getY(p2) - centerY;
        float vetorZ2 = getZ(p2) - centerZ;

        float comprimento2 = std::sqrt(vetorX2 * vetorX2 + vetorY2 * vetorY2 + vetorZ2 * vetorZ2);

        float vetorX3 = getX(p3) - centerX;
        float vetorY3 = getY(p3) - centerY;
        float vetorZ3 = getZ(p3) - centerZ;

        float comprimento3 = std::sqrt(vetorX3 * vetorX3 + vetorY3 * vetorY3 + vetorZ3 * vetorZ3);

        float vetorX4 = getX(p4) - centerX;
        float vetorY4 = getY(p4) - centerY;
        float vetorZ4 = getZ(p4) - centerZ;

        float comprimento4 = std::sqrt(vetorX4 * vetorX4 + vetorY4 * vetorY4 + vetorZ4 * vetorZ4);

        normals.push_back(novoPonto(vetorX1 / comprimento1, vetorY1 / comprimento1, vetorZ1 / comprimento1));
        normals.push_back(novoPonto(vetorX2 / comprimento2, vetorY2 / comprimento2, vetorZ2 / comprimento2));
        normals.push_back(novoPonto(vetorX3 / comprimento3, vetorY3 / comprimento3, vetorZ3 / comprimento3));
        normals.push_back(novoPonto(vetorX2 / comprimento2, vetorY2 / comprimento2, vetorZ2 / comprimento2));
        normals.push_back(novoPonto(vetorX4 / comprimento4, vetorY4 / comprimento4, vetorZ4 / comprimento4));
        normals.push_back(novoPonto(vetorX3 / comprimento3, vetorY3 / comprimento3, vetorZ3 / comprimento3));
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

