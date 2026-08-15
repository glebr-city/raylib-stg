//
// Created by n on 14/08/2026.
//

#ifndef RAYLIB_STG_MENUS_H
#define RAYLIB_STG_MENUS_H
#include "MenuOptions.h"

class Menu
{
protected:
    std::vector<std::unique_ptr<MenuOption>> menuOptions;
    size_t selectedOption = 0;
    MENUS desiredMenu = MENU_MAIN;
    Menu() = default;
public:
    virtual ~Menu() = default;
    virtual void InitMenu() = 0;
    virtual bool HandleMenu() { return true; }; //Return false to return to the main menu.
    virtual void OpenMenu(){};
    virtual MENUS GetDesiredMenu()
    {
        return desiredMenu;
    }
};

class MainMenu : public Menu
{

public:
    void InitMenu() override
    {
        menuOptions.emplace_back(std::make_unique<ResumeOption>());
        menuOptions.emplace_back(std::make_unique<RestartOption>());
        menuOptions.emplace_back(std::make_unique<ControlMenuEnterOption>());
        menuOptions.emplace_back(std::make_unique<SoundVolumeOption>());
        menuOptions.emplace_back(std::make_unique<ScreenFilterOption>());
        menuOptions.emplace_back(std::make_unique<ScreenRotationOption>());
        menuOptions.emplace_back(std::make_unique<QuitOption>());
    }

    bool HandleMenu() override
    {
        DrawRectangle(0, 0, gameWidth, gameHeight, {30, 30, 30, 100});
        for (int i = 0; i < menuOptions.size(); i++)
        {
            if (i == selectedOption)
                DrawText(menuOptions.at(i)->GetText().c_str(), 0, 10 + i*10, 10, WHITE);
            else
                DrawText(menuOptions.at(i)->GetText().c_str(), 0, 10 + i*10, 10, {255, 255, 255, 100});
        }

        if (InputHandler::CheckInputsPressedMenu(INPUT_MENU))
        {
            selectedOption = 0;
            PauseHandler::SetPause(false);
        }
        if (InputHandler::CheckInputsPressedMenu(INPUT_DOWN))
        {
            SoundHandler::PlaySound(THUMP_1);
            if (selectedOption++ >= menuOptions.size() - 1)
                selectedOption = 0;
        }
        if (InputHandler::CheckInputsPressedMenu(INPUT_UP))
        {
            SoundHandler::PlaySound(THUMP_1);
            if (selectedOption-- == 0)
                selectedOption = menuOptions.size() - 1;
        }
        if (InputHandler::CheckInputsPressedMenu(INPUT_FIRE))
        {
            if (menuOptions.at(selectedOption)->PressOK())
            {
                desiredMenu = menuOptions.at(selectedOption)->GetDesiredMenu();
                return false;
            }
        }
        if (InputHandler::CheckInputsPressedMenu(INPUT_LEFT))
        {
            menuOptions.at(selectedOption)->PressLeft();
        }
        if (InputHandler::CheckInputsPressedMenu(INPUT_RIGHT))
        {
            menuOptions.at(selectedOption)->PressRight();
        }
        return true;
    }

    void OpenMenu() override
    {
        selectedOption = 0;
    }
};

class ControlDeviceSelectionMenu : public Menu
{
    void InitMenu() override
    {
        menuOptions.emplace_back(std::make_unique<ControlDeviceSelectionMenuOptionKeyboard>());
        menuOptions.emplace_back(std::make_unique<ControlDeviceSelectionMenuOptionGamepad>());
    };
    bool HandleMenu() override
    {
        DrawRectangle(0, 0, gameWidth, gameHeight, {30, 30, 30, 100});
        for (int i = 0; i < menuOptions.size(); i++)
        {
            if (i == selectedOption)
                DrawText(menuOptions.at(i)->GetText().c_str(), 0, 10 + i*10, 10, WHITE);
            else
                DrawText(menuOptions.at(i)->GetText().c_str(), 0, 10 + i*10, 10, {255, 255, 255, 100});
        }

        if (InputHandler::CheckInputsPressedMenu(INPUT_MENU))
            return false;
        if (InputHandler::CheckInputsPressedMenu(INPUT_FIRE))
        {
            if (menuOptions.at(selectedOption)->PressOK())
            {
                desiredMenu = menuOptions.at(selectedOption)->GetDesiredMenu();
                return false;
            }
        }
        if (InputHandler::CheckInputsPressedMenu(INPUT_DOWN))
        {
            SoundHandler::PlaySound(THUMP_1);
            if (selectedOption++ >= menuOptions.size() - 1)
                selectedOption = 0;
        }
        if (InputHandler::CheckInputsPressedMenu(INPUT_UP))
        {
            SoundHandler::PlaySound(THUMP_1);
            if (selectedOption-- == 0)
                selectedOption = menuOptions.size() - 1;
        }
        return true;
    }
};


