//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_SPAWNEDENEMIES_H
#define RAYLIB_STG_SPAWNEDENEMIES_H
#include <memory>

#include "Enemy.h"
//#include "EphemeraHandler.h"
class SpawnedEnemies {
    static std::vector<std::shared_ptr<Enemy>> spawnedEnemies;
public:

    static void doPreStep() {
        for (const auto& e: spawnedEnemies) {
            e->doPreStep();
        }
    }

    static void doPhysics() {

        for (int e = 0; e < spawnedEnemies.size();) {
            const auto _enemy = spawnedEnemies.at(e);
            if (_enemy->doPhysics()) {
                e++;
                continue;
            }
            _enemy->despawn();
            const Enemy::EnemyDeathInfo* _enemyDeathInfo = _enemy->GetDeathInfo();
            const Vector2 _pos = _enemy->GetPosition();
            EphemeraHandler::Spawn(_pos, _enemyDeathInfo->t, _enemyDeathInfo->l);
            spawnedEnemies.erase(spawnedEnemies.begin() + e);
            GlobalVariables::getCurrentPhase()->enemyDespawned(_enemy->GetID());
        }
    }
    static void spawnEnemy(std::shared_ptr<Enemy> _enemy) { //Add an enemy to the vector.
        spawnedEnemies.emplace_back(std::move(_enemy));
    }

    static std::vector<std::shared_ptr<Enemy>>* getSpawnedEnemies() {
        return &spawnedEnemies;
    }

    static void clear() {
        spawnedEnemies.clear();
    }

};

#endif //RAYLIB_STG_SPAWNEDENEMIES_H