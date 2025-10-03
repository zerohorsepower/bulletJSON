#pragma once

#include "raylib.h"
#include "Global.hpp"
#include <stdlib.h>

// Forward declaration
namespace PatternEditor {

    class GameManager;
}

namespace BulletJSON {

    struct Bullet;
    struct BulletSpawner;
    struct BulletSprite;

    struct BulletSprite {

        PatternEditor::Global::Sprite *spriteRef = nullptr;
        float angle = 0;
        float anglePerFrame = 0;
        bool sameAngleAsBulletDirection = true;
    };

    struct Bullet {

        Vector2 position;
        Vector2 acceleration; // Amount of pixels to add on position every frame, recalculate if on "changeSpeed" or "changeDirection" actions
        float speed = 0.0f;
        float direction = 0.0f;
        bool disabled = true;
        BulletSpawner *spawnerRef = nullptr;
        BulletSprite sprite;
    };

    struct BulletSpawner {

        Vector2 position;
    };

    class BulletManager {

        friend class PatternEditor::GameManager;

        int maxBullets; // default pre-allocated bullet array size, can expand when necessary (def on ResetBulletArray())
        int lastBulletPoolIndex { 0 };
        int screenDisableOffset { 50 };
        
        Bullet *bullets = nullptr;

        private:
            // life-cycle
            void Update();
            void Draw(Texture *gameTextureAtlas);
            void Clean();

            // bullet managing
            Bullet* CreateBullet();
            void UpdateBullet(Bullet *bullet);
            void VanishBullet(Bullet *bullet);
            
            // bullet array managing
            void SortBulletPool();
            void ExtendMaxBullets();
            void ResetBulletPool();
            int GetBulletCount();
            

        public:
            BulletManager();
    };

}