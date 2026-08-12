//
// Created by g on 04/02/2026.
//

#ifndef RAYLIB_STG_STEPTHINKER_H
#define RAYLIB_STG_STEPTHINKER_H
#include <iostream>

#include "raylib/raylib.h"


class StepThinker {
public:
    virtual ~StepThinker() = default;
    virtual void doPreStep(){};
    virtual bool doPhysics()
    {
        return true;
    };
    virtual void doPostStep(){}
    virtual Vector2 GetPosition()
    {
        std::cout << "!!! StepThinker::getPosition() always returns {0, 0} !";
        return Vector2{};
    }
};


#endif //RAYLIB_STG_STEPTHINKER_H