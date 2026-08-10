//
// Created by n on 09/08/2026.
//

#ifndef RAYLIB_STG_BOSS1PHASE4_H
#define RAYLIB_STG_BOSS1PHASE4_H
#include "BackgroundHandler.h"
#include "Boss1.h"
#include "GameHandler.h"
#include "PhaseHelper.h"
#include "SimpleBullet1Fast.h"
#include "SpawnedEnemies.h"

class Boss1Phase4  : public Boss1Phase1
{
    static constexpr int PHASE_4_HEALTH = 300;
    static constexpr int PHASE_4_TIME = 4500;
    static constexpr Boss1::BOSS_1_PHASES PHASE_4_BOSS_PHASE = Boss1::PHASE_4;
public:
    Boss1Phase4() : Boss1Phase1(PHASE_4_HEALTH, PHASE_4_TIME, PHASE_4_BOSS_PHASE){};
};
#endif //RAYLIB_STG_BOSS1PHASE4_H