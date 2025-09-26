#include "GameManager.hpp"
#include "Global.hpp"
#include "Utils.hpp"
#include "raylib.h"
#include "raymath.h"

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

    // Load game texture atlas
    gameTextureAtlas = LoadTexture((Global::assetsPath + "texture.png").c_str());
    
    // Set texture filter
    SetTextureFilter(gameTextureAtlas, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(gameRenderTexture.texture, TEXTURE_FILTER_BILINEAR);
    SetTextureFilter(gameRenderTextureYInverted.texture, TEXTURE_FILTER_BILINEAR);
};

void PatternEditor::GameManager::update() {

    Global::deltaTime = GetFrameTime() * Global::deltaTimeScale;

    // Ship position movement
    float _xInput = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
    float _yInput = (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) - (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));

    if (_xInput != 0 || _yInput != 0) {

        float _moveDirection = PointDirection(Vector2 {0, 0}, Vector2 {_xInput, _yInput});

        shipPosition.x += LengthDirX(shipSpeed * Global::deltaTime, _moveDirection);
        shipPosition.y += LengthDirY(shipSpeed * Global::deltaTime, _moveDirection);

        shipPosition.x = Clamp(shipPosition.x, 0 + shipSpriteRectangle.width/2, baseGameWidth - shipSpriteRectangle.width/2);
        shipPosition.y = Clamp(shipPosition.y, 0 + shipSpriteRectangle.height/2, baseGameHeight - shipSpriteRectangle.height/2);
    }


    editor.update();
    draw();
};

void PatternEditor::GameManager::drawGameRenderTexture() {

    BeginTextureMode(gameRenderTexture);
        
        ClearBackground(BLACK);

        // Draw game background
        DrawTexturePro(
            gameTextureAtlas,
            { 3, 3, 800, 800 },
            { 0, 0, 800, 800 },
            { 0, 0 },
            0,
            WHITE
        );

        // Draw ship
        DrawTexturePro(
            gameTextureAtlas,
            shipSpriteRectangle,
            { shipPosition.x, shipPosition.y, shipSpriteRectangle.width, shipSpriteRectangle.height },
            { shipSpriteRectangle.width/2, shipSpriteRectangle.height/2 },
            0,
            WHITE
        );
    
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

    UnloadTexture(gameTextureAtlas);

    PatternEditor::gameManagerPtr = nullptr;
};