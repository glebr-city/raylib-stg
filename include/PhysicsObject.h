//
// Created by g on 06/02/2026.
//

#ifndef RAYLIB_STG_PHYSICSOBJECT_H
#define RAYLIB_STG_PHYSICSOBJECT_H
#include "GameObject.h"
#include "raylib.h"


class PhysicsObject : public GameObject {
public:
    ~PhysicsObject() override = delete;

private:
    virtual void doPhysics(Vector2 playerPos);
};


#endif //RAYLIB_STG_PHYSICSOBJECT_H