//
// Created by g on 16/10/2026.
//

#ifndef RAYLIB_STG_STAGE3PHASE2_H
#define RAYLIB_STG_STAGE3PHASE2_H
#include "BackgroundHandler.h"
#include "Enemy1_4.h"
#include "HomingBullet.h"
#include "HomingBulletHelper.h"
#include "PhaseHelper.h"

class Stage3Phase2 : public PhaseHelper {

    std::shared_ptr<PoolingVector<HomingBullet>> homingBulletPool;
    std::shared_ptr<PoolingVector<Enemy1_2Bullet1>> enemy1_2BulletPool;
    std::shared_ptr<PoolingVector<Enemy1_2Bullet2>> enemy1_2BulletPool2;
public:
    Stage3Phase2() : PhaseHelper("Stage3Phase2", {}, {0, -0.2f}, STAGE_3_BACKGROUND) {
        BackgroundHandler::SetBackgroundSprite(defaultBackgroundSprite);
        BackgroundHandler::SetScrollVector(defaultScrollVector);
        homingBulletPool = std::make_shared<PoolingVector<HomingBullet>>(50);
        enemy1_2BulletPool = std::make_shared<PoolingVector<Enemy1_2Bullet1>>(100);
        enemy1_2BulletPool2 = std::make_shared<PoolingVector<Enemy1_2Bullet2>>(100);
        GlobalPools::AddPools({homingBulletPool, enemy1_2BulletPool, enemy1_2BulletPool2});
    }
    void InitPhase() override {
        for (int j = 11; j >= -1; j--) {
            for (int i = -1; i <= 1; i++) {
                const u_int spawnDelay = 151- j*150;
                const std::vector newEnemy1_4StateVector{Enemy1State{.duration=spawnDelay}, {.desiredPos = Vector2(60+20*i+10*j, 15), .speed = 75, .slowAtDesiredPos=false}, {.desiredPos = Vector2(60+20*i+10*j, 30-15 * std::abs(i)), .speed = 75, .fireRate=60}, {.desiredPos = Vector2(60+40*i+10*j, 50-15 * std::abs(i)), .speed = 20, .fireRate = 60}, {.desiredPos = Vector2(60+60*i+10*j, -20), .speed = 50, .despawn=true, .slowAtDesiredPos=false }};
                Enemy1_4 newEnemy1_4{homingBulletPool, newEnemy1_4StateVector};
                newEnemy1_4.spawn({.pos=Vector2(60+20*i, -20-15*std::abs(i))});
                SpawnedEnemies::spawnEnemy(std::make_unique<Enemy1_4>(std::move(newEnemy1_4)));
            }
        }
        for (int i=0;i<6;i++) {
            const std::vector<Enemy1State> enemy1StateVector = {{.duration=static_cast<u_int>(630+i*10)}, {.desiredPos = Vector2(10+i*20, 20), .speed = 90, .slowAtDesiredPos = false}, {.desiredPos=Vector2(10+i*20, 60), .speed = 80, .fireRate = 20}, {.desiredPos=Vector2(10+i*20, 200), .speed = 150, .despawn = true},};
            auto newEnemy = Enemy1_2(enemy1_2BulletPool, enemy1_2BulletPool2, enemy1StateVector);
            newEnemy.spawn({.pos=Vector2(10+i*20, -15-20*i)});
            SpawnedEnemies::spawnEnemy(std::make_unique<Enemy1_2>(std::move(newEnemy)));
        }
        for (int i = 1; i >= -1; i -= 2) {
                const u_int spawnDelay = 630- i*60;
                const u_int fireRate = 60;
                const std::vector newEnemy1_4StateVector{Enemy1State{.duration=spawnDelay}, {.desiredPos = Vector2(60+40*i, 30-15), .speed = 75, .slowAtDesiredPos=false}, {.desiredPos = Vector2(60+40*i, 50-15 * std::abs(i)-15), .speed = 75, .fireRate=fireRate}, {.desiredPos = Vector2(60+40*i, 70-15 * std::abs(i)-15), .speed = 30, .fireRate = fireRate}, {.desiredPos = Vector2(60+80*i, -20-15), .speed = 50, .despawn=true, .slowAtDesiredPos=false }};
                Enemy1_4 newEnemy1_4{homingBulletPool, newEnemy1_4StateVector};
                newEnemy1_4.spawn({.pos=Vector2(60+80*i, 30-15*std::abs(i)-15)});
                SpawnedEnemies::spawnEnemy(std::make_unique<Enemy1_4>(std::move(newEnemy1_4)));
        }
    };

    bool doPhysics() override {
        if (stepsElapsed > 1200) {
            GameHandler::NextPhase();
            return false;
        }
        return PhaseHelper::doPhysics();
    };
    void enemyDespawned(u_int _id) override {};
    void enemyKilled(u_int _id) override {};
};
#endif //RAYLIB_STG_STAGE3PHASE2_H