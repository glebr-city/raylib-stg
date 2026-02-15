//
// Created by g on 13/02/2026.
//

#ifndef RAYLIB_STG_SPAWNABLE_H
#define RAYLIB_STG_SPAWNABLE_H
#include "StepThinker.h"

class Spawnable : public StepThinker {
protected:
    Vector2 position{};
    public:
    virtual void spawn(Vector2 _position) = 0;
    virtual void spawn(Vector2 _position, int _scoreValue) = 0;
    Vector2 getPosition() override {
        return position;
    }
};

#endif //RAYLIB_STG_SPAWNABLE_H