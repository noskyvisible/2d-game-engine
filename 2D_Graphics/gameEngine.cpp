#include "GameEngine.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

GameEngine::GameEngine(int w, int h)
    : width(w), height(h), running(false), window(nullptr),
    shader(nullptr), renderer(nullptr), player(nullptr) {
}

bool GameEngine::Initialize() {
    if (!InitializeWindow()) return false;
    if (!InitializeOpenGL()) return false;
    if (!InitializeShaders()) return false;
    if (!InitializeGameObjects()) return false;

    running = true;
    std::cout << "Game Engine Initialized!" << std::endl;
    std::cout << "OpenGL: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GPU: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Controls: WASD or Arrow Keys to move, ESC to exit" << std::endl;

    return true;
}

void GameEngine::Run() {
    double lastTime = glfwGetTime();
    double deltaTime = 0.0;

    while (running && !glfwWindowShouldClose(window)) {
        double currentTime = glfwGetTime();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        HandleInput();
        Update((float)deltaTime);
        Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void GameEngine::Render() {
    // Clear screen
    renderer->Clear();

    // Render all game objects
    if (player && shader) {
        player->Render(*renderer, *shader);
    }
}

void GameEngine::Shutdown() {
    delete player;
    delete shader;
    delete renderer;

    if (window) {
        glfwDestroyWindow(window);
        window = nullptr;
    }
    glfwTerminate();
    std::cout << "Game Engine Shutdown" << std::endl;
}

GameEngine::~GameEngine() {
    Shutdown();
}

bool GameEngine::InitializeWindow() {
    glfwSetErrorCallback([](int error, const char* description) {
        std::cerr << "GLFW Error: " << description << std::endl;
        });

    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return false;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

    window = glfwCreateWindow(width, height, "2D Game Engine - Modular Design", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwMakeContextCurrent(window);
    return true;
}

bool GameEngine::InitializeOpenGL() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return false;
    }

    glViewport(0, 0, width, height);

    // Set up callbacks
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
        glViewport(0, 0, width, height);
        GameEngine* engine = static_cast<GameEngine*>(glfwGetWindowUserPointer(window));
        if (engine && engine->renderer) {
            engine->width = width;
            engine->height = height;
            engine->renderer->SetProjection(width, height);
            engine->Render();
            glfwSwapBuffers(window);
        }
        });

    glfwSwapInterval(1);
    return true;
}

bool GameEngine::InitializeShaders() {
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec2 aPos;
        
        uniform mat4 model;
        uniform mat4 projection;
        
        void main() {
            gl_Position = projection * model * vec4(aPos, 0.0, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        
        uniform vec3 color;
        
        void main() {
            FragColor = vec4(color, 1.0);
        }
    )";

    try {
        shader = new Shader(vertexShaderSource, fragmentShaderSource);
        renderer = new Renderer();
        renderer->SetProjection(width, height);
        return true;
    }
    catch (...) {
        std::cerr << "Failed to create shader or renderer" << std::endl;
        return false;
    }
}

bool GameEngine::InitializeGameObjects() {
    try {
        // Create player at center of screen
        player = new Player(glm::vec2(width / 2 - 25, height / 2 - 25), glm::vec2(50.0f, 50.0f));
        return true;
    }
    catch (...) {
        std::cerr << "Failed to create game objects" << std::endl;
        return false;
    }
}

void GameEngine::HandleInput() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        running = false;
    }
}

void GameEngine::Update(float deltaTime) {
    if (player) {
        player->Update(deltaTime, window);
        player->KeepInBounds(width, height);
    }
}
