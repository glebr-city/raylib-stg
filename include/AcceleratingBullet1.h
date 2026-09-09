//
// Created by n on 09/09/2026.
//

#ifndef RAYLIB_STG_ACCELERATINGBULLET1_H
#define RAYLIB_STG_ACCELERATINGBULLET1_H
#include "raylib.h"
#include "SimpleBullet.h"

class AcceleratingBullet1 : public SimpleBullet{
protected:
    static constexpr float radius = 3;
    float speed = 1;
    int grazeValue = 40;
    static constexpr ANIMATED_SPRITES sprite = BULLET_1_MONOCHROME;
    Vector2 direction{};

public:
    using StepThinker::doPhysics;
    AcceleratingBullet1(const Vector2 _pos = {}, const uint _grazeValue = 40) : SimpleBullet(_grazeValue, _pos, sprite, LAYER_BULLET_LOW), grazeValue(20)
    {
        grazeValue = _grazeValue;
    };

    AcceleratingBullet1(const Vector2 pos, const Vector2 dir, const Color col = GREEN, const uint _grazeValue = 40) : SimpleBullet(grazeValue, pos)
    {
        direction = dir;
        color = col;
        grazeValue = _grazeValue;
    }
    void spawn(const Vector2 pos, const Vector2 dir, const Color col = GREEN, const float _speed = 1)
    {
        position = pos;
        direction = dir;
        speed = _speed;
        hasBeenGrazed = false;
        color = col;
    }
    void doPreStep() override
    {}
    bool doPhysics() override
    {
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer().get()->GetPosition(), PlayerHandler::GetPlayer().get()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        speed += 0.0125f;
        position = Vector2Add(position, direction * speed);
        if (position.x < -2 || position.x > 122 || position.y < -1000 || position.y > 182)
            return false;
        return true;
    }
};
#endif //RAYLIB_STG_ACCELERATINGBULLET1_H