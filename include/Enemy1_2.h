//
// Created by n on 07/09/2026.
//

#ifndef RAYLIB_STG_ENEMY1_2_H
#define RAYLIB_STG_ENEMY1_2_H
#include "Enemy1.h"
#include "Enemy1_2Bullet1.h"

class Enemy1_2 : public Enemy1
{
    static inline const ANIMATED_SPRITES sprite = ENEMY_1_2;
    private:
    std::shared_ptr<PoolingVector<Enemy1_2Bullet1>> bulletPool2;
protected:
    void handleShooting(const Enemy1State currentState) override
    {
        const Vector2 playerFinalPos = PlayerHandler::GetPlayer().get()->GetFinalPos();
        if (currentState.fireRate > 0 && elapsedSteps % currentState.fireRate == 0)
        {
            SoundHandler::PlaySound(THUMP_1);
            Vector2 bulletSpawnPos = {position.x - 6, position.y};
            bulletPool2->spawn().spawn(bulletSpawnPos, Vector2Normalize(Vector2Subtract({playerFinalPos.x - 1, playerFinalPos.y}, bulletSpawnPos)), RED);
            bulletSpawnPos = {position.x + 6, position.y};
            bulletPool2->spawn().spawn(bulletSpawnPos, Vector2Normalize(Vector2Subtract({playerFinalPos.x + 1, playerFinalPos.y}, bulletSpawnPos)), RED);
            bulletSpawnPos = {position.x, position.y};

        }
    }
    public:
    Enemy1_2(const std::shared_ptr<PoolingVector<Enemy1_2Bullet1>>& _bulletPool2, const std::shared_ptr<PoolingVector<SimpleBullet2>>& _bulletPool, const std::vector<Enemy1State>& _stateVector, const uint _scoreValue = 500) : Enemy1(_bulletPool, _stateVector, _scoreValue)
    {
        collider = {0, 0, 14, 12};
        bulletPool2 = _bulletPool2;
    }

    void doPostStep() override
    {
        if (stateVector[currentStateIndex].fireRate == 0)
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_ENEMY});
        else
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .yOffset = 1, .l = LAYER_ENEMY});
    }
};
#endif //RAYLIB_STG_ENEMY1_2_H