//
// Created by g on 08/02/2026.
//

#include "../include/TestPhase1.h"

#include <cmath>

#include "GlobalVariables.h"

TestPhase1::TestPhase1() : darkPurplePool(8000), simpleBullet1Pool(2000), orangePool(100), simpleBullet2Pool(100) {
    phasePools.push_back(&darkPurplePool);
    phasePools.push_back(&simpleBullet1Pool);
    phasePools.push_back(&orangePool);
    phasePools.push_back(&simpleBullet2Pool);
}

bool TestPhase1::doPhysics(Player* player) {
    if (currentStep() < 200)
        return true;
    std::array<Vector2, 2> playerPosAndMovement = player->getPosAndMovement();
    if (currentStep() % 9 == 0) {
        for (int i = -1; i < 121; i += 12) {
            if (currentStep() % 240 < 120) {
                if (i < ((currentStep() % 120) + 16) && (i > (currentStep() % 120) - 16))
                    continue;
            } else if (i <= (120 - (currentStep() % 120) + 16) && (i >= 120 - (currentStep() % 120) - 16))
                continue;
            darkPurplePool.spawn()->spawn(Vector2 {static_cast<float>(i), 0}, Vector2{0,1}, DARKPURPLE);
            darkPurplePool.spawn()->spawn(Vector2 {static_cast<float>(i+6), -6}, Vector2{0,1}, DARKPURPLE);
        }
    }
    /*simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 120), 0}, Vector2{0,1});
    simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 120), -4}, Vector2{0,1}, DARKGREEN);
    simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 120), 0}, Vector2{0,1});
    simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 120), -4}, Vector2{0,1}, DARKGREEN);*/

    if (currentStep() % 40 == 0) {
        float tempY = static_cast<float>((currentStep() % 20) / 10);
        orangePool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 100), tempY-8}, Vector2{-0.4, 0.91652}, ORANGE);
        simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 100), tempY-4}, Vector2{-0.4, 0.91652}, YELLOW);
        orangePool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 100) + 15, tempY-8}, Vector2{-0.4, 0.91652}, ORANGE);
        simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 100) + 15, tempY-12}, Vector2{-0.4, 0.91652}, YELLOW);
        simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 100) + 30, tempY-20}, Vector2{0, 1}, GREEN);
        simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 100) + 30, tempY-16}, Vector2{0, 1}, DARKGREEN);

        simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 100), tempY-12}, Vector2{0.4, 0.91652}, YELLOW);
        orangePool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 100), tempY-8}, Vector2{0.4, 0.91652}, ORANGE);
        simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 100) - 15, tempY-12}, Vector2{0.4, 0.91652}, YELLOW);
        orangePool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 100) - 15, tempY-8}, Vector2{0.4, 0.91652}, ORANGE);
        simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 100) - 30, tempY-20}, Vector2{0, 1}, GREEN);
        simpleBullet2Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 100) - 30, tempY-16}, Vector2{0, 1}, DARKGREEN);
    }
    for (auto pooling_vector: phasePools) {
        pooling_vector->doPhysics(playerPosAndMovement);
    }
    return true;
}
