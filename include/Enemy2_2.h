//
// Created by n on 15/10/2026.
//

#ifndef RAYLIB_STG_ENEMY2_2_H
#define RAYLIB_STG_ENEMY2_2_H
#include "Enemy2Base.h"
#include "SimpleBullet1VariableSpeed.h"

class Enemy2_2 : public Enemy2Base
{
protected:
    std::shared_ptr<PoolingVector<SimpleBullet1VariableSpeed>> bullet1Pool;
    bool shootingLeft = false;
    Vector2 shotSpawnPosition{};
    static constexpr Vector2 shotSpawnOffset = {0, 0};


    constexpr int getMaxHealth() override
    {
        return 6;
    }
    [[nodiscard]] constexpr STATIC_SPRITES sprite() const override //I just realised that I should probably have been doing this the whole time.
    {
        return ENEMY_2_2;
    }

    constexpr SOUNDS getFireSound() override
    {
        return THUMP_1;
    }

    public:
    Enemy2_2(const std::shared_ptr<PoolingVector<SimpleBullet1VariableSpeed>>& _bullet1Pool, const std::vector<Enemy2State>& _stateVector, const uint _scoreValue = 500) : Enemy2Base(_stateVector, _scoreValue)
    {
        bullet1Pool = _bullet1Pool;
        health = Enemy2_2::getMaxHealth();
        collider = {0, 0, 16, 14};
    }

    void fireShot(const float speed, Vector2 direction)
    {
        direction = Vector2Rotate(direction, direction.x * speed * -0.3f);
        direction = Vector2Normalize({direction.x * speed, direction.y});
        Color col = {static_cast<unsigned char>(140 + 50 * speed), static_cast<unsigned char>(80 + 10 * speed), static_cast<unsigned char>(100 + 10 * speed), 255};
        bullet1Pool->spawn().spawn(speed, {shotSpawnPosition.x + direction.x * 5, shotSpawnPosition.y}, direction, col);
    }

    bool checkRemainingShots(const Enemy2State &currentState, const bool lockAngle) override {
        if (remainingShots > 0) {
            float rotationAngle = static_cast<float>(remainingShots) * -0.075f + 0.15f;
            if (shootingLeft)
                rotationAngle *= -1;
            Vector2 direction = Vector2Rotate({0, 1}, rotationAngle);
            if (currentShotWaitTime-- == 1) {
                currentShotGlowTime = shotGlowTime;
                shotSpawnPosition = Vector2Add(position, shotSpawnOffset);
                for (int i = remainingShots; i > 0; i -= 2)
                {
                    float extraRotation = static_cast<float>(RNGHandler::GetSeed() % 100) * 0.0001f - 0.005f;
                    float speed = 1 + i * 0.1f;
                    shotSpawnPosition.y += 2;
                    for (int j = -1; j < 2; j += 2)
                    {
                        direction = Vector2Rotate(direction, extraRotation);
                        fireShot(speed, Vector2Rotate(direction, direction.x * 0.1f * j));
                    }
                }

                currentShotWaitTime = currentState.shotWaitTime;
                remainingShots--;
            }
            return true;
        }
        return false;
    }

    void handleShooting(const Enemy2State currentState) override
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

    bool enterNewState(const u_int newStateIndex) override
    {
        if (!Enemy2Base::enterNewState(newStateIndex))
            return false;
        if (stateVector[currentStateIndex].desiredPos.x < position.x)
            shootingLeft = true;
        else if (stateVector[currentStateIndex].desiredPos.x > position.x)
            shootingLeft = false;
        return true;
    }

};
#endif //RAYLIB_STG_ENEMY2_2_H