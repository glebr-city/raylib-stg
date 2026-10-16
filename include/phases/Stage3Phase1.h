//
// Created by n on 10/10/2026.
//

#ifndef RAYLIB_STG_STAGE3PHASE1_H
#define RAYLIB_STG_STAGE3PHASE1_H
#include "Enemy1_3.h"
#include "Enemy2.h"
#include "Enemy2_2.h"
#include "PhaseHelper.h"

class Stage3Phase1 : public PhaseHelper
{
    protected:
    std::shared_ptr<PoolingVector<Enemy2Bullet1>> enemy2Bullet1Pool;
    std::shared_ptr<PoolingVector<SimpleBullet1VariableSpeed>> enemy2_2Bullet1Pool;
    std::shared_ptr<PoolingVector<SimpleBullet2Fast>> enemy1_3Bullet1Pool;
    public:
    Stage3Phase1() : PhaseHelper("Stage3Phase1", {}, {0, -0.2f}, STAGE_3_BACKGROUND)
    {
        BackgroundHandler::SetBackgroundSprite(defaultBackgroundSprite);
        BackgroundHandler::SetBackgroundPosition({0, 0});
        BackgroundHandler::SetScrollVector(defaultScrollVector);
        enemy2Bullet1Pool = std::make_shared<PoolingVector<Enemy2Bullet1>>(500);
        enemy2_2Bullet1Pool = std::make_shared<PoolingVector<SimpleBullet1VariableSpeed>>(200);
        enemy1_3Bullet1Pool = std::make_shared<PoolingVector<SimpleBullet2Fast>>(200);
        GlobalPools::AddPools({enemy2Bullet1Pool, enemy2_2Bullet1Pool, enemy1_3Bullet1Pool});
    }
    void InitPhase() override
    {
        PlayerHandler::GetPlayer()->reset();
        for (int n = 0; n <= 1; n++)
        {
            for (int j = 0; j <= 1; j++)
            {
                u_int spawnDelay = 610 * j + 1 + 1000 * n;
                for (int i = 0; i < 3; i++)
                {
                    const std::vector<Enemy2State> newEnemy2StateVector{
                        {.duration = static_cast<u_int>(1 + i * 53)}, {.duration = spawnDelay},
                        {.desiredPos = Vector2{-10, static_cast<float>(9 + i * 6)}, .speed = 70, .shotCount = 7, .despawn = true}
                    };
                    Enemy2 newEnemy2{enemy2Bullet1Pool, newEnemy2StateVector};
                    newEnemy2.spawn({.pos = {static_cast<float>(135), static_cast<float>(i * 5)}});
                    SpawnedEnemies::spawnEnemy(std::make_shared<Enemy2>(std::move(newEnemy2)));
                }

                for (int i = 0; i < 3; i++)
                {
                    const std::vector<Enemy2State> newEnemy2StateVector{
                        {.duration = static_cast<u_int>(200 + i * 53)}, {.duration = spawnDelay},
                        {.desiredPos = {static_cast<float>(130 + i), static_cast<float>(24 - i * 12)}, .speed = 70, .shotCount = 7, .lockAngle = false, .despawn = true}
                    };
                    Enemy2 newEnemy2{enemy2Bullet1Pool, newEnemy2StateVector};
                    newEnemy2.spawn({.pos = {static_cast<float>(-15), static_cast<float>(i * 5)}});
                    SpawnedEnemies::spawnEnemy(std::make_shared<Enemy2>(std::move(newEnemy2)));
                }
            }
        }

        u_int spawnDelay = 1800;
        for (int i = 0; i < 4; i++)
        {
            const std::vector<Enemy2State> newEnemy2StateVector{
                            {.duration = static_cast<u_int>(1 + i * 35)}, {.duration = spawnDelay},
                            {.desiredPos = Vector2{-10, static_cast<float>(9 + i * 6)}, .speed = 70, .shotCount = 4, .lockAngle = false, .despawn = true}
            };
            Enemy2 newEnemy2{enemy2Bullet1Pool, newEnemy2StateVector};
            newEnemy2.spawn({.pos = {static_cast<float>(135), static_cast<float>(i * 5)}});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy2>(std::move(newEnemy2)));
        }

