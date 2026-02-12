//
// Created by g on 08/02/2026.
//

#include "../include/TestPhase1.h"

#include <cmath>

#include "GlobalVariables.h"

TestPhase1::TestPhase1() : PhaseHelper(phasePools), phasePools(), movingDarkPurplePool(200), darkPurplePool(400) {
    phasePools.push_back(&movingDarkPurplePool);
    phasePools.push_back(&darkPurplePool);
}

bool TestPhase1::doPhysics(Player* player) {
    if (GlobalVariables::currentStep() < 50)
        return true;
    std::array<Vector2, 2> playerPosAndMovement = player->getPosAndMovement();
    Color tempColour = Color {130, 20, 130, 255};
    Color tempColour2 = Color {180, 80, 180, 255};
    Color* currentColour = &tempColour;
    if (GlobalVariables::currentStep() % 150 == 0) {
        for (int y = -1; y > -9; y--) {
            for (int i = 0; i < 9; i++) {
                if (i == -y || i == -y-1)
                    continue;
                if (i == -y + 1 || i == -y - 2)
                    currentColour = &tempColour2;
                else {
                    movingDarkPurplePool.spawn()->spawn(Vector2 {static_cast<float>(i * 15 + 10), static_cast<float>(y*15)}, Vector2{0.07, 0.997547}, DARKPURPLE);
                    movingDarkPurplePool.spawn()->spawn(Vector2 {120-static_cast<float>(i * 15 + 4 + y), static_cast<float>(y*15-120)}, Vector2{-0.07, 0.997547}, DARKPURPLE);
                    //Decorative bullets below
                    movingDarkPurplePool.spawn()->spawn(Vector2 {static_cast<float>(i * 15 + 10), static_cast<float>(y*15)}, Vector2{-0.02,0.9998}, DARKPURPLE);
                    movingDarkPurplePool.spawn()->spawn(Vector2 {120-static_cast<float>(i * 15 + 4 + y), static_cast<float>(y*15-120)}, Vector2{-0.02,0.9998}, DARKPURPLE);
                }

                darkPurplePool.spawn()->spawn(Vector2 {static_cast<float>(i * 15), static_cast<float>(y*15)}, Vector2{0, 1}, *currentColour);
                darkPurplePool.spawn()->spawn(Vector2 {static_cast<float>(i * 15 + 8), static_cast<float>(y*15-8)}, Vector2{0, 1}, *currentColour);
                darkPurplePool.spawn()->spawn(Vector2 {120-static_cast<float>(i * 15), static_cast<float>(y*15-120)}, Vector2{0, 1}, *currentColour);
                darkPurplePool.spawn()->spawn(Vector2 {120-static_cast<float>(i * 15 - 8), static_cast<float>(y*15-112)}, Vector2{0, 1}, *currentColour);

                currentColour = &tempColour;

            }
        }
    }
    if (false) {
        for (int i = 0; i < 9; i++) {
            if (i >= GlobalVariables::currentStep() % 8 - 1 && i <= GlobalVariables::currentStep() % 8 + 1)
                continue;
            darkPurplePool.spawn()->spawn(Vector2 {static_cast<float>(i * 16), 0}, Vector2{0, 1}, tempColour);
            darkPurplePool.spawn()->spawn(Vector2 {static_cast<float>(i * 16 + 8), -8}, Vector2{0, 1}, tempColour);
        }
        darkPurplePool.spawn()->spawn(Vector2 {0, 180 - static_cast<float>(GlobalVariables::currentStep() % 8) * 3}, Vector2{1, 0}, tempColour);
    }
    //darkPurplePool.spawn()->spawn(Vector2 {120, 180 - static_cast<float>(currentStep() % 8 * 3)}, Vector2{-1, 0}, tempColour);
    /*simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 120), 0}, Vector2{0,1});
    simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(currentStep() % 120), -4}, Vector2{0,1}, DARKGREEN);
    simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 120), 0}, Vector2{0,1});
    simpleBullet1Pool.spawn()->spawn(Vector2 {static_cast<float>(120 - currentStep() % 120), -4}, Vector2{0,1}, DARKGREEN);*/
    for (auto pooling_vector: phasePools) {
        pooling_vector->doPhysics(playerPosAndMovement);
    }
    return true;
}
