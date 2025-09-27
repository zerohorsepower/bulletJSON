#include "GameManager.hpp"
#include "Global.hpp"
#include "Utils.hpp"
#include "raylib.h"
#include "raymath.h"
#include <string>

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
    setTextureFilterAll(Global::textureFilter);
};

void PatternEditor::GameManager::update() {

    Global::deltaTime = GetFrameTime() * Global::deltaTimeScale;

    // -- performance mode
    if (IsKeyPressed(KEY_SPACE)) Global::isPerformanceMode = !Global::isPerformanceMode; 
    // -- end performance mode

    // -- ship movement
    float _xInput = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
    float _yInput = (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) - (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));

    if (_xInput != 0 || _yInput != 0) {

        float _moveDirection = PointDirection(Vector2 {0, 0}, Vector2 {_xInput, _yInput});

        shipPosition.x += LengthDirX(shipSpeed * Global::deltaTime, _moveDirection);
        shipPosition.y += LengthDirY(shipSpeed * Global::deltaTime, _moveDirection);

        shipPosition.x = Clamp(shipPosition.x, 0 + shipSpriteRectangle.width/2, baseGameWidth - shipSpriteRectangle.width/2);
        shipPosition.y = Clamp(shipPosition.y, 0 + shipSpriteRectangle.height/2, baseGameHeight - shipSpriteRectangle.height/2);
    }
    // --- end ship movement


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

        // Draw ship shadow
        DrawTexturePro(
            gameTextureAtlas,
            shipSpriteRectangle,
            { shipPosition.x + 40, shipPosition.y + 150, shipSpriteRectangle.width*0.8f, shipSpriteRectangle.height*0.8f },
            { shipSpriteRectangle.width/2, shipSpriteRectangle.height/2 },
            0,
            { 0, 0, 0, 120 }
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

        if (Global::drawFPS) {

            std::string _fps = std::string("FPS: ") + std::to_string(GetFPS()) + "\nBullet: 0";
            DrawRectangle(10, 10, MeasureText("Bullet: 99999", 20) + 20, 60, { 0, 0, 0, 80});
            DrawText(_fps.c_str(), 20, 20, 20, RED);
        }

        if (Global::isPerformanceMode) {

            std::string _performanceMode = "Press SPACE to exit from performance mode!";
            float _pmWidth = MeasureText(_performanceMode.c_str(), 20);
            Vector2 _pmPosition = { (float) baseGameWidth/2 - _pmWidth/2, baseGameHeight * 0.95f };

            DrawRectangle(_pmPosition.x - 10, _pmPosition.y - 10, _pmWidth + 20, 40, { 0, 0, 0, 80});
            DrawText(_performanceMode.c_str(), _pmPosition.x, _pmPosition.y, 20, RED);
        }
    
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

        if (Global::isPerformanceMode) {

            float _renderTextureScale = (float) GetScreenHeight() / gameRenderTextureYInverted.texture.height;
            float _renderTextureX = (float) GetScreenWidth()/2 - (gameRenderTextureYInverted.texture.width * _renderTextureScale)/2;
            DrawTextureEx(gameRenderTextureYInverted.texture, { _renderTextureX, 0 }, 0, _renderTextureScale, WHITE);
        } else {

            editor.draw();
        }
    
    EndDrawing();
};

void PatternEditor::GameManager::clean() {

    editor.clean();

    UnloadRenderTexture(gameRenderTextureYInverted);
    UnloadRenderTexture(gameRenderTexture);

    UnloadTexture(gameTextureAtlas);

    PatternEditor::gameManagerPtr = nullptr;
};

void PatternEditor::GameManager::setTextureFilterAll(int textureFilter) {

    Global::textureFilter = textureFilter;

    SetTextureFilter(gameTextureAtlas, textureFilter);
    SetTextureFilter(gameRenderTexture.texture, textureFilter);
    SetTextureFilter(gameRenderTextureYInverted.texture, textureFilter);
}