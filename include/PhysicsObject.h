//
// Created by g on 06/02/2026.
//

#ifndef RAYLIB_STG_PHYSICSOBJECT_H
#define RAYLIB_STG_PHYSICSOBJECT_H
#include "GameObject.h"
#include "raylib.h"


class PhysicsObject{
public:
    virtual ~PhysicsObject() = default;

    virtual void doPhysics(Vector2 playerPosition) = 0;
};


#endif //RAYLIB_STG_PHYSICSOBJECT_H