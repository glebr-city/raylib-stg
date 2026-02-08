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
    virtual void PreStep();
    virtual void doPhysics(std::array<Vector2, 2> playerPosAndMovement);
};


#endif //RAYLIB_STG_STEPTHINKER_H