        for (int i = 0; i < 4; i++)
        {
            const std::vector<Enemy2State> newEnemy2StateVector{
                            {.duration = static_cast<u_int>(100 + i * 35)}, {.duration = spawnDelay},
                            {.desiredPos = {static_cast<float>(130 + i), static_cast<float>(24 - i * 12)}, .speed = 70, .shotCount = 4, .lockAngle = true, .despawn = true}
            };
            Enemy2 newEnemy2{enemy2Bullet1Pool, newEnemy2StateVector};
            newEnemy2.spawn({.pos = {static_cast<float>(-15), static_cast<float>(i * 5)}});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy2>(std::move(newEnemy2)));
        }

        const std::vector<Enemy2State> newEnemy2_2StateVector{{.speed=0, .duration=380}, {.desiredPos = Vector2{20, 9}, .speed=90, .slowAtDesiredPos=false}, {.desiredPos={21, 200}, .speed=10, .duration=300, .shotCount=5, .burstWaitTime=60}, {.desiredPos = Vector2{0, -20}, .speed=90}, {.duration=1, .despawn=true}};
        Enemy2_2 newEnemy2_2{enemy2_2Bullet1Pool, newEnemy2_2StateVector};
        newEnemy2_2.spawn({.pos={-15, 0}});
        SpawnedEnemies::spawnEnemy(std::make_shared<Enemy2_2>(std::move(newEnemy2_2)));

        const std::vector<Enemy2State> newEnemy2_2StateVector_2{{.speed=0, .duration=500}, {.desiredPos = Vector2{100, 9}, .speed=90, .slowAtDesiredPos=false}, {.desiredPos={}, .speed=0, .duration=300, .shotCount=5, .burstWaitTime=60}, {.desiredPos = Vector2{120, -20}, .speed=90}, {.duration=1, .despawn=true}};
        Enemy2_2 newEnemy2_2_2{enemy2_2Bullet1Pool, newEnemy2_2StateVector_2};
        newEnemy2_2_2.spawn({.pos={135, 0}});
        SpawnedEnemies::spawnEnemy(std::make_shared<Enemy2_2>(std::move(newEnemy2_2_2)));

        for (int k = 0; k <= 2; k++)
        {
            const std::vector<Enemy2State> newEnemy2_2StateVector_3{{.speed=0, .duration=static_cast<u_int>(1000 + k * 100)}, {.desiredPos = Vector2{60, 9}, .speed=40, .slowAtDesiredPos=false}, {.desiredPos={static_cast<float>(140 - k % 2 * 160), 30}, .speed=40, .shotCount=5, .burstWaitTime=60, .despawn=true}};
            Enemy2_2 newEnemy2_2_3{enemy2_2Bullet1Pool, newEnemy2_2StateVector_3};
            newEnemy2_2_3.spawn({.pos={60, -20}});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy2_2>(std::move(newEnemy2_2_3)));
        }

        int enemy1_3Count = 7;
        float enemy1_3Distance = 120.0f / enemy1_3Count;
        for (int m = 0; m < 3; m++)
        {
            for (int l = 0; l <= enemy1_3Count; l++)
            {
                const std::vector<Enemy1State> newEnemy1StateVector{{.duration=static_cast<u_int>(1360 + 80 * m)}, {.desiredPos={l * enemy1_3Distance + m * 10, 130}, .speed=40, .fireRate=static_cast<u_int>(30 + (5 * m)), .slowAtDesiredPos=false}, {.desiredPos={l * enemy1_3Distance + m * 5, 200}, .speed=120, .despawn=true}};
                Enemy1_3 newEnemy1_3{enemy1_3Bullet1Pool, newEnemy1StateVector};
                newEnemy1_3.spawn({.pos={l * enemy1_3Distance, -20}});
                SpawnedEnemies::spawnEnemy(std::make_shared<Enemy1_3>(std::move(newEnemy1_3)));
            };
        }
    };

    bool doPhysics() override
    {
        if (stepsElapsed > 2400)
        {
            GameHandler::NextPhase();
            return false;
        }
        return PhaseHelper::doPhysics();
    }
    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};
#endif //RAYLIB_STG_STAGE3PHASE1_H