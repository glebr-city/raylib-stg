//
// Created by n on 07/09/2026.
//

#ifndef RAYLIB_STG_ENEMY1_2BULLET1_H
#define RAYLIB_STG_ENEMY1_2BULLET1_H
#include "SimpleBullet2.h"

class Enemy1_2Bullet1 : public SimpleBullet2
{
    protected:
    static constexpr float speed = 1.8f;
    static constexpr int grazeValue = 30;
public:
    Enemy1_2Bullet1() : SimpleBullet2({}, {}, RED)
    {
    }
    bool doPhysics() override
    {
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer()->GetPosition(), PlayerHandler::GetPlayer()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        position = Vector2Add(position, direction * speed);
        if (position.x < -2 || position.x > 122 || position.y < -100 || position.y > 182)
            return false;
        SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_BULLET_LOW, .col = color});
        return true;
    }
};
#endif //RAYLIB_STG_ENEMY1_2BULLET1_H