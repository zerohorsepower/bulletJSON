#pragma once

#include "raylib.h"
#include <string>

namespace PatternEditor {

    #ifndef GAME_NAME
        #define GAME_NAME "BulletJSON Pattern Editor"
    #endif

    namespace Global {

        // #### General
        inline float deltaTime { GetFrameTime() }, deltaTimeScale { 1.0f };
        inline bool isPaused { false }, drawFPS { true }, isFullscreen { false }, isPerformanceMode { false }, isEditingJSON { false };
        inline int textureFilter { TEXTURE_FILTER_POINT }, fpsLimit { 99999 };
        
        // #### Game Logic
        inline float rank { 0.0f };
        inline bool enableSlowdown { false };
        inline int bulletsToSlowdown { 10000 };
        inline float targetSlowdown { 0.5f };

        // #### Path
        #ifdef IS_OS_BUILD_WEB
            inline std::string gameRootPath { "" };
        #else
            inline std::string gameRootPath { GetApplicationDirectory() };
        #endif
        
        inline std::string assetsPath { gameRootPath + "assets/" };
    }
}