//
// Created by n on 14/08/2026.
//

#ifndef RAYLIB_STG_MENUS_H
#define RAYLIB_STG_MENUS_H
class Menu
{
protected:
    std::vector<std::unique_ptr<MenuOption>> menuOptions;
    size_t selectedOption = 0;
    Menu() = default;
public:
    virtual ~Menu() = default;
    virtual void InitMenu() = 0;
    virtual void HandleMenu(){};
};

class MainMenu : public Menu
{

public:
    void InitMenu() override
    {
        menuOptions.emplace_back(std::make_unique<ResumeOption>());
        menuOptions.emplace_back(std::make_unique<RestartOption>());
        menuOptions.emplace_back(std::make_unique<SoundVolumeOption>());
        menuOptions.emplace_back(std::make_unique<ScreenFilterOption>());
        menuOptions.emplace_back(std::make_unique<QuitOption>());
    }

    void HandleMenu() override
    {
        DrawRectangle(0, 0, gameWidth, gameHeight, {30, 30, 30, 100});
        for (int i = 0; i < menuOptions.size(); i++)
        {
            if (i == selectedOption)
                DrawText(menuOptions.at(i)->GetText().c_str(), 0, 10 + i*10, 10, WHITE);
            else
                DrawText(menuOptions.at(i)->GetText().c_str(), 0, 10 + i*10, 10, {255, 255, 255, 100});
        }
        if (!PauseHandler::GetReleased())
        {
            if (IsKeyReleased(KEY_TAB))
                PauseHandler::ReleaseButton();
        } else if (IsKeyPressed(KEY_TAB))
            PauseHandler::SetPause(false);
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
#endif //RAYLIB_STG_MENUS_H