#pragma once

#include "raylib.h"
#include <string>

#define BASE_GAME_WIDTH 800
#define BASE_GAME_HEIGHT 800

namespace PatternEditor {

    #ifndef GAME_NAME
        #define GAME_NAME "BulletJSON Pattern Editor"
    #endif

    namespace Global {

        // Enums
        enum SpriteList {
            SPRITE_BACKGROUND,
            SPRITE_PLAYER_SHIP,
            SPRITE_BULLET_SPAWNER,
            SPRITE_BULLET_1,
            SPRITE_BULLET_2,
            SPRITE_BULLET_3,
            SPRITE_BULLET_4,
            SPRITE_BULLET_5,
            SPRITE_BULLET_6,
            SPRITE_BULLET_7,
            SPRITE_BULLET_8,
            SPRITE_BULLET_9,
            SPRITE_BULLET_10,
            SPRITE_BULLET_11,
            SPRITE_BULLET_12,
            SPRITE_BULLET_13,
            SPRITE_BULLET_CRISTAL,
            SPRITE_BULLET_LASER,
            SPRITE_LASER_1,
            SPRITE_LASER_2,
            SPRITE_COUNT
        };

        // Structs
        typedef Rectangle Sprite;

        // #### General
        inline float deltaTime { GetFrameTime() }, deltaTimeScale { 1.0f };
        inline bool isPaused { false }, drawFPS { true }, isFullscreen { false }, isPerformanceMode { false }, isGameFocused { true };
        inline int textureFilter { TEXTURE_FILTER_POINT }, fpsLimit { 99999 };
        
        // #### Game Logic
        inline float rank { 0.0f };
        inline bool enableSlowdown { false };
        inline int bulletsToSlowdown { 10000 };
        inline float targetSlowdown { 0.5f };

        inline Sprite sprites[SPRITE_COUNT];

        // #### Path
        #ifdef IS_OS_BUILD_WEB
            inline std::string gameRootPath { "" };
        #else
            inline std::string gameRootPath { GetApplicationDirectory() };
        #endif
        
        inline std::string assetsPath { gameRootPath + "assets/" };
    }
}