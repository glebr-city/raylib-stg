//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_SPAWNEDENEMIES_H
#define RAYLIB_STG_SPAWNEDENEMIES_H
#include <array>
#include <memory>

#include "Enemy.h"
#include "OrbEnemy1.h"
#include "Player.h"
class SpawnedEnemies {
    static std::unique_ptr<std::vector<std::unique_ptr<Enemy>>> spawnedEnemies;
public:

    static void doPreStep() {
        for (auto& e: *spawnedEnemies) {
            e->doPreStep();
        }
    }

    static void doPhysics(Player* player) {
        const std::array<Vector2, 2> playerPosAndMovement = player->getPosAndMovement();

        for (int e = 0; e < spawnedEnemies->size();) {
            if (spawnedEnemies->at(e)->doPhysics(playerPosAndMovement)) {
                e++;
                continue;
            }
            spawnedEnemies->erase(spawnedEnemies->begin() + e);
        }
    }
    static void spawnEnemy(std::unique_ptr<Enemy> _enemy) { //Add an enemy to the vector.
        spawnedEnemies->emplace_back(std::move(_enemy));
    }

    static std::vector<std::unique_ptr<Enemy>> *getSpawnedEnemies() {
        return spawnedEnemies.get();
    }

};

#endif //RAYLIB_STG_SPAWNEDENEMIES_H