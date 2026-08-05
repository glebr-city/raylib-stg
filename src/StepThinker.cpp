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

Vector2 StepThinker::GetPosition() {
    std::cout << "!!! StepThinker::getPosition() always returns {0, 0} !";
    return Vector2{};
}

bool StepThinker::doPhysics() {
    return true;
}

