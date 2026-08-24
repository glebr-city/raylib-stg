//
// Created by g on 15/02/2026.
//

#ifndef RAYLIB_STG_GAMEHANDLER_H
#define RAYLIB_STG_GAMEHANDLER_H
#include "BackgroundHandler.h"
#include "HUDHandler.h"
#include "LifeHandler.h"
#include "PauseHandler.h"
#include "PlayerHandler.h"
#include "RNGHandler.h"
#include "SoundHandler.h"
#include "SpawnedEnemies.h"

// Generic name, but this is what loads levels and such!
class GameHandler {
    static bool shouldRestartGame;
    static bool shouldSwitchPhase;
    static PHASES desiredPhase;
    static uint_fast8_t desiredStage;
private:
    static void actuallyRestartGame() {
        shouldRestartGame = false;
        RNGHandler::InitSeed();
        PlayerHandler::SetPlayer(std::make_shared<Player>(Vector2{60, 140}));
        PlayerBullets::clearPlayerBullets();
        LifeHandler::resetLives();
        DamageHandler::Reset();
        SoundHandler::StopAllSounds();
        GlobalVariables::currentStep() = 0;
        GlobalPools::Clear();
        PlayerHandler::GetPlayer().get()->reset(Vector2 {60, 140});
        hitsTaken = 0;
        SpawnedEnemies::clear();
        GlobalVariables::SetGrazeMetre(0);
        ScoreItemHandler::clear();
        ScoreHandler::resetScore();
        HUDHandler::endBoss();
        GlobalVariables::SetCurrentPhase(desiredPhase);
        BackgroundHandler::SetBackgroundPosition(GlobalVariables::GetCurrentPhase()->getDefaultBackgroundPosition());
        BackgroundHandler::SetBackgroundSprite(GlobalVariables::GetCurrentPhase()->getDefaultBackgroundSprite());
        BackgroundHandler::SetScrollVector(GlobalVariables::GetCurrentPhase()->getDefaultScrollVector());
        GlobalVariables::GetCurrentPhase()->InitPhase();
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
        GlobalVariables::SetCurrentPhase(desiredPhase);
        GlobalVariables::GetCurrentPhase()->InitPhase();
    }
public:
    static void RestartGame(const uint_fast8_t _desiredStage = 0, const uint_fast8_t _desiredPhaseIndex = 0) {
        desiredStage = _desiredStage;
        GlobalVariables::SetCurrentStage(_desiredStage);
        desiredPhase = GlobalVariables::GetCurrentStage()->GetPhase(_desiredPhaseIndex);
        PauseHandler::SetPause(false);
        shouldRestartGame = true;
    }

    static void SwitchPhase(const uint_fast8_t _desiredStage, const uint_fast8_t _desiredPhaseIndex)
    {
        shouldSwitchPhase = true;
        GlobalVariables::SetCurrentStage(_desiredStage);
        desiredPhase = GlobalVariables::GetCurrentStage()->GetPhase(_desiredPhaseIndex);
        desiredStage = _desiredStage;
    }

    static void doPreStep() {
        if (shouldRestartGame)
            actuallyRestartGame();
        BackgroundHandler::ScrollBackground();
        RNGHandler::StepSeed();
        ScoreItemHandler::doPreStep();
        EphemeraHandler::doPreStep();
        PlayerBullets::getPlayerBullets()->doPreStep();
       PlayerHandler::GetPlayer().get()->doPreStep();
        SpawnedEnemies::doPreStep();
        GlobalPools::doPreStep();
        GlobalVariables::GetCurrentPhase()->doPreStep();
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
        if (GlobalVariables::GetCurrentPhase()->CanSpawnBullets())
            GlobalPools::doPhysics();
        GlobalVariables::GetCurrentPhase()->doPhysics();
        GlobalVariables::GetCurrentPhase()->tickStep();
        PlayerHandler::GetPlayer().get()->doPhysics();
    }

    static void doPostStep()
    {
        GlobalPools::DoPostStep();
        PlayerHandler::GetPlayer().get()->doPostStep();
        SpawnedEnemies::doPostStep();
    }

    static void NextPhase(const bool _restart = false)
    {
        int nextPhaseIndex = GlobalVariables::GetCurrentPhaseIndex() + 1;
        auto currentStage = GlobalVariables::GetCurrentStage();
        if (nextPhaseIndex >= currentStage->GetPhaseCount())
        {
            GlobalVariables::NextStage();
            nextPhaseIndex = 0;
            if (_restart)
                RestartGame(0, 0);
            else
                SwitchPhase(GlobalVariables::GetCurrentStageIndex(), nextPhaseIndex);
            return;
        }
        if (_restart)
            RestartGame(GlobalVariables::GetCurrentStageIndex(), nextPhaseIndex);
        else
            SwitchPhase(GlobalVariables::GetCurrentStageIndex(), nextPhaseIndex);
    }
};
#endif //RAYLIB_STG_GAMEHANDLER_H