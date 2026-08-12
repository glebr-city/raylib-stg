//
// Created by n on 09/08/2026.
//

#ifndef RAYLIB_STG_BOSS1SMALLBULLETS_H
#define RAYLIB_STG_BOSS1SMALLBULLETS_H
#include "SimpleBullet2.h"

class Boss1SmallBullet : public SimpleBullet2
{
    static constexpr float speed = 1.5f;
    static constexpr int grazeValue = 45;
public:
    bool doPhysics() override
    {
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer()->GetPosition(), PlayerHandler::GetPlayer()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        position = Vector2Add(position, direction * speed);
        if (position.x < -2 || position.x > 122 || position.y < -100 || position.y > 182)
            return false;
        return true;
    }


};
#endif //RAYLIB_STG_BOSS1SMALLBULLETS_H