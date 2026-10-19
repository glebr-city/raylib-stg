//
// Created by g on 16/10/2026.
//

#ifndef RAYLIB_STG_STAGE3PHASE2_H
#define RAYLIB_STG_STAGE3PHASE2_H
#include "BackgroundHandler.h"
#include "HomingBullet.h"
#include "HomingBulletHelper.h"
#include "PhaseHelper.h"

class Stage3Phase2 : public PhaseHelper {

    std::shared_ptr<PoolingVector<HomingBullet>> homingBulletPool;
public:
    Stage3Phase2() : PhaseHelper("Stage3Phase2", {}, {0, -0.2f}, STAGE_3_BACKGROUND) {
        BackgroundHandler::SetBackgroundSprite(defaultBackgroundSprite);
        BackgroundHandler::SetScrollVector(defaultScrollVector);
        homingBulletPool = std::make_shared<PoolingVector<HomingBullet>>(50);
        GlobalPools::AddPools({homingBulletPool});
    }
    void InitPhase() override {
    };

    bool doPhysics() override {
        if (stepsElapsed % 60 == 0) {
            HomingBulletHelper newHomingBulletHelper{homingBulletPool};
            newHomingBulletHelper.spawn({{static_cast<float>(stepsElapsed % 600) * 0.2f, 0}});
            SpawnedEnemies::spawnEnemy(std::make_shared<HomingBulletHelper>(std::move(newHomingBulletHelper)));
        }
        return PhaseHelper::doPhysics();
    };
    void enemyDespawned(u_int _id) override {};
    void enemyKilled(u_int _id) override {};
};
#endif //RAYLIB_STG_STAGE3PHASE2_H