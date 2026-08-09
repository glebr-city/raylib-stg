//
// Created by g on 06/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET2_H
#define RAYLIB_STG_SIMPLEBULLET2_H
#include "Bullet.h"
#include "SimpleBullet1.h"


class SimpleBullet2 : public SimpleBullet {
public:
    SimpleBullet2()
    {
        position = {};
        direction = {};
    }

    SimpleBullet2(Vector2 pos, Vector2 dir);

    SimpleBullet2(Vector2 pos, Vector2 dir, Color col);

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
    void spawn(Vector2 pos, Vector2 dir);

    void spawn(Vector2 pos, Vector2 dir, Color col);

    void doPreStep() override;


protected:
    static constexpr float radius = 1.15f;
    static constexpr ANIMATED_SPRITES sprite = BULLET_SMALL_MONOCHROME;
    Vector2 direction{};
    Color color = WHITE;
    static constexpr float speed = 2;
    static constexpr int grazeValue = 30;

};


#endif //RAYLIB_STG_SIMPLEBULLET2_H