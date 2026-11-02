#include "ReplayHandler.h"

#include <string>
//
// Created by n on 29/10/2026.
//
std::string ReplayHandler::currentReplayPath;
std::string ReplayHandler::replayPath;
u_int8_t ReplayHandler::lastInputs = 0;
int32_t ReplayHandler::stepsWithoutChange = 0;
size_t ReplayHandler::currentReplayDatumIndex = 0;
std::vector<u_int16_t> ReplayHandler::currentReplayData{};
bool ReplayHandler::isReadingFromFile = false;

std::vector<std::string> ReplayHandler::replayFilePaths{};