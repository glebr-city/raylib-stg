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
    static constexpr int mercyInvincibilityDuration = 60;
    static uint_fast32_t stepHit;
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


    static void grazePlayer(int i) {
        ScoreHandler::addScore(static_cast<u_int>(i * 0.25 * ScoreHandler::getMultiplier()));
        if (PlayerHandler::GetPlayer()->GetHyperOn())
            i = static_cast<int>(i * 0.5f);
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

    static void Reset()
    {
        stepHit = UINT_FAST32_MAX;
    }
};
#endif //RAYLIB_STG_DAMAGEHANDLER_H