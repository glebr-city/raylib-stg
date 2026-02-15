//
// Created by g on 15/02/2026.
//

#include "GameHandler.h"

#include "Player.h"
Player GameHandler::player = Player(Vector2 {60, 140});
bool GameHandler::shouldRestartGame = false;
