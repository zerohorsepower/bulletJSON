#pragma once

#include "raylib.h"

namespace PatternEditor {

    #ifndef GAME_NAME
        #define GAME_NAME "Bullet Hell Pattern Editor"
    #endif

    namespace Global {

        // #### General
        inline float deltaTime { GetFrameTime() }, deltaTimeScale { 1.0f };
        inline bool isPaused { false }, drawFPS { false };
    }
}