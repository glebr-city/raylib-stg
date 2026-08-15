//
// Created by n on 12/08/2026.
//

#ifndef RAYLIB_STG_MENUHANDLER_H
#define RAYLIB_STG_MENUHANDLER_H
#include <array>
#include <cstdint>
#include <memory>

#include "MenuList.h"
#include "MenuOptions.h"
#include "Menus.h"



class MenuHandler
{
private:
    static constexpr uint8_t OPTION_COUNT = 5;
    static std::array<std::unique_ptr<Menu>, MENU_COUNT> menus;
    static size_t selectedMenu;
public:

    static void InitMenus()
    {
        menus = {
            std::make_unique<MainMenu>(),
            std::make_unique<ControlMenu>(),
        };

        for (const auto &i : menus)
        {
            i->InitMenu();
        }
    }

    static void HandleMenus()
    {
        if (!menus.at(selectedMenu)->HandleMenu())
            SwitchMenu(menus.at(selectedMenu)->GetDesiredMenu());
    }

    static void OpenMenu()
    {
        menus.at(selectedMenu)->OpenMenu();
    }

    static void SwitchMenu(const MENUS _menu)
    {
        if (_menu == selectedMenu)
            return;
        selectedMenu = _menu;
        OpenMenu();
        return;
    }
};
#endif //RAYLIB_STG_MENUHANDLER_H