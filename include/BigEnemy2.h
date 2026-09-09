//
// Created by n on 08/09/2026.
//

#ifndef RAYLIB_STG_BIGENEMY2_H
#define RAYLIB_STG_BIGENEMY2_H
#include "AcceleratingBullet1.h"
#include "Enemy1Base.h"

class BigEnemy2 : public Enemy1Base
{
private:
    static inline const int SCORE_VALUE = 700;
    static inline const ANIMATED_SPRITES sprite = BIG_ENEMY_2;
    static constexpr uint8_t maxHealth = 13;
    static constexpr uint_fast8_t maxShots = 20;
    static constexpr uint8_t maxCooldown = 30;
    int currentCooldown = 0;
    uint8_t humIndex = 254;
    std::shared_ptr<PoolingVector<AcceleratingBullet1>> bulletPool;
    uint8_t health = maxHealth;
    uint_fast8_t shotsFired = 0;
    float randomRotation = 0.0f;

    bool takeDamage() override
    {
        if (--health <= 0)
        {
            die();
            SoundHandler::StopSound(HUM_1, 1);
            return false;
        }
        startDamageAnimation();
        return true;
    }

    void setRandomRotation()
    {
        RNGHandler::StepSeed();
        randomRotation = (static_cast<float>(RNGHandler::GetSeed() % 260) - 130) / 1000 * PI;
    }

    void handleShooting(const Enemy1State currentState) override
    {
        if (currentState.fireRate == 0)
            return;
        if (!SoundHandler::IsSoundPlaying(HUM_1, humIndex))
            humIndex = SoundHandler::PlaySound(HUM_1, true);
        const Vector2 bulletSpawnPos = {position.x, position.y + 10};
        if (shotsFired == maxShots)
        {
            if (++currentCooldown < maxCooldown)
                return;
            currentCooldown = 0;
            shotsFired = 0;
        }
        if (shotsFired == 0)
        {
            setRandomRotation();
            const float fireRateFraction = static_cast<float>(elapsedStepsInState) / static_cast<float>(currentState.fireRate);
            //bulletPool->spawn().spawn(bulletSpawnPos, Vector2Rotate(Vector2(0, 1), randomRotation), YELLOW, 1 + fireRateFraction);
        }
        std::cout << static_cast<int>(elapsedStepsInState) << std::endl;
        if (elapsedStepsInState % currentState.fireRate == 0)
        {
            float fireRateFraction = static_cast<float>(shotsFired) / static_cast<float>(maxShots);
            shotsFired += 1;
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Rotate(Vector2(0, 1), fireRateFraction * PI + randomRotation), {253, 249, static_cast<u_char>(150 * (1 - fireRateFraction)), 255}, 0.1f + fireRateFraction * 1.5f);
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Rotate(Vector2(0, 1), fireRateFraction * -PI + randomRotation), {253, 249, static_cast<u_char>(150 * (1 - fireRateFraction)), 255}, 0.1f + fireRateFraction * 1.5f);
            fireRateFraction = static_cast<float>(shotsFired - 2) / static_cast<float>(maxShots);
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Rotate(Vector2(0, 1), fireRateFraction * PI + randomRotation), {253, 249, static_cast<u_char>(150 * (1 - fireRateFraction)), 255}, 0.1f + fireRateFraction * 1.5f);
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Rotate(Vector2(0, 1), fireRateFraction * -PI + randomRotation), {253, 249, static_cast<u_char>(150 * (1 - fireRateFraction)), 255}, 0.1f + fireRateFraction * 1.5f);

        }
        if (shotsFired > maxShots && false)
        {
            const float fireRateFraction = static_cast<float>(shotsFired - (maxShots / 4)) / static_cast<float>(maxShots);
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Rotate(Vector2(0, 1), fireRateFraction * PI + randomRotation), {253, 249, static_cast<u_char>(150 * (1 - fireRateFraction)), 255}, 0.1f + fireRateFraction * 1.5f);
            bulletPool->spawn().spawn(bulletSpawnPos, Vector2Rotate(Vector2(0, 1), fireRateFraction * -PI + randomRotation), {253, 249, static_cast<u_char>(150 * (1 - fireRateFraction)), 255}, 0.1f + fireRateFraction * 1.5f);

        }
    }

    void despawn() override
    {
        SoundHandler::StopSound(HUM_1);
        Enemy::despawn();
    }
public:
    BigEnemy2(const std::shared_ptr<PoolingVector<AcceleratingBullet1>>& _bulletPool,const std::vector<Enemy1State>& _stateVector) : Enemy1Base(_stateVector, 3750)
    {
        scoreValue = SCORE_VALUE;
        elapsedSteps = -1;
        bulletPool = _bulletPool;
        position = {0, 0};
        collider = {0, 0, 17, 23};
        stateVector = _stateVector;
        enterNewState(0);
    }

    void doPostStep() override
    {
        SpriteParametres spriteParams = {.i = sprite, .pos = Vector2(position.x, position.y), .l = LAYER_ENEMY,};
        if (currentFlashDuration-- > 0)
        {
            spriteParams.flashing = true;
        }
        if (stateVector[currentStateIndex].fireRate > 0)
            spriteParams.yOffset = 1;
        SpriteHandler::QueueMyAnimatedSprite(spriteParams);
    }

    bool enterNewState(const u_int newStateIndex) override
    {
        currentCooldown = 0;
        shotsFired = 0;
        return Enemy1Base::enterNewState(newStateIndex);
    }
};
#endif //RAYLIB_STG_BIGENEMY2_H