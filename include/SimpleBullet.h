//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET_H
#define RAYLIB_STG_SIMPLEBULLET_H
#include "Bullet.h"


class SimpleBullet : public Bullet {
public:
    SimpleBullet(Vector2 pos);
private:
    static const float radius;
    Vector2 position{};

};


#endif //RAYLIB_STG_SIMPLEBULLET_H