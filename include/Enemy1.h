//
// Created by n on 29/07/2026.
//

#ifndef RAYLIB_STG_ENEMY1_H
#include "Enemy.h"
#include "SimpleBullet2.h"
#include "SoundHandler.h"

struct Enemy1State //Enemy1 can only do a few things, and all of them can be specified here; pass a Vector of Enemy1States when spawning.
{
    Vector2 desiredPos = {};
    float speed = 0; // Movement speed, units per second.
    u_int duration = 0; // State will end after this many ticks if > 0 .
    u_int fireRate = 0; // No. of ticks between shots; 0 to not shoot.
    bool despawn = false; // Despawn after completing this state?
};

class Enemy1 : public Enemy
{
private:
    std::shared_ptr<PoolingVector<SimpleBullet2>> bulletPool;
protected:
    static inline const ANIMATED_SPRITES sprite = ENEMY_1;
    u_int elapsedSteps;
    std::vector<Enemy1State> stateVector;
    u_int currentStateIndex = 0;
    float currentSpeed = 0;
    u_int elapsedStepsInState;

    virtual void handleShooting(const Enemy1State currentState)
    {
        const Vector2 playerFinalPos = PlayerHandler::GetPlayer().get()->GetFinalPos();
        if (currentState.fireRate > 0 && elapsedSteps % currentState.fireRate == 0)
        {
            SoundHandler::PlaySound(THUMP_1);
            Vector2 bulletSpawnPos = {position.x - 5, position.y};
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Normalize(Vector2Subtract({playerFinalPos.x - 1, playerFinalPos.y}, bulletSpawnPos)), RED);
            bulletSpawnPos = {position.x + 5, position.y};
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Normalize(Vector2Subtract({playerFinalPos.x + 1, playerFinalPos.y}, bulletSpawnPos)), RED);
        }
    }

public:
    Enemy1(const std::shared_ptr<PoolingVector<SimpleBullet2>>& _bulletPool, const std::vector<Enemy1State>& _stateVector, const uint _scoreValue = 500) : Enemy(_scoreValue) {
        elapsedSteps = -1;
        bulletPool = _bulletPool;
        position = {0, 0};
        collider = {0, 0, 10, 10};
        stateVector = _stateVector;
        enterNewState(0);
    }

    void doPreStep() override
    {
        if (stateVector[currentStateIndex].fireRate == 0)
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_ENEMY});
        else
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .yOffset = 1, .l = LAYER_ENEMY});
    }

    bool doPhysics() override
    {
        elapsedSteps++;
        checkPlayerCollision();
        if (checkPlayerBulletCollision())
        {
            if (!takeDamage())
                return false;
        }
        const Enemy1State currentState = stateVector[currentStateIndex];
        if (++elapsedStepsInState == currentState.duration)
            return enterNewState(currentStateIndex + 1);
        if (Vector2DistanceSqr(position, currentState.desiredPos) < (currentState.speed / 4) * (currentState.speed / 4))
        {
            currentSpeed = std::clamp(currentSpeed - currentState.speed / 60, 0.0f, currentState.speed);
            if (currentSpeed == 0.0f) //Done moving, now enter the new state!
                return enterNewState(currentStateIndex + 1);
        }
        else if (currentSpeed < currentState.speed)
            currentSpeed = currentSpeed + currentState.speed / 60;
        position = Vector2MoveTowards(position, currentState.desiredPos, currentSpeed / 120);
        collider.x = position.x - collider.width / 2;
        collider.y = position.y - collider.height / 2;
        handleShooting(currentState);
        return true;
    }

    bool enterNewState(const u_int newStateIndex)
    {
        if (stateVector[currentStateIndex].despawn)
            return false;
        elapsedStepsInState = 0;
        if (newStateIndex < stateVector.size())
            currentStateIndex = newStateIndex;
        else
            currentStateIndex = 0;
        currentSpeed = 0;
        return true;
    }
};
#define RAYLIB_STG_ENEMY1_H

#endif //RAYLIB_STG_ENEMY1_H