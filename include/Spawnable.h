//
// Created by g on 13/02/2026.
//

#ifndef RAYLIB_STG_SPAWNABLE_H
#define RAYLIB_STG_SPAWNABLE_H
#include "StepThinker.h"

class Spawnable : public StepThinker {
    public:
    virtual void spawn(Vector2 _position) = 0;
};

#endif //RAYLIB_STG_SPAWNABLE_H