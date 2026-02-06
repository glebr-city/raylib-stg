//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET_H
#define RAYLIB_STG_SIMPLEBULLET_H
#include "Bullet.h"


class SimpleBullet : public Bullet {
public:
    SimpleBullet(Vector2 pos);
    void doPhysics(Vector2 playerPos) override;
private:
    static constexpr float radius = 0.5f;
    Vector2 position{};

};


#endif //RAYLIB_STG_SIMPLEBULLET_H