#include "GameManager.hpp"
#include "Global.hpp"
#include "raylib.h"

PatternEditor::GameManager::GameManager() {

    PatternEditor::gameManagerPtr = this;

    // Init game render texture
    gameRenderTexture = LoadRenderTexture(
        baseGameWidth,
        baseGameHeight
    );

    gameRenderTextureYInverted = LoadRenderTexture(
        gameRenderTexture.texture.width,
        gameRenderTexture.texture.height
    );
};

void PatternEditor::GameManager::update() {

    Global::deltaTime = GetFrameTime() * Global::deltaTimeScale;

    editor.update();
    draw();
};

void PatternEditor::GameManager::drawGameRenderTexture() {

    BeginTextureMode(gameRenderTexture);
        
        ClearBackground(BLACK);

        DrawText("TEST TEXT", 300, 300, 30, RED);
    
    EndTextureMode();

    // This is a fix for the RenderTexture with Y inverted, loading another render texture will invert the Y
    // again and fix it. The Y inverted is a behavior from OpenGL. The intention is to skip the use of 2 Rectangles and
    // DrawTexturePro() 
    BeginTextureMode(gameRenderTextureYInverted);

        ClearBackground(BLACK);
        DrawTexture(gameRenderTexture.texture, 0, 0, WHITE);

    EndTextureMode();
}

void PatternEditor::GameManager::draw() {

    drawGameRenderTexture();

    BeginDrawing();
        ClearBackground(BLACK);
        editor.draw(); 
    
    EndDrawing();
};

void PatternEditor::GameManager::clean() {

    editor.clean();

    UnloadRenderTexture(gameRenderTextureYInverted);
    UnloadRenderTexture(gameRenderTexture);

    PatternEditor::gameManagerPtr = nullptr;
};