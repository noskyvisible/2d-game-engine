#include "GameEngine.h"
#include <iostream>

int main() {
    // Create engine with desired window size
    GameEngine engine(800, 600);

    // Initialize the engine
    if (!engine.Initialize()) {
        std::cerr << "Failed to initialize game engine" << std::endl;
        return -1;
    }

    // Run the game
    engine.Run();

    return 0;
}
