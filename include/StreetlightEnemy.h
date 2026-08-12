//
// Created by n on 06/08/2026.
//

#ifndef RAYLIB_STG_STREETLIGHTENEMY_H
#define RAYLIB_STG_STREETLIGHTENEMY_H
#include "BackgroundHandler.h"
#include "Enemy.h"
#include "SimpleBullet1Fast.h"

class StreetlightEnemy : public Enemy
{
private:
    std::shared_ptr<PoolingVector<SimpleBullet1Fast>> bulletPool;
    Vector2 aimingDirection;
    static constexpr int firingPositionOffset = -4;
    static constexpr uint maxHealth = 11;
    static constexpr Color color2 = {150, 150, 50, 255};
    uint health = maxHealth;
public:
    StreetlightEnemy(const std::shared_ptr<PoolingVector<SimpleBullet1Fast>>& _bulletPool) : Enemy(1000, Rectangle {0, 0, 8, 10}, maxHealth, {EphemeraHandler::EXPLOSION_SMALL, LAYER_GROUNDED})
    {
        position = {};
        aimingDirection = {0, 1};
        bulletPool = _bulletPool;
    }

    virtual bool takeDamage() override
    {
        if (--health <= 0)
        {
            die();
            return false;
        }
        startDamageAnimation();
        return true;
    }

    void doPostStep() override
    {
        SpriteParametres opts = {.i=STREETLIGHT_ENEMY, .pos=position, .l=LAYER_GROUNDED};
        if (currentFlashDuration-- > 0 && GlobalVariables::getCurrentPhase()->getStepsElapsed() % 60 <= 30)
            opts.col = RED;
        SpriteHandler::QueueMyAnimatedSprite(opts);
    }

    bool doPhysics() override
    {
        position -= BackgroundHandler::GetScrollVector();
        collider.x = position.x - collider.width / 2;
        collider.y = position.y - collider.height / 2;
        Vector2 firingPosition = {position.x, position.y + firingPositionOffset};
        if (position.y > 10)
        {
            if (position.y > 185)
                return false;
            if (position.y <= 140)
            {
                if (GlobalVariables::getCurrentPhase()->getStepsElapsed() % 80 == 0)
                {
                    SoundHandler::PlaySound(BANG_1);
                    bulletPool->spawn().spawn(firingPosition, aimingDirection);
                    aimingDirection = Vector2Rotate(aimingDirection, 0.5 * PI);
                    bulletPool->spawn().spawn(firingPosition, aimingDirection);
                    aimingDirection = Vector2Rotate(aimingDirection, 0.5 * PI);
                    bulletPool->spawn().spawn(firingPosition, aimingDirection);
                    aimingDirection = Vector2Rotate(aimingDirection, 0.5 * PI);
                    bulletPool->spawn().spawn(firingPosition, aimingDirection);
                    aimingDirection = Vector2Rotate(aimingDirection, 0.25 * PI);
                } else if (GlobalVariables::getCurrentPhase()->getStepsElapsed() % 80 == 30)
                {
                    SoundHandler::PlaySound(BANG_2);
                    bulletPool->spawn().spawn(position, aimingDirection, color2);
                    aimingDirection = Vector2Rotate(aimingDirection, 0.5 * PI);
                    bulletPool->spawn().spawn(position, aimingDirection, color2);
                    aimingDirection = Vector2Rotate(aimingDirection, 0.5 * PI);
                    bulletPool->spawn().spawn(position, aimingDirection, color2);
                    aimingDirection = Vector2Rotate(aimingDirection, 0.5 * PI);
                    bulletPool->spawn().spawn(position, aimingDirection, color2);
                    aimingDirection = Vector2Rotate(aimingDirection, 0.3 * PI);
                }
            }
        }
        if (checkPlayerBulletCollision()) {
            return takeDamage();
        }
        return true;
    }
};
#endif //RAYLIB_STG_STREETLIGHTENEMY_H