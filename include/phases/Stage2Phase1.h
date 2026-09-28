//
// Created by n on 07/09/2026.
//

#ifndef RAYLIB_STG_STAGE2PHASE1_H
#define RAYLIB_STG_STAGE2PHASE1_H
#include "BackgroundHandler.h"
#include "BigEnemy2.h"
#include "Enemy1_2.h"
#include "PhaseHelper.h"
#include "SpawnedEnemies.h"


class SimpleBullet1;
class SimpleBullet3;
class SimpleBullet2;

class Stage2Phase1 : public PhaseHelper
{
     std::shared_ptr<PoolingVector<Enemy1_2Bullet1>> enemy1_2BulletPool;
     std::shared_ptr<PoolingVector<Enemy1_2Bullet2>> enemy1_2BulletPool2;
    std::shared_ptr<PoolingVector<SimpleBullet2>> enemy1BulletPool;
    std::shared_ptr<PoolingVector<AcceleratingBullet1>> bigEnemy2Bullet2Pool;
    bool bigEnemy2Killed = false;
private:
    void spawnEnemy1_2Wave1()
    {
        std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {100, 20}, .speed = 100, .slowAtDesiredPos = false}, {.desiredPos = {50, 20}, .speed = 100, .fireRate = 15}, {.desiredPos = {190, 20}, .speed = 100, .fireRate = 15, .despawn = true},};
        auto newEnemy = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector);
        newEnemy->spawn({Vector2(128, -5)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy));
        std::vector<Enemy1State> enemy1StateVector_2 = {{.desiredPos = {20, 55}, .speed = 100, .slowAtDesiredPos = false}, {.desiredPos = {130, 50}, .speed = 100, .fireRate = 15, .despawn = true},};
        auto newEnemy2 = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector_2);
        newEnemy2->spawn({Vector2(-30, 10)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy2));
    }

    void spawnEnemy1_2Wave2()
    {
        std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {100, 10}, .speed = 100, .slowAtDesiredPos = false},{.desiredPos = {-10, 20}, .speed = 100, .fireRate = 15, .despawn = true},};
        auto newEnemy = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector);
        newEnemy->spawn({Vector2(130, 90)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy));

        std::vector<Enemy1State> enemy1StateVector_2 = {{.desiredPos = {20, 66}, .speed = 100, .slowAtDesiredPos = false}, {.desiredPos = {130, 50}, .speed = 100, .fireRate = 15, .despawn = true},};
        auto newEnemy2 = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector_2);
        newEnemy2->spawn({Vector2(-40, 90)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy2));
    }
public:
    Stage2Phase1() : PhaseHelper("Stage2Phase1", {}, {0, -0.2f}, STAGE_2_BACKGROUND)
    {
        enemy1_2BulletPool = std::make_shared<PoolingVector<Enemy1_2Bullet1>>(90);
        enemy1_2BulletPool2 = std::make_shared<PoolingVector<Enemy1_2Bullet2>>(90);
        enemy1BulletPool = std::make_shared<PoolingVector<SimpleBullet2>>(90);
        BackgroundHandler::SetBackgroundSprite(defaultBackgroundSprite);
        BackgroundHandler::SetBackgroundPosition({0, 0});
        BackgroundHandler::SetScrollVector(defaultScrollVector);

        bigEnemy2Bullet2Pool = std::make_shared<PoolingVector<AcceleratingBullet1>>(300);
        GlobalPools::AddPools({enemy1_2BulletPool, enemy1_2BulletPool2, enemy1BulletPool, bigEnemy2Bullet2Pool});

    }
    void InitPhase() override
    {
        PlayerHandler::GetPlayer()->reset();
        spawnEnemy1_2Wave1();

    }

    void doPreStep() override {
        if (stepsElapsed == 120)
        {
            spawnEnemy1_2Wave2();
        } else if (stepsElapsed == 300)
        {
            for (int row = 0; row < 4; row++)
            {
                for (int i = -1; i <= 1; i += 2)
                {
                    const uint fireRate = 30 + row * 2;
                    std::vector<Enemy1State> enemy1StateVector = {Enemy1State{.desiredPos = {static_cast<float>(60 + (10 + 8 * row) * i), 0}, .speed = 70, .slowAtDesiredPos = false}, Enemy1State{.desiredPos = {static_cast<float>(60 + (10 + 10 * row) * i), 15}, .speed = 70, .fireRate = 30, .slowAtDesiredPos = false}, Enemy1State{.desiredPos = Vector2(60 + static_cast<float>(70 * i), 15 + 30 * row), .speed = 120, .fireRate = fireRate, .despawn=true}};
                    std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                    newEnemy->spawn({Vector2(60 + 5 * i, -6 - 30 * row)});
                    SpawnedEnemies::spawnEnemy(std::move(newEnemy));
                }
            }
        } else if (stepsElapsed == 360)
        {
            spawnEnemy1_2Wave1();
        } else if (stepsElapsed == 480)
        {
            spawnEnemy1_2Wave2();
        } else if (stepsElapsed == 660)
        {
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {60, 20}, .speed = 90,}, {.desiredPos = {60, -20}, .speed = 8, .duration = 600, .fireRate = 2, .despawn = true}};
            auto bigEnemy2 = std::make_unique<BigEnemy2>(bigEnemy2Bullet2Pool, enemy1StateVector);
            bigEnemy2->spawn({Vector2(60, -10), 10});
            SpawnedEnemies::spawnEnemy(std::move(bigEnemy2));
        } else if (stepsElapsed == 760)
        {
            spawnEnemy1_2Wave1();
        } else if (stepsElapsed == 960)
        {
            spawnEnemy1_2Wave2();
        } else if (BackgroundHandler::GetBackgroundPosition().y <= -280)
        {
            GameHandler::NextPhase();
        } else if (bigEnemy2Killed && stepsElapsed % 30 == 0)
        {
            auto enemy1StateVector = std::vector<Enemy1State>{{.desiredPos = {5, 20}, .speed = 90, .fireRate = 90, .slowAtDesiredPos = false}, {.desiredPos = {130, 20}, .speed = 90, .fireRate = 45, .despawn = true, .slowAtDesiredPos = false}};
            auto enemy1 = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
            enemy1->spawn(Vector2{-5, 40});
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
#endif //RAYLIB_STG_STAGE2PHASE1_H