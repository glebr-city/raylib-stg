//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_ORBENEMY1_H
#define RAYLIB_STG_ORBENEMY1_H

#include "Enemy.h"
#include "raymath.h"
#include "SimpleBullet2.h"

class OrbEnemy1 : public Enemy {
protected:
    int elapsedSteps = -1;
    PoolingVector<SimpleBullet2>* bulletPool;
    inline static const ANIMATED_SPRITES sprite = BULLET_1_MONOCHROME;
public:
    OrbEnemy1(PoolingVector<SimpleBullet2>* _bulletPool) {
        elapsedSteps = -1;
        bulletPool = _bulletPool;
        position = {-5, 30};
        collider = {-5, 30, 5, 5};
    }

    void doPreStep() override  {
        SpriteHandler::DrawMyAnimatedSprite(sprite, position);
    }

    bool doPhysics(std::array<Vector2, 2> playerPosAndMovement) override {
        elapsedSteps++;
        if (checkPlayerBulletCollision()) {
            return false;
        }
        position.x += 0.2f;
        if (position.x > 125)
            return false;
        collider.x = position.x;
        Vector2 playerFinalPos = Vector2Add(playerPosAndMovement[0], playerPosAndMovement[1]);
        if (elapsedSteps % 31 == 0) {
            bulletPool->spawn().spawn(position, Vector2Normalize(playerFinalPos - position));
        }
        return true;
    }
};

#endif //RAYLIB_STG_ORBENEMY1_H