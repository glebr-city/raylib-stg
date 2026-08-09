//
// Created by n on 05/08/2026.
//

#ifndef RAYLIB_STG_PHASE2_H
#define RAYLIB_STG_PHASE2_H
#include "Enemy1.h"
#include "PhaseHelper.h"
#include "SimpleBullet2.h"
#include "SpawnedEnemies.h"
#include "StreetlightEnemy.h"

class Phase2 : public PhaseHelper
{
private:
    std::shared_ptr<PoolingVector<SimpleBullet2>> enemy1BulletPool;
    std::shared_ptr<PoolingVector<SimpleBullet1Fast>> streetlightBulletPool;
    std::shared_ptr<PoolingVector<SimpleBullet3>> bigEnemy1Bullet1Pool;
    std::shared_ptr<PoolingVector<SimpleBullet1>> bigEnemy1Bullet2Pool;
    bool bigEnemySpawned = false;
    bool extraBigEnemyAlive = false;
public:
    Phase2() : PhaseHelper({0, -240}, {0, -0.2f}, DIAGONAL_TANK_BACKGROUND)
    {
        phaseName = "Phase2";
        enemy1BulletPool = std::make_shared<PoolingVector<SimpleBullet2>>(30, 30);
        streetlightBulletPool = std::make_shared<PoolingVector<SimpleBullet1Fast>>(60, 30);
        bigEnemy1Bullet1Pool = std::make_shared<PoolingVector<SimpleBullet3>>(100, 30);
        bigEnemy1Bullet2Pool = std::make_shared<PoolingVector<SimpleBullet1>>(100, 30);
        GlobalPools::AddPools({enemy1BulletPool, streetlightBulletPool, bigEnemy1Bullet1Pool, bigEnemy1Bullet2Pool});
        BackgroundHandler::SetBackgroundSprite(DIAGONAL_TANK_BACKGROUND);
        BackgroundHandler::SetScrollVector(defaultScrollVector);

    }

    void InitPhase() override
    {
        std::unique_ptr<StreetlightEnemy> newStreetlightEnemy = std::make_unique<StreetlightEnemy>(streetlightBulletPool);
        newStreetlightEnemy->spawn( {BackgroundHandler::GetRelativePos({10, -500}), 11});
        SpawnedEnemies::spawnEnemy(std::move(newStreetlightEnemy));

        std::unique_ptr<StreetlightEnemy> newStreetlightEnemy2 = std::make_unique<StreetlightEnemy>(streetlightBulletPool);
        newStreetlightEnemy2->spawn( {BackgroundHandler::GetRelativePos({110, -510}), 10});
        SpawnedEnemies::spawnEnemy(std::move(newStreetlightEnemy2));
    }

