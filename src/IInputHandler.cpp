//
// Created by g on 30/10/2026.
//
#include <array>
#include <IInputHandler.h>
#include <memory>
#include <vector>

Vector2 IInputHandler::inputVector {};


const std::vector<MyKey> IInputHandler::leftInputs = {MyKey(KEY_LEFT), MyKey(KEY_P), MyKey(KEY_A)};
const std::vector<MyKey> IInputHandler::rightInputs = {MyKey(KEY_RIGHT), MyKey(KEY_RIGHT_BRACKET), MyKey(KEY_D)};
const std::vector<MyKey> IInputHandler::upInputs = {MyKey(KEY_UP), MyKey(KEY_RIGHT_ALT), MyKey(KEY_W)};
const std::vector<MyKey> IInputHandler::downInputs = {MyKey(KEY_DOWN), MyKey(KEY_LEFT_BRACKET), MyKey(KEY_S)};
const std::vector<MyKey> IInputHandler::focusInputs = {MyKey(KEY_LEFT_SHIFT), MyKey(KEY_RIGHT_SHIFT), MyKey(KEY_SPACE)};
const std::vector<MyKey> IInputHandler::hyperInputs = {MyKey(KEY_X), MyKey(KEY_LEFT_CONTROL), MyKey(KEY_PERIOD)};
const std::vector<MyKey> IInputHandler::fireInputs = {MyKey(KEY_Z), MyKey(KEY_SLASH), MyKey(KEY_NULL)};
const std::vector<MyKey> IInputHandler::menuInputs = {MyKey(KEY_TAB), MyKey(KEY_NULL), MyKey(KEY_NULL)};
const std::vector<MyKey> IInputHandler::restartInputs = {MyKey(KEY_R), MyKey(KEY_NULL), MyKey(KEY_NULL)};

const std::vector<MyButton> IInputHandler::leftInputsGamepad = {MyButton(GAMEPAD_BUTTON_LEFT_FACE_LEFT), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> IInputHandler::rightInputsGamepad = {MyButton(GAMEPAD_BUTTON_LEFT_FACE_RIGHT), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> IInputHandler::upInputsGamepad = {MyButton(GAMEPAD_BUTTON_LEFT_FACE_UP), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> IInputHandler::downInputsGamepad = {MyButton(GAMEPAD_BUTTON_LEFT_FACE_DOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> IInputHandler::focusInputsGamepad = {MyButton(GAMEPAD_BUTTON_LEFT_TRIGGER_1), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> IInputHandler::hyperInputsGamepad = {MyButton(GAMEPAD_BUTTON_RIGHT_FACE_RIGHT), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> IInputHandler::fireInputsGamepad = {MyButton(GAMEPAD_BUTTON_RIGHT_FACE_DOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> IInputHandler::menuInputsGamepad = {MyButton(GAMEPAD_BUTTON_MIDDLE_RIGHT), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::vector<MyButton> IInputHandler::restartInputsGamepad = {MyButton(GAMEPAD_BUTTON_MIDDLE_LEFT), MyButton(GAMEPAD_BUTTON_UNKNOWN), MyButton(GAMEPAD_BUTTON_UNKNOWN)};
const std::array<std::shared_ptr<GameInput>, INPUT_COUNT> IInputHandler::gameInputs =  {
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
