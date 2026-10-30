#include "ReplayHandler.h"

#include <string>
//
// Created by n on 29/10/2026.
//
std::string ReplayHandler::currentReplayPath;
std::string ReplayHandler::replayPath;
u_int8_t ReplayHandler::lastInputs = 0;
u_int16_t ReplayHandler::stepsWithoutChange = 0;
std::vector<u_int16_t> ReplayHandler::currentReplayData{};