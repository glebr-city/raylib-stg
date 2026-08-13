//
// Created by n on 12/08/2026.
//

#include "MenuHandler.h"

#include <array>

#include "MenuOptions.h"
std::array<std::unique_ptr<MenuOption>, MenuHandler::OPTION_COUNT> MenuHandler::menuOptions = {
    std::make_unique<ResumeOption>(),
    std::make_unique<RestartOption>(),
    std::make_unique<SoundVolumeOption>(),
    std::make_unique<QuitOption>(),
};
size_t MenuHandler::selectedOption = 0;
