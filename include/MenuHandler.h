//
// Created by n on 12/08/2026.
//

#ifndef RAYLIB_STG_MENUHANDLER_H
#define RAYLIB_STG_MENUHANDLER_H
#include <array>
#include <cstdint>
#include <memory>

#include "GlobalVariables.h"
#include "MenuOptions.h"
#include "raylib.h"

class MenuHandler
{
private:
    static constexpr uint8_t OPTION_COUNT = 5;
    static std::array<std::unique_ptr<MenuOption>, OPTION_COUNT> menuOptions;
    static size_t selectedOption;
public:
    static void HandleMenus()
    {
        DrawRectangle(0, 0, gameWidth, gameHeight, {30, 30, 30, 100});
        for (int i = 0; i < menuOptions.size(); i++)
        {
            if (i == selectedOption)
                DrawText(menuOptions.at(i)->GetText().c_str(), 0, 10 + i*10, 10, WHITE);
            else
                DrawText(menuOptions.at(i)->GetText().c_str(), 0, 10 + i*10, 10, {255, 255, 255, 100});
        }
        if (IsKeyPressed(KEY_DOWN))
        {
            SoundHandler::PlaySound(THUMP_1);
            if (selectedOption++ >= menuOptions.size() - 1)
                selectedOption = 0;
        }
        if (IsKeyPressed(KEY_UP))
        {
            SoundHandler::PlaySound(THUMP_1);
            if (selectedOption-- == 0)
                selectedOption = menuOptions.size() - 1;
        }
        if (IsKeyPressed(KEY_Z))
        {
            menuOptions.at(selectedOption)->PressOK();
        }
        if (IsKeyPressed(KEY_LEFT))
        {
            menuOptions.at(selectedOption)->PressLeft();
        }
        if (IsKeyPressed(KEY_RIGHT))
        {
            menuOptions.at(selectedOption)->PressRight();
        }
    }
};
#endif //RAYLIB_STG_MENUHANDLER_H