//
// Created by n on 06/08/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET1FAST_H
#define RAYLIB_STG_SIMPLEBULLET1FAST_H
#include "SimpleBullet1.h"

class SimpleBullet1Fast : public SimpleBullet1
{
    static constexpr float speed = 2.0f;
public:
    SimpleBullet1Fast()
    {
        grazeValue = 300;
    }

    bool doPhysics() override
    {
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer().get()->GetPosition(), PlayerHandler::GetPlayer().get()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        position = Vector2Add(position, direction * speed);
        if (position.x < -2 || position.x > 122 || position.y < -1000 || position.y > 182)
            return false;
        SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_BULLET_LOW, .col = color});
        return true;
    }
};
#endif //RAYLIB_STG_SIMPLEBULLET1FAST_H