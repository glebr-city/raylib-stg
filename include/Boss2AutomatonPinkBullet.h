//
// Created by n on 29/09/2026.
//

#ifndef RAYLIB_STG_BOSS2AUTOMATONPINKBULLET_H
#define RAYLIB_STG_BOSS2AUTOMATONPINKBULLET_H
#include "SimpleBullet2.h"

class Boss2AutomatonPinkBullet : public SimpleBullet2
{
protected:
    static constexpr float speed = 1;
    static constexpr int grazeValue = 30;
public:
    Boss2AutomatonPinkBullet() : SimpleBullet2({}, {}, PINK)
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
#endif //RAYLIB_STG_BOSS2AUTOMATONPINKBULLET_H