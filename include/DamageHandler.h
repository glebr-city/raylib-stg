//
// Created by g on 09/02/2026.
//

#ifndef RAYLIB_STG_DAMAGEHANDLER_H
#define RAYLIB_STG_DAMAGEHANDLER_H
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
        std::cout << "Hit taken? " << getHitsTaken() << std::endl;
    }

    static int getHitsTaken() {
        return hitsTaken;
    }
};
#endif //RAYLIB_STG_DAMAGEHANDLER_H