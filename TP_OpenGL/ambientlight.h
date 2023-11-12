#ifndef AMBIENTLIGHT
#define AMBIENTLIGHT
#include <glm/glm.hpp>

class AmbientLight {
public:
    glm::vec3 color;

    AmbientLight(const glm::vec3& col);
};

#endif // AMBIENTLIGHT