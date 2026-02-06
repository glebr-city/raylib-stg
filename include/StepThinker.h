//
// Created by g on 04/02/2026.
//

#ifndef RAYLIB_STG_STEPTHINKER_H
#define RAYLIB_STG_STEPTHINKER_H
#include "GameObject.h"
#include "raylib.h"

class StepThinker : public GameObject{
public:
    virtual ~StepThinker() = default;

    virtual void PreStep();
    //virtual void doPhysics(Vector2 playerPos);
};


#endif //RAYLIB_STG_STEPTHINKER_H