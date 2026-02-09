//
// Created by g on 08/02/2026.
//

#include "../include/TestPhase1.h"

#include "GlobalVariables.h"

TestPhase1::TestPhase1() : simpleBullet1Pool(10000), simpleBullet2Pool(10000) {
    phasePools.push_back(&simpleBullet1Pool);
    phasePools.push_back(&simpleBullet2Pool);
}

bool TestPhase1::doPhysics(Player* player) {
    std::array<Vector2, 2> playerPosAndMovement = player->getPosAndMovement();
    for (int i = -1; i < 182; i++) {
        if (i > 54 && i < 66) {
            continue;
        }
        simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(i), 0}, Vector2{0,1}, DARKPURPLE);
    }
    simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 120), 0}, Vector2{0,1});
    simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 120), -4}, Vector2{0,1}, DARKGREEN);
    simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 120), 0}, Vector2{0,1});
    simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 120), -4}, Vector2{0,1}, DARKGREEN);

    simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 120), -4}, Vector2{0,1}, YELLOW);
    simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 120), 0}, Vector2{0,1}, ORANGE);
    simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 120), -4}, Vector2{0,1}, YELLOW);
    simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 120), 0}, Vector2{0,1}, ORANGE);
    for (auto pooling_vector: phasePools) {
        pooling_vector->doPhysics(playerPosAndMovement);
    }
    return true;
}
