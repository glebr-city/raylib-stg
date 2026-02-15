//
// Created by g on 08/02/2026.
//

#ifndef RAYLIB_STG_PHASEHELPER_H
#define RAYLIB_STG_PHASEHELPER_H
#include <array>

#include "Player.h"
#include "PoolingVector.h"
#include "ScoreItemHandler.h"
#include "StepThinker.h"


class PhaseHelper : public StepThinker {
    protected:
        bool playerHit = false;
        int currentWaitSteps = 0; //Don't spawn bullets for a while after a hyper.
        std::vector<std::shared_ptr<IPoolingVector>> phasePools;

    public:
        PhaseHelper(std::vector<std::shared_ptr<IPoolingVector>> _phasePools){
            this->phasePools = std::move(_phasePools);
        }

        void doPreStep() override {
            for (auto& pool : phasePools) {
                pool->doPreStep();
            }
        }

        virtual bool doPhysics(Player* player) {
            if (playerHit) {
                clearBullets();
                playerHit = false;
                return true;
            }
            if (--currentWaitSteps > 0) {
                for (auto& pool : phasePools) {
                    pool->setNumActive(0);
                }
                return true;
            }
            const std::array<Vector2, 2> playerPosAndMovement = player->getPosAndMovement();
        for (auto& pool : phasePools) {
            pool->doPhysics(playerPosAndMovement);
        }
            return true;
    };

    void hitPlayer() {
        playerHit = true;
    }

    int getNumActive() {
        int i = 0;
        for (const auto& pooling_vector : phasePools) {
            i += pooling_vector->getNumActive();
        }
        return i;
    }

    void clearBullets() { //Clear bullets and set cooldown timer on spawning more.
        for (const auto& pooling_vector : phasePools) {
            pooling_vector->setNumActive(0);
        }
        currentWaitSteps = 60;
    }

    void cancelBullets() { //Clear bullets AND spawn score items.
        for (const auto& pooling_vector : phasePools) {
            std::cout << "Active position count: " << pooling_vector->getActivePositions().size() << std::endl;
            for (const auto& pos : pooling_vector->getActivePositions()) {
                if (pos.x < -2 || pos.x > 122 || pos.y < -2 || pos.y > 182)
                    continue;
                ScoreItemHandler::spawn(pos, pooling_vector->getValue());
            }
            pooling_vector->setNumActive(0);
        }
        currentWaitSteps = 60;
    }
};


#endif //RAYLIB_STG_PHASEHELPER_H