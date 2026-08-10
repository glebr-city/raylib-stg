//
// Created by g on 15/02/2026.
//

#ifndef RAYLIB_STG_GAMEHANDLER_H
#define RAYLIB_STG_GAMEHANDLER_H
#include "BackgroundHandler.h"
#include "HUDHandler.h"
#include "LifeHandler.h"
#include "PlayerHandler.h"
#include "SoundHandler.h"
#include "SpawnedEnemies.h"

// Generic name, but this is what loads levels and such!
class GameHandler {
    static bool shouldRestartGame;
    static bool shouldSwitchPhase;
    static PHASES desiredPhase;
private:
    static void actuallyRestartGame() {
        shouldRestartGame = false;
        PlayerHandler::SetPlayer(std::make_shared<Player>(Vector2{60, 140}));
        PlayerBullets::clearPlayerBullets();
        LifeHandler::resetLives();
        SoundHandler::StopAllSounds();
        GlobalVariables::currentStep() = 0;
        GlobalPools::Clear();
        PlayerHandler::GetPlayer().get()->reset(Vector2 {60, 140});
        hitsTaken = 0;
        SpawnedEnemies::clear();
        GlobalVariables::setGrazeMetre(0);
        ScoreItemHandler::clear();
        ScoreHandler::resetScore();
        HUDHandler::endBoss();
        GlobalVariables::setCurrentPhase(desiredPhase);
        BackgroundHandler::SetBackgroundPosition(GlobalVariables::getCurrentPhase()->getDefaultBackgroundPosition());
        BackgroundHandler::SetBackgroundSprite(GlobalVariables::getCurrentPhase()->getDefaultBackgroundSprite());
        BackgroundHandler::SetScrollVector(GlobalVariables::getCurrentPhase()->getDefaultScrollVector());
        GlobalVariables::getCurrentPhase()->InitPhase();
    }
    static void actuallySwitchPhase()
    {
        shouldSwitchPhase = false;
        HUDHandler::RemoveBossTimer();
        HUDHandler::RemoveBossHealth();
        const std::vector<std::shared_ptr<IPoolingVector>>* pools = GlobalPools::GetPools();
        GlobalVariables::DestroyCurrentPhase();
        for (uint i = 0; i < pools->size(); i++)
        {
            if (pools->at(i).use_count() <= 1 && pools->at(i)->getNumActive() == 0)
                GlobalPools::RemoveAt(i);
        }
        GlobalVariables::setCurrentPhase(desiredPhase);
        GlobalVariables::getCurrentPhase()->InitPhase();
    }
public:
    static void RestartGame(const PHASES _desiredPhase = DIAGONAL_TANKS) {
        desiredPhase = _desiredPhase;
        shouldRestartGame = true;
    }

    static void SwitchPhase(const PHASES _desiredPhase = DIAGONAL_TANKS)
    {
        shouldSwitchPhase = true;
        desiredPhase = _desiredPhase;
    }

    static void doPreStep() {
        if (shouldRestartGame)
            actuallyRestartGame();
        BackgroundHandler::ScrollBackground();
        ScoreItemHandler::doPreStep();
        EphemeraHandler::doPreStep();
        PlayerBullets::getPlayerBullets()->doPreStep();
       PlayerHandler::GetPlayer().get()->doPreStep();
        SpawnedEnemies::doPreStep();
        GlobalPools::doPreStep();
        GlobalVariables::getCurrentPhase()->doPreStep();
    }

    static void HandleHUD() //Hacky for this to be here, but it's fine.
    {
        HUDHandler::HandleHud(PlayerHandler::GetPlayer().get()->GetPosition()); //Hacky for this to be here, but it's fine.
    }

    static void doPhysics() {
        if (shouldSwitchPhase)
            actuallySwitchPhase();
        ScoreItemHandler::doPhysics();
        PlayerBullets::getPlayerBullets()->doPhysics();
        SpawnedEnemies::doPhysics();
        EphemeraHandler::doPhysics();
        if (GlobalVariables::getCurrentPhase()->CanSpawnBullets())
            GlobalPools::doPhysics();
        GlobalVariables::getCurrentPhase()->doPhysics();
        GlobalVariables::getCurrentPhase()->tickStep();
        PlayerHandler::GetPlayer().get()->doPhysics();
    }

    static void NextPhase()
    {
        SwitchPhase(static_cast<PHASES>(static_cast<int>(desiredPhase) + 1));
    }
};
#endif //RAYLIB_STG_GAMEHANDLER_H