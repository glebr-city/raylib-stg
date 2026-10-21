//
// Created by g on 20/10/2026.
//

#ifndef RAYLIB_STG_STAGE3PHASE3_H
#define RAYLIB_STG_STAGE3PHASE3_H
#include "PhaseHelper.h"

class Stage3Phase3 : public PhaseHelper {
    std::shared_ptr<PoolingVector<Enemy2Bullet1>> enemy2Bullet1Pool;
    std::shared_ptr<PoolingVector<HomingBullet>> homingBulletPool;
    std::shared_ptr<PoolingVector<Enemy1_2Bullet1>> enemy1_2BulletPool;
    std::shared_ptr<PoolingVector<Enemy1_2Bullet2>> enemy1_2BulletPool2;
    std::shared_ptr<PoolingVector<AcceleratingBullet1>> bigEnemy2Bullet2Pool;
    int enemy1_4ToKillForBonusWaveLeft = 2;
    int enemy1_4ToKillForBonusWaveRight = 2;
    static constexpr u_int wave2Delay = 300;
    public:
    Stage3Phase3() : PhaseHelper("Stage3Phase3", {}, {0, -0.2f}, STAGE_3_BACKGROUND) {
        enemy2Bullet1Pool = std::make_shared<PoolingVector<Enemy2Bullet1>>(300);
        homingBulletPool = std::make_shared<PoolingVector<HomingBullet>>(50);
        enemy1_2BulletPool = std::make_shared<PoolingVector<Enemy1_2Bullet1>>(100);
        enemy1_2BulletPool2 = std::make_shared<PoolingVector<Enemy1_2Bullet2>>(100);
        bigEnemy2Bullet2Pool = std::make_shared<PoolingVector<AcceleratingBullet1>>(150);
        GlobalPools::AddPools({enemy2Bullet1Pool, homingBulletPool, enemy1_2BulletPool, enemy1_2BulletPool2, bigEnemy2Bullet2Pool});
    }

