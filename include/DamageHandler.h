//
// Created by g on 09/02/2026.
//

#ifndef RAYLIB_STG_DAMAGEHANDLER_H
#define RAYLIB_STG_DAMAGEHANDLER_H
#include <algorithm>

#include "GlobalVariables.h"
#include "GrazeConstants.h"
#include "PhaseHelper.h"
#include "Player.h"
#include "PlayerHandler.h"
#include "ScoreHandler.h"
#include "SoundHandler.h"

inline int hitsTaken = 0;
class DamageHandler {
private:
    static const int mercyInvincibilityDuration = 60;
    static int stepHit;
    public:

    static void hitPlayer() {
        if (GlobalVariables::currentStep() - stepHit < mercyInvincibilityDuration)
            return;
        stepHit = GlobalVariables::currentStep();
        hitsTaken++;
        PlayerHandler::GetPlayer()->getHit();
        GlobalVariables::getCurrentPhase()->hitPlayer();
    }

    static int getHitsTaken() {
        return hitsTaken;
    }

    static void grazePlayer() {
        ScoreHandler::addScore(5);
        currentGrazeMetre = std::min(currentGrazeMetre + 20, maxGrazeMetre);
    }

    static void grazePlayer(const int i) {
        ScoreHandler::addScore(std::floor(i / 4) * ScoreHandler::getMultiplier());
        if (currentGrazeMetre >= maxGrazeMetre)
        {
            SoundHandler::PlayAnySound({PLAYER_GRAZE_1, PLAYER_GRAZE_2}, true, 0);
            return;
        }
        if (currentGrazeMetre + i < maxGrazeMetre)
        {
            SoundHandler::PlayAnySound({PLAYER_GRAZE_1, PLAYER_GRAZE_2}, true, 0);
            currentGrazeMetre = currentGrazeMetre + i;
            return;
        }
        currentGrazeMetre = maxGrazeMetre;
        SoundHandler::PlaySound(PLAYER_HYPER_3, false, 0);
    }
};
#endif //RAYLIB_STG_DAMAGEHANDLER_H