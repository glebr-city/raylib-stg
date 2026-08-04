//
// Created by g on 15/02/2026.
//

#ifndef RAYLIB_STG_GAMEHANDLER_H
#define RAYLIB_STG_GAMEHANDLER_H
#include "HUDHandler.h"
#include "LifeHandler.h"
#include "SpawnedEnemies.h"

// Generic name, but this is what loads levels and such!
class GameHandler {
    static Player player;
    static bool shouldRestartGame;
    static PHASES desiredPhase;
private:
    static void actuallyRestartGame() {
        shouldRestartGame = false;
        player =  {Vector2 {60, 140}};
        PlayerBullets::clearPlayerBullets();
        DamageHandler::setPlayer(&player);
        LifeHandler::resetLives();
        SoundHandler::StopAllSounds();
        GlobalVariables::currentStep() = 0;
        player.reset(Vector2 {60, 140});
        hitsTaken = 0;
        GlobalVariables::setCurrentPhase(desiredPhase);
        DamageHandler::setPlayer(&player);
        GlobalVariables::setGrazeMetre(0);
        SpawnedEnemies::clear();
        ScoreItemHandler::clear();
        ScoreHandler::resetScore();
    }
public:
    static void RestartGame(const PHASES _desiredPhase = DIAGONAL_TANKS) {
        desiredPhase = _desiredPhase;
        shouldRestartGame = true;
    }

    static void SwitchPhase(const PHASES _desiredPhase = DIAGONAL_TANKS)
    {
        desiredPhase = _desiredPhase;
        std::vector<std::shared_ptr<IPoolingVector>> transientPools = {};
        std::vector<std::shared_ptr<IPoolingVector>>* phasePools = GlobalVariables::getCurrentPhase()->getPhasePools();
        for (auto & phasePool : *phasePools)
        {
            if (phasePool.use_count() > 2)
                transientPools.emplace_back(std::move(phasePool));
        }
        GlobalVariables::setCurrentPhase(_desiredPhase);
        GlobalVariables::getCurrentPhase()->addPhasePools(&transientPools);
    }

    static void doPreStep() {
        if (shouldRestartGame)
            actuallyRestartGame();
        ScoreItemHandler::doPreStep();
        PlayerBullets::getPlayerBullets()->doPreStep();
        player.doPreStep();
        SpawnedEnemies::doPreStep();
        GlobalVariables::getCurrentPhase()->doPreStep();
        HUDHandler::doPreStep(player.getPosition());
    }

    static void doPhysics() {
        ScoreItemHandler::doPhysics(&player);
        PlayerBullets::getPlayerBullets()->doPhysics();
        SpawnedEnemies::doPhysics(&player);
        GlobalVariables::getCurrentPhase()->doPhysics(&player);
        player.doPhysics();
    }
};
#endif //RAYLIB_STG_GAMEHANDLER_H