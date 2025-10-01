#include "Bullet.hpp"
#include "Global.hpp"
#include "raylib.h"
#include <math.h>
#include <stdlib.h>

BulletJSON::BulletManager::BulletManager()
{

    // Initialize bullets pool
    ResetBulletPool();

    // Set all bullet sprites map
    sprites[SPRITE_BULLET_1] = Rectangle { 873, 163, 43, 20 };
    sprites[SPRITE_BULLET_2] = Rectangle { 873, 189, 43, 20 };
    sprites[SPRITE_BULLET_3] = Rectangle { 873, 215, 42, 12 };
    sprites[SPRITE_BULLET_4] = Rectangle { 873, 233, 42, 12 };
    sprites[SPRITE_BULLET_5] = Rectangle { 809, 265, 30, 30 };
    sprites[SPRITE_BULLET_6] = Rectangle { 901, 276, 30, 30 };
    sprites[SPRITE_BULLET_7] = Rectangle { 937, 276, 16, 16 };
    sprites[SPRITE_BULLET_8] = Rectangle { 937, 298, 16, 16 };
    sprites[SPRITE_BULLET_9] = Rectangle { 855, 251, 40, 24 };
    sprites[SPRITE_BULLET_10] = Rectangle { 809, 235, 40, 24 };
    sprites[SPRITE_BULLET_11] = Rectangle { 922, 163, 32, 32 };
    sprites[SPRITE_BULLET_12] = Rectangle { 922, 201, 32, 31 };
    sprites[SPRITE_BULLET_13] = Rectangle { 921, 238, 32, 32 };
}

void BulletJSON::BulletManager::Update()
{

    // TEMP: Spawn bullets for test
    if (IsKeyDown(KEY_J))
    {
        for (int i = 0; i < 60; i++)
        {
            Bullet *_bullet = CreateBullet();

            _bullet->spriteRef = &sprites[GetRandomValue(0, SPRITE_COUNT - 1)];
            _bullet->position = { (float) BASE_GAME_WIDTH/2, (float) BASE_GAME_HEIGHT/2 };
            _bullet->direction = (float) GetRandomValue(0, 359);
            _bullet->speed = (float) GetRandomValue(1, 200);

            _bullet->acceleration.x = _bullet->speed * (cosf(_bullet->direction * DEG2RAD));
            _bullet->acceleration.y = _bullet->speed * (sinf(_bullet->direction * DEG2RAD));
        }
    }

    // Update bullets
    for (int i = 0; i < lastBulletPoolIndex; i++)
    {
        if (!bullets[i].disabled)
        {

            UpdateBullet(&bullets[i]);
        }
    }
}

void BulletJSON::BulletManager::Draw(Texture *gameTextureAtlas)
{

    // Draw bullets
    for (int i = 0; i < lastBulletPoolIndex; i++)
    {
        if (!bullets[i].disabled)
        {
            DrawTexturePro(
                *gameTextureAtlas,
                *bullets[i].spriteRef,
                { 
                    bullets[i].position.x,
                    bullets[i].position.y,
                    bullets[i].spriteRef->width,
                    bullets[i].spriteRef->height
                },
                { bullets[i].spriteRef->width*0.5f, bullets[i].spriteRef->height*0.5f },
                bullets[i].direction,
                WHITE
            );
        }
    }
}

void BulletJSON::BulletManager::Clean()
{

    free(bullets);
}

BulletJSON::Bullet* BulletJSON::BulletManager::CreateBullet()
{

    if (!(lastBulletPoolIndex < maxBullets))
    {
        ExtendMaxBullets();
    }

    // Reset bullet attributes
    Bullet *_bullet = &bullets[lastBulletPoolIndex];
    _bullet->poolId = lastBulletPoolIndex;
    _bullet->disabled = false;
    _bullet->position = Vector2 {};
    _bullet->acceleration = Vector2 {};
    _bullet->direction = 0;
    _bullet->speed = 0;
    _bullet->spawnerRef = nullptr;
    _bullet->spriteRef = &sprites[SPRITE_BULLET_1];

    lastBulletPoolIndex++;

    return _bullet;
}

void BulletJSON::BulletManager::UpdateBullet(Bullet *bullet)
{

    bullet->position.x += bullet->acceleration.x * PatternEditor::Global::deltaTime;
    bullet->position.y += bullet->acceleration.y * PatternEditor::Global::deltaTime;

    if (
        (bullet->position.x < (-screenDisableOffset - bullet->spriteRef->width)) ||
        (bullet->position.x > (BASE_GAME_WIDTH + screenDisableOffset + bullet->spriteRef->width)) ||
        (bullet->position.y < (-screenDisableOffset - bullet->spriteRef->height)) ||
        (bullet->position.y > (BASE_GAME_HEIGHT + screenDisableOffset + bullet->spriteRef->height))
    ) {

        VanishBullet(bullet);
    }
}

void BulletJSON::BulletManager::VanishBullet(Bullet *bullet)
{

    int _newBulletPoolId = lastBulletPoolIndex - 1; 
    
    bullet->disabled = true;
    Bullet _bulletCopy = *bullet;

    // Moving all bullets with index between disabled and last_activated
    // This basically sort the array to remove the gap from deactivated bullet
    // Note: This for loop is the most expensive part of the entire bullet pool system
    // Try to only perform this sort once in every 5 or 10 seconds instead of every time you disable a bullet
    for (int i = bullet->poolId; i < lastBulletPoolIndex; i++)
    {

        bullets[i + 1].poolId--;
        bullets[i] = bullets[i + 1];
    }

    // Put the deactivated bullet after the last activated bullet
    _bulletCopy.poolId = _newBulletPoolId;
    bullets[_newBulletPoolId] = _bulletCopy;
    lastBulletPoolIndex--;
}

void BulletJSON::BulletManager::ExtendMaxBullets()
{

    maxBullets += 1000;

    
    Bullet *_bulletsReallocated = (Bullet *) realloc(bullets, maxBullets*sizeof(Bullet));
    if (_bulletsReallocated)
    {

        bullets = _bulletsReallocated;
    } else {
        
        // Couldn't reallocate memory for some reason
        lastBulletPoolIndex--;
        maxBullets -= 1000;
    }
}

void BulletJSON::BulletManager::ResetBulletPool()
{

    maxBullets = 5000;
    lastBulletPoolIndex = 0;

    if (bullets) free(bullets);
    bullets = (Bullet *) malloc(maxBullets*sizeof(Bullet));
}

int BulletJSON::BulletManager::GetBulletCount()
{

    return lastBulletPoolIndex;
}