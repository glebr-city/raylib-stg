//
// Created by g on 15/02/2026.
//

#ifndef RAYLIB_STG_HUDHANDLER_H
#define RAYLIB_STG_HUDHANDLER_H
#include <string>

#include "LifeHandler.h"
#include "raylib.h"
#include "ScoreHandler.h"
#include "SpriteHandler.h"

class HUDHandler {
private:
    static const Color scoreColour;
    static const Color multiplierColour;
    static int yOffset;
    static const Texture2D lifeIcon;
    static bool enableBossHealthBar;
    static int bossMaxHealth;
    static int bossHealth;
    static int* bossTimer; //References an int given by a PhaseHelper. This is misusing unique_ptrs, so we must make sure to always clear this :)
    static int currentBossTimer;
public:
    static void HandleHud(const Vector2 playerPos)
    {
        enableBossHealthBar = true;
        const float healthBarRatio = static_cast<float>(bossHealth) / bossMaxHealth;
        const int healthBarWidth = healthBarRatio * gameWidth;
        const Color healthBarColour = {static_cast<u_char>(255 - healthBarRatio * 255), static_cast<u_char>(healthBarRatio * 255), 0, 130};
        if (playerPos.y > 14)
        {
            yOffset = -1;
            if (enableBossHealthBar)
            {
                if (bossTimer != nullptr)
                {
                    DrawRectangle(0, 0, --currentBossTimer / *bossTimer * gameWidth, 1, scoreColour);
                }
                else
                {
                    DrawRectangle(0, 0, gameWidth, 1, scoreColour);
                }
                yOffset += 2;
                DrawRectangle(0, 1, healthBarWidth, 1, healthBarColour);

            }
        }
        else
        {
            yOffset = 172;
            if (enableBossHealthBar)
            {
                if (bossTimer != nullptr)
                {
                    DrawRectangle(0, 179, --currentBossTimer / *bossTimer * gameWidth, 1, scoreColour);
                }
                else
                {
                    DrawRectangle(0, 179, gameWidth, 1, scoreColour);
                }
                yOffset -= 2;
                DrawRectangle(0, 178, healthBarWidth, 1, healthBarColour);
            }
        }
        const std::string scoreStr = ScoreHandler::getString();
        const float currentMultiplier = ScoreHandler::getMultiplier();
        //SpriteHandler::QueueText({scoreStr, Vector2{0, static_cast<float>(yOffset)}, 0, scoreColour});
        DrawText(scoreStr.c_str(), 0, static_cast<float>(yOffset), 0, scoreColour);
        //SpriteHandler::QueueMyStaticSprite({.i = LIFE_ICON, .pos = Vector2 {105, static_cast<float>(yOffset + 5)}, .l=LAYER_HUD, .col = scoreColour});
        SpriteHandler::DrawMyStaticSprite({.i = LIFE_ICON, .pos = Vector2 {105, static_cast<float>(yOffset + 5)}, .col = scoreColour});
        const std::string lifeStr = "x" + std::to_string(LifeHandler::getCurrentLives());
        SpriteHandler::QueueText({lifeStr, Vector2{109, static_cast<float>(yOffset)}, 0, scoreColour});
        if (currentMultiplier > 1) {
            std::string tempStr = "x" + std::to_string(static_cast<int>(std::round(currentMultiplier * 100)));
            tempStr.insert(tempStr.length() - 2, ".");
            //SpriteHandler::QueueText({tempStr, Vector2{0, static_cast<float>(yOffset + 7)}, 0, multiplierColour});
            DrawText(tempStr.c_str(), 0, yOffset + 7, 0, multiplierColour);
        }
    }

    static void startBoss(const int maxHealth, const int* _bossTimer = nullptr, const int _bossHealth = 1)
    {
        enableBossHealthBar = true;
        bossMaxHealth = maxHealth;
        bossHealth = _bossHealth;
        if (_bossTimer != nullptr)
        {
            currentBossTimer = *_bossTimer;
        }
    }

    static void endBoss()
    {
        enableBossHealthBar = false;
        bossTimer = nullptr;
    }

    static void RemoveBossTimer()
    {
        bossTimer = nullptr;
    }

    static void setBossHealth(const int _bossHealth)
    {
        bossHealth = _bossHealth;
    }

};
#endif //RAYLIB_STG_HUDHANDLER_H