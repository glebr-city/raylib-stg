//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_TESTPHASE2_H
#define RAYLIB_STG_TESTPHASE2_H
#include "OrbEnemy1.h"
#include "PhaseHelper.h"
#include "SpawnedEnemies.h"

class TestPhase2 : public PhaseHelper {
private:
    std::vector<IPoolingVector*> phasePools;
    PoolingVector<SimpleBullet2> orbBulletPool;
    PoolingVector<SimpleBullet1> miscellaneousBulletPool;
    int stepsElapsed{};
public:
    TestPhase2() : PhaseHelper(phasePools), orbBulletPool(200, 30), miscellaneousBulletPool(2000, 5) {
        phasePools.push_back(&orbBulletPool);
        phasePools.push_back(&miscellaneousBulletPool);
    }

    bool doPhysics(Player *_player) override {
        if (stepsElapsed % 20 == 0) {
            miscellaneousBulletPool.spawn()->spawn(Vector2 {static_cast<float>(stepsElapsed % 120), 1}, Vector2 {0, 1}, RED);
        }
        if (stepsElapsed % 120 == 0) {
            SpawnedEnemies::spawnEnemy(std::make_unique<OrbEnemy1>(&orbBulletPool));
        }
        stepsElapsed++;
        return PhaseHelper::doPhysics(_player);
    }
};


#endif //RAYLIB_STG_TESTPHASE2_H