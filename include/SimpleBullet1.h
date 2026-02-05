//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET1_H
#define RAYLIB_STG_SIMPLEBULLET1_H
#include "raylib.h"
#include "SimpleBullet.h"


class SimpleBullet1 : public SimpleBullet{
    private:
    static constexpr float radius = 1;
    static constexpr float speed = 3.0f;
    Vector2 position;
    Vector2 direction;
public:
    SimpleBullet1(const Vector2 pos, const Vector2 dir);
private:
    void PreStep();
};


#endif //RAYLIB_STG_SIMPLEBULLET1_H