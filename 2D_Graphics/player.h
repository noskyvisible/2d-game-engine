#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include "Renderer.h"
#include "Shader.h"

// Forward declaration to avoid including GLFW in header
struct GLFWwindow;

class Player {
private:
    glm::vec2 position;
    glm::vec2 size;
    glm::vec3 color;
    float speed;

    // OpenGL objects
    unsigned int VAO, VBO;

    void SetupMesh();

public:
    Player(glm::vec2 pos = glm::vec2(0.0f, 0.0f), glm::vec2 sz = glm::vec2(50.0f, 50.0f));

    void Update(float deltaTime, GLFWwindow* window);
    void KeepInBounds(int screenWidth, int screenHeight);
    void Render(Renderer& renderer, Shader& shader);

    // Getters
    glm::vec2 GetPosition() const;
    glm::vec2 GetSize() const;
    glm::vec3 GetColor() const;

    // Setters
    void SetPosition(glm::vec2 pos);
    void SetColor(glm::vec3 col);
    void SetSpeed(float spd);

    ~Player();
};

#endif // PLAYER_H

