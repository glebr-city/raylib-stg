//
// Created by n on 10/10/2026.
//

#ifndef RAYLIB_STG_STAGE3PHASE1_H
#define RAYLIB_STG_STAGE3PHASE1_H
#include "Enemy2.h"
#include "PhaseHelper.h"

class Stage3Phase1 : public PhaseHelper
{
    protected:
    std::shared_ptr<PoolingVector<Enemy2Bullet1>> enemy2Bullet1Pool;
    public:
    Stage3Phase1() : PhaseHelper("Stage3Phase1", {}, {0, -0.2f}, STAGE_3_BACKGROUND)
    {
        BackgroundHandler::SetBackgroundSprite(defaultBackgroundSprite);
        BackgroundHandler::SetBackgroundPosition({0, 0});
        BackgroundHandler::SetScrollVector(defaultScrollVector);
        enemy2Bullet1Pool = std::make_shared<PoolingVector<Enemy2Bullet1>>(300);
        GlobalPools::AddPools({enemy2Bullet1Pool});
    }
    void InitPhase() override
    {
        PlayerHandler::GetPlayer()->reset();
        for (int i = 0; i < 3; i++) {
            const std::vector<Enemy2State> newEnemy2StateVector{{.desiredPos = Vector2{-10, static_cast<float>(9 + i * 6)}, .speed=90, .shotCount=10, .despawn=true}};
            Enemy2 newEnemy2{enemy2Bullet1Pool, newEnemy2StateVector};
            newEnemy2.spawn({.pos={static_cast<float>(210 - i * 40), static_cast<float>(i * 5)}});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy2>(std::move(newEnemy2)));
        }

        for (int i = 0; i < 3; i++) {
            const std::vector<Enemy2State> newEnemy2StateVector{{.desiredPos = {static_cast<float>(130 + i), static_cast<float>(24 - i * 12)}, .speed=90, .shotCount=10, .lockAngle=false, .despawn=true}};
            Enemy2 newEnemy2{enemy2Bullet1Pool, newEnemy2StateVector};
            newEnemy2.spawn({.pos={static_cast<float>(-250 + i * 40), static_cast<float>(i * 5)}});
            SpawnedEnemies::spawnEnemy(std::make_shared<Enemy2>(std::move(newEnemy2)));
        }
    };
    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};
#endif //RAYLIB_STG_STAGE3PHASE1_H