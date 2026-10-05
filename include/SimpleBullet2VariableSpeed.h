//
// Created by n on 04/10/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET2VARIABLESPEED_H
#define RAYLIB_STG_SIMPLEBULLET2VARIABLESPEED_H
#include "SimpleBullet2.h"

class SimpleBullet2VariableSpeed : public SimpleBullet2
{
protected:
    float speed = 1;
public:
    SimpleBullet2VariableSpeed(const Vector2 pos = {}, const Vector2 dir = {}, const Color col = YELLOW) : SimpleBullet2(pos, dir, col)
    {

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
    };

    bool doPhysics() override
    {
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer()->GetPosition(), PlayerHandler::GetPlayer()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        position = Vector2Add(position, direction * speed);
        if (position.x < -6 || position.x > 126 || position.y < -100 || position.y > 186)
            return false;
        SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_BULLET_LOW, .col = color});
        return true;
    }
};
#endif //RAYLIB_STG_SIMPLEBULLET2VARIABLESPEED_H