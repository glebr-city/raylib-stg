//
// Created by n on 09/09/2026.
//

#ifndef RAYLIB_STG_STAGE2PHASE3_H
#define RAYLIB_STG_STAGE2PHASE3_H
#include "PhaseHelper.h"

class Stage2Phase3 : public PhaseHelper
{
private:
    std::shared_ptr<PoolingVector<SimpleBullet3>> bigEnemy1Bullet1Pool;
    std::shared_ptr<PoolingVector<SimpleBullet1>> bigEnemy1Bullet2Pool;
    std::shared_ptr<PoolingVector<Enemy1_2Bullet1>> enemy1_2BulletPool;
    std::shared_ptr<PoolingVector<Enemy1_2Bullet2>> enemy1_2BulletPool2;
public:
    Stage2Phase3() : PhaseHelper("Stage2Phase3", {0, -650}, {0, -0.2f}, STAGE_2_BACKGROUND)
    {
        BackgroundHandler::SetBackgroundSprite(defaultBackgroundSprite);
        BackgroundHandler::SetScrollVector(defaultScrollVector);
        bigEnemy1Bullet1Pool = std::make_shared<PoolingVector<SimpleBullet3>>(200);
        bigEnemy1Bullet2Pool = std::make_shared<PoolingVector<SimpleBullet1>>(200);

        enemy1_2BulletPool = std::make_shared<PoolingVector<Enemy1_2Bullet1>>(200);
        enemy1_2BulletPool2 = std::make_shared<PoolingVector<Enemy1_2Bullet2>>(200);
        GlobalPools::AddPools({bigEnemy1Bullet1Pool, bigEnemy1Bullet2Pool, enemy1_2BulletPool, enemy1_2BulletPool2});
    };
    void InitPhase() override
    {
        std::vector<Enemy1State> bigEnemy1StateVector = {{.desiredPos = {20, 20}, .speed = 30,}, {.desiredPos = {10, 20}, .speed = 0, .duration = 600, .fireRate = 8, .despawn = false}, {.desiredPos = {20, -15}, .speed = 30, .fireRate = 8, .despawn = true},};
        auto newBigEnemy1 = std::make_unique<BigEnemy1>(bigEnemy1Bullet1Pool, bigEnemy1Bullet2Pool, bigEnemy1StateVector);
        newBigEnemy1->spawn({Vector2(20, -15), 15});
        SpawnedEnemies::spawnEnemy(std::move(newBigEnemy1));

        std::vector<Enemy1State> bigEnemy1StateVector2 = {{.desiredPos = {100, 20}, .speed = 30,}, {.desiredPos = {110, 20}, .speed = 0, .duration = 600, .fireRate = 8, .despawn = false}, {.desiredPos = {100, -15}, .speed = 30, .fireRate = 8, .despawn = true},};
        auto newBigEnemy1_2 = std::make_unique<BigEnemy1>(bigEnemy1Bullet1Pool, bigEnemy1Bullet2Pool, bigEnemy1StateVector2);
        newBigEnemy1_2->spawn({Vector2(100, -15), 15});
        SpawnedEnemies::spawnEnemy(std::move(newBigEnemy1_2));

        for (int i = 0; i < 5; i++)
        {
            std::vector<Enemy1State> enemy1_2StateVector1 = {{.speed = 0, .duration = static_cast<uint>(1 + i * 120)}, {.desiredPos = {60, 30}, .speed = 70, .fireRate = 25, .slowAtDesiredPos = false}, {.desiredPos = {-10, 60}, .speed = 70, .fireRate = 25, .despawn = true, .slowAtDesiredPos = false},};
            auto newEnemy1_2 = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1_2StateVector1);
            newEnemy1_2->spawn({.pos = {60, -20}});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy1_2));

            std::vector<Enemy1State> enemy1_2StateVector1Mirrored = {{.speed = 0, .duration = static_cast<uint>(61 + i * 120)}, {.desiredPos = {60, 30}, .speed = 70, .fireRate = 25, .slowAtDesiredPos = false}, {.desiredPos = {130, 60}, .speed = 70, .fireRate = 25, .despawn = true, .slowAtDesiredPos = false},};
            auto newEnemy1_2Mirrored = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1_2StateVector1Mirrored);
            newEnemy1_2Mirrored->spawn({.pos = {60, -20}});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy1_2Mirrored));
        }
    };

    void doPreStep() override
    {
        if (BackgroundHandler::GetBackgroundPosition().y <= -890)
        {
            GameHandler::NextPhase();
        }
    };
    void enemyKilled(u_int _id) override {};
    void enemyDespawned(u_int _id) override {};
};
#endif //RAYLIB_STG_STAGE2PHASE3_H