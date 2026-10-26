//
// Created by g on 26/10/2026.
//

#ifndef RAYLIB_STG_BOSS3PHASE1_H
#define RAYLIB_STG_BOSS3PHASE1_H
#include "Boss3.h"
#include "PhaseHelper.h"

class Boss3Phase1 : public PhaseHelper {
public:
    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
    void InitPhase() override
    {
        const auto boss3 = std::make_shared<Boss3>();
        boss3->spawn({.pos={60, 30}});
        SpawnedEnemies::spawnEnemy(boss3);
    };
};
#endif //RAYLIB_STG_BOSS3PHASE1_H