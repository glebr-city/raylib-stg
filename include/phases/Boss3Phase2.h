//
// Created by g on 28/10/2026.
//

#ifndef RAYLIB_STG_BOSS3PHASE2_H
#define RAYLIB_STG_BOSS3PHASE2_H
#include "Boss3Phase1.h"

class Boss3Phase2 : public Boss3Phase1 {
    static constexpr int PHASE_2_HEALTH = 154;
    static constexpr int PHASE_2_TIME = 3800;
    static constexpr Boss3::BOSS_3_PHASES PHASE_2_BOSS_PHASE = Boss3::PHASE_2;
public:
    Boss3Phase2() : Boss3Phase1("Boss3Phase2", PHASE_2_HEALTH, PHASE_2_TIME, PHASE_2_BOSS_PHASE, 1){};
};
#endif //RAYLIB_STG_BOSS3PHASE2_H