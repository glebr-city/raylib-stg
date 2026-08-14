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
#include "Menus.h"
#include "raylib.h"

typedef enum
{
    MENU_MAIN = 0,
    MENU_COUNT
}MENUS;

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
        };

        for (const auto &i : menus)
        {
            i->InitMenu();
        }
    }

    static void HandleMenus()
    {
        menus.at(selectedMenu)->HandleMenu();
    }
};
#endif //RAYLIB_STG_MENUHANDLER_H