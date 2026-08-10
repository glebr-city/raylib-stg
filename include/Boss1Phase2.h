//
// Created by n on 09/08/2026.
//

#ifndef RAYLIB_STG_BOSS1PHASE2_H
#define RAYLIB_STG_BOSS1PHASE2_H

#include "Boss1.h"
#include "Boss1Phase1.h"


class Boss1Phase2 : public Boss1Phase1
{
    static constexpr int PHASE_2_HEALTH = 180;
    static constexpr int PHASE_2_TIME = 3000;
    static constexpr Boss1::BOSS_1_PHASES PHASE_2_BOSS_PHASE = Boss1::PHASE_2;
public:
    Boss1Phase2() : Boss1Phase1(PHASE_2_HEALTH, PHASE_2_TIME, PHASE_2_BOSS_PHASE){};
};
#endif //RAYLIB_STG_BOSS1PHASE2_H