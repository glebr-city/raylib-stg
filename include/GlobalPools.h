//
// Created by n on 04/08/2026.
//

#ifndef RAYLIB_STG_GLOBALPOOLS_H
#define RAYLIB_STG_GLOBALPOOLS_H
#include <memory>
#include <vector>

#include "Player.h"
#include "PoolingVector.h"


class IPoolingVector;

class GlobalPools
{
private:
    static std::vector<std::shared_ptr<IPoolingVector>> pools;
public:
    static std::vector<std::shared_ptr<IPoolingVector>>* GetPools()
    {
        return &pools;
    }
    static void AddPools(std::vector<std::shared_ptr<IPoolingVector>> _phasePools)
    {
        pools.reserve(pools.size() + _phasePools.size());
        pools.insert(pools.end(),
            std::make_move_iterator(_phasePools.begin()),
            std::make_move_iterator(_phasePools.end()));
    }

    static void doPreStep()
    {
        for (const auto& pool : pools) {
            pool->doPreStep();
        }
    }

    static void doPhysics(Player* player)
    {
        const std::array<Vector2, 2> playerPosAndMovement = player->getPosAndMovement();
        for (const auto& pool : *GlobalPools::GetPools()) {
            pool->doPhysics(playerPosAndMovement);
        }
    }
    static void RemoveAt(const uint i)
    {
        pools.erase(pools.begin() + i);
    }
};

#endif //RAYLIB_STG_GLOBALPOOLS_H