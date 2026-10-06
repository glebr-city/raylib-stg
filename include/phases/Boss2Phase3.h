//
// Created by g on 06/10/2026.
//

#ifndef RAYLIB_STG_BOSS2PHASE3_H
#define RAYLIB_STG_BOSS2PHASE3_H
#include "Boss2.h"
#include "Boss2Phase1.h"

class Boss2Phase3 : public Boss2Phase1
{
    static constexpr int PHASE_3_HEALTH = 180;
    static constexpr int PHASE_3_TIME = 3000;
    static constexpr Boss2::BOSS_2_PHASES PHASE_3_BOSS_PHASE = Boss2::PHASE_3;
public:
    Boss2Phase3() : Boss2Phase1("Boss2Phase3", PHASE_3_HEALTH, PHASE_3_TIME, PHASE_3_BOSS_PHASE){};
};
#endif //RAYLIB_STG_BOSS2PHASE3_H