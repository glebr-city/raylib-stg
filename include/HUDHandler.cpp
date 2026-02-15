#include "HUDHandler.h"

#include "LifeHandler.h"
#include "SpriteHandler.h"
//
// Created by g on 15/02/2026.
//
int HUDHandler::yOffset = -1;
const Color HUDHandler::scoreColour = {255, 255, 255, 130};
const Color HUDHandler::multiplierColour = {255, 255, 0, 130};

void HUDHandler::doPreStep(Vector2 playerPos)  {
    if (playerPos.y > 14)
        yOffset = -1;
    else
        yOffset = 165;
    const std::string scoreStr = ScoreHandler::getString();
    const float currentMultiplier = ScoreHandler::getMultiplier();
    DrawText(scoreStr.c_str(), 0, yOffset, 0, scoreColour);
    SpriteHandler::DrawStaticSprite(LIFE_ICON, Vector2 {105, static_cast<float>(yOffset + 5)}, scoreColour);
    std::string lifeStr = "x" + std::to_string(LifeHandler::getCurrentLives());
    DrawText(lifeStr.c_str(), 109, yOffset, 0, scoreColour);
    if (currentMultiplier > 1) {
        std::string tempStr = "x" + std::to_string(static_cast<int>(std::round(currentMultiplier * 100)));
        tempStr.insert(tempStr.length() - 2, ".");
        DrawText(tempStr.c_str(), 0, yOffset+7, 0, multiplierColour);
    }
}