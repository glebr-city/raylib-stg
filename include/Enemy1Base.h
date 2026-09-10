//
// Created by n on 29/07/2026.
//

#ifndef RAYLIB_STG_ENEMY1BASE_H
#define RAYLIB_STG_ENEMY1BASE_H
#include "Enemy.h"
#include "SimpleBullet2.h"

struct Enemy1State //Enemy1 can only do a few things, and all of them can be specified here; pass a Vector of Enemy1States when spawning.
{
    Vector2 desiredPos = {};
    float speed = 0; // Movement speed, units per second.
    u_int duration = 0; // State will end after this many ticks if > 0 .
    u_int fireRate = 0; // No. of ticks between shots; 0 to not shoot.
    bool despawn = false; // Despawn after completing this state?
    bool slowAtDesiredPos = true; //Should the enemy slow down between states?
};

class Enemy1Base : public Enemy
{
private:
protected:
    static constexpr ANIMATED_SPRITES sprite = ENEMY_1;
    u_int elapsedSteps;
    std::vector<Enemy1State> stateVector;
    u_int currentStateIndex = 0;
    float currentSpeed = 0;
    u_int elapsedStepsInState = 0;
    bool hasStartedSlowing = false;

    virtual void handleShooting(const Enemy1State currentState)
    {

    }

public:
    Enemy1Base( const std::vector<Enemy1State>& _stateVector, const uint _scoreValue = 500) : Enemy(_scoreValue) {
        elapsedSteps = -1;
        position = {0, 0};
        collider = {0, 0, 10, 10};
        stateVector = _stateVector;
        enterNewState(0);
    }

    void doPostStep() override
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
        if (currentState.slowAtDesiredPos)
        {
            if (Vector2DistanceSqr(position, currentState.desiredPos) < (currentState.speed / 4) * (currentState.speed / 4))
            {
                if (!hasStartedSlowing)
                {
                    hasStartedSlowing = true;
                    currentSpeed = currentState.speed;
                }
                currentSpeed = std::clamp(currentSpeed - currentState.speed / 60, 0.0f, currentState.speed);
                if (currentSpeed == 0.0f) //Done moving, now enter the new state!
                {
                    position = currentState.desiredPos;
                    return enterNewState(currentStateIndex + 1);
                }
            }
            else if (currentSpeed < currentState.speed)
                currentSpeed = currentSpeed + currentState.speed / 60;
        } else
        {
            if (currentSpeed < currentState.speed)
                currentSpeed = std::clamp(currentSpeed + currentState.speed / 60, 0.0f, currentState.speed);
            else if (currentSpeed > currentState.speed)
                currentSpeed = std::clamp(currentSpeed - currentState.speed / 60, 0.0f, currentState.speed);
            if (Vector2DistanceSqr(position, currentState.desiredPos) <= (currentState.speed / 120) * (currentState.speed / 120))
            {
                position = currentState.desiredPos;
                return enterNewState(currentStateIndex + 1);
            }
        }
        position = Vector2MoveTowards(position, currentState.desiredPos, currentSpeed / 120);
        collider.x = position.x - collider.width / 2;
        collider.y = position.y - collider.height / 2;
        handleShooting(currentState);
        return true;
    }

    virtual bool enterNewState(const u_int newStateIndex)
    {
        hasStartedSlowing = false;
        if (stateVector[currentStateIndex].despawn)
            return false;
        if (stateVector[currentStateIndex].slowAtDesiredPos)
            currentSpeed = 0;
        elapsedStepsInState = 0;
        if (newStateIndex < stateVector.size())
            currentStateIndex = newStateIndex;
        else
            currentStateIndex = 0;
        return true;
    }
};


#endif //RAYLIB_STG_ENEMY1BASE_H