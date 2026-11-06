//
// Created by g on 06/11/2026.
//

#ifndef RAYLIB_STG_BOSS3PHASE5_H
#define RAYLIB_STG_BOSS3PHASE5_H
#include "Boss3Phase1.h"

class Boss3Phase5 : public Boss3Phase1
{
    static constexpr int PHASE_5_HEALTH = 80;
    static constexpr int PHASE_5_TIME = 4800;
    static constexpr Boss3::BOSS_3_PHASES PHASE_5_BOSS_PHASE = Boss3::PHASE_5;
    bool isWaiting = false;
    int extraWaitingTime = 180;
    void killBoss()
    {
        currentWaitSteps = 0;
        boss3->SetPhase(Boss3::PHASE_DEFEAT);
        boss3->SetPhase(Boss3::PRE_FIGHT);
        HUDHandler::endBoss();
    }
public:
    Boss3Phase5() : Boss3Phase1("Boss3Phase5", PHASE_5_HEALTH, PHASE_5_TIME, PHASE_5_BOSS_PHASE, 4, Boss3::PRE_PHASE_5) {};
    bool doPhysics() override
    {
        if (isWaiting)
        {
            if (--extraWaitingTime <= 0)
            {
                SpawnedEnemies::Clear();
                GameHandler::NextPhase();
                return false;
            }
            return true;
        }
        if (stepsElapsed < 180)
            return true;
        if (stepsElapsed == 180)
        {
            boss3->SetHealth(maxHealth);
            boss3->SetPhase(bossPhase);
            HUDHandler::startBoss(maxHealth, maxTimer, &bossTimer,  bossHealth);
        }
        if (--bossTimer == 0)
        {
            cancelBullets();
            SoundHandler::PlaySound(PLAYER_HYPER_1);
            SpawnedEnemies::Clear();
            killBoss();
            isWaiting = true;
            return true;
        }
        if (*bossHealth <= 0)
        {
            cancelBullets();
            killBoss();
            ScoreHandler::addScore(100000, false);
            isWaiting = true;
            return true;
        }
        return PhaseHelper::doPhysics();
    }
};
#endif //RAYLIB_STG_BOSS3PHASE5_H