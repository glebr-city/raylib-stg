//
// Created by g on 04/02/2026.
//

#ifndef RAYLIB_STG_STEPTHINKER_H
#define RAYLIB_STG_STEPTHINKER_H
#include <memory>
#include <vector>

#include <GameObject.h>

#include "raylib.h"

class StepThinker : public GameObject{
public:
    virtual void doPreStep();
    virtual bool doPhysics(std::array<Vector2, 2> playerPosAndMovement);
    virtual bool doPhysics();
    virtual Vector2 getPosition();
};


#endif //RAYLIB_STG_STEPTHINKER_H