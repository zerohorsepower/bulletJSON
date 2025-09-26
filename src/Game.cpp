#include "GameManager.hpp"
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

    PatternEditor::GameLoop();
    PatternEditor::EndGame();
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
    SetWindowState(FLAG_WINDOW_RESIZABLE);

    // #### Audio
    InitAudioDevice();

    // ##### Load assets

};

// Run the game loop
void PatternEditor::GameLoop() {

    #ifdef IS_OS_BUILD_WEB
    
        emscripten_set_main_loop(GameLoopImplementation, 0, 1);
    
    #else

        while (!WindowShouldClose()) {

            GameLoopImplementation();
        }

    #endif
};

void PatternEditor::GameLoopImplementation() {

    if (PatternEditor::gameManagerPtr != nullptr) PatternEditor::gameManagerPtr->update();
}

// Clean and close the game
void PatternEditor::EndGame() {


    if (PatternEditor::gameManagerPtr != nullptr) PatternEditor::gameManagerPtr->clean();

    // Clean assets

    // Close
    CloseAudioDevice();
    CloseWindow();
};