//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET1_H
#define RAYLIB_STG_SIMPLEBULLET1_H
#include "SimpleBullet.h"
#include "raylib/raylib.h"
#include "SimpleBullet.h"


class SimpleBullet1 : public SimpleBullet{
protected:
    static constexpr float radius = 3;
    static constexpr float speed = 1;
    uint grazeValue = 30;
    static constexpr ANIMATED_SPRITES sprite = BULLET_1_MONOCHROME;
    Vector2 direction{};

public:
    using StepThinker::doPhysics;
    SimpleBullet1(const Vector2 _pos = {}) : SimpleBullet(_pos, sprite, LAYER_BULLET_LOW) {};

    SimpleBullet1(const Vector2 pos, const Vector2 dir, const Color col = GREEN, const uint _grazeValue = 20) : SimpleBullet(pos)
    {
        direction = dir;
        color = col;
        grazeValue = _grazeValue;
    }
    virtual void spawn(const Vector2 pos, const Vector2 dir, const Color col = GREEN)
    {
        position = pos;
        direction = dir;
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
        position = Vector2Add(position, direction * speed);
        if (position.x < -2 || position.x > 122 || position.y < -1000 || position.y > 182)
            return false;
        //SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_BULLET_LOW, .col = color});
        return true;
    }
};


#endif //RAYLIB_STG_SIMPLEBULLET1_H