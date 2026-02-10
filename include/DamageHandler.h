//
// Created by g on 09/02/2026.
//

#ifndef RAYLIB_STG_DAMAGEHANDLER_H
#define RAYLIB_STG_DAMAGEHANDLER_H
#include <algorithm>

#include "Player.h"

static Player* player;
inline int hitsTaken = 0;
inline int maxGrazeMetre = 10;
inline int currentGrazeMetre = 0;
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
    static int getGrazeMetre() {
        return currentGrazeMetre;
    }

    static void setGrazeMetre(int i) {
        currentGrazeMetre = i;
    }
};
#endif //RAYLIB_STG_DAMAGEHANDLER_H