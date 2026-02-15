//
// Created by g on 10/02/2026.
//

#include "GlobalVariables.h"

#include "PhaseHelper.h"
#include "PlayerBullet.h"
std::unique_ptr<PhaseHelper> GlobalVariables::currentPhase = nullptr;
int& GlobalVariables::currentStep() {
    static int currentStep = 0;
    return currentStep;
}


 void GlobalVariables::setCurrentPhase(std::unique_ptr<PhaseHelper> newPhase) {
    currentPhase = std::move(newPhase);
}


