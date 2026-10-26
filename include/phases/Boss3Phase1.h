//
// Created by g on 26/10/2026.
//

#ifndef RAYLIB_STG_BOSS3PHASE1_H
#define RAYLIB_STG_BOSS3PHASE1_H
#include "PhaseHelper.h"

class Boss3Phase1 : public PhaseHelper {
public:
    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};
#endif //RAYLIB_STG_BOSS3PHASE1_H