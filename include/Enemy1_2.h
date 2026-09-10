//
// Created by n on 07/09/2026.
//

#ifndef RAYLIB_STG_ENEMY1_2_H
#define RAYLIB_STG_ENEMY1_2_H
#include "Enemy1Base.h"
#include "Enemy1_2Bullet1.h"
#include "Enemy1_2Bullet2.h"

class Enemy1_2 : public Enemy1Base
{
    static constexpr int ENEMY_1_2_HEALTH = 4;
    static inline const ANIMATED_SPRITES sprite = ENEMY_1_2;
    static inline const Color mainShotColour = { 200, 80, 130, 255 };
    private:
    bool doMainFireThisTime = false;
    std::shared_ptr<PoolingVector<Enemy1_2Bullet1>> bulletPool1;

    std::shared_ptr<PoolingVector<Enemy1_2Bullet2>> bulletPool2;
protected:
    void handleShooting(const Enemy1State currentState) override
    {
        const Vector2 playerFinalPos = PlayerHandler::GetPlayer().get()->GetFinalPos();
        if (currentState.fireRate > 0 && elapsedSteps % currentState.fireRate == 0)
        {
            doMainFireThisTime = !doMainFireThisTime;
            SoundHandler::PlaySound(THUMP_1);
            Vector2 bulletSpawnPos = {position.x, position.y};
            Vector2 pinkBulletDirection = Vector2Normalize(Vector2Subtract({playerFinalPos.x - 1, playerFinalPos.y}, bulletSpawnPos));
            RNGHandler::StepSeed();
            pinkBulletDirection = Vector2Rotate(pinkBulletDirection, (static_cast<float>(static_cast<int>(RNGHandler::GetSeed() % 31) - 15)) / 100);
            bulletPool2->spawn().spawn(bulletSpawnPos, pinkBulletDirection, PINK);
            if (doMainFireThisTime)
            {
                bulletSpawnPos = {position.x - 6, position.y};
                bulletPool1->spawn().spawn(bulletSpawnPos, Vector2Normalize(Vector2Subtract({playerFinalPos.x - 1.2f, playerFinalPos.y}, bulletSpawnPos)), mainShotColour);
                bulletSpawnPos = {position.x + 6, position.y};
                bulletPool1->spawn().spawn(bulletSpawnPos, Vector2Normalize(Vector2Subtract({playerFinalPos.x + 1.2f, playerFinalPos.y}, bulletSpawnPos)), mainShotColour);

            }
        }
    }
    public:
    Enemy1_2(const std::shared_ptr<PoolingVector<Enemy1_2Bullet1>>& _bulletPool1, const std::shared_ptr<PoolingVector<Enemy1_2Bullet2>>& _bulletPool2, const std::vector<Enemy1State>& _stateVector, const uint _scoreValue = 800) : Enemy1Base(_stateVector, _scoreValue)
    {
        collider = {0, 0, 14, 12};
        bulletPool1 = _bulletPool1;
        bulletPool2 = _bulletPool2;
        health = ENEMY_1_2_HEALTH;
    }

    void doPostStep() override
    {
        Color spriteColour = WHITE;
        if (currentFlashDuration-- > 0 && elapsedSteps % 61 <= 30)
            spriteColour = RED;
        if (stateVector[currentStateIndex].fireRate == 0)
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_ENEMY, .col = spriteColour});
        else
            SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .yOffset = 1, .l = LAYER_ENEMY, .col = spriteColour});
    }
};
#endif //RAYLIB_STG_ENEMY1_2_H