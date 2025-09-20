#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>
#include "Shader.h"

class Renderer {
private:
    glm::mat4 projectionMatrix;

public:
    Renderer();

    void SetProjection(int screenWidth, int screenHeight);
    void DrawQuad(Shader& shader, glm::vec2 position, glm::vec2 size, glm::vec3 color, unsigned int VAO);
    void Clear(glm::vec3 clearColor = glm::vec3(0.1f, 0.1f, 0.15f));

    ~Renderer();
};

#endif // RENDERER_H

