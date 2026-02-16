//
// Created by g on 15/02/2026.
//

#ifndef RAYLIB_STG_GAMEHANDLER_H
#define RAYLIB_STG_GAMEHANDLER_H
#include "HUDHandler.h"
#include "LifeHandler.h"
#include "SpawnedEnemies.h"
#include "TestPhase1.h"
#include "TestPhase2.h"

// Generic name, but this is what loads levels and such!
class GameHandler {
    static Player player;
    static bool shouldRestartGame;
private:
    static void actuallyRestartGame() {
        shouldRestartGame = false;
        GlobalVariables::setCurrentPhase(std::make_unique<TestPhase2>());
        player =  {Vector2 {60, 140}};
        DamageHandler::setPlayer(&player);
        LifeHandler::resetLives();
        GlobalVariables::currentStep() = 0;
        player.reset(Vector2 {60, 140});
        hitsTaken = 0;
        auto newPhase = std::make_unique<TestPhase2>();
        GlobalVariables::setCurrentPhase(std::move(newPhase));
        DamageHandler::setPlayer(&player);
        GlobalVariables::setGrazeMetre(0);
        SpawnedEnemies::clear();
        ScoreItemHandler::clear();
        ScoreHandler::resetScore();
    }
public:
    static void restartGame() {
        shouldRestartGame = true;

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