//
// Created by g on 28/10/2026.
//

#ifndef RAYLIB_STG_BOSS3PHASE4_H
#define RAYLIB_STG_BOSS3PHASE4_H
#include "Boss3Phase1.h"

class Boss3Phase4 : public Boss3Phase1
{
    static constexpr int PHASE_4_HEALTH = 360;
    static constexpr int PHASE_4_TIME = 120;
    static constexpr Boss3::BOSS_3_PHASES PHASE_4_BOSS_PHASE = Boss3::PHASE_4;
public:
    Boss3Phase4() : Boss3Phase1("Boss3Phase4", PHASE_4_HEALTH, PHASE_4_TIME, PHASE_4_BOSS_PHASE, 3, Boss3::PRE_FIGHT){};
};
#endif //RAYLIB_STG_BOSS3PHASE4_H