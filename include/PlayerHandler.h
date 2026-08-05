//
// Created by n on 05/08/2026.
//

#ifndef RAYLIB_STG_PLAYERHANDLER_H
#define RAYLIB_STG_PLAYERHANDLER_H
#include <memory>

#include "Player.h"

class PlayerHandler
{
private:
    static std::shared_ptr<Player> player;
    public:
    static std::shared_ptr<Player> GetPlayer()
    {
        return player;
    }

    static void SetPlayer(const std::shared_ptr<Player>& p)
    {
        player = std::move(p);
    }
};
#endif //RAYLIB_STG_PLAYERHANDLER_H