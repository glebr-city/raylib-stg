//
// Created by n on 09/09/2026.
//

#ifndef RAYLIB_STG_STAGE2PHASE2_H
#define RAYLIB_STG_STAGE2PHASE2_H
#include "PhaseHelper.h"

class Stage2Phase2 : public PhaseHelper
{
private:
    std::shared_ptr<PoolingVector<SimpleBullet1Fast>> streetlightBulletPool;
    std::shared_ptr<PoolingVector<Enemy1_2Bullet1>> enemy1_2BulletPool;
    std::shared_ptr<PoolingVector<Enemy1_2Bullet2>> enemy1_2BulletPool2;
    std::shared_ptr<PoolingVector<AcceleratingBullet1>> bigEnemy2Bullet2Pool;
    std::shared_ptr<PoolingVector<SimpleBullet2>> enemy1BulletPool;
    public:
    Stage2Phase2() : PhaseHelper("Stage2Phase2", {0, -280}, {0, -0.2f}, STAGE_2_BACKGROUND)
    {
        streetlightBulletPool = std::make_shared<PoolingVector<SimpleBullet1Fast>>(60);
        enemy1_2BulletPool = std::make_shared<PoolingVector<Enemy1_2Bullet1>>(90);
        enemy1_2BulletPool2 = std::make_shared<PoolingVector<Enemy1_2Bullet2>>(90);
        BackgroundHandler::SetBackgroundSprite(defaultBackgroundSprite);
        BackgroundHandler::SetScrollVector(defaultScrollVector);
        bigEnemy2Bullet2Pool = std::make_shared<PoolingVector<AcceleratingBullet1>>(300);
        enemy1BulletPool = std::make_shared<PoolingVector<SimpleBullet2>>(90);
        GlobalPools::AddPools({streetlightBulletPool, enemy1_2BulletPool, enemy1_2BulletPool2, bigEnemy2Bullet2Pool, enemy1BulletPool});
    }
    void InitPhase() override
    {
        auto newStreetlightEnemy = std::make_unique<StreetlightEnemy>(streetlightBulletPool);
        newStreetlightEnemy->spawn( {BackgroundHandler::GetRelativePos({30, -500})});
        SpawnedEnemies::spawnEnemy(std::move(newStreetlightEnemy));
        auto newStreetlightEnemy2 = std::make_unique<StreetlightEnemy>(streetlightBulletPool);
        newStreetlightEnemy2->spawn( {BackgroundHandler::GetRelativePos({90, -550})});
        SpawnedEnemies::spawnEnemy(std::move(newStreetlightEnemy2));

        auto newStreetlightEnemy3 = std::make_unique<StreetlightEnemy>(streetlightBulletPool);
        newStreetlightEnemy3->spawn( {BackgroundHandler::GetRelativePos({30, -650})});
        SpawnedEnemies::spawnEnemy(std::move(newStreetlightEnemy3));
        auto newStreetlightEnemy4 = std::make_unique<StreetlightEnemy>(streetlightBulletPool);
        newStreetlightEnemy4->spawn( {BackgroundHandler::GetRelativePos({90, -700})});
        SpawnedEnemies::spawnEnemy(std::move(newStreetlightEnemy4));

        std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {10, 20}, .speed = 100, .slowAtDesiredPos = false}, {.desiredPos = {50, 40}, .speed = 75, .fireRate = 25, .slowAtDesiredPos = false}, {.desiredPos = {100, 130}, .speed = 100, .fireRate = 25, .slowAtDesiredPos = false}, {.desiredPos = {130, 190}, .speed = 100, .despawn = true},};
        auto newEnemy = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector);
        newEnemy->spawn({Vector2(-20, -5)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy));
        auto newEnemy2 = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector);
        newEnemy2->spawn({Vector2(-120, -30)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy2));
        auto newEnemy3 = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector);
        newEnemy3->spawn({Vector2(-220, -55)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy3));

        std::vector<Enemy1State> enemy1StateVector2 = {{.desiredPos = {110, 20}, .speed = 100, .slowAtDesiredPos = false}, {.desiredPos = {70, 40}, .speed = 75, .fireRate = 25, .slowAtDesiredPos = false}, {.desiredPos = {20, 130}, .speed = 100, .fireRate = 25, .slowAtDesiredPos = false}, {.desiredPos = {-10, 190}, .speed = 100, .despawn = true},};
        auto newEnemy4 = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector2);
        newEnemy4->spawn({Vector2(450, -5)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy4));
        auto newEnemy5 = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector2);
        newEnemy5->spawn({Vector2(550, -30)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy5));
        auto newEnemy6 = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector2);
        newEnemy6->spawn({Vector2(650, -55)});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy6));

        std::vector<Enemy1State> bigEnemy2StateVector = {{.speed = 0, .duration = 760}, {.desiredPos = {60, 20}, .speed = 90,}, {.desiredPos = {60, -20}, .speed = 8, .duration = 600, .fireRate = 2, .despawn = true}};
        auto bigEnemy2 = std::make_unique<BigEnemy2>(bigEnemy2Bullet2Pool, bigEnemy2StateVector);
        bigEnemy2->spawn({Vector2(60, -30), 10});
        SpawnedEnemies::spawnEnemy(std::move(bigEnemy2));

        for (int i = 0; i < 5; i++)
        {
            auto enemy1StateVector3 = std::vector{Enemy1State{.speed = 0, .duration = static_cast<uint>(920 + i * 120)}, {.desiredPos = {130, static_cast<float>(80 + i * 20)}, .speed = 60, .fireRate = 30, .despawn = true}};
            auto newEnemy1 = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector3);
            newEnemy1->spawn(Vector2(-10, static_cast<float>(i * 20)));
            SpawnedEnemies::spawnEnemy(std::move(newEnemy1));
            auto enemy1StateVector3Mirrored = std::vector{Enemy1State{.speed = 0, .duration = static_cast<uint>(920 + i * 120)}, {.desiredPos = {-10, static_cast<float>(80 + i * 20)}, .speed = 60, .fireRate = 30, .despawn = true}};
            auto newEnemy1Mirrored = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector3Mirrored);
            newEnemy1Mirrored->spawn(Vector2(130, static_cast<float>(i * 20)));
            SpawnedEnemies::spawnEnemy(std::move(newEnemy1Mirrored));
        }
    };

    void doPreStep() override
    {
        PhaseHelper::doPreStep();
        if (stepsElapsed == 1400)
        {
            spawnEnemy1_2Wave1();
        }
        else if (BackgroundHandler::GetBackgroundPosition().y <= -650)
        {
            GameHandler::NextPhase();
        }
    }
    void enemyKilled(u_int _id) override
    {}
    void enemyDespawned(u_int _id) override {};
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
};
#endif //RAYLIB_STG_STAGE2PHASE2_H