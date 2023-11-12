#include "pointlight.h"

PointLight::PointLight(const glm::vec3& pos, const glm::vec3& col, float pow)
    : position(pos), color(col), power(pow) {}

void PointLight::Bind(Shader *shader) {
    shader->setUniform3fv("LightPosition_worldspace", position);
    shader->setUniform3fv("pointLightColor", color);
    shader->setUniform1f("pointLightPower", power);
}

void PointLight::Unbind(Shader *shader) {
    shader->setUniform3fv("LightPosition_worldspace", glm::vec3(0.0f));
    shader->setUniform3fv("pointLightColor", glm::vec3(0.0f));
    shader->setUniform1f("pointLightPower", 0.0f);
}
