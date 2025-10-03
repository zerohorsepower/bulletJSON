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

    // Setup sprites map
    Global::sprites[Global::SPRITE_BACKGROUND] = Global::Sprite { 3, 3, 800, 800 };
    Global::sprites[Global::SPRITE_PLAYER_SHIP] = Global::Sprite { 155, 809, 58, 66 };
    Global::sprites[Global::SPRITE_BULLET_SPAWNER] = Global::Sprite { 3, 809, 146, 154 };
    Global::sprites[Global::SPRITE_BULLET_1] = Global::Sprite { 229, 918, 43, 20 };
    Global::sprites[Global::SPRITE_BULLET_2] = Global::Sprite { 229, 990, 43, 20 };
    Global::sprites[Global::SPRITE_BULLET_3] = Global::Sprite { 258, 944, 42, 12 };
    Global::sprites[Global::SPRITE_BULLET_4] = Global::Sprite { 258, 962, 42, 12 };
    Global::sprites[Global::SPRITE_BULLET_5] = Global::Sprite { 193, 918, 30, 30 };
    Global::sprites[Global::SPRITE_BULLET_6] = Global::Sprite { 222, 954, 30, 30 };
    Global::sprites[Global::SPRITE_BULLET_7] = Global::Sprite { 278, 1004, 16, 16 };
    Global::sprites[Global::SPRITE_BULLET_8] = Global::Sprite { 300, 1004, 16, 16 };
    Global::sprites[Global::SPRITE_BULLET_9] = Global::Sprite { 183, 993, 40, 24 };
    Global::sprites[Global::SPRITE_BULLET_10] = Global::Sprite { 137, 993, 40, 24 };
    Global::sprites[Global::SPRITE_BULLET_11] = Global::Sprite { 155, 881, 32, 32 };
    Global::sprites[Global::SPRITE_BULLET_12] = Global::Sprite { 193, 881, 32, 31 };
    Global::sprites[Global::SPRITE_BULLET_13] = Global::Sprite { 155, 919, 32, 32 };
    Global::sprites[Global::SPRITE_BULLET_CRISTAL] = Global::Sprite { 3, 993, 128, 20 };
    Global::sprites[Global::SPRITE_BULLET_LASER] = Global::Sprite { 3, 969, 213, 18 };
    Global::sprites[Global::SPRITE_LASER_1] = Global::Sprite { 278, 980, 18, 18 };
    Global::sprites[Global::SPRITE_LASER_2] = Global::Sprite { 302, 980, 18, 18 };
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