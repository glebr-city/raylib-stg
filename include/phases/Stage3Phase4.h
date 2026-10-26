//
// Created by n on 22/10/2026.
//

#ifndef RAYLIB_STG_STAGE3PHASE4_H
#define RAYLIB_STG_STAGE3PHASE4_H
#include "PhaseHelper.h"

class Stage3Phase4 : public PhaseHelper
{
private:
    std::shared_ptr<PoolingVector<HomingBullet>> homingBulletPool;
    std::shared_ptr<PoolingVector<SimpleBullet1VariableSpeed>> enemy2_2Bullet1Pool;
    std::shared_ptr<PoolingVector<AcceleratingBullet1>> bigEnemy2Bullet2Pool;
    std::shared_ptr<PoolingVector<SimpleBullet2Fast>> enemy1_3Bullet1Pool;

    std::shared_ptr<PoolingVector<Enemy1_2Bullet1>> enemy1_2BulletPool;
    std::shared_ptr<PoolingVector<Enemy1_2Bullet2>> enemy1_2BulletPool2;
    static constexpr u_int cornerEnemy1_4RespawnTime = 400; //For what period do the enemies respawn when killed?
    static constexpr u_int wave2Delay = 300;

    void spawnCornerEnemy1_4(const bool right, const u_int id=0) {
        const auto spawnPos = Vector2(-15+150*right, 0);
        const std::vector cornerEnemy1_4StateVector{Enemy1State{.desiredPos=Vector2(8 + 104 * right, 12), .speed=60, .slowAtDesiredPos=false},
            {.speed=0, .duration=(cornerEnemy1_4RespawnTime-stepsElapsed), .fireRate=120}, {.desiredPos=spawnPos, .speed=60, .despawn=true, .slowAtDesiredPos=false},};
        Enemy1_4 newEnemy1_4{homingBulletPool, cornerEnemy1_4StateVector};
        newEnemy1_4.spawn({.pos=spawnPos, .id=id});
        SpawnedEnemies::spawnEnemy(std::make_unique<Enemy1_4>(std::move(newEnemy1_4)));
    }

    void spawnEnemy2_2Wave1(const bool right) {
        for (int k = 0; k <= 4; k++)
        {
            const std::vector<Enemy2State> newEnemy2_2StateVector{{.speed=0, .duration=static_cast<u_int>(k * 50)}, {.desiredPos = Vector2(30 + 60 * right, 9), .speed=70, .slowAtDesiredPos=false}, {.desiredPos = Vector2(25 + k - k*2*right + 70 * right, 30), .speed=70, .shotCount=5, .burstWaitTime=60, .slowAtDesiredPos=false}, {.desiredPos=Vector2(-20 + right * 160, 80+50*k), .speed=70, .shotCount=5, .burstWaitTime=60, .despawn=true}};
            Enemy2_2 newEnemy2_2{enemy2_2Bullet1Pool, newEnemy2_2StateVector};
            newEnemy2_2.spawn({.pos=Vector2(45+30*right+k*5-k*10*right, -10)});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy2_2>(std::move(newEnemy2_2)));
        }
    }

    void spawnEnemy1_2Wave2(const bool right, const u_int spawnDelay = 0) {
        for (int k = 0; k <= 1; k++)
        {
            const std::vector<Enemy1State> newEnemy1_2StateVector{{.duration=spawnDelay+1}, {.speed=0, .duration=static_cast<u_int>(k * 50)}, {.desiredPos = Vector2(30 + 60 * right, 9), .speed=300, .slowAtDesiredPos=false}, {.desiredPos = Vector2(95 - k + k*2*right - 70 * right, 30), .speed=90, .fireRate=60, .slowAtDesiredPos=false}, {.desiredPos=Vector2(-20 + right * 160, 40-10*k), .speed=70, .fireRate=60, .despawn=true}};
            Enemy1_2 newEnemy1_2{enemy1_2BulletPool, enemy1_2BulletPool2, newEnemy1_2StateVector};
            newEnemy1_2.spawn({.pos=Vector2(45+30*right+k*5-k*10*right, -15)});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy1_2>(std::move(newEnemy1_2)));
        }
    }

    void spawnEnemy1_3Wave2(const u_int spawnDelay, const int i, const bool right) {
        if (!right) {
            const std::vector newEnemy1_3StateVector{Enemy1State{.duration = static_cast<u_int>(1 + i * 53)}, {.duration = spawnDelay}, {.desiredPos=Vector2(20 + i * 5, 10 + i * 20), .speed = 60},
                             {.desiredPos = Vector2{-10, 195}, .speed = 120, .duration=120, .fireRate = 60, .slowAtDesiredPos=false},
                        {.desiredPos = Vector2{-10, 195}, .speed = 120, .despawn = true, .slowAtDesiredPos=false}
            };

            Enemy1_3 newEnemy1_3{enemy1_3Bullet1Pool, newEnemy1_3StateVector};
            newEnemy1_3.spawn({.pos = Vector2(-15, 30 + i * 5)});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy1_3>(std::move(newEnemy1_3)));
            return;
        } else {
            const std::vector newEnemy1_3StateVector{Enemy1State{.duration = static_cast<u_int>(1 + i * 53)}, {.duration = spawnDelay}, {.desiredPos=Vector2(100 - i * 5, 10 + i * 20), .speed = 60},
                        {.desiredPos = Vector2{130, 195}, .speed = 120, .duration=120, .fireRate = 60, .slowAtDesiredPos=false},
                        {.desiredPos = Vector2{130, 195}, .speed = 120, .despawn = true, .slowAtDesiredPos=false}
            };

            Enemy1_3 newEnemy1_3{enemy1_3Bullet1Pool, newEnemy1_3StateVector};
            newEnemy1_3.spawn({.pos = Vector2(135, 90 - i * 5)});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy1_3>(std::move(newEnemy1_3)));
            return;
        }
    }
    void spawnEnemy1_4Wave2(const bool right, const u_int spawnDelay=0) {
        const auto spawnPos = Vector2(-15+150*right, 15*right);
        const std::vector newEnemy1_4StateVector{Enemy1State{.duration=spawnDelay+1}, {.desiredPos=Vector2(8 + 104 * right, 12+15*right), .speed=100, .slowAtDesiredPos=false},
            {.desiredPos=Vector2(130-140*right, 12+15*right), .speed=100, .fireRate=120, .despawn=true, .slowAtDesiredPos=false},};
        Enemy1_4 newEnemy1_4{homingBulletPool, newEnemy1_4StateVector};
        newEnemy1_4.spawn({.pos=spawnPos});
        SpawnedEnemies::spawnEnemy(std::make_unique<Enemy1_4>(std::move(newEnemy1_4)));
    }

    void spawnEnemy2_2Wave2(const bool right, const u_int spawnDelay=0) {
        const auto spawnPos = Vector2(-15+150*right, 15*right);
        const std::vector newEnemy2_2StateVector{Enemy2State{.duration=spawnDelay+1}, {.desiredPos=Vector2(8 + 104 * right, 12+15*right), .speed=100, .slowAtDesiredPos=false},
            {.desiredPos=Vector2(130-140*right, 12+15*right), .speed=100, .shotCount=5, .burstWaitTime=60, .despawn=true, .slowAtDesiredPos=false},};
        Enemy2_2 newEnemy2_2{enemy2_2Bullet1Pool, newEnemy2_2StateVector};
        newEnemy2_2.spawn({.pos=spawnPos});
        SpawnedEnemies::spawnEnemy(std::make_unique<Enemy2_2>(std::move(newEnemy2_2)));
    }
