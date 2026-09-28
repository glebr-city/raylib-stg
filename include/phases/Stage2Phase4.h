//
// Created by n on 10/09/2026.
//

#ifndef RAYLIB_STG_STAGE2PHASE4_H
#define RAYLIB_STG_STAGE2PHASE4_H
#include <algorithm>
#include <memory>
#include <vector>
#include <sys/types.h>

#include "AcceleratingBullet1.h"
#include "BackgroundHandler.h"
#include "BigEnemy2.h"
#include "Enemy1.h"
#include "Enemy1Base.h"
#include "Enemy1_2.h"
#include "Enemy1_2Bullet1.h"
#include "Enemy1_2Bullet2.h"
#include "GameHandler.h"
#include "GlobalPools.h"
#include "PhaseHelper.h"
#include "PlayerHandler.h"
#include "PoolingVector.h"
#include "raylib.h"
#include "SimpleBullet2.h"
#include "SpawnedEnemies.h"
#include "SpriteHandler.h"

class Stage2Phase4 : public PhaseHelper
{
     std::shared_ptr<PoolingVector<Enemy1_2Bullet1>> enemy1_2BulletPool;
     std::shared_ptr<PoolingVector<Enemy1_2Bullet2>> enemy1_2BulletPool2;
    std::shared_ptr<PoolingVector<SimpleBullet2>> enemy1BulletPool;
    std::shared_ptr<PoolingVector<AcceleratingBullet1>> bigEnemy2Bullet2Pool;
    std::shared_ptr<PoolingVector<SimpleBullet1Fast>> streetlightBulletPool;
    bool bigEnemy2Killed = false;
private:
    void spawnEnemy1_2Wave1()
    {
        std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {100, 160}, .speed = 100, .slowAtDesiredPos = false}, {.desiredPos = {50, 20}, .speed = 100, .fireRate = 15}, {.desiredPos = {190, 20}, .speed = 100, .fireRate = 15, .despawn = true},};
        auto newEnemy = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector);
        newEnemy->spawn({Vector2(128, 190)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy));
        std::vector<Enemy1State> enemy1StateVector_2 = {{.desiredPos = {20, 160}, .speed = 100, .slowAtDesiredPos = false}, {.desiredPos = {70, 20}, .speed = 100, .fireRate = 15}, {.desiredPos = {-70, 20}, .speed = 100, .fireRate = 15, .despawn = true},};
        auto newEnemy2 = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector_2);
        newEnemy2->spawn({Vector2(-8, 190)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy2));
    }

    void spawnEnemy1_2Wave2()
    {
        std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {100, 170}, .speed = 100, .slowAtDesiredPos = false},{.desiredPos = {-10, 20}, .speed = 100, .fireRate = 15, .despawn = true},};
        auto newEnemy = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector);
        newEnemy->spawn({Vector2(130, 180)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy));

        std::vector<Enemy1State> enemy1StateVector_2 = {{.desiredPos = {20, 170}, .speed = 100, .slowAtDesiredPos = false},{.desiredPos = {130, 20}, .speed = 100, .fireRate = 15, .despawn = true},};
        auto newEnemy2 = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector_2);
        newEnemy2->spawn({Vector2(-10, 180)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy2));
    }
