//
// Created by g on 06/02/2026.
//

#ifndef RAYLIB_STG_GAMEOBJECTHANDLER_H
#define RAYLIB_STG_GAMEOBJECTHANDLER_H
#include <memory>
#include <vector>

#include "../../include/Player.h"
#include "../../include/PoolingVector.h"
#include "../../include/raylib.h"


class PhysicsObject;
class StepThinker;

class GameObjectHandler {
private:
    std::vector<IPoolingVector*> poolingVectors;
public:
    GameObjectHandler();
    virtual ~GameObjectHandler();
    void addStepThinker(std::unique_ptr<StepThinker> thinker);
    void doPreStep(Player player);
    void doPhysics(Player player);
    int getObjectCount();
    void clearStepThinkers();

    template<class T>
    void addPoolingVector(PoolingVector<T> *poolingVector);

    void removeStepThinkers(int number);
};


#endif //RAYLIB_STG_GAMEOBJECTHANDLER_H