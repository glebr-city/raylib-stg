//
// Created by g on 06/02/2026.
//

#ifndef RAYLIB_STG_GAMEOBJECTHANDLER_H
#define RAYLIB_STG_GAMEOBJECTHANDLER_H
#include <memory>
#include <vector>

#include "raylib.h"


class PhysicsObject;
class StepThinker;

class GameObjectHandler {
private:
    std::vector<std::unique_ptr<StepThinker>> step_thinkers;
public:
    GameObjectHandler();
    virtual ~GameObjectHandler();
    void addStepThinker(std::unique_ptr<StepThinker> thinker);
    void doPreStep();
    void doPhysics(Vector2 playerPosition);
    int getObjectCount();
};


#endif //RAYLIB_STG_GAMEOBJECTHANDLER_H