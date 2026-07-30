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
        STATIC_SPRITES background = DEFAULT_BACKGROUND;
        std::string phaseName = "Unnamed Phase"; //Phase name. For debug purposes?
        bool playerHit = false;
        int currentWaitSteps = 0; //Don't spawn bullets for a while after a hyper.
        std::vector<std::shared_ptr<IPoolingVector>> phasePools;
        Vector2 defaultScrollVector; //Scrolling for the background and grounded enemies!
        Vector2 currentScrollVector; //Scrolling for the background and grounded enemies!
        Vector2 currentBackgroundPosition;
        u_int stepsElapsed = 0;

    public:
        PhaseHelper(std::vector<std::shared_ptr<IPoolingVector>> _phasePools){
            this->phasePools = std::move(_phasePools);
        }

        void doPreStep() override {
            for (auto& pool : phasePools) {
                pool->doPreStep();
            }
            currentBackgroundPosition += currentScrollVector;
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

    std::string getPhaseName()
    {
        return phaseName;
    }

    Vector2 getScrollVector() //Get the phase's (current) scroll vector; used by grounded enemies and the background.
    {
        return currentScrollVector;
    }

    STATIC_SPRITES* getBackgroundSprite()
    {
        return &background;
    }

    Vector2* getBackgroundPosition()
    {
        return &currentBackgroundPosition;
    }

    u_int getStepsElapsed()
    {
        return stepsElapsed;
    }

    virtual void enemyKilled(u_int _id) = 0;
};


#endif //RAYLIB_STG_PHASEHELPER_H