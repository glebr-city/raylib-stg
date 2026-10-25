//
// Created by n on 15/10/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET2FAST_H
#define RAYLIB_STG_SIMPLEBULLET2FAST_H
#include "SimpleBullet2.h"

class SimpleBullet2Fast : public SimpleBullet2
{
public:
    bool doPhysics() override
    {
        position = Vector2Add(position, direction * 3.25f);
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer()->GetPosition(), PlayerHandler::GetPlayer()->GetFinalPos(), 15)) {
            DamageHandler::hitPlayer();
            return false;
        }
        if (position.x < -2 || position.x > 122 || position.y < -100 || position.y > 182)
            return false;
        SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_BULLET_LOW, .col = color});
        return true;
    }
};
#endif //RAYLIB_STG_SIMPLEBULLET2FAST_H