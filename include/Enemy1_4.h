//
// Created by n on 20/10/2026.
//

#ifndef RAYLIB_STG_ENEMY1_4_H
#define RAYLIB_STG_ENEMY1_4_H
#include "Enemy1Base.h"
#include "HomingBullet.h"
#include "HomingBulletHelper.h"
#include "SpawnedEnemies.h"

class Enemy1_4 : public Enemy1Base
{
    static constexpr ANIMATED_SPRITES sprite = ENEMY_1_4;
    static constexpr int ENEMY_1_4_HEALTH = 4;
    const std::shared_ptr<PoolingVector<HomingBullet>> bulletPool;
    public:
    Enemy1_4(const std::shared_ptr<PoolingVector<HomingBullet>>& _bulletPool, const std::vector<Enemy1State>& _stateVector, const uint _scoreValue = 500) :
        Enemy1Base(_stateVector, _scoreValue), bulletPool(_bulletPool)
    {
        collider = {0, 0, 14, 14};
        health = ENEMY_1_4_HEALTH;
    }

    void handleShooting(const Enemy1State currentState) override
    {
        if (currentState.fireRate > 0 && elapsedSteps % currentState.fireRate == 0)
        {
            SoundHandler::PlaySound(MAGIC_1);
            auto newHomingBulletHelper = std::make_shared<HomingBulletHelper>(bulletPool);
            newHomingBulletHelper->spawn({.pos={position.x, position.y - 7}});
            SpawnedEnemies::spawnEnemy(std::move(newHomingBulletHelper));
        }
    };

    void doPostStep() override
    {
        Color spriteColour = WHITE;
        if (currentFlashDuration-- > 0 && elapsedSteps % 61 <= 30)
            spriteColour = RED;
        if (stateVector[currentStateIndex].fireRate == 0)
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_ENEMY, .col = spriteColour});
        else
        {
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .yOffset = 1, .l = LAYER_ENEMY, .col = spriteColour});
            SpriteHandler::QueueMyAnimatedSprite({.i = ENEMY_1_4_ORB, .pos = Vector2Add(position, {0, -7}), .l = LAYER_ENEMY, .col = spriteColour});
        }
    }
};
#endif //RAYLIB_STG_ENEMY1_4_H