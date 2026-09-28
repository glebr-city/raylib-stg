//
// Created by n on 10/09/2026.
//

#ifndef RAYLIB_STG_STAGE2PHASE5_H
#define RAYLIB_STG_STAGE2PHASE5_H
#include <algorithm>
#include <memory>
#include <vector>
#include <sys/types.h>

#include "AcceleratingBullet1.h"
#include "BackgroundHandler.h"
#include "BigEnemy2.h"
#include "Boss2.h"
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
#include "StreetlightEnemy.h"

class Stage2Phase5 : public PhaseHelper
{
     std::shared_ptr<PoolingVector<Enemy1_2Bullet1>> enemy1_2BulletPool;
     std::shared_ptr<PoolingVector<Enemy1_2Bullet2>> enemy1_2BulletPool2;
    std::shared_ptr<PoolingVector<SimpleBullet2>> enemy1BulletPool;
    std::shared_ptr<PoolingVector<AcceleratingBullet1>> bigEnemy2Bullet2Pool;
    std::shared_ptr<PoolingVector<SimpleBullet1Fast>> streetlightBulletPool;
    uint startBigEnemy2KillCount = 0;
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
    Stage2Phase5() : PhaseHelper("Stage2Phase5", {0, -1290}, {0, -0.3f}, STAGE_2_BACKGROUND)
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
        auto bigEnemy2StateVector1 = std::vector{Enemy1State{.desiredPos = {5, 170}, .speed = 40, .fireRate = 60, .slowAtDesiredPos = false}, Enemy1State{.desiredPos = {5, -30}, .speed = 40, .fireRate = 16, .despawn= true, .slowAtDesiredPos = false},};
        auto newBigEnemy2 = std::make_unique<BigEnemy2>(bigEnemy2Bullet2Pool, bigEnemy2StateVector1);
        newBigEnemy2->spawn( {Vector2{5, 195}, 1});
        SpawnedEnemies::spawnEnemy(std::move(newBigEnemy2));
        auto bigEnemy2StateVector1Mirrored = std::vector{Enemy1State{.desiredPos = {115, 170}, .speed = 40, .fireRate = 60, .slowAtDesiredPos = false}, Enemy1State{.desiredPos = {115, -30}, .speed = 40, .fireRate = 16, .despawn= true, .slowAtDesiredPos = false},};
        auto newBigEnemy2Mirrored = std::make_unique<BigEnemy2>(bigEnemy2Bullet2Pool, bigEnemy2StateVector1Mirrored);
        newBigEnemy2Mirrored->spawn( {Vector2{115, 250}, 1});
        SpawnedEnemies::spawnEnemy(std::move(newBigEnemy2Mirrored));

        auto boss2 = std::make_unique<Boss2>(std::shared_ptr<PoolingVector<Boss1SmallBullet>>{}, std::shared_ptr<PoolingVector<SimpleBullet1Slow>>{}, std::shared_ptr<PoolingVector<Boss1FastBurstBullet>> {}, 100);
        boss2->spawn({BackgroundHandler::GetRelativePos(Vector2{60, -1925}), 1000});
        SpawnedEnemies::spawnEnemy(std::move(boss2));

        for (int row = 0; row < 4; row++)
        {
            for (int i = -1; i <= 1; i += 2)
            {
                auto newEnemy1_2StateVector1 = std::vector{Enemy1State{.speed = 0, .duration = static_cast<uint>(800 + row * 100)}, {.desiredPos = {static_cast<float>(60 + (i * 50)), 150}, .speed = 70, .fireRate = static_cast<uint>(25 + row * 10), .despawn = false, .slowAtDesiredPos = false}, {.desiredPos = {static_cast<float>(60 + (i * 50)), 190}, .speed = 70, .despawn = true, .slowAtDesiredPos = false},};
                auto newEnemy1_2 = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, newEnemy1_2StateVector1);
                newEnemy1_2->spawn(Vector2(60 + i * 50, -20));
                SpawnedEnemies::spawnEnemy(std::move(newEnemy1_2));
            }
        }
    }

    void doPreStep() override
    {
        if (startBigEnemy2KillCount >= 2 && stepsElapsed <= 500)
        {
            startBigEnemy2KillCount = 0;
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {60, 20}, .speed = 90,}, {.desiredPos = {60, -20}, .speed = 8, .duration = 300, .fireRate = 2, .despawn = true}};
            auto bigEnemy2 = std::make_unique<BigEnemy2>(bigEnemy2Bullet2Pool, enemy1StateVector);
            bigEnemy2->spawn({Vector2(60, -10)});
            SpawnedEnemies::spawnEnemy(std::move(bigEnemy2));
        } else if (BackgroundHandler::GetBackgroundPosition().y <= -1800)
        {
            BackgroundHandler::SetScrollVector(Vector2{0,0});
        }
        PhaseHelper::doPreStep();
    }

    void enemyKilled(const u_int _id) override
    {
        if (_id == 1)
            startBigEnemy2KillCount++;
    };
    void enemyDespawned(const u_int _id) override
    {};
};
#endif //RAYLIB_STG_STAGE2PHASE5_H