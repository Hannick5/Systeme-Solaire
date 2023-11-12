#ifndef OBJECT_H
#define OBJECT_H

#include <string>

#include <glm/glm.hpp>

#include "vertexbuffer.h"
#include "vertexarray.h"
#include "texture.h"
#include "uvbuffer.h"

class Object
{
public:
    Object(std::vector< glm::vec3 > vertices, std::vector< glm::vec2 > uvs, std::string texturePath);
    Object(std::vector< glm::vec3 > vertices,std::vector< glm::vec3 > normals, std::vector< glm::vec2 > uvs, std::string texturePath);
    Object(const char *pathObj, std::string pathText);
    Object(const char *pathObj, std::string pathText, glm::vec3 scale_);
    ~Object();
    void Bind() const;
    void Unbind() const;
    void Draw() const;
    void rotateAround(Object& centerObject, float currentTime, float distance);
    glm::vec3 position;
    glm::vec3 rotationAngles;
    glm::vec3 scale;
    glm::mat4 getModelMatrix();


private:
    VertexBuffer *m_vb;
    UVBuffer *m_uvsb;
    Texture *m_texture;
    VertexBuffer *m_normalsb;
    bool loadObj(const char *path, std::vector<glm::vec3> &out_vertices, std::vector<glm::vec2> &out_uvs, std::vector<glm::vec3> &out_normals);
};

#endif // OBJECT_H