    bool doPhysics() override
    {
        if (stepsElapsed < 360 && stepsElapsed % 90 == 0)
        {
            for (int i = 0; i < 2; i++)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {5, static_cast<float>(35 + i * 10)}, .speed = 30}, {.desiredPos = {125, static_cast<float>(35 + i * 10)}, .speed = 120, .fireRate = 45, .despawn=true}};
                std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                newEnemy->spawn({Vector2(-5 - i * 5, 15 + i * 10)});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
        } else if (stepsElapsed == 500)
        {
            for (int j = 0; j < 5; j++)
            {
                for (int i = -1; i <= 1; i += 2)
                {
                    std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {static_cast<float>(60 + 10 * i), 15}, .speed = 30}, {.desiredPos = {60 + static_cast<float>(65 * i), 15}, .speed = 120, .fireRate = 45, .despawn=true}};
                    std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                    newEnemy->spawn({Vector2(60 + 5 * i, -6 - 30 * j)});
                    SpawnedEnemies::spawnEnemy(std::move(newEnemy));
                }
            }
        }
        if (BackgroundHandler::GetBackgroundPosition().y < -470 && BackgroundHandler::GetBackgroundPosition().y > -500 && !extraBigEnemyAlive && SpawnedEnemies::getSpawnedEnemies()->empty())
        {
            extraBigEnemyAlive = true;
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {60, 20}, .speed = 60,}, {.desiredPos = {50, 20}, .speed = 0, .duration = 200, .fireRate = 8, .despawn = false}, {.desiredPos = {60, -15}, .speed = 60, .fireRate = 8, .despawn = true},};
            std::unique_ptr<BigEnemy1> newEnemy = std::make_unique<BigEnemy1>(bigEnemy1Bullet1Pool, bigEnemy1Bullet2Pool, enemy1StateVector);
            newEnemy->spawn({Vector2(60, -15), 16});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy));
        }
        if (BackgroundHandler::GetBackgroundPosition().y < -550 && !bigEnemySpawned)
        {
            auto boss1SmallBulletPool = std::make_shared<PoolingVector<Boss1SmallBullet>>(100);
            auto simpleBullet1Pool = std::make_shared<PoolingVector<SimpleBullet1>>(100);
            const auto boss1 = std::make_shared<Boss1>(boss1SmallBulletPool, simpleBullet1Pool);
            GlobalPools::AddPools({boss1SmallBulletPool, simpleBullet1Pool});
            boss1->spawn({.pos=BackgroundHandler::GetRelativePos(Vector2(60, -921.5)), .id = 201});
            SpawnedEnemies::spawnEnemy(boss1);

            bigEnemySpawned = true;
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {60, 20}, .speed = 30,}, {.desiredPos = {50, 20}, .speed = 0, .duration = 600, .fireRate = 8, .despawn = false}, {.desiredPos = {60, -15}, .speed = 30, .fireRate = 8, .despawn = true},};
            std::unique_ptr<BigEnemy1> newEnemy = std::make_unique<BigEnemy1>(bigEnemy1Bullet1Pool, bigEnemy1Bullet2Pool, enemy1StateVector);
            newEnemy->spawn({Vector2(60, -15), 15});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy));

            std::unique_ptr<StreetlightEnemy> newStreetlightEnemy = std::make_unique<StreetlightEnemy>(streetlightBulletPool);
            newStreetlightEnemy->spawn( {BackgroundHandler::GetRelativePos({30, -765})});
            SpawnedEnemies::spawnEnemy(std::move(newStreetlightEnemy));

            std::unique_ptr<StreetlightEnemy> newStreetlightEnemy2 = std::make_unique<StreetlightEnemy>(streetlightBulletPool);
            newStreetlightEnemy2->spawn( {BackgroundHandler::GetRelativePos({90, -765})});
            SpawnedEnemies::spawnEnemy(std::move(newStreetlightEnemy2));
        }
        else if (BackgroundHandler::GetBackgroundPosition().y <= -770)
        {
            GameHandler::NextPhase();
            return false;
        }
        return PhaseHelper::doPhysics();
    }

    void enemyKilled(u_int _id) override
    {
        switch (_id)
        {
        case 10:
            for (int i = 0; i < 2; i++)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {5, static_cast<float>(35 + i * 10)}, .speed = 30}, {.desiredPos = {125, static_cast<float>(35 + i * 10)}, .speed = 120, .fireRate = 45, .despawn=true}};
                std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                newEnemy->spawn({Vector2(-5 - i * 20, 15 + i * 10)});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
            break;
        case 11:
            for (int i = 0; i < 2; i++)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {115, static_cast<float>(35 + i * 10)}, .speed = 30}, {.desiredPos = {-5, static_cast<float>(35 + i * 10)}, .speed = 120, .fireRate = 45, .despawn=true}};
                std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                newEnemy->spawn({Vector2(125 + i * 20, 15 + i * 10)});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
            break;
        case 15:
            {
                for (int i = 0; i < 1; i++)
                {
                    std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {115, 15}, .speed = 30}, {.desiredPos = {-5, 15}, .speed = 120, .fireRate = 60, .despawn=true}};
                    std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                    newEnemy->spawn({Vector2(125 + i * 20, 15 + i * 10)});
                    SpawnedEnemies::spawnEnemy(std::move(newEnemy));
                }
                for (int i = 0; i < 1; i++)
                {
                    std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {5, 15}, .speed = 30}, {.desiredPos = {125, 15}, .speed = 120, .fireRate = 60, .despawn=true}};
                    std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                    newEnemy->spawn({Vector2(-5 - i * 20, 15 + i * 10)});
                    SpawnedEnemies::spawnEnemy(std::move(newEnemy));
                }
            }
        case 16:
            extraBigEnemyAlive = false;
        default:
            break;
        }
    };
    void enemyDespawned(const u_int _id) override {};
};
#endif //RAYLIB_STG_PHASE2_H