//
// Created by n on 12/07/2026.
//

#ifndef RAYLIB_STG_DIAGONALTANKPHASE1_H
#define RAYLIB_STG_DIAGONALTANKPHASE1_H
#include "BigEnemy1.h"
#include "DiagonalTank.h"
#include "Enemy1.h"
#include "GameHandler.h"
#include "PhaseHelper.h"
#include "SpawnedEnemies.h"

class DiagonalTankPhase1 : public PhaseHelper
{
private:
    std::shared_ptr<PoolingVector<SimpleBullet2>> diagonalTankBulletPool;
    std::shared_ptr<PoolingVector<SimpleBullet2>> enemy1BulletPool;
    std::shared_ptr<PoolingVector<SimpleBullet3>> bigEnemy1Bullet1Pool;
    std::shared_ptr<PoolingVector<SimpleBullet1>> bigEnemy1Bullet2Pool;
    bool switchEarly = false;
public:
    DiagonalTankPhase1() : PhaseHelper({}, {0, -0.2f}, DIAGONAL_TANK_BACKGROUND)
    {
        phaseName = "Diagonal Tanks";
        diagonalTankBulletPool = std::make_shared<PoolingVector<SimpleBullet2>>(55);
        enemy1BulletPool = std::make_shared<PoolingVector<SimpleBullet2>>(30);
        bigEnemy1Bullet1Pool = std::make_shared<PoolingVector<SimpleBullet3>>(100);
        bigEnemy1Bullet2Pool = std::make_shared<PoolingVector<SimpleBullet1>>(100);
        BackgroundHandler::SetBackgroundSprite(DIAGONAL_TANK_BACKGROUND);
        BackgroundHandler::SetBackgroundPosition({0, 0});
        BackgroundHandler::SetScrollVector(defaultScrollVector);
        GlobalPools::AddPools({diagonalTankBulletPool, enemy1BulletPool, bigEnemy1Bullet1Pool, bigEnemy1Bullet2Pool});

    }

    void InitPhase() override
    {
        std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {100, 20}, .speed = 100,}, {.desiredPos = {50, 20}, .speed = 100, .fireRate = 30}, {.desiredPos = {190, 20}, .speed = 100, .fireRate = 30, .despawn = true},};
        std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
        newEnemy->spawn({Vector2(125, -5), 1});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy));
        for (int rowNumber = 0; rowNumber < 3; rowNumber++)
        {
            for (int i = 0; i < 6; i++)
            {
                std::unique_ptr<DiagonalTank> newTank = std::make_unique<DiagonalTank>(diagonalTankBulletPool, 400 + i * 10 + rowNumber * 24);
                newTank->spawn(EnemySpawnParametres { Vector2(i * 17 - 31, i * -17 + rowNumber * -21 + 17)});
                SpawnedEnemies::spawnEnemy(std::move(newTank));
            }
        }
    }
    bool doPhysics() override
    {
        if (stepsElapsed == 500)
        {
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {100, 40}, .speed = 100,}, {.desiredPos = {-10, 30}, .speed = 100, .fireRate = 30, .despawn = true},};
            std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
            newEnemy->spawn({Vector2(-5, -5), 2});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy));
        }
        else if (stepsElapsed == 600)
        {
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {95, 25}, .speed = 100,}, {.desiredPos = {-10, 30}, .speed = 100, .fireRate = 30, .despawn = true},};
            std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
            newEnemy->spawn({Vector2(-5, 0), 3});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            std::vector<Enemy1State> enemy1StateVector_2 = {{.desiredPos = {105, 55}, .speed = 100,}, {.desiredPos = {-10, 50}, .speed = 100, .fireRate = 30, .despawn = true},};
            std::unique_ptr<Enemy1> newEnemy2 = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector_2);
            newEnemy2->spawn({Vector2(-5, 10), 4});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy2));
        }

        else if (stepsElapsed == 840)
        {
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {60, 20}, .speed = 30,}, {.desiredPos = {50, 20}, .speed = 0, .duration = 600, .fireRate = 8, .despawn = false}, {.desiredPos = {60, -15}, .speed = 30, .fireRate = 8, .despawn = true},};
            std::unique_ptr<BigEnemy1> newEnemy = std::make_unique<BigEnemy1>(bigEnemy1Bullet1Pool, bigEnemy1Bullet2Pool, enemy1StateVector);
            newEnemy->spawn({Vector2(60, -15), 5});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy));
        }

        else if (stepsElapsed >= 1200 && switchEarly)
        {
            GameHandler::SwitchPhase(PHASE_2);
        }

        else if (stepsElapsed == 1460)
            GameHandler::SwitchPhase(PHASE_2);
        return PhaseHelper::doPhysics();
    };

    void enemyKilled(const u_int _id) override
    {
        switch (_id)
        {
            case 1:
            if (stepsElapsed < 300)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {100, 20}, .speed = 100,}, {.desiredPos = {50, 20}, .speed = 100, .fireRate = 30}, {.desiredPos = {190, 20}, .speed = 100, .fireRate = 30, .despawn = true},};
                std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                newEnemy->spawn({Vector2(135, -5)});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
            break;
            case 2:
            if (stepsElapsed < 640)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {95, 25}, .speed = 100,}, {.desiredPos = {-10, 30}, .speed = 100, .fireRate = 30, .despawn = true},};
                std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                newEnemy->spawn({Vector2(-15, 0)});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
            break;
            case 3:
            if (stepsElapsed < 840)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {95, 25}, .speed = 100,}, {.desiredPos = {-10, 30}, .speed = 100, .fireRate = 30, .despawn = true},};
                std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector);
                newEnemy->spawn({Vector2(-15, 0)});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
            break;
            case 4:
            if (stepsElapsed < 780)
            {
                std::vector<Enemy1State> enemy1StateVector_2 = {{.desiredPos = {105, 55}, .speed = 100,}, {.desiredPos = {-10, 50}, .speed = 100, .fireRate = 30, .despawn = true},};
                std::unique_ptr<Enemy1> newEnemy2 = std::make_unique<Enemy1>(enemy1BulletPool, enemy1StateVector_2);
                newEnemy2->spawn({Vector2(-15, 10)});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy2));
            }
            break;
            case 5:
            if (stepsElapsed < 1200)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {60, 20}, .speed = 70,}, {.desiredPos = {50, 20}, .speed = 0, .duration = 600, .fireRate = 8, .despawn = false}, {.desiredPos = {60, -15}, .speed = 30, .fireRate = 8, .despawn = true},};
                std::unique_ptr<BigEnemy1> newEnemy = std::make_unique<BigEnemy1>(bigEnemy1Bullet1Pool, bigEnemy1Bullet2Pool, enemy1StateVector);
                newEnemy->spawn({Vector2(60, -15),  6});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
        default:
            break;
        }
    }
    void enemyDespawned(const u_int _id) override
    {
        switch (_id)
        {
        case 5:
            if (stepsElapsed >= 1200)
            {
                GameHandler::SwitchPhase(PHASE_2);
            }
            break;
        case 6:
            switchEarly = true;
            break;
        default:
            break;
        }
    }
};
#endif //RAYLIB_STG_DIAGONALTANKPHASE1_H