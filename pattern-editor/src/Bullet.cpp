#include "Bullet.hpp"
#include "Global.hpp"
#include "raylib.h"
#include <algorithm>
#include <math.h>
#include <stdlib.h>

BulletJSON::BulletManager::BulletManager()
{

    // Initialize bullets pool
    ResetBulletPool();
}

void BulletJSON::BulletManager::Update()
{
    // TEMP: Reset bullet pool
    if (IsKeyPressed(KEY_C))
    {
        ResetBulletPool();
    }

    // TEMP: Spawn bullets for test
    if (IsKeyDown(KEY_J))
    {
        for (int i = 0; i < 200; i++)
        {
            Bullet *_bullet = CreateBullet();

            _bullet->position = { (float) BASE_GAME_WIDTH/2, (float) BASE_GAME_HEIGHT/2 };
            _bullet->direction = (float) GetRandomValue(0, 359);
            _bullet->speed = (float) GetRandomValue(1, 500)/100;

            _bullet->acceleration.x = _bullet->speed * (cosf(_bullet->direction * DEG2RAD));
            _bullet->acceleration.y = _bullet->speed * (sinf(_bullet->direction * DEG2RAD));

            _bullet->sprite = { 
                &PatternEditor::Global::sprites[
                    GetRandomValue(PatternEditor::Global::SPRITE_BULLET_1, PatternEditor::Global::SPRITE_BULLET_LASER)
                ],
                _bullet->direction,
                (float) GetRandomValue(-15, 15),
                (bool) GetRandomValue(0, 1)
            };

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

    // Sort bullets (move disabled to the end)
    SortBulletPool();
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
                *bullets[i].sprite.spriteRef,
                { 
                    bullets[i].position.x,
                    bullets[i].position.y,
                    bullets[i].sprite.spriteRef->width,
                    bullets[i].sprite.spriteRef->height
                },
                { bullets[i].sprite.spriteRef->width*0.5f, bullets[i].sprite.spriteRef->height*0.5f },
                bullets[i].sprite.angle,
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
    _bullet->disabled = false;
    _bullet->sprite.spriteRef = &PatternEditor::Global::sprites[PatternEditor::Global::SPRITE_BULLET_1];

    lastBulletPoolIndex++;

    return _bullet;
}

void BulletJSON::BulletManager::UpdateBullet(Bullet *bullet)
{

    bullet->position.x += bullet->acceleration.x * PatternEditor::Global::deltaTime;
    bullet->position.y += bullet->acceleration.y * PatternEditor::Global::deltaTime;

    if (!bullet->sprite.sameAngleAsBulletDirection) bullet->sprite.angle += bullet->sprite.anglePerFrame * PatternEditor::Global::deltaTime;

    int _bulletOffset = std::max(bullet->sprite.spriteRef->width, bullet->sprite.spriteRef->height);

    if (
        (bullet->position.x < (-screenDisableOffset - _bulletOffset)) ||
        (bullet->position.x > (BASE_GAME_WIDTH + screenDisableOffset + _bulletOffset)) ||
        (bullet->position.y < (-screenDisableOffset - _bulletOffset)) ||
        (bullet->position.y > (BASE_GAME_HEIGHT + screenDisableOffset + _bulletOffset))
    ) {

        VanishBullet(bullet);
    }
}

void BulletJSON::BulletManager::VanishBullet(Bullet *bullet)
{

    bullet->disabled = true;
}

// This moves all disabled bullets to the end of the pool
// at out of index of "lastBulletPoolIndex"
// This is being done with a single for loop per frame
// How it works: It iterate the entire bullet pool until "lastBulletPoolIndex"
// (everything after that is already disabled).
// When it identifies a disabled bullet it increment the disabled bullet count,
// all the next bullet will be copied to (1*disabledBulletCount) back
// (except other disabled bullets). It will replace all disabled bullets 
// in the array and also keep all enabled bullets sorted at the spawn order.
// At the end it will have a couple of duplicated bullets, these bullets are
// replaced with a copy of a disabled bullets and the "lastBulletPoolIndex"
// is adjusted in accord.
void BulletJSON::BulletManager::SortBulletPool()
{

    int _disabledBulletsCount = 0;
    for (int i = 0; i < lastBulletPoolIndex; i++)
    {

        if (bullets[i].disabled)
        {

            _disabledBulletsCount++;
        } else if (_disabledBulletsCount > 0) {

            bullets[i - _disabledBulletsCount] = bullets[i];
        }
    }

    if (_disabledBulletsCount > 0)
    {

        Bullet _disabledBullet = Bullet {};
        for (int i = 0; i < _disabledBulletsCount; i++)
        {

            // Fill the remaining slots that have duplicated bullets at the end
            // with a copy of a reseted disabled bullet
            bullets[lastBulletPoolIndex - 1 - i] = _disabledBullet;
        }

        lastBulletPoolIndex -= _disabledBulletsCount;
    }

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