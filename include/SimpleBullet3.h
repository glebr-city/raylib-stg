//
// Created by n on 30/07/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET3_H
#define RAYLIB_STG_SIMPLEBULLET3_H
#include "SimpleBullet.h"

class SimpleBullet3 : public SimpleBullet
{
private:
    static constexpr float radius = 1.5f;
    static constexpr float speed = 1.25f;
    static constexpr int grazeValue = 40;
    static constexpr ANIMATED_SPRITES sprite = SPINNING_ROD_MONOCHROME;
    Vector2 direction{};
    Color color = WHITE;

public:
    using StepThinker::doPhysics;

    SimpleBullet3(const Vector2 pos = {}, const Vector2 dir = {}, const Color col = RED) : SimpleBullet(pos, sprite, col)
    {
        direction = dir;
    }
    void spawn(const Vector2 _pos, const Vector2 _dir, const Color _col = RED)
    {
        direction = _dir;
        color = _col;
        SimpleBullet::spawn(_pos);
    };
    bool doPhysics() override
    {
        if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer().get()->GetPosition(), PlayerHandler::GetPlayer().get()->GetFinalPos(), grazeValue)) {
            DamageHandler::hitPlayer();
            return false;
        }
        position = Vector2Add(position, direction * speed);
        if (position.x < -2 || position.x > 122 || position.y < -1000 || position.y > 182)
            return false;
        SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_BULLET, .col = color});
        return true;
    }
};
#endif //RAYLIB_STG_SIMPLEBULLET3_H