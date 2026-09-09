//
// Created by n on 07/09/2026.
//

#ifndef RAYLIB_STG_ENEMY1_H
#define RAYLIB_STG_ENEMY1_H
#include "Enemy1Base.h"

class Enemy1 : public Enemy1Base
{
private:
    std::shared_ptr<PoolingVector<SimpleBullet2>> bulletPool;
    void handleShooting(const Enemy1State currentState) override
    {
        const Vector2 playerFinalPos = PlayerHandler::GetPlayer().get()->GetFinalPos();
        if (currentState.fireRate > 0 && elapsedSteps % currentState.fireRate == 0)
        {
            SoundHandler::PlaySound(THUMP_1);
            Vector2 bulletSpawnPos = {position.x - 5, position.y};
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Normalize(Vector2Subtract({playerFinalPos.x - 1, playerFinalPos.y}, bulletSpawnPos)), RED);
            bulletSpawnPos = {position.x + 5, position.y};
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Normalize(Vector2Subtract({playerFinalPos.x + 1, playerFinalPos.y}, bulletSpawnPos)), RED);
        }
    };
public:
    Enemy1(const std::shared_ptr<PoolingVector<SimpleBullet2>>& _bulletPool, const std::vector<Enemy1State>& _stateVector, const uint _scoreValue = 500) : Enemy1Base(_stateVector, _scoreValue)
    {
        bulletPool = _bulletPool;
    }
};
#endif //RAYLIB_STG_ENEMY1_H