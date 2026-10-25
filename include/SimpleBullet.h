//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET_H
#define RAYLIB_STG_SIMPLEBULLET_H
#include "Bullet.h"
#include "SpriteHandler.h"


class SimpleBullet : public Bullet {
public:
    explicit SimpleBullet(const u_int _scoreValue, const Vector2 pos = {}, const ANIMATED_SPRITES _sprite = BULLET_1_MONOCHROME, const LAYERS _layer = LAYER_BULLET, const Color _col = WHITE) : Bullet(_scoreValue, pos)
    {
        sprite = _sprite;
        layer = _layer;
        color = _col;
    };


    bool doPhysics() override
    {
        const std::shared_ptr<Player> player = PlayerHandler::GetPlayer();
        return !CheckCollisionCircleLine(position, radius, player->GetPosition(), player->GetFinalPos());
    }

    void doPostStep() override
    {
        SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos= position, .l = layer, .col = color});
    }

    void spawn(const Vector2 _position) override
    {
        position = _position;
        SetStartOfTickPos();
        hasBeenGrazed = false;
    }

    Vector2 GetPosition() override
    {
        return position;
    }




protected:
    static constexpr float radius = 0.5f;
    ANIMATED_SPRITES sprite = BULLET_1_MONOCHROME;
    Color color = GREEN;
    LAYERS layer = LAYER_BULLET;

};


#endif //RAYLIB_STG_SIMPLEBULLET_H