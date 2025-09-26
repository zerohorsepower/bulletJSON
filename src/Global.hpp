#pragma once

#include "raylib.h"
#include <string>

namespace PatternEditor {

    #ifndef GAME_NAME
        #define GAME_NAME "Bullet Hell Pattern Editor"
    #endif

    namespace Global {

        // #### General
        inline float deltaTime { GetFrameTime() }, deltaTimeScale { 1.0f };
        inline bool isPaused { false }, drawFPS { false };

        // #### Path
        #ifdef IS_OS_BUILD_WEB
            inline std::string gameRootPath { "" };
        #else
            inline std::string gameRootPath { GetApplicationDirectory() };
        #endif
        
        inline std::string assetsPath { gameRootPath + "assets/" };
    }
}