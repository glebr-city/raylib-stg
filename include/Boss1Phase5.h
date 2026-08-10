//
// Created by n on 10/08/2026.
//

#ifndef RAYLIB_STG_BOSS1PHASE5_H
#define RAYLIB_STG_BOSS1PHASE5_H
#include "Boss1Phase1.h"

class Boss1Phase5 : public Boss1Phase1
{
    static constexpr int PHASE_5_HEALTH = -1;
    static constexpr int PHASE_5_TIME = 4500;
    static constexpr Boss1::BOSS_1_PHASES PHASE_5_BOSS_PHASE = Boss1::PHASE_DEFEAT;
public:
    Boss1Phase5() : Boss1Phase1(PHASE_5_HEALTH, PHASE_5_TIME, PHASE_5_BOSS_PHASE){};
    void InitPhase() override
    {
        Boss1Phase1::InitPhase();
        boss1->SetPhase(PHASE_5_BOSS_PHASE);
        boss1->SetPhase(Boss1::PRE_FIGHT);
        HUDHandler::endBoss();
        //GameHandler::NextPhase();
    }

    bool doPhysics() override
    {
        return true;
    };
};
#endif //RAYLIB_STG_BOSS1PHASE5_H