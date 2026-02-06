//
// Created by g on 06/02/2026.
//

#ifndef RAYLIB_STG_GAMEOBJECTHANDLER_H
#define RAYLIB_STG_GAMEOBJECTHANDLER_H
#include <memory>
#include <vector>

#include "Player.h"
#include "raylib.h"


class PhysicsObject;
class StepThinker;

class GameObjectHandler {
private:
    std::vector<std::unique_ptr<StepThinker>> step_thinkers;
    int stepCount = 1;
public:
    GameObjectHandler(int _stepCount);
    virtual ~GameObjectHandler();
    void addStepThinker(std::unique_ptr<StepThinker> thinker);
    void doPreStep(Player player);
    void doPhysics(Player player, Vector2 playerPosition);
    int getObjectCount();
};


#endif //RAYLIB_STG_GAMEOBJECTHANDLER_H