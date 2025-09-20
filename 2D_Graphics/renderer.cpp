#include "Renderer.h"
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

Renderer::Renderer() {
    // Constructor - could initialize default projection here if needed
}

void Renderer::SetProjection(int screenWidth, int screenHeight) {
    // Create orthographic projection for 2D rendering
    projectionMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, -1.0f, 1.0f);
}

void Renderer::DrawQuad(Shader& shader, glm::vec2 position, glm::vec2 size, glm::vec3 color, unsigned int VAO) {
    // Create transformation matrix
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(position, 0.0f));
    model = glm::scale(model, glm::vec3(size, 1.0f));

    // Use shader and set uniforms
    shader.Use();
    shader.SetMat4("model", model);
    shader.SetMat4("projection", projectionMatrix);
    shader.SetVec3("color", color);

    // Render the quad
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void Renderer::Clear(glm::vec3 clearColor) {
    glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

Renderer::~Renderer() {
    // Destructor - cleanup if needed
}
