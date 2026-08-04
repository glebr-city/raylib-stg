//
// Created by g on 10/02/2026.
//

#include "GlobalVariables.h"

#include "DiagonalTankPhase1.h"
#include "PhaseHelper.h"
#include "TestPhase1.h"

std::unique_ptr<PhaseHelper> GlobalVariables::currentPhase = nullptr;
const std::array<PhaseRef, PHASE_COUNT> GlobalVariables::phases = {{
    {"Diagonal Tank Ref", []() -> PhaseHelper* { return new DiagonalTankPhase1(); }},
    {"TestPhase1", []() -> PhaseHelper* { return new TestPhase1(); }},
    }};

PhaseRef GlobalVariables::getPhase(const PHASES _index)
{
    return phases[_index];
}

uint32_t& GlobalVariables::currentStep() {
    static uint32_t currentStep = 0;
    return currentStep;
}

void GlobalVariables::setCurrentPhase(const PHASES _desiredPhase)
{
    PhaseHelper* newPhase = getPhase(_desiredPhase).initPhase();
    currentPhase = std::unique_ptr<PhaseHelper>(newPhase);
}
 /*void GlobalVariables::setCurrentPhase(std::unique_ptr<PhaseHelper> newPhase) {
    currentPhase = std::move(newPhase);
}*/


