//
// Created by g on 05/02/2026.
//

#include "../include/InputHandler.h"

#include <algorithm>

Vector2 InputHandler::inputVector {};



const std::vector<MyKey> InputHandler::leftInputs = {MyKey(KEY_LEFT), MyKey(KEY_P), MyKey(KEY_A)};
const std::vector<MyKey> InputHandler::rightInputs = {MyKey(KEY_RIGHT), MyKey(KEY_RIGHT_BRACKET), MyKey(KEY_D)};
const std::vector<MyKey> InputHandler::upInputs = {MyKey(KEY_UP), MyKey(KEY_RIGHT_ALT), MyKey(KEY_W)};
const std::vector<MyKey> InputHandler::downInputs = {MyKey(KEY_DOWN), MyKey(KEY_LEFT_BRACKET), MyKey(KEY_S)};
const std::vector<MyKey> InputHandler::focusInputs = {MyKey(KEY_LEFT_SHIFT), MyKey(KEY_RIGHT_SHIFT), MyKey(KEY_SPACE)};
const std::vector<MyKey> InputHandler::hyperInputs = {MyKey(KEY_X), MyKey(KEY_LEFT_CONTROL), MyKey(KEY_PERIOD)};
const std::vector<MyKey> InputHandler::fireInputs = {MyKey(KEY_Z), MyKey(KEY_SLASH), MyKey(KEY_NULL)};
const std::vector<MyKey> InputHandler::menuInputs = {MyKey(KEY_TAB), MyKey(KEY_NULL), MyKey(KEY_NULL)};
const std::vector<MyKey> InputHandler::restartInputs = {MyKey(KEY_R), MyKey(KEY_NULL), MyKey(KEY_NULL)};

const std::vector<MyButton> InputHandler::leftInputsGamepad = {MyButton(GAMEPAD_BUTTON_LEFT_FACE_LEFT), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> InputHandler::rightInputsGamepad = {MyButton(GAMEPAD_BUTTON_LEFT_FACE_RIGHT), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> InputHandler::upInputsGamepad = {MyButton(GAMEPAD_BUTTON_LEFT_FACE_UP), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> InputHandler::downInputsGamepad = {MyButton(GAMEPAD_BUTTON_LEFT_FACE_DOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> InputHandler::focusInputsGamepad = {MyButton(GAMEPAD_BUTTON_LEFT_TRIGGER_1), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> InputHandler::hyperInputsGamepad = {MyButton(GAMEPAD_BUTTON_RIGHT_FACE_RIGHT), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> InputHandler::fireInputsGamepad = {MyButton(GAMEPAD_BUTTON_RIGHT_FACE_DOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> InputHandler::menuInputsGamepad = {MyButton(GAMEPAD_BUTTON_MIDDLE_RIGHT), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> InputHandler::restartInputsGamepad = {MyButton(GAMEPAD_BUTTON_MIDDLE_LEFT), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};

const std::array<std::shared_ptr<GameInput>, INPUT_COUNT> InputHandler::gameInputs =  {
    std::make_shared<GameInput>("left" , leftInputs, leftInputsGamepad),
    std::make_shared<GameInput>("right", rightInputs, rightInputsGamepad),
    std::make_shared<GameInput>("up", upInputs, upInputsGamepad),
    std::make_shared<GameInput>("down", downInputs, downInputsGamepad),
    std::make_shared<GameInput>("focus", focusInputs, focusInputsGamepad),
    std::make_shared<GameInput>("hyper", hyperInputs, hyperInputsGamepad),
    std::make_shared<GameInput>("fire", fireInputs, fireInputsGamepad),
    std::make_shared<GameInput>("menu", menuInputs, menuInputsGamepad),
    std::make_shared<GameInput>("restart", restartInputs, restartInputsGamepad),
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

