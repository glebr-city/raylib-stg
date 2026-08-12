//
// Created by n on 09/08/2026.
//

#ifndef RAYLIB_STG_BOSS1PHASE3_H
#define RAYLIB_STG_BOSS1PHASE3_H
#include "Boss1.h"

class Boss1Phase3 : public Boss1Phase1
{
    static constexpr int PHASE_3_HEALTH = 220;
    static constexpr int PHASE_3_TIME = 3500;
    static constexpr Boss1::BOSS_1_PHASES PHASE_3_BOSS_PHASE = Boss1::PHASE_3;
public:
    Boss1Phase3() : Boss1Phase1(PHASE_3_HEALTH, PHASE_3_TIME, PHASE_3_BOSS_PHASE){};
};
#endif //RAYLIB_STG_BOSS1PHASE3_H