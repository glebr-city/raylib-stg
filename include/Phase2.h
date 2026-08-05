//
// Created by n on 05/08/2026.
//

#ifndef RAYLIB_STG_PHASE2_H
#define RAYLIB_STG_PHASE2_H
#include "Enemy1.h"
#include "PhaseHelper.h"
#include "SimpleBullet2.h"
#include "SpawnedEnemies.h"

class Phase2 : public PhaseHelper
{
private:
    std::shared_ptr<PoolingVector<SimpleBullet2>> enemy1BulletPool;
public:
    Phase2() : PhaseHelper({0, 240}, {0, 0.2f}, DIAGONAL_TANK_BACKGROUND)
    {
        phaseName = "Phase2";
        enemy1BulletPool = std::make_shared<PoolingVector<SimpleBullet2>>(30, 30);
        GlobalPools::AddPools({enemy1BulletPool});
        BackgroundHandler::SetBackgroundSprite(DIAGONAL_TANK_BACKGROUND);
        BackgroundHandler::SetScrollVector({0, 0.2f});
        if (BackgroundHandler::GetBackgroundPosition().y < 240)
            BackgroundHandler::SetBackgroundPosition({0, 240});



    }

    bool doPhysics() override
    {
        if (stepsElapsed < 360 && stepsElapsed % 90 == 0)
        {
            for (int i = 0; i < 2; i++)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {5, static_cast<float>(35 + i * 10)}, .speed = 30}, {.desiredPos = {125, static_cast<float>(35 + i * 10)}, .speed = 120, .fireRate = 30, .despawn=true}};
                std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                newEnemy->spawn({Vector2(-5 - i, 15 + i * 10), 50});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
        }
        return PhaseHelper::doPhysics();
    }

    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};
#endif //RAYLIB_STG_PHASE2_H