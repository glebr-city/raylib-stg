//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_PLAYERBULLETS_H
#define RAYLIB_STG_PLAYERBULLETS_H

#include "PlayerBullet.h"
#include "PoolingVector.h"
class PlayerBullets {
    static std::unique_ptr<PoolingVector<PlayerBullet>> playerBullets;
public:
    static void spawnPlayerBullet(const Vector2 pos) {
        playerBullets->spawn()->spawn(pos);
    }

    static PoolingVector<PlayerBullet>* getPlayerBullets() {
        return playerBullets.get();
    }

    static void destroyPlayerBullet(int i) {
        std::vector<PlayerBullet>* bulletVector = playerBullets->getVector();
        playerBullets->setNumActive(playerBullets->getNumActive() - 1);
        std::iter_swap(bulletVector->begin() + i, bulletVector->begin() + playerBullets->getNumActive());
    }


};
#endif //RAYLIB_STG_PLAYERBULLETS_H