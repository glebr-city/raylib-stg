//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_BULLET_H
#define RAYLIB_STG_BULLET_H
#include "raylib.h"
#include "StepThinker.h"


class Bullet  : public StepThinker{
public:
 Bullet(Vector2 pos);
private:
 static const float radius;
 Vector2 position{};

};


#endif //RAYLIB_STG_BULLET_H