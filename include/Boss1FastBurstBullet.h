//
// Created by n on 09/08/2026.
//

#ifndef RAYLIB_STG_BOSS1FASTBURSTBULLET_H
#define RAYLIB_STG_BOSS1FASTBURSTBULLET_H
#include "SimpleBullet1.h"

class Boss1FastBurstBullet : public SimpleBullet1
{
    static constexpr float speed = 1.5f;
public:
    Boss1FastBurstBullet()
    {
        grazeValue = 70;
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
        return true;
    }
};
#endif //RAYLIB_STG_BOSS1FASTBURSTBULLET_H