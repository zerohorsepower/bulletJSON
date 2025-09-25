#pragma once

#include "GameManager.hpp"

namespace PatternEditor {
    
    // Main function
    void Game();

    // Game Managing
    void InitGame();
    void GameLoop(GameManager * gameManager);
    void GameLoopImplementation(GameManager * gameManager);
    void EndGame(GameManager * gameManager);

    // Other
    bool IsGamePaused();
}