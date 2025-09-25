#include "GameManager.hpp"
#include "raylib.h"

PatternEditor::GameManager::GameManager() {};

void PatternEditor::GameManager::update() {

    draw();
};

void PatternEditor::GameManager::draw() {


    BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();
};

void PatternEditor::GameManager::clean() {};