    void spawnEnemy1_4Wave1(const u_int spawnDelay, const int i, const bool right, const u_int _id = 0) {
        if (!right) {
            const std::vector newEnemy1_4StateVector{Enemy1State{.duration = static_cast<u_int>(1 + i * 53)}, {.duration = spawnDelay}, {.desiredPos=Vector2(20 + i * 5, 10 + i * 20), .speed = 60},
                             {.desiredPos = Vector2{-10, 195}, .speed = 120, .duration=120, .fireRate = 60, .slowAtDesiredPos=false},
                        {.desiredPos = Vector2{-10, 195}, .speed = 120, .despawn = true, .slowAtDesiredPos=false}
            };

            Enemy1_4 newEnemy1_4{homingBulletPool, newEnemy1_4StateVector};
            newEnemy1_4.spawn({.pos = Vector2(-15, 30 + i * 5), .id=_id});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy1_4>(std::move(newEnemy1_4)));
            return;
        } else {
            const std::vector newEnemy1_4StateVector{Enemy1State{.duration = static_cast<u_int>(1 + i * 53)}, {.duration = spawnDelay}, {.desiredPos=Vector2(100 - i * 5, 10 + i * 20), .speed = 60},
                        {.desiredPos = Vector2{130, 195}, .speed = 120, .duration=120, .fireRate = 60, .slowAtDesiredPos=false},
                        {.desiredPos = Vector2{130, 195}, .speed = 120, .despawn = true, .slowAtDesiredPos=false}
            };

            Enemy1_4 newEnemy1_4{homingBulletPool, newEnemy1_4StateVector};
            newEnemy1_4.spawn({.pos = Vector2(135, 90 - i * 5), .id= _id});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy1_4>(std::move(newEnemy1_4)));
            return;
        }
    }

    void spawnEnemy1_4Wave2(const u_int spawnDelay, const int i, const bool right, const u_int _id = 0) {
        if (!right) {
            const std::vector newEnemy1_4StateVector{Enemy1State{.duration = static_cast<u_int>(1 + i * 53)}, {.duration = spawnDelay}, {.desiredPos=Vector2(20 + i * 5, 10 + i * 20), .speed = 60},
                             {.desiredPos = Vector2{135, 5}, .speed = 120, .duration=120, .fireRate = 90, .slowAtDesiredPos=false},
                        {.desiredPos = Vector2{135, 5}, .speed = 120, .despawn = true, .slowAtDesiredPos=false}
            };

            Enemy1_4 newEnemy1_4{homingBulletPool, newEnemy1_4StateVector};
            newEnemy1_4.spawn({.pos = Vector2(-15, 30 + i * 5), .id=_id});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy1_4>(std::move(newEnemy1_4)));
            return;
        } else {
            const std::vector newEnemy1_4StateVector{Enemy1State{.duration = static_cast<u_int>(1 + i * 53)}, {.duration = spawnDelay}, {.desiredPos=Vector2(100 - i * 5, 10 + i * 20), .speed = 60},
                        {.desiredPos = Vector2{-15, 5}, .speed = 120, .duration=120, .fireRate = 90, .slowAtDesiredPos=false},
                        {.desiredPos = Vector2{-15, 5}, .speed = 120, .despawn = true, .slowAtDesiredPos=false}
            };

            Enemy1_4 newEnemy1_4{homingBulletPool, newEnemy1_4StateVector};
            newEnemy1_4.spawn({.pos = Vector2(135, 90 - i * 5), .id= _id});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy1_4>(std::move(newEnemy1_4)));
            return;
        }
    }
    void InitPhase() override {
            const u_int spawnDelay = 1;
            for (int i = 0; i < 2; i++)
            {
                const std::vector newEnemy1_2StateVector{Enemy1State{.duration = static_cast<u_int>(1 + i * 53)}, {.duration = spawnDelay},
                        {.desiredPos = Vector2{-10, static_cast<float>(9 + i * 6)}, .speed = 70, .fireRate = 15, .despawn = true}
                };
                Enemy1_2 newEnemy1_2{enemy1_2BulletPool, enemy1_2BulletPool2, newEnemy1_2StateVector};
                newEnemy1_2.spawn({.pos = {static_cast<float>(135), static_cast<float>(i * 5)}});
                SpawnedEnemies::spawnEnemy(std::make_shared<Enemy1_2>(std::move(newEnemy1_2)));
                spawnEnemy1_4Wave1(spawnDelay, i, false);
            }
            for (int i = 0; i < 2; i++)
            {
                const std::vector newEnemy1_2StateVector{Enemy1State{.duration = static_cast<u_int>(1 + i * 53)}, {.duration = spawnDelay},
                        {.desiredPos = Vector2{130, static_cast<float>(9 + i * 6)}, .speed = 70, .fireRate = 15, .despawn = true}
                };
                Enemy1_2 newEnemy1_2{enemy1_2BulletPool, enemy1_2BulletPool2, newEnemy1_2StateVector};
                newEnemy1_2.spawn({.pos = {static_cast<float>(-15), static_cast<float>(i * 5)}});
                SpawnedEnemies::spawnEnemy(std::make_shared<Enemy1_2>(std::move(newEnemy1_2)));
                spawnEnemy1_4Wave1(spawnDelay, i, true);
            }
        std::vector<Enemy1State> bigEnemy2StateVector = {{.duration = wave2Delay + 40}, {.desiredPos = {60, 20}, .speed = 90,}, {.desiredPos = {60, -20}, .speed = 8, .duration = 600, .fireRate = 3, .despawn = true}};
        auto bigEnemy2 = std::make_unique<BigEnemy2>(bigEnemy2Bullet2Pool, bigEnemy2StateVector);
        bigEnemy2->spawn({Vector2(60, -30), 10});
        SpawnedEnemies::spawnEnemy(std::move(bigEnemy2));
        for (int i =0; i < 2; i++) {
            spawnEnemy1_4Wave2(wave2Delay, i, false, 1);
            spawnEnemy1_4Wave2(wave2Delay, i, true, 2);
        }
    };
    void enemyKilled(const u_int _id) override {
        if (_id == 1 && stepsElapsed < 700 && --enemy1_4ToKillForBonusWaveLeft == 0) {
            for (int i =0; i < 2; i++) {
                spawnEnemy1_4Wave2(10, i, false);
            }
            return;
        }
        if (_id == 2 && stepsElapsed < 700 && --enemy1_4ToKillForBonusWaveRight == 0) {
            for (int i =0; i < 2; i++) {
                spawnEnemy1_4Wave2(10, i, true);
            }
            return;
        }


    };
    void enemyDespawned(const u_int _id) override{};
};
#endif //RAYLIB_STG_STAGE3PHASE3_H