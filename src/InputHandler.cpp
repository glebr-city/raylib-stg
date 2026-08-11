//
// Created by g on 05/02/2026.
//

#include "../include/InputHandler.h"

#include <algorithm>

Vector2 InputHandler::inputVector {};



const std::array<std::shared_ptr<MyKey>, 3> InputHandler::leftInputs = {std::make_shared<MyKey>(KEY_LEFT), std::make_shared<MyKey>(KEY_P), std::make_shared<MyKey>(KEY_A)};
const std::array<std::shared_ptr<MyKey>, 3> InputHandler::rightInputs = {std::make_shared<MyKey>(KEY_RIGHT), std::make_shared<MyKey>(KEY_RIGHT_BRACKET), std::make_shared<MyKey>(KEY_D)};
const std::array<std::shared_ptr<MyKey>, 3> InputHandler::upInputs = {std::make_shared<MyKey>(KEY_UP), std::make_shared<MyKey>(KEY_RIGHT_ALT), std::make_shared<MyKey>(KEY_W)};
const std::array<std::shared_ptr<MyKey>, 3> InputHandler::downInputs = {std::make_shared<MyKey>(KEY_DOWN), std::make_shared<MyKey>(KEY_LEFT_BRACKET), std::make_shared<MyKey>(KEY_S)};
const std::array<std::shared_ptr<MyKey>, 3> InputHandler::focusInputs = {std::make_shared<MyKey>(KEY_LEFT_SHIFT), std::make_shared<MyKey>(KEY_RIGHT_SHIFT), std::make_shared<MyKey>(KEY_SPACE)};
const std::array<std::shared_ptr<MyKey>, 3> InputHandler::hyperInputs = {std::make_shared<MyKey>(KEY_X), std::make_shared<MyKey>(KEY_LEFT_CONTROL), std::make_shared<MyKey>(KEY_PERIOD)};
const std::array<std::shared_ptr<MyKey>, 3> InputHandler::fireInputs = {std::make_shared<MyKey>(KEY_Z), std::make_shared<MyKey>(KEY_SLASH), std::make_shared<MyKey>(KEY_Z)};
const std::array<std::shared_ptr<MyKey>, 3> InputHandler::restartInputs = {std::make_shared<MyKey>(KEY_R), std::make_shared<MyKey>(KEY_R), std::make_shared<MyKey>(KEY_R)};

const std::array<std::shared_ptr<std::array<std::shared_ptr<MyKey>, 3>>, INPUT_COUNT> InputHandler::gameInputs =  {
    std::make_shared<std::array<std::shared_ptr<MyKey>, 3>>(leftInputs),
    std::make_shared<std::array<std::shared_ptr<MyKey>, 3>>(rightInputs),
    std::make_shared<std::array<std::shared_ptr<MyKey>, 3>>(upInputs),
    std::make_shared<std::array<std::shared_ptr<MyKey>, 3>>(downInputs),
    std::make_shared<std::array<std::shared_ptr<MyKey>, 3>>(focusInputs),
    std::make_shared<std::array<std::shared_ptr<MyKey>, 3>>(hyperInputs),
    std::make_shared<std::array<std::shared_ptr<MyKey>, 3>>(fireInputs),
    std::make_shared<std::array<std::shared_ptr<MyKey>, 3>>(restartInputs),
};


//std::array<std::shared_ptr<std::array<std::shared_ptr<GameInput>, 3>({})>, INPUT_COUNT> InputHandler::gameInputs =  {
    //std::make_shared<std::array<std::shared_ptr<GameInput>, 3>>()
    /*
    std::make_shared<std::array<std::make_shared<GameInput>, 3>>({KEY_LEFT, KEY_P, KEY_A}))),
    std::make_shared<GameInput>(std::array<KeyboardKey, 3>({KEY_RIGHT, KEY_RIGHT_BRACKET, KEY_D})),
    std::make_shared<GameInput>(std::array<KeyboardKey, 3>({KEY_UP, KEY_RIGHT_ALT, KEY_W})),
    std::make_shared<GameInput>(std::array<KeyboardKey, 3>({KEY_DOWN, KEY_LEFT_BRACKET, KEY_S})),
    std::make_shared<GameInput>(std::array<KeyboardKey, 3>({KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT, KEY_SPACE})),

    std::make_shared<GameInput>(std::array<KeyboardKey, 3>({KEY_X, KEY_LEFT_CONTROL, KEY_PERIOD})),
    std::make_shared<GameInput>(std::array<KeyboardKey, 3>({KEY_Z, KEY_SLASH})),
    std::make_shared<GameInput>(std::array<KeyboardKey, 3>({KEY_R})),
};*/

