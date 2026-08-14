//
// Created by n on 12/08/2026.
//

#include "MenuHandler.h"

#include <array>

#include "MenuOptions.h"
std::array<std::unique_ptr<Menu>, MENU_COUNT> MenuHandler::menus = {};
size_t MenuHandler::selectedMenu = 0;
