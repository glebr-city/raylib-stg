//
// Created by g on 28/10/2026.
//

#ifndef RAYLIB_STG_BOSS3PHASE3_H
#define RAYLIB_STG_BOSS3PHASE3_H
#include "Boss3.h"
#include "Boss3Phase1.h"

class Boss3Phase3 : public Boss3Phase1
{
    static constexpr int PHASE_3_HEALTH = 120;
    static constexpr int PHASE_3_TIME = 4800;
    static constexpr Boss3::BOSS_3_PHASES PHASE_3_BOSS_PHASE = Boss3::PHASE_3;
public:
    Boss3Phase3() : Boss3Phase1("Boss3Phase3", PHASE_3_HEALTH, PHASE_3_TIME, PHASE_3_BOSS_PHASE, 2, Boss3::PRE_PHASE_3){};
};
#endif //RAYLIB_STG_BOSS3PHASE3_H