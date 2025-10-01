#include "GameManager.hpp"
#include "Game.hpp"
#include "Global.hpp"
#include "raylib.h"

#ifdef IS_OS_BUILD_WEB
    #include <emscripten/emscripten.h>
#endif

int main()
{

    PatternEditor::Game();

    return 0;
}

// Main function call
void PatternEditor::Game()
{

    PatternEditor::InitGame();

    PatternEditor::GameManager gameManager;

    PatternEditor::GameLoop();
    PatternEditor::EndGame();
}

// Init basic game structure
void PatternEditor::InitGame()
{

    // ##### Get Screen Resolution
    InitWindow(400,400, GAME_NAME);
    int screenHeight = GetMonitorHeight(GetCurrentMonitor()) * 0.9f;
    int screenWidth = GetMonitorWidth(GetCurrentMonitor()) * 0.9f;
    CloseWindow();

    // ##### Setup
    InitWindow(
        screenWidth,
        screenHeight,
        GAME_NAME
    );

    SetExitKey(KEY_NULL);

    SetWindowState(FLAG_WINDOW_RESIZABLE);
    SetWindowMinSize(400, 400);
    MaximizeWindow();

    // #### Audio
    InitAudioDevice();

    #ifdef IS_OS_BUILD_WEB
        Global::fpsLimit = 144;
        SetTargetFPS(144);
    #endif
};

// Run the game loop
void PatternEditor::GameLoop()
{

    #ifdef IS_OS_BUILD_WEB
    
        emscripten_set_main_loop(GameLoopImplementation, 0, 1);
    
    #else

        while (!WindowShouldClose())
        {

            GameLoopImplementation();
        }

    #endif
};

void PatternEditor::GameLoopImplementation()
{

    if (PatternEditor::gameManagerPtr != nullptr) PatternEditor::gameManagerPtr->Update();
}

// Clean and close the game
void PatternEditor::EndGame()
{


    if (PatternEditor::gameManagerPtr != nullptr) PatternEditor::gameManagerPtr->Clean();

    // Clean assets

    // Close
    CloseAudioDevice();
    CloseWindow();
};