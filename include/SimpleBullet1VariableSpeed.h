//
// Created by n on 15/10/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET1VARIABLESPEED_H
#define RAYLIB_STG_SIMPLEBULLET1VARIABLESPEED_H
#include "SimpleBullet1.h"

class SimpleBullet1VariableSpeed : public SimpleBullet1
{
protected:
    float speed = 1;
public:
    SimpleBullet1VariableSpeed(const Vector2 pos = {}, const Vector2 dir = {}, const Color col = YELLOW) : SimpleBullet1(pos, dir, col)
    {
        grazeValue = 40;
    }
    /*void spawn(Vector2 _position) override = 0;
    void spawn(Vector2 _position, u_int _scoreValue) override = 0;
    void spawn(const Vector2 pos, const Vector2 dir, const Color col) override = 0;*/

    void spawn(const float _speed, Vector2 pos, const Vector2 dir, const Color col)
    {
        speed = _speed;
        position = pos;
        direction = dir;
        color = col;
        SetStartOfTickPos();
    };

    bool doPhysics() override
    {
        position = Vector2Add(position, direction * speed);
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer()->GetPosition(), PlayerHandler::GetPlayer()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        if (position.x < -6 || position.x > 126 || position.y < -100 || position.y > 186)
            return false;
        SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_BULLET_LOW, .col = color});
        return true;
    }
};
#endif //RAYLIB_STG_SIMPLEBULLET1VARIABLESPEED_H