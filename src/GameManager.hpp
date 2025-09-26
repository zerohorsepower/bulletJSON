#pragma once

#include "Editor.hpp"
#include "raylib.h"

namespace PatternEditor {

    class GameManager {

        friend class Editor;

        private:
            Editor editor;

            int baseGameWidth { 800 }, baseGameHeight { 800 };
            RenderTexture gameRenderTexture;
            RenderTexture gameRenderTextureYInverted;

            Texture gameTextureAtlas;

            Vector2 shipPosition { 400, 700 };
            float shipSpeed { 400.0f };
            Rectangle shipSpriteRectangle { 809, 163, 58, 66 };

            void drawGameRenderTexture();

        public:
            GameManager();
            void update();
            void draw();
            void clean();

            
    };

    inline GameManager * gameManagerPtr { nullptr };
}