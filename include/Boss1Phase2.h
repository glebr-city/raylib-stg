//
// Created by n on 09/08/2026.
//

#ifndef RAYLIB_STG_BOSS1PHASE2_H
#define RAYLIB_STG_BOSS1PHASE2_H
#include "BackgroundHandler.h"
#include "Boss1.h"
#include "GameHandler.h"
#include "PhaseHelper.h"
#include "SpawnedEnemies.h"

class Boss1Phase2 : public PhaseHelper
{
    std::shared_ptr<Boss1> boss1 = nullptr;
    int* bossHealth = nullptr;
    int maxHealth = 140;
    int maxTimer = 7200;
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
        auto _pool2 = std::make_shared<PoolingVector<SimpleBullet1>>(100);
        GlobalPools::AddPools({_pool1, _pool2});
        boss1 = std::make_shared<Boss1>(_pool1, _pool2);
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
        boss1->SetPhase(Boss1::PRE_FIGHT);
    }

    bool doPhysics() override
    {
        if (stepsElapsed < 120)
            return true;
        if (stepsElapsed == 120)
        {
            boss1->SetHealth(maxHealth);
            boss1->SetPhase(Boss1::PHASE_2);
            HUDHandler::startBoss(maxHealth, maxTimer, &bossTimer,  bossHealth);
        }
        if (--bossTimer == 0)
        {
            GameHandler::SwitchPhase(BOSS_1_PHASE_3);
            return false;
        }
        if (*bossHealth <= 0)
        {
            ScoreHandler::addScore(1000);
            GameHandler::SwitchPhase(BOSS_1_PHASE_3);
            return false;
        }
        return PhaseHelper::doPhysics();
    }

    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};
#endif //RAYLIB_STG_BOSS1PHASE2_H