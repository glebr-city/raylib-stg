//
// Created by g on 06/02/2026.
//

#include <array>
#include <GameObjectHandler.h>
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


void GameObjectHandler::doPreStep(Player player) {
    player.PreStep();
    for (auto& step_thinker : step_thinkers) {
        step_thinker->PreStep();
    }
}


void GameObjectHandler::doPhysics(Player player) {
        std::array<Vector2, 2> playerPosAndMovement = player.getPosAndMovement();
        for (auto& step_thinker : step_thinkers ) {
            step_thinker->doPhysics(playerPosAndMovement);
        }
        player.doPhysics();
}

int GameObjectHandler::getObjectCount() {
    return step_thinkers.size();
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
