//
// Created by g on 15/02/2026.
//

#include "GameHandler.h"

#include "Player.h"
bool GameHandler::shouldRestartGame = false;
bool GameHandler::shouldSwitchPhase = false;
PHASES GameHandler::desiredPhase = DIAGONAL_TANKS;
