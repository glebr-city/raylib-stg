//
// Created by n on 22/10/2026.
//

#ifndef RAYLIB_STG_STAGE3PHASE4_H
#define RAYLIB_STG_STAGE3PHASE4_H
#include "PhaseHelper.h"

class Stage3Phase4 : public PhaseHelper
{
    public:
    Stage3Phase4() : PhaseHelper("Stage3Phase4") {};
    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};
#endif //RAYLIB_STG_STAGE3PHASE4_H