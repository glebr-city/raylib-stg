//
// Created by n on 09/08/2026.
//

#ifndef RAYLIB_STG_BOSS1PHASE4_H
#define RAYLIB_STG_BOSS1PHASE4_H
#include "../Boss1.h"
class Boss1Phase4  : public Boss1Phase1
{
    static constexpr int PHASE_4_HEALTH = 300;
    static constexpr int PHASE_4_TIME = 4500;
    static constexpr Boss1::BOSS_1_PHASES PHASE_4_BOSS_PHASE = Boss1::PHASE_4;
    bool isWaiting = false;
    int extraWaitingTime = 180;
private:
    void killBoss()
    {
        currentWaitSteps = 0;
        boss1->SetPhase(Boss1::PHASE_DEFEAT);
        boss1->SetPhase(Boss1::PRE_FIGHT);
        HUDHandler::endBoss();
    }
public:
    Boss1Phase4() : Boss1Phase1("Boss1Phase4", PHASE_4_HEALTH, PHASE_4_TIME, PHASE_4_BOSS_PHASE)
    {
        isWaiting = false;
        extraWaitingTime = 180;
    };

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
            boss1->SetHealth(maxHealth);
            boss1->SetPhase(bossPhase);
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
            ScoreHandler::addScore(10000, false);
            isWaiting = true;
            return true;
        }
        return PhaseHelper::doPhysics();
    }
};
#endif //RAYLIB_STG_BOSS1PHASE4_H