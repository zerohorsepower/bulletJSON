#include "GameManager.hpp"
#include "Global.hpp"
#include "Utils.hpp"
#include "raylib.h"
#include "raymath.h"
#include <string>

PatternEditor::GameManager::GameManager()
{

    PatternEditor::gameManagerPtr = this;

    // Init game render texture
    gameRenderTexture = LoadRenderTexture(
        BASE_GAME_WIDTH,
        BASE_GAME_HEIGHT
    );

    gameRenderTextureYInverted = LoadRenderTexture(
        gameRenderTexture.texture.width,
        gameRenderTexture.texture.height
    );

    // Load game texture atlas
    gameTextureAtlas = LoadTexture((Global::assetsPath + "texture.png").c_str());
    
    // Set texture filter
    SetTextureFilterAll(Global::textureFilter);
};

void PatternEditor::GameManager::Update()
{

    Global::deltaTime = GetFrameTime() * Global::deltaTimeScale;

    // -- performance mode
    if (IsKeyPressed(KEY_SPACE) && Global::isPerformanceMode) Global::isPerformanceMode = false;
    // -- end performance mode

    // -- ship movement
    float _xInput = (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) - (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT));
    float _yInput = (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) - (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP));

    if ((_xInput != 0 || _yInput != 0) && (Global::isGameFocused | Global::isPerformanceMode))
    {

        float _moveDirection = PointDirection(Vector2 {0, 0}, Vector2 {_xInput, _yInput});

        shipPosition.x += LengthDirX(shipSpeed * Global::deltaTime, _moveDirection);
        shipPosition.y += LengthDirY(shipSpeed * Global::deltaTime, _moveDirection);

        shipPosition.x = Clamp(
            shipPosition.x,
            Global::sprites[Global::SPRITE_PLAYER_SHIP].width*0.5f,
            BASE_GAME_WIDTH - Global::sprites[Global::SPRITE_PLAYER_SHIP].width*0.5f
        );
        shipPosition.y = Clamp(
            shipPosition.y,
            Global::sprites[Global::SPRITE_PLAYER_SHIP].height*0.5f,
            BASE_GAME_HEIGHT - Global::sprites[Global::SPRITE_PLAYER_SHIP].height*0.5f
        );
    }
    // --- end ship movement

    // Instance update
    bulletManager.Update();
    editor.Update();

    // Call draw
    Draw();
};

void PatternEditor::GameManager::DrawGameRenderTexture()
{

    BeginTextureMode(gameRenderTexture);
        
        ClearBackground(BLACK);

        // Draw game background
        DrawTexturePro(
            gameTextureAtlas,
            Global::sprites[Global::SPRITE_BACKGROUND],
            {
                0,
                0,
                Global::sprites[Global::SPRITE_BACKGROUND].width,
                Global::sprites[Global::SPRITE_BACKGROUND].height
            },
            { 0, 0 },
            0,
            WHITE
        );

        // Draw ship shadow
        DrawTexturePro(
            gameTextureAtlas,
            Global::sprites[Global::SPRITE_PLAYER_SHIP],
            {
                shipPosition.x + 40,
                shipPosition.y + 150,
                Global::sprites[Global::SPRITE_PLAYER_SHIP].width*0.8f,
                Global::sprites[Global::SPRITE_PLAYER_SHIP].height*0.8f
            },
            {
                Global::sprites[Global::SPRITE_PLAYER_SHIP].width*0.5f,
                Global::sprites[Global::SPRITE_PLAYER_SHIP].height*0.5f
            },
            0,
            { 0, 0, 0, 120 }
        );

        // Draw ship
        DrawTexturePro(
            gameTextureAtlas,
            Global::sprites[Global::SPRITE_PLAYER_SHIP],
            {
                shipPosition.x,
                shipPosition.y,
                Global::sprites[Global::SPRITE_PLAYER_SHIP].width,
                Global::sprites[Global::SPRITE_PLAYER_SHIP].height
            },
            {
                Global::sprites[Global::SPRITE_PLAYER_SHIP].width*0.5f,
                Global::sprites[Global::SPRITE_PLAYER_SHIP].height*0.5f
            },
            0,
            WHITE
        );

        bulletManager.Draw(&gameTextureAtlas);

        // In-game UI
        if (Global::drawFPS)
        {

            std::string _fps = std::string("FPS: ") + std::to_string(GetFPS()) + "\nBullet: " + std::to_string(bulletManager.GetBulletCount());
            DrawRectangle(10, 10, MeasureText("Bullet: 99999", 20) + 20, 60, { 0, 0, 0, 80});
            DrawText(_fps.c_str(), 20, 20, 20, RED);
        }

        if (Global::isPerformanceMode)
        {

            std::string _performanceMode = "Press SPACE to exit from performance mode!";
            float _pmWidth = MeasureText(_performanceMode.c_str(), 20);
            Vector2 _pmPosition = { (float) BASE_GAME_WIDTH/2 - _pmWidth/2, BASE_GAME_HEIGHT * 0.95f };

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

void PatternEditor::GameManager::Draw()
{

    DrawGameRenderTexture();

    BeginDrawing();
        ClearBackground(BLACK);

        if (Global::isPerformanceMode)
        {

            float _renderTextureScale = (float) GetScreenHeight() / gameRenderTextureYInverted.texture.height;
            float _renderTextureX = (float) GetScreenWidth()/2 - (gameRenderTextureYInverted.texture.width * _renderTextureScale)/2;
            DrawTextureEx(gameRenderTextureYInverted.texture, { _renderTextureX, 0 }, 0, _renderTextureScale, WHITE);
        } else {

            editor.Draw();
        }
    
    EndDrawing();
};

void PatternEditor::GameManager::Clean()
{

    bulletManager.Clean();
    editor.Clean();

    UnloadRenderTexture(gameRenderTextureYInverted);
    UnloadRenderTexture(gameRenderTexture);

    UnloadTexture(gameTextureAtlas);

    PatternEditor::gameManagerPtr = nullptr;
};

void PatternEditor::GameManager::SetTextureFilterAll(int textureFilter)
{

    Global::textureFilter = textureFilter;

    SetTextureFilter(gameTextureAtlas, textureFilter);
    SetTextureFilter(gameRenderTexture.texture, textureFilter);
    SetTextureFilter(gameRenderTextureYInverted.texture, textureFilter);
}