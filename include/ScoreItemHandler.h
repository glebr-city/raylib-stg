//
// Created by g on 14/02/2026.
//

#ifndef RAYLIB_STG_SCOREITEMHANDLER_H
#define RAYLIB_STG_SCOREITEMHANDLER_H
#include "Player.h"
#include "PoolingVector.h"
#include "ScoreItem.h"

class ScoreItemHandler {
private:
    static PoolingVector<ScoreItem> scoreItemPool;

    public:

    static void doPreStep() {
        scoreItemPool.doPreStep();
    }

    static void doPhysics(Player* player) {
        const std::array<Vector2, 2> playerPosAndMovement = player->getPosAndMovement();
        scoreItemPool.doPhysics(playerPosAndMovement);
    }
    static void spawn(const Vector2 _position) {
        scoreItemPool.spawn()->spawn(_position);
    }
    static void spawn(const Vector2 _position, const int _value) {
        scoreItemPool.spawn()->spawn(_position, static_cast<int>(floor(_value * ScoreHandler::getMultiplier())));
    }


};
#endif //RAYLIB_STG_SCOREITEMHANDLER_H