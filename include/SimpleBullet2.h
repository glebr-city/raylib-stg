//
// Created by g on 06/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET2_H
#define RAYLIB_STG_SIMPLEBULLET2_H
#include "Bullet.h"
#include "SimpleBullet1.h"


class SimpleBullet2 : public SimpleBullet {
public:

    void doPreStep() override{};

    SimpleBullet2(const Vector2 pos = {}, const Vector2 dir = {}, const Color col = YELLOW) : SimpleBullet(grazeValue, pos, sprite)
    {
        position = pos;
        direction = dir;
        color = col;
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

    void spawn(const Vector2 pos, const Vector2 dir, const Color col)
    {
        direction = dir;
        color = col;
        SimpleBullet::spawn(pos);
    }



protected:
    static constexpr float radius = 1.15f;
    static constexpr ANIMATED_SPRITES sprite = BULLET_SMALL_MONOCHROME;
    Vector2 direction{};
    static constexpr float speed = 2;
    static constexpr int grazeValue = 30;

};


#endif //RAYLIB_STG_SIMPLEBULLET2_H