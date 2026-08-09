//
// Created by n on 08/08/2026.
//

#ifndef RAYLIB_STG_BOSS1PHASE1_H
#define RAYLIB_STG_BOSS1PHASE1_H

#include "BackgroundHandler.h"
#include "Boss1.h"
#include "GameHandler.h"
#include "PhaseHelper.h"
#include "SpawnedEnemies.h"

class Boss1Phase1 : public PhaseHelper
{
    std::shared_ptr<Boss1> boss1 = nullptr;
    int* bossHealth = nullptr;
    int maxHealth = 140;
    int maxTimer = 3000;
    int bossTimer = maxTimer;
private:
    void attemptFindingBoss1()
    {

        for (const auto & _spawnedEnemy : *SpawnedEnemies::getSpawnedEnemies())
        {
            if (_spawnedEnemy->GetID() == 201)
            {
                boss1 = std::static_pointer_cast<Boss1>(_spawnedEnemy);
                return;
            }
        }
        auto _pool1 = std::make_shared<PoolingVector<Boss1SmallBullet>>(100);
        auto _pool2 = std::make_shared<PoolingVector<SimpleBullet1Slow>>(100);
        auto _pool3 = std::make_shared<PoolingVector<Boss1FastBurstBullet>>(100);
        GlobalPools::AddPools({_pool1, _pool2, _pool3});
        boss1 = std::make_shared<Boss1>(_pool1, _pool2, _pool3);
        boss1->spawn({.pos=BackgroundHandler::GetRelativePos(Vector2(60, -921.5)), .id = 201});
        SpawnedEnemies::spawnEnemy(boss1);
    }
    public:
    void InitPhase() override
    {
        BackgroundHandler::SetScrollVector({0, 0});
        BackgroundHandler::SetBackgroundPosition({0, -770});
        attemptFindingBoss1();
        bossHealth = boss1->GetHealth();
    }

    bool doPhysics() override
    {
        if (stepsElapsed < 180)
            return true;
        if (stepsElapsed == 180)
        {
            boss1->SetHealth(maxHealth);
            boss1->SetPhase(Boss1::PHASE_1);
            HUDHandler::startBoss(maxHealth, maxTimer, &bossTimer,  bossHealth);
        }
        if (--bossTimer == 0)
        {
            cancelBullets();
            GameHandler::SwitchPhase(BOSS_1_PHASE_2);
            return false;
        }
        if (*bossHealth <= 0)
        {
            cancelBullets();
            ScoreHandler::addScore(1000);
            GameHandler::SwitchPhase(BOSS_1_PHASE_2);
            return false;
        }
        return PhaseHelper::doPhysics();
    }

    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};
#endif //RAYLIB_STG_BOSS1PHASE1_H