class ControlMenu : public Menu
{
protected:
    std::vector<std::unique_ptr<ControlRebindOption>> menuOptions;
    bool isFocused = false;
    bool isRebinding = false;
public:
    void InitMenu() override
    {
        int yPos = 0;
        for (auto& i : *InputHandler::GetGameInputList())
        {
            menuOptions.emplace_back(std::make_unique<ControlRebindOption>(i));
            yPos += 10;
        }
    }

        bool HandleMenu() override
    {
        DrawRectangle(0, 0, gameWidth, gameHeight, {30, 30, 30, 100});
        int yCount = 0;
        for (size_t i = selectedOption; i < menuOptions.size(); i++)
        {
            const size_t real_i = i % menuOptions.size(); //To draw an infinite menu~
            int xOffset = 0;
            auto binds  = menuOptions.at(real_i)->GetBinds();
            Color colour = {255, 255, 255, 100};
            if (real_i == selectedOption)
            {
                colour = WHITE;
            }
            DrawText(menuOptions.at(real_i)->GetText().c_str(), 0, 10 + yCount*30, 10, colour);
            if (isFocused)
            {
                for (int j = 0; j < binds.size(); j++)
                {
                    if (real_i == selectedOption && j == menuOptions.at(real_i)->GetSelectedBind())
                    {
                        if (isRebinding)
                            DrawText("?", xOffset, 10 + yCount*30 + 10, 10, WHITE);
                        else
                            DrawText(binds.at(j).data(), xOffset, 10 + yCount*30 + 10, 10, WHITE);
                    }
                    else
                        DrawText(binds.at(j).data(), xOffset, 10 + yCount*30 + 10, 10, {255, 255, 255, 100});
                    xOffset += 5 + MeasureText(binds.at(j).data(), 10);
                }
            } else
            {
                for (int j = 0; j < binds.size(); j++)
                {
                    DrawText(binds.at(j).data(), xOffset, 10 + yCount*30 + 10, 10, {255, 255, 255, 100});
                    xOffset += 5 + MeasureText(binds.at(j).data(), 10);
                }
            }
            yCount++;
        }

        if (isRebinding)
        {
            if (menuOptions.at(selectedOption)->HandleRebinding())
                isRebinding = false;
            return true;
        }

        if (InputHandler::CheckInputsPressedMenu(INPUT_MENU))
        {
            if (isFocused)
            {
                isFocused = false;
                isRebinding = false;
                return true;
            }
            ConfigHandler::WriteFile();
            return false;
        }

        if (InputHandler::CheckInputsPressedMenu(INPUT_DOWN))
        {
            if (!isFocused)
            {
                SoundHandler::PlaySound(THUMP_1);
                if (selectedOption++ >= menuOptions.size() - 1)
                    selectedOption = 0;
            }
        }
        if (InputHandler::CheckInputsPressedMenu(INPUT_UP))
        {
            if (!isFocused)
            {
                SoundHandler::PlaySound(THUMP_1);
                if (selectedOption-- == 0)
                    selectedOption = menuOptions.size() - 1;
            }
        }
        if (InputHandler::CheckInputsPressedMenu(INPUT_FIRE))
        {
            if (!isFocused)
            {
                isFocused = true;
                menuOptions.at(selectedOption)->PressOK();
            } else
            {
                menuOptions.at(selectedOption)->WaitForGamepadRelease();
                isRebinding = true;
            }
        }

        if (InputHandler::CheckInputsPressedMenu(INPUT_HYPER))
        {
            if (isFocused)
                isFocused = false;
            else
            {
                ConfigHandler::WriteFile();
                return false;
            }
        }

        if (InputHandler::CheckInputsPressedMenu(INPUT_LEFT) && isFocused)
        {
            menuOptions.at(selectedOption)->PressLeft();
        }
        if (InputHandler::CheckInputsPressedMenu(INPUT_RIGHT) && isFocused)
        {
            menuOptions.at(selectedOption)->PressRight();
        }
        return true;
    }
};

class ControlMenuGamepad : public ControlMenu
{
    void InitMenu() override
    {
        int yPos = 0;
        for (auto& i : *InputHandler::GetGameInputList())
        {
            menuOptions.emplace_back(std::make_unique<ControlRebindOption>(i, true));
            yPos += 10;
        }
    }
};
#endif //RAYLIB_STG_MENUS_H