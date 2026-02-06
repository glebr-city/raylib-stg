//
// Created by g on 06/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET2_H
#define RAYLIB_STG_SIMPLEBULLET2_H
#include "Bullet.h"
#include "SimpleBullet1.h"


class SimpleBullet2 : public SimpleBullet {
public:
    SimpleBullet2(GameObjectHandler &handler, Vector2 pos, Vector2 dir);

    SimpleBullet2(GameObjectHandler &handler, const Vector2 pos, const Vector2 dir, Color col);

    void PreStep() override;

    void doPhysics(Vector2 playerPosition);

private:
    static constexpr float radius = 1;
    static constexpr float speed = 2;
    static constexpr ANIMATED_SPRITES sprite = BULLET_SMALL_MONOCHROME;
    Vector2 position{};
    Vector2 direction{};
    Color color = WHITE;

};


#endif //RAYLIB_STG_SIMPLEBULLET2_H