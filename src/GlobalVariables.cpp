//
// Created by g on 10/02/2026.
//

#include "GlobalVariables.h"

#include "Boss1Phase1.h"
#include "Boss1Phase2.h"
#include "Boss1Phase3.h"
#include "Boss1Phase4.h"
#include "Boss1Phase5.h"
#include "DiagonalTankPhase1.h"
#include "Phase2.h"
#include "PhaseHelper.h"

std::unique_ptr<PhaseHelper> GlobalVariables::currentPhase = nullptr;
RenderTexture2D GlobalVariables::renderTexture = {};
int GlobalVariables::renderTextureFilter = 0;
int GlobalVariables::effectVolume = 100;
int GlobalVariables::screenRotation = 0;
int GlobalVariables::zoomFactor = 1;
const std::array<PhaseRef, PHASE_COUNT> GlobalVariables::phases = {{
    {[]() -> PhaseHelper* { return new DiagonalTankPhase1(); }},
    {[]() -> PhaseHelper* { return new Phase2(); }},
    {[]() -> PhaseHelper* { return new Boss1Phase1(); }},
    {[]() -> PhaseHelper* { return new Boss1Phase2(); }},
    {[]() -> PhaseHelper* { return new Boss1Phase3(); }},
    {[]() -> PhaseHelper* { return new Boss1Phase4(); }},
    {[]() -> PhaseHelper* { return new Boss1Phase5(); }},
    }};

PhaseRef GlobalVariables::getPhase(const PHASES _index)
{
    return phases[_index];
}

uint_fast32_t& GlobalVariables::currentStep() {
    static uint_fast32_t currentStep = 0;
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


