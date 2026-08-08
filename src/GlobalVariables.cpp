//
// Created by g on 10/02/2026.
//

#include "GlobalVariables.h"

#include "Boss1Phase1.h"
#include "DiagonalTankPhase1.h"
#include "Phase2.h"
#include "PhaseHelper.h"
#include "TestPhase1.h"

std::unique_ptr<PhaseHelper> GlobalVariables::currentPhase = nullptr;
const std::array<PhaseRef, PHASE_COUNT> GlobalVariables::phases = {{
    {[]() -> PhaseHelper* { return new DiagonalTankPhase1(); }},
    {[]() -> PhaseHelper* { return new Phase2(); }},
    {[]() -> PhaseHelper* { return new Boss1Phase1(); }},
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


