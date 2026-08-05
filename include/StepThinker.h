//
// Created by g on 04/02/2026.
//

#ifndef RAYLIB_STG_STEPTHINKER_H
#define RAYLIB_STG_STEPTHINKER_H
#include <vector>

#include "raylib.h"

class Player;

class StepThinker {
public:
    virtual ~StepThinker() = default;
    virtual void doPreStep();
    virtual bool doPhysics();
    virtual Vector2 GetPosition();
};


#endif //RAYLIB_STG_STEPTHINKER_H