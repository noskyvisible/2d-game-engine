#include "Player.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Player::Player(glm::vec2 pos, glm::vec2 sz)
    : position(pos), size(sz), color(glm::vec3(1.0f, 0.5f, 0.2f)), speed(300.0f) {
    SetupMesh();
}

void Player::SetupMesh() {
    // Create square vertices (normalized coordinates)
    float vertices[] = {
        // Positions
        0.0f, 1.0f,  // Top Left
        1.0f, 0.0f,  // Bottom Right
        0.0f, 0.0f,  // Bottom Left

        0.0f, 1.0f,  // Top Left
        1.0f, 1.0f,  // Top Right
        1.0f, 0.0f   // Bottom Right
    };

    // Generate and bind VAO and VBO
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Player::Update(float deltaTime, GLFWwindow* window) {
    // Handle WASD movement
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        position.y += speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        position.y -= speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        position.x -= speed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        position.x += speed * deltaTime;
    }
}

void Player::KeepInBounds(int screenWidth, int screenHeight) {
    // Keep player within screen bounds
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + size.x > screenWidth) position.x = screenWidth - size.x;
    if (position.y + size.y > screenHeight) position.y = screenHeight - size.y;
}

void Player::Render(Renderer& renderer, Shader& shader) {
    renderer.DrawQuad(shader, position, size, color, VAO);
}

// Getters
glm::vec2 Player::GetPosition() const {
    return position;
}

glm::vec2 Player::GetSize() const {
    return size;
}

glm::vec3 Player::GetColor() const {
    return color;
}

// Setters
void Player::SetPosition(glm::vec2 pos) {
    position = pos;
}

void Player::SetColor(glm::vec3 col) {
    color = col;
}

void Player::SetSpeed(float spd) {
    speed = spd;
}

Player::~Player() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}