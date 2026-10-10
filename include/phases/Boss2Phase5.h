//
// Created by n on 10/10/2026.
//

#ifndef RAYLIB_STG_BOSS2PHASE5_H
#define RAYLIB_STG_BOSS2PHASE5_H
#include "Boss2Phase1.h"

class Boss2Phase5 : public Boss2Phase1
{
    static constexpr int PHASE_5_HEALTH = Boss2::PHASE_5_AUTOMATON_HEALTH * 4;
    static constexpr int PHASE_5_TIME = 3500;
    static constexpr Boss2::BOSS_2_PHASES PHASE_5_BOSS_PHASE = Boss2::PHASE_5;
    int extraWaitingTime = 180;
    bool isWaiting = false;
public:
    Boss2Phase5() : Boss2Phase1("Boss2Phase5", PHASE_5_HEALTH, PHASE_5_TIME, PHASE_5_BOSS_PHASE, 4, Boss2::PRE_PHASE_5), extraWaitingTime(180), isWaiting(false)
    {};

    bool doPhysics() override
    {
        if (isWaiting)
        {
            if (--extraWaitingTime <= 0)
            {
                GameHandler::NextPhase();
                return false;
            }
            return true;
        }
        if (stepsElapsed < 180)
            return true;
        if (stepsElapsed == 180)
        {
            boss2->SetHealth(maxHealth);
            boss2->SetPhase(bossPhase);
            HUDHandler::startBoss(maxHealth, maxTimer, &bossTimer,  bossHealth);
        }
        if (--bossTimer == 0)
        {
            cancelBullets();
            SoundHandler::PlaySound(PLAYER_HYPER_1);
            SpawnedEnemies::Clear();
            isWaiting = true;
            return true;
        }
        if (*bossHealth <= 0)
        {
            cancelBullets();
            ScoreHandler::addScore(10000, false);
            isWaiting = true;
            return true;
        }
        return PhaseHelper::doPhysics();
    }
};
#endif //RAYLIB_STG_BOSS2PHASE5_H