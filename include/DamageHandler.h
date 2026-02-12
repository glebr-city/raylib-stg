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
    }

    static int getHitsTaken() {
        return hitsTaken;
    }

    static void grazePlayer() {
        currentGrazeMetre = std::min(currentGrazeMetre + 20, maxGrazeMetre);
    }

    static void grazePlayer(int i) {
        currentGrazeMetre = std::min(currentGrazeMetre + i, maxGrazeMetre);
    }
};
#endif //RAYLIB_STG_DAMAGEHANDLER_H