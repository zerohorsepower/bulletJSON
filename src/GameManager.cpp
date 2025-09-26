#include "GameManager.hpp"
#include "Global.hpp"
#include "raylib.h"

PatternEditor::GameManager::GameManager() {

    PatternEditor::gameManagerPtr = this;
};

void PatternEditor::GameManager::update() {

    Global::deltaTime = GetFrameTime() * Global::deltaTimeScale;

    editor.update();
    draw();
};

void PatternEditor::GameManager::draw() {

    BeginDrawing();
        ClearBackground(BLACK);
        editor.draw(); 
    
    EndDrawing();
};

void PatternEditor::GameManager::clean() {

    editor.clean();

    PatternEditor::gameManagerPtr = nullptr;
};