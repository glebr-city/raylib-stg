//
// Created by n on 15/10/2026.
//

#ifndef RAYLIB_STG_ENEMY1_3_H
#define RAYLIB_STG_ENEMY1_3_H
#include "Enemy1Base.h"
#include "SimpleBullet2Fast.h"

class Enemy1_3 : public Enemy1Base
{
private:
    static constexpr ANIMATED_SPRITES sprite = ENEMY_1_3;
    static constexpr Color bulletColour = {255, 20, 20, 255};
    std::shared_ptr<PoolingVector<SimpleBullet2Fast>> bulletPool;
    void handleShooting(const Enemy1State currentState) override
    {
        const Vector2 playerFinalPos = PlayerHandler::GetPlayer().get()->GetFinalPos();
        if (currentState.fireRate > 0 && elapsedSteps % currentState.fireRate == 0)
        {
            SoundHandler::PlaySound(THUMP_1);
            Vector2 bulletSpawnPos = {position.x - 5, position.y};
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Normalize(Vector2Subtract({playerFinalPos.x - 1, playerFinalPos.y}, bulletSpawnPos)), bulletColour);
            bulletSpawnPos = {position.x + 5, position.y};
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Normalize(Vector2Subtract({playerFinalPos.x + 1, playerFinalPos.y}, bulletSpawnPos)), bulletColour);
        }
    };
public:
    Enemy1_3(const std::shared_ptr<PoolingVector<SimpleBullet2Fast>>& _bulletPool, const std::vector<Enemy1State>& _stateVector, const uint _scoreValue = 500) : Enemy1Base(_stateVector, _scoreValue)
    {
        bulletPool = _bulletPool;
    }

    void doPostStep() override
    {
        Color spriteColour = WHITE;
        if (currentFlashDuration-- > 0 && elapsedSteps % 61 <= 30)
            spriteColour = RED;
        if (stateVector[currentStateIndex].fireRate == 0)
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_ENEMY, .col = spriteColour});
        else
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .yOffset = 1, .l = LAYER_ENEMY, .col = spriteColour});
    }
};
#endif //RAYLIB_STG_ENEMY1_3_H