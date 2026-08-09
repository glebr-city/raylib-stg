#include "../include/HUDHandler.h"

#include "../include/LifeHandler.h"
#include "../include/SpriteHandler.h"
//
// Created by g on 15/02/2026.
//
int HUDHandler::yOffset = -1;
const Color HUDHandler::scoreColour = {255, 255, 255, 130};
const Color HUDHandler::multiplierColour = {255, 255, 0, 130};
bool HUDHandler::enableBossHealthBar = false;
int* HUDHandler::bossHealth = nullptr;
int HUDHandler::bossMaxHealth = 600;
int HUDHandler::bossMaxTimer = 1200;
int* HUDHandler::bossTimer = nullptr;
