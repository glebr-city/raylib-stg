//
// Created by g on 08/02/2026.
//

#ifndef RAYLIB_STG_PHASEHELPER_H
#define RAYLIB_STG_PHASEHELPER_H
#include <array>

#include "Player.h"
#include "PoolingVector.h"
#include "StepThinker.h"


class PhaseHelper : public StepThinker {
    protected:
        std::vector<IPoolingVector*> phasePools;

    public:

        void doPreStep() override {
            for (auto* pool : phasePools) {
                pool->doPreStep();
            }
        }

        virtual bool doPhysics(Player* player) {
            std::array<Vector2, 2> playerPosAndMovement = player->getPosAndMovement();
        for (auto* pool : phasePools) {
            pool->doPhysics(playerPosAndMovement);
        }
            return true;
    };

    int getNumActive() {
        int i = 0;
        for (const auto pooling_vector : phasePools) {
            i += pooling_vector->getNumActive();
        }
        return i;
    }
};


#endif //RAYLIB_STG_PHASEHELPER_H