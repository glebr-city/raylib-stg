//
// Created by n on 02/10/2026.
//

#ifndef RAYLIB_STG_BOSS2PHASE2_H
#define RAYLIB_STG_BOSS2PHASE2_H
#include "Boss2Phase1.h"

class Boss2Phase2 : public Boss2Phase1
{
    static constexpr int PHASE_2_HEALTH = 180;
    static constexpr int PHASE_2_TIME = 3000;
    static constexpr Boss2::BOSS_2_PHASES PHASE_2_BOSS_PHASE = Boss2::PHASE_2;
public:
    Boss2Phase2() : Boss2Phase1("Boss2Phase2", PHASE_2_HEALTH, PHASE_2_TIME, PHASE_2_BOSS_PHASE){};
};
#endif //RAYLIB_STG_BOSS2PHASE2_H