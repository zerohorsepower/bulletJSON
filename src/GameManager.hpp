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

            void drawGameRenderTexture();

        public:
            GameManager();
            void update();
            void draw();
            void clean();

            
    };

    inline GameManager * gameManagerPtr { nullptr };
}