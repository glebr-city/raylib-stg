//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_INPUTHANDLER_H
#define RAYLIB_STG_INPUTHANDLER_H
#include <memory>
#include <vector>

#include "OtherInputHandlers.h"
#include "raylib/raylib.h"

typedef enum
{
    DEFAULT_INPUT_HANDLER = 0,
    REPLAY_INPUT_HANDLER,

    INPUT_HANDLER_COUNT
}INPUT_HANDLERS;

class InputHandler {
private:
    static std::array<IInputHandler*, INPUT_HANDLER_COUNT> inputHandlers;
    static INPUT_HANDLERS currentInputHandler;
public:
    static void Init() {
        inputHandlers = {new DefaultInputHandler(), new ReplayInputHandler()};
        SetInputHandler(DEFAULT_INPUT_HANDLER);
    }

    static auto GetGameInputList() {
        return IInputHandler::GetGameInputList();
    }

    static std::vector<KeyboardKey> GetGameInputKeys (const INPUTS _i)
    {
        return IInputHandler::GetGameInputKeys(_i);
    }

    static bool CheckInputsPressedMenu(const INPUTS i)
    {
        return inputHandlers[currentInputHandler]->CheckInputsPressedMenu(i);
    }

    static bool CheckInputsPressed(const INPUTS i) {
        return inputHandlers[currentInputHandler]->CheckInputsPressed(i);
    }

    static bool CheckInputsDown(const INPUTS i) {
        return inputHandlers[currentInputHandler]->CheckInputsDown(i);
    }
    static bool CheckInputsDown(int i) {
        return inputHandlers[currentInputHandler]->CheckInputsDown(i);
    }

    static bool CheckInputsReleased(const INPUTS i) {
        return inputHandlers[currentInputHandler]->CheckInputsReleased(i);
    }

    static void UpdateInputsMenu()
    {
        return inputHandlers[currentInputHandler]->UpdateInputsMenu();
    }

    static void ClearInputsMenu()
    {
        return inputHandlers[currentInputHandler]->ClearInputsMenu();
    }

    static void UpdateInputs()
    {
        return inputHandlers[currentInputHandler]->UpdateInputs();
    }

    static Vector2 GetInputVector()
    {
        return IInputHandler::GetInputVector();
    }


    static void SetKeyBind(const std::shared_ptr<GameInput>& i, const size_t index, const KeyboardKey _newBind)
    {
        return IInputHandler::SetKeyBind(i, index, _newBind);
    }

    static void SetButtonBind(const std::shared_ptr<GameInput>& i, const size_t index, GamepadButton _newBind)
    {
        return IInputHandler::SetButtonBind(i, index, _newBind);
    }


    static void SetInputHandler(const INPUT_HANDLERS newHandler)
    {
        currentInputHandler = newHandler;
    }
    static void SetInputHandler(const size_t newHandler)
    {
        currentInputHandler = static_cast<INPUT_HANDLERS>(newHandler);
    }
    static size_t GetCurrentInputHandlerIndex()
    {
        return static_cast<size_t>(currentInputHandler);
    }
};
#endif //RAYLIB_STG_INPUTHANDLER_H