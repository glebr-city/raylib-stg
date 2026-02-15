//
// Created by g on 14/02/2026.
//

#include "ScoreHandler.h"

#include <string>
std::string ScoreHandler::scoreStr = "0";
const Color ScoreHandler::scoreColour = {255, 255, 255, 130};
const Color ScoreHandler::multiplierColour = {255, 255, 0, 130};
u_long ScoreHandler::currentScore = 100000000000;
float ScoreHandler::currentMultiplier = 1;
