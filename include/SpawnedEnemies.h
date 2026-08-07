//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_SPAWNEDENEMIES_H
#define RAYLIB_STG_SPAWNEDENEMIES_H
#include <array>
#include <memory>

#include "Enemy.h"
#include "Player.h"
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
            if (spawnedEnemies.at(e)->doPhysics()) {
                e++;
                continue;
            }
            spawnedEnemies.at(e)->despawn();
            const u_int id = spawnedEnemies.at(e)->GetID();
            spawnedEnemies.erase(spawnedEnemies.begin() + e);
            GlobalVariables::getCurrentPhase()->enemyDespawned(id);
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