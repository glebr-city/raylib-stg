//
// Created by g on 15/02/2026.
//

#ifndef RAYLIB_STG_GAMEHANDLER_H
#define RAYLIB_STG_GAMEHANDLER_H
#include "BackgroundHandler.h"
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
        //std::vector<std::shared_ptr<IPoolingVector>> transientPools = {};
        //std::vector<std::shared_ptr<IPoolingVector>>* phasePools = GlobalVariables::getCurrentPhase()->getPhasePools();
        const std::vector<std::shared_ptr<IPoolingVector>>* pools = GlobalPools::GetPools();
        for (uint i = 0; i < pools->size(); i++)
        {
            if (pools->at(i).use_count() <= 2)
                GlobalPools::RemoveAt(i);
        }
        GlobalVariables::setCurrentPhase(_desiredPhase);
        //GlobalVariables::getCurrentPhase()->addPhasePools(&transientPools);
    }

    static void doPreStep() {
        if (shouldRestartGame)
            actuallyRestartGame();
        BackgroundHandler::ScrollBackground();
        ScoreItemHandler::doPreStep();
        PlayerBullets::getPlayerBullets()->doPreStep();
        player.doPreStep();
        SpawnedEnemies::doPreStep();
        GlobalPools::doPreStep();
        GlobalVariables::getCurrentPhase()->doPreStep();
        HUDHandler::doPreStep(player.getPosition());
    }

    static void doPhysics() {
        player.doPhysics();
        ScoreItemHandler::doPhysics(&player);
        PlayerBullets::getPlayerBullets()->doPhysics();
        SpawnedEnemies::doPhysics(&player);
        GlobalPools::doPhysics(&player);
        GlobalVariables::getCurrentPhase()->doPhysics(&player);
    }
};
#endif //RAYLIB_STG_GAMEHANDLER_H