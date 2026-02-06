//
// Created by g on 04/02/2026.
//

#include "../include/StepThinker.h"

#include <iostream>
#include <ostream>

#include "GlobalVariables.h"
#include "PhysicsObject.h"

/*private StepThinker::StepThinker(std::vector<std::unique_ptr<GameObject> > vector) {
    vector.push_back(std::make_unique<StepThinker>(this));
}*/


void StepThinker::PreStep() {
};

void StepThinker::doPhysics(Vector2 playerPosition) {

}
