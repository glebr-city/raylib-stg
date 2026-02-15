//
// Created by g on 09/02/2026.
//

#ifndef RAYLIB_STG_DAMAGEHANDLER_H
#define RAYLIB_STG_DAMAGEHANDLER_H
#include <algorithm>

#include "GlobalVariables.h"
#include "GrazeConstants.h"
#include "Player.h"

static Player* player;
inline int hitsTaken = 0;
class DamageHandler {
private:
    public:
    static void setPlayer(Player* _player) {
        player = _player;
    }

    static void hitPlayer() {
        hitsTaken++;
        player->getHit();
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
        currentGrazeMetre = std::min(currentGrazeMetre + i, maxGrazeMetre);
    }
};
#endif //RAYLIB_STG_DAMAGEHANDLER_H