//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET_H
#define RAYLIB_STG_SIMPLEBULLET_H
#include "Bullet.h"
#include "SpriteHandler.h"


class SimpleBullet : public Bullet {
public:
    SimpleBullet();
    SimpleBullet(Vector2 pos);

    void doPreStep();

    bool doPhysics(std::array<Vector2, 2> playerPosAndMovement) override;

    void spawn(Vector2 _position) override;

protected:
    static constexpr int grazeValue = 20;
    static constexpr float radius = 0.5f;
    ANIMATED_SPRITES sprite = BULLET_1_MONOCHROME;
protected:
    Vector2 position{};

};


#endif //RAYLIB_STG_SIMPLEBULLET_H