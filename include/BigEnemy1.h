//
// Created by n on 30/07/2026.
//

#ifndef RAYLIB_STG_BIGENEMY1_H
#define RAYLIB_STG_BIGENEMY1_H
#include "Enemy1.h"
#include "SimpleBullet3.h"

class BigEnemy1 : public Enemy1
{
private:
    static inline const int SCORE_VALUE = 700;
    static inline const ANIMATED_SPRITES sprite = BIG_ENEMY_1;
    uint8_t humIndex = 254;
    std::shared_ptr<PoolingVector<SimpleBullet3>> bullet1Pool;
    std::shared_ptr<PoolingVector<SimpleBullet1>> bullet2Pool;
    const uint8_t maxHealth = 20;
    uint8_t health = maxHealth;
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

    void handleShooting(Enemy1State currentState) override
    {
        if (currentState.fireRate == 0)
            return;
        if (!SoundHandler::IsSoundPlaying(HUM_1, humIndex))
            humIndex = SoundHandler::PlaySound(HUM_1, true);
        Vector2 bulletSpawnPos = {position.x, position.y - 5};
        float elapsedStepsOffsetThing = std::min(static_cast<float>(elapsedSteps % 60) / 60, 1.0f);
        if (elapsedSteps % 120 < 60)
            elapsedStepsOffsetThing = 1 - elapsedStepsOffsetThing;
        if (elapsedSteps % 8 == 0)
        {
            bullet2Pool->spawn().spawn(bulletSpawnPos, {0, -1}, RED);
            bulletSpawnPos = {position.x - 7, position.y - 5};
            bullet2Pool->spawn().spawn(bulletSpawnPos, Vector2Normalize({-1, 1 + -elapsedStepsOffsetThing}), RED);
        } else if (elapsedSteps % 8 == 1)
        {
            bulletSpawnPos = {position.x + 7, position.y - 5};
            bullet2Pool->spawn().spawn(bulletSpawnPos, Vector2Normalize({1, 1 + -elapsedStepsOffsetThing}), RED);
            bulletSpawnPos = {position.x - 7, position.y - 5};
            bullet2Pool->spawn().spawn(bulletSpawnPos, Vector2Normalize({-1, -0.5f + elapsedStepsOffsetThing}), RED);
        } else if (elapsedSteps % 8 == 2)
        {
            bulletSpawnPos = {position.x - 7, position.y - 5};
            bullet2Pool->spawn().spawn(bulletSpawnPos, Vector2Normalize({-1, -elapsedStepsOffsetThing}), RED);
            bulletSpawnPos = {position.x + 7, position.y - 5};
            bullet2Pool->spawn().spawn(bulletSpawnPos, Vector2Normalize({1, -0.5f + elapsedStepsOffsetThing}), RED);
        } else if (elapsedSteps % 8 == 3)
        {
            bulletSpawnPos = {position.x + 7, position.y - 5};
            bullet2Pool->spawn().spawn(bulletSpawnPos, Vector2Normalize({1, -elapsedStepsOffsetThing}), RED);
        } else if (elapsedSteps % 8 == 4)
        {
            bulletSpawnPos = {position.x - 7, position.y - 5};
            bullet2Pool->spawn().spawn(bulletSpawnPos, Vector2Normalize({-1, -1 + -elapsedStepsOffsetThing}), RED);
        } else if (elapsedSteps % 8 == 5)
        {
            bulletSpawnPos = {position.x + 7, position.y - 5};
            bullet2Pool->spawn().spawn(bulletSpawnPos, Vector2Normalize({1, -1 + -elapsedStepsOffsetThing}), RED);
        }

        if (elapsedSteps % currentState.fireRate == 0)
        {
            bulletSpawnPos = {position.x - 5, position.y};
            const Vector2 playerFinalPos = PlayerHandler::GetPlayer().get()->GetFinalPos();
            Vector2 bulletSpawnDir = Vector2Normalize(Vector2Subtract({playerFinalPos.x, playerFinalPos.y}, bulletSpawnPos));
            if (elapsedSteps % 100 > 50)
                bulletSpawnDir.x = bulletSpawnDir.x - 0.25f + (static_cast<float>((elapsedSteps % 50)) + 1) / 480;
            else
                bulletSpawnDir.x = bulletSpawnDir.x - 0.25f + (50 - static_cast<float>((elapsedSteps % 50)) + 1) / 480;
            bulletSpawnDir = Vector2Normalize(bulletSpawnDir);
            bullet1Pool->spawn().spawn(bulletSpawnPos, bulletSpawnDir, RED);
            bulletSpawnDir = Vector2Normalize({bulletSpawnDir.x - 0.3f, bulletSpawnDir.y});
            bullet1Pool->spawn().spawn(bulletSpawnPos, bulletSpawnDir, RED);
            bulletSpawnPos = {position.x + 5, position.y};
            bulletSpawnDir = Vector2Normalize(Vector2Subtract({playerFinalPos.x, playerFinalPos.y}, bulletSpawnPos));
            if (elapsedSteps % 100 > 50)
                bulletSpawnDir.x = bulletSpawnDir.x + 0.25f - (static_cast<float>(elapsedSteps % 50) + 1) / 480;
            else
                bulletSpawnDir.x = bulletSpawnDir.x + 0.25f - (50 - static_cast<float>(elapsedSteps % 50) + 1) / 480;
            bulletSpawnDir = Vector2Normalize(bulletSpawnDir);
            bullet1Pool->spawn().spawn(bulletSpawnPos, bulletSpawnDir, RED);
            bulletSpawnDir = Vector2Normalize({bulletSpawnDir.x + 0.3f, bulletSpawnDir.y});
            bullet1Pool->spawn().spawn(bulletSpawnPos, bulletSpawnDir, RED);
            bulletSpawnPos = {position.x, position.y - 1};
            bullet1Pool->spawn().spawn(bulletSpawnPos, Vector2Normalize(Vector2Subtract({playerFinalPos.x, playerFinalPos.y}, bulletSpawnPos)), RED);
        }
    }

    void despawn() override
    {
        SoundHandler::StopSound(HUM_1);
        Enemy::despawn();
    }
public:
    BigEnemy1(const std::shared_ptr<PoolingVector<SimpleBullet3>>& _bullet1Pool, const std::shared_ptr<PoolingVector<SimpleBullet1>>& _bullet2Pool,const std::vector<Enemy1State>& _stateVector) : Enemy1({}, _stateVector, 3750)
    {
        scoreValue = SCORE_VALUE;
        elapsedSteps = -1;
        bullet1Pool = _bullet1Pool;
        bullet2Pool = _bullet2Pool;
        position = {0, 0};
        collider = {0, 0, 31, 19};
        stateVector = _stateVector;
        enterNewState(0);
    }

    void doPreStep() override
    {
        SpriteParametres spriteParams = {.i = sprite, .pos = position, .l = LAYER_ENEMY};
        if (currentFlashDuration-- > 0)
        {
            spriteParams.flashing = true;
        }
        if (stateVector[currentStateIndex].fireRate > 0)
            spriteParams.yOffset = 1;
        SpriteHandler::QueueMyAnimatedSprite(spriteParams);
    }
};
#endif //RAYLIB_STG_BIGENEMY1_H