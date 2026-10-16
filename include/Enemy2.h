//
// Created by g on 13/10/2026.
//

#ifndef RAYLIB_STG_ENEMY2_H
#define RAYLIB_STG_ENEMY2_H
#include "Enemy.h"
#include "Enemy2Bullet1.h"

struct Enemy2State //Copied and pasted from Enemy1Base for the most part... it should be all right!
{
    Vector2 desiredPos = {};
    float speed = 0; // Movement speed, units per second.
    u_int duration = 0; // State will end after this many ticks if > 0 .
    int shotCount = 0; //No. of shots per burst; 0 not to shoot.
    int shotWaitTime = 3; // No. of ticks between shots; 0 to not shoot.
    int burstWaitTime = 15; // The enemy aims once for every burst.
    bool lockAngle = true; //Lock shot angle between shots, or lock the targeted position?
    bool despawn = false; // Despawn after completing this state?
    bool slowAtDesiredPos = true; //Should the enemy slow down between states?
};
class Enemy2 : public Enemy {
private:
protected:
    std::shared_ptr<PoolingVector<Enemy2Bullet1>> bullet1Pool;
    //static constexpr STATIC_SPRITES sprite = ENEMY_2;
    static constexpr int shotGlowTime = 10; //How long to glow for after a shot.
    int currentShotGlowTime = 0;
    u_int elapsedSteps;
    std::vector<Enemy2State> stateVector;
    int remainingShots = 0; //How many more times to shoot in this burst?
    u_int currentStateIndex = 0;
    int currentShotWaitTime = 0;
    int currentBurstWaitTime = 0;
    float currentSpeed = 0;
    u_int elapsedStepsInState = 0;
    Vector2 shotDirection = {};
    Vector2 targetPosition = {};

    bool hasStartedSlowing = false;

    virtual constexpr SOUNDS getFireSound()
    {
        return CLICK_1;
    }

    virtual constexpr int getMaxHealth()
    {
        return 3;
    }

    virtual void fireShot(const bool lockAngle) {
        if (!lockAngle) {
            shotDirection = Vector2Normalize(Vector2Subtract(targetPosition, position));
            bullet1Pool->spawn().spawn(position, shotDirection, YELLOW);
            bullet1Pool->spawn().spawn(position, Vector2Rotate(shotDirection, 0.3f), ORANGE);
            bullet1Pool->spawn().spawn(position, Vector2Rotate(shotDirection, -0.3f), ORANGE);
        }
        else {
            bullet1Pool->spawn().spawn(position, shotDirection, ORANGE);
            bullet1Pool->spawn().spawn(position, Vector2Rotate(shotDirection, 0.3f), YELLOW);
            bullet1Pool->spawn().spawn(position, Vector2Rotate(shotDirection, -0.3f), YELLOW);
        }
    }

    virtual bool checkRemainingShots(const Enemy2State &currentState, const bool lockAngle) {
        if (remainingShots > 0) {
            if (currentShotWaitTime-- == 1) {
                currentShotGlowTime = shotGlowTime;
                fireShot(lockAngle);
                currentShotWaitTime = currentState.shotWaitTime;
                remainingShots--;
            }
            return true;
        }
        return false;
    }
    virtual void handleShooting(const Enemy2State currentState)
    {
        if (position.x < -5 || position.x > 125 || position.y < -5 || position.y > 185)
            return;
        const bool lockAngle = currentState.lockAngle;
        if (checkRemainingShots(currentState, lockAngle))
            return;
        if (currentBurstWaitTime-- == 1) {
            SoundHandler::PlaySound(getFireSound());
            currentBurstWaitTime = currentState.burstWaitTime;
            remainingShots = currentState.shotCount;
            targetPosition = PlayerHandler::GetPlayer()->GetFinalPos();
            shotDirection = Vector2Normalize(Vector2Subtract(targetPosition, position));
            checkRemainingShots(currentState, lockAngle);
        }

    }

    [[nodiscard]] virtual constexpr STATIC_SPRITES sprite() const //I just realised that I should probably have been doing this the whole time.
    {
        return ENEMY_2;
    }

public:
    Enemy2(const std::shared_ptr<PoolingVector<Enemy2Bullet1>> _bullet1Pool, const std::vector<Enemy2State>& _stateVector, const uint _scoreValue = 500) : Enemy(_scoreValue) {
        health = Enemy2::getMaxHealth();
        elapsedSteps = -1;
        position = {0, 0};
        collider = {0, 0, 14, 14};
        stateVector = _stateVector;
        bullet1Pool = _bullet1Pool;
        Enemy2::enterNewState({});
    }

    void doPostStep() override
    {
        SpriteParametres spriteParams = {.i = sprite(), .pos = position, .l = LAYER_ENEMY};
        if (currentFlashDuration-- > 0)
        {
            spriteParams.flashing = true;
        }
        if (--currentShotGlowTime >= 0)
            spriteParams.yOffset = 1;
        SpriteHandler::QueueMyStaticSprite(spriteParams);
    }

    bool doPhysics() override
    {
        elapsedSteps++;
        checkPlayerCollision();
        if (checkPlayerBulletCollision())
        {
            if (!takeDamage())
            {
                die();
                return false;
            }
        }
        const Enemy2State currentState = stateVector[currentStateIndex];
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
        if (stateVector[currentStateIndex].despawn)
            return false;
        hasStartedSlowing = false;
        if (stateVector[currentStateIndex].slowAtDesiredPos)
            currentSpeed = 0;
        elapsedStepsInState = 0;
        if (newStateIndex < stateVector.size())
            currentStateIndex = newStateIndex;
        else
            currentStateIndex = 0;
        currentSpeed = std::min(currentSpeed, stateVector[currentStateIndex].speed);
        remainingShots = stateVector[currentStateIndex].shotCount;
        if (stateVector[currentStateIndex].shotCount > 0) {
            targetPosition = PlayerHandler::GetPlayer()->GetFinalPos();
            shotDirection = Vector2Normalize(Vector2Subtract(targetPosition, position));
            currentShotWaitTime = 2;
            currentBurstWaitTime = 2;
        }
        return true;
    }

    void spawn(const EnemySpawnParametres _params) override {
        Enemy::spawn(_params);
        enterNewState(0);
        health = getMaxHealth();
    }

    void spawn(const Vector2 _position, const u_int _scoreValue) override {
        spawn({.pos=_position});
        scoreValue = _scoreValue;
    }

    void spawn(const Vector2 _position) override {
        spawn({.pos=_position});
    }
};
#endif //RAYLIB_STG_ENEMY2_H