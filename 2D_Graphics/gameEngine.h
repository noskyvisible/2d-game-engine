#ifndef GAMEENGINE_H
#define GAMEENGINE_H

#include "Shader.h"
#include "Renderer.h"
#include "Player.h"

// Forward declaration to avoid including GLFW in header
struct GLFWwindow;

class GameEngine {
private:
    GLFWwindow* window;
    bool running;

    // Core systems
    Shader* shader;
    Renderer* renderer;

    // Game objects
    Player* player;

    // Private initialization methods
    bool InitializeWindow();
    bool InitializeOpenGL();
    bool InitializeShaders();
    bool InitializeGameObjects();

    // Private game loop methods
    void HandleInput();
    void Update(float deltaTime);

public:
    int width, height;

    GameEngine(int w = 800, int h = 600);

    bool Initialize();
    void Run();
    void Render();
    void Shutdown();

    ~GameEngine();
};

#endif // GAMEENGINE_H

