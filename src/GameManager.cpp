#include "GameManager.hpp"
#include "Global.hpp"
#include "raylib.h"

PatternEditor::GameManager::GameManager() {

    PatternEditor::gameManagerPtr = this;
};

void PatternEditor::GameManager::update() {

    editor.update();
    draw();
};

void PatternEditor::GameManager::draw() {

    editor.draw();   
};

void PatternEditor::GameManager::clean() {

    editor.clean();

    PatternEditor::gameManagerPtr = nullptr;
};