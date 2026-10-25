//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET1_H
#define RAYLIB_STG_SIMPLEBULLET1_H
#include "SimpleBullet.h"
#include "raylib/raylib.h"


class SimpleBullet1 : public SimpleBullet{
protected:
    static constexpr float radius = 3;
    static constexpr float speed = 100;
    u_int grazeValue = 20;
    static constexpr ANIMATED_SPRITES sprite = BULLET_1_MONOCHROME;
    Vector2 direction{};

public:
    using StepThinker::doPhysics;
    SimpleBullet1(const Vector2 _pos = {}, const u_int _grazeValue = 20) : SimpleBullet(_grazeValue, _pos, sprite, LAYER_BULLET_LOW)
    {
        grazeValue = _grazeValue;
    };

    SimpleBullet1(const Vector2 pos, const Vector2 dir, const Color col = GREEN, const uint _grazeValue = 20) : SimpleBullet(_grazeValue, pos)
    {
        direction = dir;
        color = col;
        grazeValue = _grazeValue;
    }
    void spawn(const Vector2 pos, const Vector2 dir, const Color col = GREEN)
    {
        position = pos;
        direction = dir;
        hasBeenGrazed = false;
        color = col;
        SetStartOfTickPos();
    }
    void doPreStep() override
    {}
    bool doPhysics() override
    {
        position = Vector2Add(position, direction * speed);
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer().get()->GetPosition(), PlayerHandler::GetPlayer().get()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        if (position.x < -2 || position.x > 122 || position.y < -1000 || position.y > 182)
            return false;
        return true;
    }
};


#endif //RAYLIB_STG_SIMPLEBULLET1_H