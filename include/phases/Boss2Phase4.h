//
// Created by g on 09/10/2026.
//

#ifndef RAYLIB_STG_BOSS2PHASE4_H
#define RAYLIB_STG_BOSS2PHASE4_H
#include "Boss2Phase1.h"

class Boss2Phase4 : public Boss2Phase1
{
    static constexpr int PHASE_4_HEALTH = 300;
    static constexpr int PHASE_4_TIME = 4000;
    static constexpr Boss2::BOSS_2_PHASES PHASE_4_BOSS_PHASE = Boss2::PHASE_4;
public:
    Boss2Phase4() : Boss2Phase1("Boss2Phase4", PHASE_4_HEALTH, PHASE_4_TIME, PHASE_4_BOSS_PHASE, Boss2::PRE_FIGHT){};
};
#endif //RAYLIB_STG_BOSS2PHASE4_H