#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include <glm/glm.hpp>
#include "shader.h"

class PointLight {
public:
    glm::vec3 position; // Position de la source de lumière
    glm::vec3 color;    // Couleur de la source de lumière
    float power;        // Puissance de la source de lumière

    PointLight(const glm::vec3& pos, const glm::vec3& col, float pow);
    void Bind(Shader *shader);
    void Unbind(Shader *shader);
};

#endif // POINTLIGHT_H
