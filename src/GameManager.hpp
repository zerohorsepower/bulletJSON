#pragma once

#include "Editor.hpp"
namespace PatternEditor {

    class GameManager {

        private:
            Editor editor;

        public:
            GameManager();
            void update();
            void draw();
            void clean();
    };

    inline GameManager * gameManagerPtr { nullptr };
}