//
// Created by n on 24/10/2026.
//

#ifndef RAYLIB_STG_STAGE3PHASE5_H
#define RAYLIB_STG_STAGE3PHASE5_H
#include "PhaseHelper.h"

class Stage3Phase5 : public PhaseHelper
{
private:
    static constexpr u_int Enemy2_2Wave1SpawnDelay = 75; //How many frames shall pass between every enemy?
    static constexpr u_int wave2Delay = 600;
    std::shared_ptr<PoolingVector<SimpleBullet1VariableSpeed>> enemy2_2Bullet1Pool;
    std::shared_ptr<PoolingVector<SimpleBullet2Fast>> enemy1_3Bullet1Pool;
    void spawnEnemy1_3Wave1()
    {
        const std::vector<Enemy1State> newEnemy1StateVector{
            {.desiredPos={130, 40}, .speed=100, .duration=40, .slowAtDesiredPos=false},
            {.desiredPos={130, 40}, .speed=100, .fireRate=30, .despawn=true, .slowAtDesiredPos=false}};
        Enemy1_3 newEnemy1_3{enemy1_3Bullet1Pool, newEnemy1StateVector};
        newEnemy1_3.spawn({.pos={80, -6}});
        SpawnedEnemies::spawnEnemy(std::make_shared<Enemy1_3>(std::move(newEnemy1_3)));
    }
    void spawnEnemy2_2Wave1() {
        for (int right=0; right<=1; right++)
            for (int j=1; j<21; j++)
            {
                const int i = std::min(j, 10);
                const auto spawnPos = Vector2(-15+150*right, 15*right);
                const std::vector newEnemy2_2StateVector{Enemy2State{.duration=j*Enemy2_2Wave1SpawnDelay+1}, {.desiredPos=Vector2(8 + i +(104 - 2*i) * right, 15*right), .speed=static_cast<float>(100+20*i), .shotCount=3, .burstWaitTime=30-2*i, .slowAtDesiredPos=false},
                    {.desiredPos=Vector2(60+i-2*i*right, 15*right), .speed=static_cast<float>(70+20*i), .shotCount=3, .burstWaitTime=40, .despawn=false, .slowAtDesiredPos=false},
                    {.desiredPos=Vector2(130-140*right, 15*right), .speed=static_cast<float>(70+20*i), .duration=30, .shotCount=1, .burstWaitTime=20-i, .despawn=false, .slowAtDesiredPos=false},
                    {.desiredPos=Vector2(130-140*right, 15*right), .speed=static_cast<float>(70+20*i), .shotCount=3, .burstWaitTime=40, .despawn=true, .slowAtDesiredPos=false},};
                Enemy2_2 newEnemy2_2{enemy2_2Bullet1Pool, newEnemy2_2StateVector};
                newEnemy2_2.spawn({.pos=spawnPos});
                SpawnedEnemies::spawnEnemy(std::make_unique<Enemy2_2>(std::move(newEnemy2_2)));
            }
    }
    void spawnEnemy1_3Wave2()
    {
        for (int right=0; right<=1; right++)
            for (int j=1; j<15; j+=3)
            {
                const int i = std::min(j, 10);
                const auto spawnPos = Vector2(-15+150*right, 15*right);
                const std::vector newEnemy1_3StateVector{Enemy1State{.duration=j*Enemy2_2Wave1SpawnDelay+1+wave2Delay}, {.desiredPos=Vector2(8 + (104) * right, 15*right), .speed=static_cast<float>(100+20*i), .fireRate=120, .slowAtDesiredPos=false},
                    {.desiredPos=Vector2(60+i-2*i*right, 15*right), .speed=static_cast<float>(70+20*i), .fireRate=120, .despawn=false, .slowAtDesiredPos=false},
                    {.desiredPos=Vector2(130-140*right, 15*right), .speed=static_cast<float>(70+20*i), .duration=30, .fireRate=120, .despawn=false, .slowAtDesiredPos=false},
                    {.desiredPos=Vector2(130-140*right, 15*right), .speed=static_cast<float>(70+20*i), .fireRate=120, .despawn=true, .slowAtDesiredPos=false},};
                Enemy1_3 newEnemy1_3{enemy1_3Bullet1Pool, newEnemy1_3StateVector};
                newEnemy1_3.spawn({.pos=spawnPos});
                SpawnedEnemies::spawnEnemy(std::make_unique<Enemy1_3>(std::move(newEnemy1_3)));
            }
    }
public:
    Stage3Phase5() : PhaseHelper("Stage3Phase5")
    {
        enemy2_2Bullet1Pool = std::make_shared<PoolingVector<SimpleBullet1VariableSpeed>>(400);
        enemy1_3Bullet1Pool = std::make_shared<PoolingVector<SimpleBullet2Fast>>(7);
        GlobalPools::AddPools({enemy2_2Bullet1Pool, enemy1_3Bullet1Pool});
    }
    void InitPhase() override
    {
        spawnEnemy1_3Wave1();
        spawnEnemy2_2Wave1();
        spawnEnemy1_3Wave2();
    };
    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};
#endif //RAYLIB_STG_STAGE3PHASE5_H