//
// Created by g on 04/02/2026.
//

#include "../include/StepThinker.h"

#include <array>
#include <iostream>
#include <ostream>

#include "GlobalVariables.h"

/*private StepThinker::StepThinker(std::vector<std::unique_ptr<GameObject> > vector) {
    vector.push_back(std::make_unique<StepThinker>(this));
}*/


void StepThinker::doPreStep() {
};

bool StepThinker::doPhysics(std::array<Vector2, 2> playerPosAndMovement) {
    return true;
}
