//
// Created by n on 08/08/2026.
//

#ifndef RAYLIB_STG_BOSS1PHASE1_H
#define RAYLIB_STG_BOSS1PHASE1_H

#include "BackgroundHandler.h"
#include "Boss1.h"
#include "GameHandler.h"
#include "PhaseHelper.h"

class Boss1Phase1 : public PhaseHelper
{
    std::shared_ptr<Boss1> boss1 = nullptr;
    int* bossHealth = nullptr;
    static constexpr int PHASE_1_HEALTH = 140;
    static constexpr int PHASE_1_TIME = 3000;
    static constexpr Boss1::BOSS_1_PHASES PHASE_1_BOSS_PHASE = Boss1::PHASE_1;
    Boss1::BOSS_1_PHASES bossPhase = Boss1::PHASE_1;
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
    explicit Boss1Phase1(const int _maxHealth = PHASE_1_HEALTH, const int _maxTimer = PHASE_1_TIME, const Boss1::BOSS_1_PHASES _bossPhase = PHASE_1_BOSS_PHASE)
    {
        maxHealth = _maxHealth;
        maxTimer = _maxTimer;
        bossPhase = _bossPhase;
        bossTimer = maxTimer;
    }

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
        if (stepsElapsed < 180)
            return true;
        if (stepsElapsed == 180)
        {
            boss1->SetHealth(maxHealth);
            boss1->SetPhase(bossPhase);
            HUDHandler::startBoss(maxHealth, maxTimer, &bossTimer,  bossHealth);
        }
        if (--bossTimer == 0)
        {
            SoundHandler::PlaySound(EXPLOSION_1);
            cancelBullets();
            GameHandler::NextPhase();
            return false;
        }
        if (*bossHealth <= 0)
        {
            SoundHandler::PlaySound(EXPLOSION_1);
            cancelBullets();
            ScoreHandler::addScore(10000, false);
            GameHandler::NextPhase();
            return false;
        }
        return PhaseHelper::doPhysics();
    }

    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};

#include "SpawnedEnemies.h"

#endif //RAYLIB_STG_BOSS1PHASE1_H