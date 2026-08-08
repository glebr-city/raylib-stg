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
    int* bossHealth = nullptr;
    int maxHealth = 120;
    int maxTimer = 3600;
    int bossTimer = maxTimer;
    public:
    void InitPhase() override
    {
        BackgroundHandler::SetScrollVector({0, 0});
        BackgroundHandler::SetBackgroundPosition({0, 770});
        auto newEnemy = std::make_shared<Boss1>();
        newEnemy->spawn({Vector2(60, 28.5)});
        newEnemy->SetHealth(maxHealth);
        bossHealth = newEnemy->GetHealth();
        SpawnedEnemies::spawnEnemy(std::move(newEnemy));
        HUDHandler::startBoss(maxHealth, maxTimer, &bossTimer,  bossHealth);
    }

    bool doPhysics() override
    {
        if (--bossTimer == 0)
        {
            GameHandler::SwitchPhase(DIAGONAL_TANKS);
            return false;
        }
        if (*bossHealth <= 0)
        {
            GameHandler::SwitchPhase(DIAGONAL_TANKS);
            return false;
        }
        return true;
    }

    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};
#endif //RAYLIB_STG_BOSS1PHASE1_H