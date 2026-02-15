//
// Created by g on 10/02/2026.
//

#include "GlobalVariables.h"

#include <mutex>

#include "PhaseHelper.h"
#include "PlayerBullet.h"
std::unique_ptr<PhaseHelper> GlobalVariables::currentPhase = nullptr;
int& GlobalVariables::currentStep() {
    static int currentStep = 0;
    return currentStep;
}


 void GlobalVariables::setCurrentPhase(std::unique_ptr<PhaseHelper> newPhase) {
    /*static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);*/
    currentPhase = std::move(newPhase);
}