public:
    Stage3Phase4() : PhaseHelper("Stage3Phase4") {
        homingBulletPool = std::make_shared<PoolingVector<HomingBullet>>(50);
        enemy2_2Bullet1Pool = std::make_shared<PoolingVector<SimpleBullet1VariableSpeed>>(400);
        bigEnemy2Bullet2Pool = std::make_shared<PoolingVector<AcceleratingBullet1>>(150);
        enemy1_3Bullet1Pool = std::make_shared<PoolingVector<SimpleBullet2Fast>>(200);
        enemy1_2BulletPool = std::make_shared<PoolingVector<Enemy1_2Bullet1>>(100);
        enemy1_2BulletPool2 = std::make_shared<PoolingVector<Enemy1_2Bullet2>>(100);
        GlobalPools::AddPools({homingBulletPool, enemy2_2Bullet1Pool, bigEnemy2Bullet2Pool, enemy1_3Bullet1Pool, enemy1_2BulletPool, enemy1_2BulletPool2});
    }
    void InitPhase() override {
        spawnCornerEnemy1_4(false, 1);
        spawnCornerEnemy1_4(true, 2);
        spawnEnemy2_2Wave1(false);
        spawnEnemy2_2Wave1(true);
        std::vector<Enemy1State> bigEnemy2StateVector = {{.duration = 40}, {.desiredPos = {60, 20}, .speed = 90,}, {.desiredPos = {60, -20}, .speed = 30, .duration = 180, .fireRate = 5, .despawn = true}};
        auto bigEnemy2 = std::make_unique<BigEnemy2>(bigEnemy2Bullet2Pool, bigEnemy2StateVector);
        bigEnemy2->spawn({Vector2(60, -30), 10});
        SpawnedEnemies::spawnEnemy(std::move(bigEnemy2));
        for (int j=0;j<3;j++) {
            for (int i=1; i < 5; i++) {
                spawnEnemy1_3Wave2(wave2Delay+j*40, i, false);
                spawnEnemy1_3Wave2(wave2Delay+j*40, i, true);
            }
        }
        for (int j=0;j<=1;j++) {
            for (int i=0; i < 2; i++) {
                spawnEnemy1_4Wave2(j, cornerEnemy1_4RespawnTime+30*i+160*j);
            }
            spawnEnemy1_2Wave2(j,wave2Delay+120+j*120);
            spawnEnemy2_2Wave2(j, 300+cornerEnemy1_4RespawnTime+160*j);
            spawnEnemy1_4Wave2(j, 360+cornerEnemy1_4RespawnTime+160*j);
        }
    }

    bool doPhysics() override
    {
        if (stepsElapsed == 1200)
        {
            SpawnedEnemies::Clear();
            GlobalPools::Clear();
            GameHandler::NextPhase();
            return false;
        }
        return PhaseHelper::doPhysics();
    };
    void enemyKilled(const u_int _id) override {
        if (_id == 1 && stepsElapsed < cornerEnemy1_4RespawnTime) {
            spawnCornerEnemy1_4(false, 1);
            return;
        }
        if (_id == 2 && stepsElapsed < cornerEnemy1_4RespawnTime) {
            spawnCornerEnemy1_4(true, 2);
            return;
        }
    }
    void enemyDespawned(u_int _id) override{}
};
#endif //RAYLIB_STG_STAGE3PHASE4_H