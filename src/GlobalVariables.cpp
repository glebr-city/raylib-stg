//
// Created by g on 10/02/2026.
//

#include "GlobalVariables.h"

#include <mutex>

#include "PhaseHelper.h"
std::unique_ptr<PhaseHelper> GlobalVariables::currentPhase = nullptr;
uint32_t& GlobalVariables::currentStep() {
    static uint32_t currentStep = 0;
    return currentStep;
}


 void GlobalVariables::setCurrentPhase(std::unique_ptr<PhaseHelper> newPhase) {
    currentPhase = std::move(newPhase);
}


