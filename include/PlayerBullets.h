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
    static void spawnPlayerBullet(bool isHyper, const Vector2 pos) {
        playerBullets->spawn().spawn(isHyper, pos);
    }

    static void spawnPlayerBullet(bool isHyper, const Vector2 pos, float _xSpeed) {
        playerBullets->spawn().spawn(isHyper, pos, _xSpeed);
    }

    static PoolingVector<PlayerBullet>* getPlayerBullets() {
        return playerBullets.get();
    }

    static void destroyPlayerBullet(const int i) {
        std::vector<PlayerBullet>& bulletVector = playerBullets->getVector();
        playerBullets->setNumActive(playerBullets->getNumActive() - 1);
        std::iter_swap(bulletVector.begin() + i, bulletVector.begin() + playerBullets->getNumActive());
    }


};
#endif //RAYLIB_STG_PLAYERBULLETS_H