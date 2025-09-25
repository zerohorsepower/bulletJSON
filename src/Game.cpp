#include "GameManager.hpp"
#include "Global.hpp"
#include "Game.hpp"
#include "raylib.h"

int main() {

    PatternEditor::Game();

    return 0;
}

// Main function call
void PatternEditor::Game() {

    PatternEditor::InitGame();

    PatternEditor::GameManager gameManager;

    PatternEditor::GameLoop(&gameManager);
    PatternEditor::EndGame(&gameManager);
}

// Init basic game structure
void PatternEditor::InitGame() {
    
    // ##### Setup
    InitWindow(
        1280,
        720,
        GAME_NAME
    );

    SetExitKey(KEY_NULL);

    // #### Audio
    InitAudioDevice();

    // ##### Load assets

};

// Run the game loop
void PatternEditor::GameLoop(GameManager * gameManager) {

    #ifdef IS_OS_BUILD_WEB
    
        emscripten_set_main_loop(GameLoopImplementation, 0, 1);
    
    #else

        while (!WindowShouldClose()) {

            GameLoopImplementation(gameManager);
        }

    #endif
};

void PatternEditor::GameLoopImplementation(GameManager * gameManager) {

    gameManager->update();
}

// Clean and close the game
void PatternEditor::EndGame(GameManager * gameManager) {


    gameManager->clean();

    // Clean assets

    // Close
    CloseAudioDevice();
    CloseWindow();
};

// Check if Global::isPaused or Global::isSoftPaused are true
bool PatternEditor::IsGamePaused() {

    return Global::isPaused;
}