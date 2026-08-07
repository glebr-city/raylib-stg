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
int HUDHandler::bossHealth = 6000;
int HUDHandler::bossMaxHealth = 6000;
int* HUDHandler::bossTimer = nullptr;
int HUDHandler::currentBossTimer = 0;

/*void HUDHandler::doPreStep(Vector2 playerPos)  {
    if (playerPos.y > 14)
        yOffset = -1;
    else
        yOffset = 165;
    const std::string scoreStr = ScoreHandler::getString();
    const float currentMultiplier = ScoreHandler::getMultiplier();
    SpriteHandler::QueueText({scoreStr, Vector2{0, static_cast<float>(yOffset)}, 0, scoreColour});
    SpriteHandler::QueueMyStaticSprite({.i = LIFE_ICON, .pos = Vector2 {105, static_cast<float>(yOffset + 5)}, .l=LAYER_HUD, .col = scoreColour});
    std::string lifeStr = "x" + std::to_string(LifeHandler::getCurrentLives());
    SpriteHandler::QueueText({lifeStr, Vector2{109, static_cast<float>(yOffset)}, 0, scoreColour});
    if (currentMultiplier > 1) {
        std::string tempStr = "x" + std::to_string(static_cast<int>(std::round(currentMultiplier * 100)));
        tempStr.insert(tempStr.length() - 2, ".");
        SpriteHandler::QueueText({tempStr, Vector2{0, static_cast<float>(yOffset + 7)}, 0, multiplierColour});
    }
}*/