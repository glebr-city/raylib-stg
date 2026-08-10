//
// Created by n on 09/08/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET1SLOW_H
#define RAYLIB_STG_SIMPLEBULLET1SLOW_H
#include "SimpleBullet1.h"
class SimpleBullet1Slow : public SimpleBullet1
{
    static constexpr float speed = 0.75f;
public:
    SimpleBullet1Slow()=default;
    bool doPhysics() override
    {
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer().get()->GetPosition(), PlayerHandler::GetPlayer().get()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        position = Vector2Add(position, direction * speed);
        if (position.x < -2 || position.x > 122 || position.y < -1000 || position.y > 182)
            return false;
        return true;
    }

    Vector2 GetPosition() override
    {
        return SimpleBullet1::GetPosition();
    }
};
#endif //RAYLIB_STG_SIMPLEBULLET1SLOW_H