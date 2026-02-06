//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET_H
#define RAYLIB_STG_SIMPLEBULLET_H
#include "Bullet.h"
#include "SpriteHandler.h"


class SimpleBullet : public Bullet {
public:
    SimpleBullet(Vector2 pos);
    void doPhysics(Vector2 playerPos) override;
private:
    static constexpr float radius = 0.5f;
    Vector2 position{};
    ANIMATED_SPRITES sprite = BULLET_1_MONOCHROME;

};


#endif //RAYLIB_STG_SIMPLEBULLET_H