//
// Created by n on 07/09/2026.
//

#ifndef RAYLIB_STG_STAGE2PHASE1_H
#define RAYLIB_STG_STAGE2PHASE1_H
#include "BackgroundHandler.h"
#include "Enemy1_2.h"
#include "PhaseHelper.h"
#include "SpawnedEnemies.h"


class SimpleBullet1;
class SimpleBullet3;
class SimpleBullet2;

class Stage2Phase1 : public PhaseHelper
{
     std::shared_ptr<PoolingVector<Enemy1_2Bullet1>> enemy1_2BulletPool;
     std::shared_ptr<PoolingVector<SimpleBullet2>> enemy1_2BulletPool2;
public:
    Stage2Phase1() : PhaseHelper("Stage2Phase1", {}, {0, -0.2f}, DEFAULT_BACKGROUND)
    {
        enemy1_2BulletPool = std::make_shared<PoolingVector<Enemy1_2Bullet1>>(30);
        enemy1_2BulletPool2 = std::make_shared<PoolingVector<SimpleBullet2>>(30);
        BackgroundHandler::SetBackgroundPosition({0, 0});
        BackgroundHandler::SetScrollVector(defaultScrollVector);
        GlobalPools::AddPools({enemy1_2BulletPool});

    }
    void InitPhase() override
    {
        PlayerHandler::GetPlayer()->reset();
        std::vector<Enemy1State> enemy1StateVector = {{.desiredPos = {100, 20}, .speed = 100,}, {.desiredPos = {50, 20}, .speed = 100, .fireRate = 30}, {.desiredPos = {190, 20}, .speed = 100, .fireRate = 30, .despawn = true},};
        std::unique_ptr<Enemy1> newEnemy = std::make_unique<Enemy1_2>(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector);
        newEnemy->spawn({Vector2(125, -5), 1});
        SpawnedEnemies::spawnEnemy(std::move(newEnemy));
    }

    void doPreStep() override
    {
        PhaseHelper::doPreStep();
    }

    void enemyKilled(u_int _id) override {};
    void enemyDespawned(u_int _id) override {};
};
#endif //RAYLIB_STG_STAGE2PHASE1_H