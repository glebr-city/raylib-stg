//
// Created by g on 15/02/2026.
//

#ifndef RAYLIB_STG_HUDHANDLER_H
#define RAYLIB_STG_HUDHANDLER_H
#include <string>

#include "LifeHandler.h"
#include "raylib/raylib.h"
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
    static int* bossHealth;
    static int bossMaxTimer;
    static int* bossTimer;

    static void handleBossHealthBar(const bool drawBelow = false)
    {
        float healthBarRatio = 1;
        if (bossHealth != nullptr && *bossHealth >= 0)
            healthBarRatio = static_cast<float>(*bossHealth) / bossMaxHealth;
        const int healthBarWidth = healthBarRatio * gameWidth;
        float timerRatio = 1;
        if (bossTimer != nullptr && *bossTimer >= 0)
            timerRatio = static_cast<float>(*bossTimer) / bossMaxTimer;
        const int timerWidth = timerRatio * gameWidth;
        const Color healthBarColour = {static_cast<u_char>(255 - healthBarRatio * 255), static_cast<u_char>(healthBarRatio * 255), 0, 130};

        if (!drawBelow)
        {
            DrawRectangle(0, 0, timerWidth, 1, scoreColour);
            yOffset += 2;
            DrawRectangle(0, 1, healthBarWidth, 1, healthBarColour);
        } else
        {
            DrawRectangle(0, 179, timerWidth, 1, scoreColour);
            yOffset -= 2;
            DrawRectangle(0, 178, healthBarWidth, 1, healthBarColour);
        }
    }
public:
    static void HandleHud(const Vector2 playerPos)
    {
        if (playerPos.y > 14)
        {
            yOffset = -1;
            if (enableBossHealthBar)
                handleBossHealthBar(false);
        }
        else
        {
            yOffset = 172;
            if (enableBossHealthBar)
                handleBossHealthBar(true);

            }
        const std::string scoreStr = ScoreHandler::getString();
        const float currentMultiplier = ScoreHandler::getMultiplier();
        //SpriteHandler::QueueText({scoreStr, Vector2{0, static_cast<float>(yOffset)}, 0, scoreColour});
        DrawText(scoreStr.c_str(), 0, static_cast<float>(yOffset), 0, scoreColour);
        //SpriteHandler::QueueMyStaticSprite({.i = LIFE_ICON, .pos = Vector2 {105, static_cast<float>(yOffset + 5)}, .l=LAYER_HUD, .col = scoreColour});
        SpriteHandler::DrawMyStaticSprite({.i = LIFE_ICON, .pos = Vector2 {105, static_cast<float>(yOffset + 5)}, .col = scoreColour});
        const std::string lifeStr = "x" + std::to_string(LifeHandler::getCurrentLives());
        DrawText(lifeStr.c_str(), 109, yOffset, 0, scoreColour);
        if (currentMultiplier > 1) {
            std::string tempStr = "x" + std::to_string(static_cast<int>(std::round(currentMultiplier * 100)));
            tempStr.insert(tempStr.length() - 2, ".");
            //SpriteHandler::QueueText({tempStr, Vector2{0, static_cast<float>(yOffset + 7)}, 0, multiplierColour});
            DrawText(tempStr.c_str(), 0, yOffset + 7, 0, multiplierColour);
        }
    }

    static void startBoss(const int maxHealth = bossMaxHealth, const int _maxTimer = bossMaxHealth, int* _bossTimer = bossTimer, int* _bossHealth = bossHealth)
    {
        enableBossHealthBar = true;
        bossMaxHealth = maxHealth;
        bossMaxTimer = _maxTimer;
        bossHealth = _bossHealth;
        bossTimer = _bossTimer;
    }

    static void endBoss()
    {
        enableBossHealthBar = false;
        bossTimer = nullptr;
        bossHealth = nullptr;
    }

    static void RemoveBossTimer()
    {
        bossTimer = nullptr;
    }

    static void SetBossHealth(int* _bossHealth, const int _bossMaxHealth = bossMaxHealth)
    {
        bossMaxHealth = _bossMaxHealth;
        bossHealth = _bossHealth;
    }

    static void SetTimer(const int _maxTimer = bossMaxTimer, int* _bossTimer = bossTimer)
    {
        bossMaxTimer = _maxTimer;
        bossTimer = _bossTimer;
    }

    static void RemoveBossHealth()
    {
        bossHealth = nullptr;
    }
};
#endif //RAYLIB_STG_HUDHANDLER_H