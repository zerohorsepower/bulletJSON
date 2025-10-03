#pragma once

#include "Bullet.hpp"
#include "Editor.hpp"
#include "raylib.h"

namespace PatternEditor {

    class GameManager {

        friend class Editor;

        private:
            BulletJSON::BulletManager bulletManager;
            Editor editor;

            RenderTexture gameRenderTexture;
            RenderTexture gameRenderTextureYInverted;

            Texture gameTextureAtlas;

            Vector2 shipPosition { 400, 600 };
            float shipSpeed { 400.0f };

            void DrawGameRenderTexture();

        public:
            GameManager();
            void Update();
            void Draw();
            void Clean();

            void SetTextureFilterAll(int textureFilter);
    };

    inline GameManager * gameManagerPtr { nullptr };
}