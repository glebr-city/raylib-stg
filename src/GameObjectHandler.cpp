//
// Created by g on 06/02/2026.
//

#include <GameObjectHandler.h>

#include <memory>
#include <vector>

#include "PhysicsObject.h"
#include "Player.h"
#include "StepThinker.h"

std::vector<std::unique_ptr<StepThinker>> step_thinkers;

GameObjectHandler::GameObjectHandler(int _stepCount) {
    step_thinkers = std::vector<std::unique_ptr<StepThinker>>();
    stepCount = _stepCount;
}

GameObjectHandler::~GameObjectHandler() = default;

void GameObjectHandler::addStepThinker(std::unique_ptr<StepThinker> thinker) {
    step_thinkers.push_back(std::move(thinker));
}


void GameObjectHandler::doPreStep(Player player) {
    player.PreStep();
    for (auto& step_thinker : step_thinkers) {
        step_thinker->PreStep();
    }
}

void GameObjectHandler::doPhysics(Player player, Vector2 playerPosition) {
    for (int i = 0; i < stepCount; i++) {
        player.doPhysics(playerPosition);
        playerPosition = player.getPosition();
        for (auto& step_thinker : step_thinkers ) {
            //for (int i = 0; i < stepCount; i++)
                step_thinker->doPhysics(playerPosition);
        }
    }
}

int GameObjectHandler::getObjectCount() {
    return step_thinkers.size();
}
