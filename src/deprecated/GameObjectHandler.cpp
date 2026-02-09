//
// Created by g on 06/02/2026.
//

#include <array>
#include <deprecated/GameObjectHandler.h>
#include <iostream>

#include <memory>
#include <vector>

#include "Player.h"
#include "StepThinker.h"

std::vector<std::unique_ptr<StepThinker>> step_thinkers;

GameObjectHandler::GameObjectHandler() {
    step_thinkers = std::vector<std::unique_ptr<StepThinker>>();
}

GameObjectHandler::~GameObjectHandler() = default;

void GameObjectHandler::addStepThinker(std::unique_ptr<StepThinker> thinker) {
    step_thinkers.push_back(std::move(thinker));
}

void GameObjectHandler::removeStepThinkers(int number) {
    int a = step_thinkers.size();
    number  = std::min(number, a);
    step_thinkers.erase(step_thinkers.begin(), step_thinkers.begin() + number - 1);

}

void GameObjectHandler::clearStepThinkers() {
    step_thinkers.clear();
    std::cout << step_thinkers.size();
}
template<typename T>
void GameObjectHandler::addPoolingVector(PoolingVector<T> *poolingVector) {
    poolingVectors.push_back(poolingVector);
}


void GameObjectHandler::doPreStep(Player player) {
    player.PreStep();
    for (PoolingVector *pooling_vector: poolingVectors) {
        int numActive = pooling_vector->getNumActive();
        std::vector<StepThinker> *thinker_vector = pooling_vector->getVector();
        /*for (int i = numActive - 1; i < pooling_vector->getVectorSize(); i++) { // This is where checks would go to see
            StepThinker *thinker = &thinker_vector->at(i);                        // if anything's reactivated, but we
            if (thinker->active) {                                                // should avoid such design!
                std::swap(thinker_vector[i], thinker_vector[numActive - 1]);
                continue;
            }*/
        for (int i = 0; i < numActive; i++) { // This is where checks would go to see
            thinker_vector->at(i).doPreStep();
        }
    }
}


void GameObjectHandler::doPhysics(Player player) {
    std::array<Vector2, 2> playerPosAndMovement = player.getPosAndMovement();
    for (PoolingVector *pooling_vector: poolingVectors) {
        int numActive = pooling_vector->getNumActive();
        std::vector<StepThinker> *thinker_vector = pooling_vector->getVector();
        for (int i = 0; i < numActive;) {
            StepThinker *thinker = &thinker_vector->at(i);
            thinker->doPhysics(playerPosAndMovement);
            if (!thinker->active) {
                std::swap(thinker_vector[i], thinker_vector[--numActive]);
                continue;
            }
            ++i;

        }
    }
    player.doPhysics();
}

int GameObjectHandler::getObjectCount() {
    return step_thinkers.size();
}
