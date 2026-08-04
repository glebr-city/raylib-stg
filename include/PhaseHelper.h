//
// Created by g on 08/02/2026.
//

#ifndef RAYLIB_STG_PHASEHELPER_H
#define RAYLIB_STG_PHASEHELPER_H
#include <array>

#include "GlobalPools.h"
#include "Player.h"
#include "PoolingVector.h"
#include "ScoreItemHandler.h"
#include "StepThinker.h"



class PhaseHelper : public StepThinker {
    protected:
        std::string phaseName = "Unnamed Phase"; //Phase name. For debug purposes?
        bool playerHit = false;
        int currentWaitSteps = 0; //Don't spawn bullets for a while after a hyper.
        Vector2 defaultScrollVector; //Scrolling for the background and grounded enemies!
        u_int stepsElapsed = 0;

    public:
        PhaseHelper(const Vector2 _defaultScrollVector)
        {
            defaultScrollVector = _defaultScrollVector;
        }

        void doPreStep() override {
            /*for (auto& pool : phasePools) {
                pool->doPreStep();
            }*/
            //MyStaticSprite* backgroundSprite = SpriteHandler::getStaticSprite(background);
            //DrawTextureRec(backgroundSprite->spriteTexture, Rectangle{currentBackgroundPosition.x, backgroundSprite->spriteSize.y - 180 - currentBackgroundPosition.y, 120, 180}, Vector2(0, 0), WHITE);
            //SpriteHandler::QueueMyStaticSprite({background, Vector2Add(currentBackgroundPosition, Vector2(0, 0))});
        }

        virtual bool doPhysics(Player* player) {
            if (playerHit) {
                clearBullets();
                playerHit = false;
                return true;
            }
            if (--currentWaitSteps > 0) {
                for (const auto& pool : *GlobalPools::GetPools()) {
                    pool->setNumActive(0);
                }
                return true;
            }
            return true;
    };

    void hitPlayer() {
        playerHit = true;
    }

    [[nodiscard]] int getNumActive() const
    {
        int i = 0;
        for (const auto& pooling_vector : *GlobalPools::GetPools()) {
            i += pooling_vector->getNumActive();
        }
        return i;
    }

    void clearBullets() { //Clear bullets and set cooldown timer on spawning more.
        for (const auto& pooling_vector : *GlobalPools::GetPools()) {
            pooling_vector->setNumActive(0);
        }
        currentWaitSteps = 60;
    }

    void cancelBullets() { //Clear bullets AND spawn score items.
        for (const auto& pooling_vector : *GlobalPools::GetPools()) {
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

    std::string getPhaseName()
    {
        return phaseName;
    }


    u_int getStepsElapsed()
    {
        return stepsElapsed;
    }

    virtual void enemyKilled(u_int _id) = 0;
    virtual void enemyDespawned(u_int _id) = 0;


};

struct PhaseRef //Used to list PhaseHelpers without loading them in their entirety.
{
    std::string name = "Unnamed Phase";
    PhaseHelper* (*initPhase)();
};


#endif //RAYLIB_STG_PHASEHELPER_H