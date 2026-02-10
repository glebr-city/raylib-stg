//
// Created by g on 08/02/2026.
//

#ifndef RAYLIB_STG_PHASEHELPER_H
#define RAYLIB_STG_PHASEHELPER_H
#include <array>

#include "GlobalVariables.h"
#include "Player.h"
#include "PoolingVector.h"
#include "StepThinker.h"


class PhaseHelper : public StepThinker {
    protected:
        int currentWaitSteps = 0; //Don't spawn bullets for a while after a hyper.
        std::vector<IPoolingVector*> phasePools;

    public:

        void doPreStep() override {
            for (auto* pool : phasePools) {
                pool->doPreStep();
            }
        }

        virtual bool doPhysics(Player* player) {
            if (--currentWaitSteps > 0) {
                return true;
            }
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

    void startHyper() {
        for (const auto pooling_vector : phasePools) {
            pooling_vector->setNumActive(0);
        }
        currentWaitSteps = 60;
    }
};


#endif //RAYLIB_STG_PHASEHELPER_H