public:
    Stage2Phase4() : PhaseHelper("Stage2Phase4", {0, -890}, {0, -0.2f}, STAGE_2_BACKGROUND)
    {
        enemy1_2BulletPool = std::make_shared<PoolingVector<Enemy1_2Bullet1>>(120);
        enemy1_2BulletPool2 = std::make_shared<PoolingVector<Enemy1_2Bullet2>>(120);
        enemy1BulletPool = std::make_shared<PoolingVector<SimpleBullet2>>(120);
        streetlightBulletPool = std::make_shared<PoolingVector<SimpleBullet1Fast>>(60);
        BackgroundHandler::SetBackgroundSprite(defaultBackgroundSprite);
        BackgroundHandler::SetScrollVector(defaultScrollVector);

        bigEnemy2Bullet2Pool = std::make_shared<PoolingVector<AcceleratingBullet1>>(300);
        GlobalPools::AddPools({enemy1_2BulletPool, enemy1_2BulletPool2, enemy1BulletPool, bigEnemy2Bullet2Pool, streetlightBulletPool});

    }
    void InitPhase() override
    {
        spawnEnemy1_2Wave1();
        auto newStreetlightEnemy = std::make_unique<StreetlightEnemy>(streetlightBulletPool);
        newStreetlightEnemy->spawn( Vector2{5, -10});
        SpawnedEnemies::spawnEnemy(std::move(newStreetlightEnemy));
        auto newStreetlightEnemy2 = std::make_unique<StreetlightEnemy>(streetlightBulletPool);
        newStreetlightEnemy2->spawn( Vector2{115, -10});
        SpawnedEnemies::spawnEnemy(std::move(newStreetlightEnemy2));

    }

    void doPreStep() override
    {
        if (stepsElapsed == 120)
        {
            spawnEnemy1_2Wave2();
        } else if (stepsElapsed == 60)
        {
            for (int row = 0; row < 8; row++)
            {
                for (int i = -1; i <= 1; i += 2)
                {
                    const uint fireRate = 30 + row * 2;
                    std::vector<Enemy1State> enemy1StateVector = {Enemy1State{.desiredPos = {static_cast<float>(60 + (10 + 4 * row) * i), 0}, .speed = 70, .slowAtDesiredPos = false}, Enemy1State{.desiredPos = {static_cast<float>(60 + (10 + 4 * row) * i), 15}, .speed = 70, .fireRate = 30, .slowAtDesiredPos = false}, Enemy1State{.desiredPos = Vector2(60 + static_cast<float>(70 * i), 15 + 10 * row), .speed = 120, .fireRate = fireRate, .despawn=true}};
                    std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                    newEnemy->spawn({Vector2(60 + 5 * i, -6 - 30 * row)});
                    SpawnedEnemies::spawnEnemy(std::move(newEnemy));
                }
            }
        } else if (stepsElapsed == 560)
        {
            spawnEnemy1_2Wave1();
        } else if (stepsElapsed == 1000)
        {
            spawnEnemy1_2Wave1();
        } else if (stepsElapsed == 1060)
        {
            spawnEnemy1_2Wave1();
        } else if (stepsElapsed == 1320)
        {
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {60, 20}, .speed = 90,}, {.desiredPos = {60, -20}, .speed = 8, .duration = 600, .fireRate = 2, .despawn = true}};
            auto bigEnemy2 = std::make_unique<BigEnemy2>(bigEnemy2Bullet2Pool, enemy1StateVector);
            bigEnemy2->spawn({Vector2(60, -10), 10});
            SpawnedEnemies::spawnEnemy(std::move(bigEnemy2));
        } else if (stepsElapsed == 1650)
        {
            spawnEnemy1_2Wave1();
        } else if (BackgroundHandler::GetBackgroundPosition().y <= -1290)
        {
            GameHandler::NextPhase();
        } else if (bigEnemy2Killed && stepsElapsed % 30 == 0)
        {
            auto enemy1StateVector = std::vector<Enemy1State>{{.desiredPos = {115, 20}, .speed = 90, .fireRate = 90, .slowAtDesiredPos = false}, {.desiredPos = {-10, 20}, .speed = 90, .fireRate = 45, .despawn = true, .slowAtDesiredPos = false}};
            auto enemy1 = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
            enemy1->spawn(Vector2{125, 40});
            SpawnedEnemies::spawnEnemy(std::move(enemy1));
        }
        PhaseHelper::doPreStep();
    }

    void enemyKilled(const u_int _id) override
    {
        if (_id == 10)
            bigEnemy2Killed = true;
    };
    void enemyDespawned(const u_int _id) override
    {};
};
#endif //RAYLIB_STG_STAGE2PHASE4_H