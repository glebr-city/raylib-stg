//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_TESTPHASE2_H
#define RAYLIB_STG_TESTPHASE2_H
#include "../OrbEnemy1.h"
#include "../PhaseHelper.h"
#include "../SpawnedEnemies.h"

class TestPhase2 : public PhaseHelper {
private:
    std::shared_ptr<PoolingVector<SimpleBullet2>> orbBulletPool;
    std::shared_ptr<PoolingVector<SimpleBullet1>> miscellaneousBulletPool;
    int stepsElapsed{};
public:
    TestPhase2() : PhaseHelper("TestPhase2") {
        orbBulletPool = std::make_shared<PoolingVector<SimpleBullet2>>(200, 30);
        miscellaneousBulletPool = std::make_shared<PoolingVector<SimpleBullet1>>(200, 5);
        GlobalPools::AddPools({miscellaneousBulletPool, orbBulletPool});
    }

    bool doPhysics() override {
        if (stepsElapsed % 30 == 0) {
            miscellaneousBulletPool->spawn().spawn(Vector2 {static_cast<float>(60), 1}, Vector2 {0, 1}, RED);
        }
        if (false && stepsElapsed % 30 == 15) {
            miscellaneousBulletPool->spawn().spawn(Vector2 {static_cast<float>(stepsElapsed % 150), 1}, Vector2 {0, 1}, BLUE);
        }

        if (false && stepsElapsed % 120 == 0) {
            SpawnedEnemies::spawnEnemy(std::make_shared<OrbEnemy1>(orbBulletPool.get()));
        }
        stepsElapsed++;
        return PhaseHelper::doPhysics();
    }
    void enemyKilled(u_int _id) override{};
    void enemyDespawned(u_int _id) override{};
};


#endif //RAYLIB_STG_TESTPHASE2_H