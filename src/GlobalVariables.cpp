//
// Created by g on 10/02/2026.
//

#include "GlobalVariables.h"

#include "PhaseHelper.h"
std::unique_ptr<PhaseHelper> GlobalVariables::currentPhase = nullptr;
std::unique_ptr<PoolingVector<PlayerBullet>> GlobalVariables::playerBullets = std::make_unique<PoolingVector<PlayerBullet>>(50);
int& GlobalVariables::currentStep() {
    static int currentStep = 0;
    return currentStep;
}

int& GlobalVariables::gameHeight() {
    static int gameHeight = 180;
    return gameHeight;
}

 int& GlobalVariables::gameWidth() {
    static int gameWidth = 120;
    return gameWidth;
}

 const int& GlobalVariables::grazeRadius() {
    static constexpr int grazeRadius = 11;
    return grazeRadius;
}

 void GlobalVariables::setCurrentPhase(std::unique_ptr<PhaseHelper> newPhase) {
    currentPhase.swap(newPhase);
}

void GlobalVariables::spawnPlayerBullet(Vector2 pos) {
    playerBullets->spawn()->spawn(pos);
}

