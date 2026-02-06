//
// Created by g on 06/02/2026.
//

#include <GameObjectHandler.h>

#include <memory>
#include <vector>

#include "PhysicsObject.h"
#include "StepThinker.h"

std::vector<std::unique_ptr<StepThinker>> step_thinkers;

GameObjectHandler::GameObjectHandler() {
    step_thinkers = std::vector<std::unique_ptr<StepThinker>>();
}

GameObjectHandler::~GameObjectHandler() = default;

void GameObjectHandler::addStepThinker(std::unique_ptr<StepThinker> thinker) {
    step_thinkers.push_back(std::move(thinker));
}


void GameObjectHandler::doPreStep() {
    for (auto& step_thinker : step_thinkers) {
        step_thinker->PreStep();
    }
}

void GameObjectHandler::doPhysics(Vector2 playerPosition) {
    for (auto& step_thinker : step_thinkers ) {
        step_thinker->doPhysics(playerPosition);
    }
}

int GameObjectHandler::getObjectCount() {
    return step_thinkers.size();
}
