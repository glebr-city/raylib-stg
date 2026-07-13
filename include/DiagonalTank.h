//
// Created by n on 12/07/2026.
//

#ifndef RAYLIB_STG_DIAGONALTANK_H
#define RAYLIB_STG_DIAGONALTANK_H
#include "Enemy.h"
#include "SimpleBullet2.h"

class DiagonalTank : public Enemy
{
    private:
    static inline const ANIMATED_SPRITES sprite = DIAGONAL_TANK;
    u_int elapsedSteps;
    PoolingVector<SimpleBullet2>* bulletPool;
    bool isMoving = true;
    u_int stopAndFireDelay = 0; //How many steps to wait before stopping and firing
    public:
    DiagonalTank(PoolingVector<SimpleBullet2>* _bulletPool, const u_int _stopAndFireDelay = 0) {
        elapsedSteps = -1;
        bulletPool = _bulletPool;
        position = {0, 0};
        collider = {0, 0, 13, 13};
        stopAndFireDelay = _stopAndFireDelay;
    }

    void doPreStep() override
    {
        if (isMoving)
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_GROUNDED});
        else
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .yOffset = 1, .l = LAYER_GROUNDED});
    }

    bool doPhysics(std::array<Vector2, 2> playerPosAndMovement) override {
        elapsedSteps++;
        position += GlobalVariables::getCurrentPhase()->getScrollVector();
        if (checkPlayerBulletCollision()) {
            return false;
        }
        if (isMoving)
        {
            position.x += 0.1f;
            position.y += -0.1f;
        }
        if (position.x > 125)
            return false;
        collider.x = position.x;
        collider.y = position.y;
        Vector2 playerFinalPos = Vector2Add(playerPosAndMovement[0], playerPosAndMovement[1]);
        if (elapsedSteps == stopAndFireDelay) {
            isMoving = false;
        } else if (elapsedSteps == stopAndFireDelay + 60)
        {
            bulletPool->spawn().spawn(position, Vector2Normalize(playerFinalPos - position), RED);
        } else if (elapsedSteps == stopAndFireDelay + 90)
        {
            bulletPool->spawn().spawn(position, Vector2Normalize(playerFinalPos - position), RED);
        } else if (elapsedSteps == stopAndFireDelay + 120)
        {
            bulletPool->spawn().spawn(position, Vector2Normalize(playerFinalPos - position), RED);
        }
        return true;
    }
};
#endif //RAYLIB_STG_DIAGONALTANK_H