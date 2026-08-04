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
public:
    DiagonalTankPhase1() : PhaseHelper(std::vector<std::shared_ptr<IPoolingVector>>())
    {
        phaseName = "Diagonal Tanks";
        background = DIAGONAL_TANK_BACKGROUND;
        diagonalTankBulletPool = std::make_shared<PoolingVector<SimpleBullet2>>(55, 30);
        enemy1BulletPool = std::make_shared<PoolingVector<SimpleBullet2>>(30, 30);
        bigEnemy1Bullet1Pool = std::make_shared<PoolingVector<SimpleBullet3>>(100, 30);
        bigEnemy1Bullet2Pool = std::make_shared<PoolingVector<SimpleBullet1>>(100, 30);
        defaultScrollVector = Vector2(0, 0.2f);
        currentScrollVector = defaultScrollVector;
        phasePools.push_back(diagonalTankBulletPool);
        phasePools.push_back(enemy1BulletPool);
        phasePools.push_back(bigEnemy1Bullet1Pool);
        phasePools.push_back(bigEnemy1Bullet2Pool);
        currentBackgroundPosition = {0, 0};
    }
    bool doPhysics(Player* _player) override
    {
        if (stepsElapsed == 0)
        {
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {100, 20}, .speed = 100,}, {.desiredPos = {50, 20}, .speed = 100, .fireRate = 30}, {.desiredPos = {190, 20}, .speed = 100, .fireRate = 30, .despawn = true},};
            std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool.get(), enemy1StateVector);
            newEnemy->spawn({Vector2(125, -5), 50, 1});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            for (int rowNumber = 0; rowNumber < 3; rowNumber++)
            {
                for (int i = 0; i < 8; i++)
                {
                    std::unique_ptr<DiagonalTank> newTank = std::make_unique<DiagonalTank>(diagonalTankBulletPool.get(), 360 + i * 8 + rowNumber * 24);
                    newTank->spawn(EnemySpawnParametres { Vector2(i * 17 - 31, i * -17 + rowNumber * -21 + 17)});
                    SpawnedEnemies::spawnEnemy(std::move(newTank));
                }
            }
        }

        else if (stepsElapsed == 500)
        {
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {100, 40}, .speed = 100,}, {.desiredPos = {-10, 30}, .speed = 100, .fireRate = 30, .despawn = true},};
            std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool.get(), enemy1StateVector);
            newEnemy->spawn({Vector2(-5, -5), 50, 2});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy));
        }
        else if (stepsElapsed == 600)
        {
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {95, 25}, .speed = 100,}, {.desiredPos = {-10, 30}, .speed = 100, .fireRate = 30, .despawn = true},};
            std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool.get(), enemy1StateVector);
            newEnemy->spawn({Vector2(-5, 0), 50, 3});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            std::vector<Enemy1State> enemy1StateVector_2 = {{.desiredPos = {105, 55}, .speed = 100,}, {.desiredPos = {-10, 50}, .speed = 100, .fireRate = 30, .despawn = true},};
            std::unique_ptr<Enemy1> newEnemy2 = std::make_unique<Enemy1>(enemy1BulletPool.get(), enemy1StateVector_2);
            newEnemy2->spawn({Vector2(-5, 10), 50, 4});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy2));
        }

        else if (stepsElapsed == 840)
        {
            std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {60, 20}, .speed = 30,}, {.desiredPos = {50, 20}, .speed = 0, .duration = 600, .fireRate = 8, .despawn = false}, {.desiredPos = {60, -15}, .speed = 30, .fireRate = 8, .despawn = true},};
            std::unique_ptr<BigEnemy1> newEnemy = std::make_unique<BigEnemy1>(bigEnemy1Bullet1Pool.get(), bigEnemy1Bullet2Pool.get(), enemy1StateVector);
            newEnemy->spawn({Vector2(60, -15), 300, 5});
            SpawnedEnemies::spawnEnemy(std::move(newEnemy));
        }
        stepsElapsed++;
        return PhaseHelper::doPhysics(_player);
    };

    void enemyKilled(const u_int _id) override
    {
        switch (_id)
        {
            case 1:
            if (stepsElapsed < 240)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {100, 20}, .speed = 100,}, {.desiredPos = {50, 20}, .speed = 100, .fireRate = 30}, {.desiredPos = {190, 20}, .speed = 100, .fireRate = 30, .despawn = true},};
                std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool.get(), enemy1StateVector);
                newEnemy->spawn({Vector2(135, -5), 50});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
            break;
            case 2:
            if (stepsElapsed < 640)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {95, 25}, .speed = 100,}, {.desiredPos = {-10, 30}, .speed = 100, .fireRate = 30, .despawn = true},};
                std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool.get(), enemy1StateVector);
                newEnemy->spawn({Vector2(-15, 0), 50});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
            break;
            case 3:
            if (stepsElapsed < 840)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {95, 25}, .speed = 100,}, {.desiredPos = {-10, 30}, .speed = 100, .fireRate = 30, .despawn = true},};
                std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool.get(), enemy1StateVector);
                newEnemy->spawn({Vector2(-15, 0), 50});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
            break;
            case 4:
            if (stepsElapsed < 780)
            {
                std::vector<Enemy1State> enemy1StateVector_2 = {{.desiredPos = {105, 55}, .speed = 100,}, {.desiredPos = {-10, 50}, .speed = 100, .fireRate = 30, .despawn = true},};
                std::unique_ptr<Enemy1> newEnemy2 = std::make_unique<Enemy1>(enemy1BulletPool.get(), enemy1StateVector_2);
                newEnemy2->spawn({Vector2(-15, 10), 50});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy2));
            }
            break;
            case 5:
            if (stepsElapsed < 1200)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {60, 20}, .speed = 70,}, {.desiredPos = {50, 20}, .speed = 0, .duration = 600, .fireRate = 8, .despawn = false}, {.desiredPos = {60, -15}, .speed = 30, .fireRate = 8, .despawn = true},};
                std::unique_ptr<BigEnemy1> newEnemy = std::make_unique<BigEnemy1>(bigEnemy1Bullet1Pool.get(), bigEnemy1Bullet2Pool.get(), enemy1StateVector);
                newEnemy->spawn({Vector2(60, -15), 300, });
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
            }
        default:
            break;
        }
    }
    void enemyDespawned(u_int _id) override
    {
        switch (_id)
        {
        case 5:
            if (stepsElapsed > 1200)
            {
                std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {95, 25}, .speed = 100,}, {.desiredPos = {-10, 30}, .speed = 100, .fireRate = 30, .despawn = true},};
                std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1>(enemy1BulletPool.get(), enemy1StateVector);
                newEnemy->spawn({Vector2(-15, 0), 50});
                SpawnedEnemies::spawnEnemy(std::move(newEnemy));
                GameHandler::SwitchPhase(TEST_PHASE_1);
            }
            break;
        default: break;
        }
    }
};
#endif //RAYLIB_STG_DIAGONALTANKPHASE1_H