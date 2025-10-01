#pragma once

#include "raylib.h"
#include <stdlib.h>

// Forward declaration
namespace PatternEditor {

    class GameManager;
}

namespace BulletJSON {

    struct Bullet;
    struct BulletSpawner;
    typedef Rectangle Sprite;

    struct Bullet {

        int poolId;
        Vector2 position;
        Vector2 acceleration; // Amount of pixels to add on position every frame, recalculate if on "changeSpeed" or "changeDirection" actions
        float speed;
        float direction;
        bool disabled = true;
        BulletSpawner *spawnerRef;
        Sprite *spriteRef;
    };

    struct BulletSpawner {

        Vector2 position;
    };

    enum SpriteList {
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
        SPRITE_COUNT
    };

    class BulletManager {

        friend class PatternEditor::GameManager;

        int maxBullets; // default pre-allocated bullet array size, can expand when necessary (def on ResetBulletArray())
        int lastBulletPoolIndex { 0 };
        int screenDisableOffset { 50 };
        
        Bullet *bullets = nullptr;
        Sprite sprites[SPRITE_COUNT];

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
            void ExtendMaxBullets();
            void ResetBulletPool();
            int GetBulletCount();
            

        public:
            BulletManager();
    };

}