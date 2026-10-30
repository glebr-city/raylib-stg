//
// Created by g on 05/02/2026.
//
#include <InputHandler.h>

IInputHandler* InputHandler::currentInputHandler = nullptr;


//std::array<std::shared_ptr<std::array<std::shared_ptr<GameInput>, 3>({})>, INPUT_COUNT> IInputHandler::gameInputs =  {
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

