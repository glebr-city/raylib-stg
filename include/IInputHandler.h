//
// Created by g on 30/10/2026.
//

#ifndef RAYLIB_STG_IINPUTHANDLER_H
#define RAYLIB_STG_IINPUTHANDLER_H
#include <memory>
#include <vector>

#include "raylib.h"

struct MyKey
{
    KeyboardKey k = KEY_SPACE; //Keys (as on a keyboard).
    bool d = false; //Down?
    bool l = false; //Last frame, down?
    bool md = false; //Menu, down?
    bool ml = false; //Menu, last frame, down?
};

struct MyButton
{
    GamepadButton b = GAMEPAD_BUTTON_RIGHT_FACE_DOWN; //Buttons (as on a gamepad controller).
    bool d = false; //Down?
    bool l = false; //Last frame, down?
    bool md = false; //Menu, down?
    bool ml = false; //Menu, last frame, down?
};

typedef enum
{
    INPUT_LEFT = 0,
    INPUT_RIGHT,
    INPUT_UP,
    INPUT_DOWN,
    INPUT_FOCUS,
    INPUT_HYPER,
    INPUT_FIRE,
    INPUT_MENU,
    INPUT_RESTART,

    INPUT_COUNT
} INPUTS;
struct GameInput
{
    std::string name;
    std::vector<MyKey> keys;
    std::vector<MyButton> buttons;
};
class IInputHandler {
public:
    virtual ~IInputHandler() = default;

    static const std::vector<MyKey> leftInputs;
    static const std::vector<MyKey> rightInputs;
    static const std::vector<MyKey> upInputs;
    static const std::vector<MyKey> downInputs;
    static const std::vector<MyKey> focusInputs;
    static const std::vector<MyKey> hyperInputs;
    static const std::vector<MyKey> fireInputs;
    static const std::vector<MyKey> menuInputs;
    static const std::vector<MyKey> restartInputs;

    static const std::vector<MyButton> leftInputsGamepad;
    static const std::vector<MyButton> rightInputsGamepad;
    static const std::vector<MyButton> upInputsGamepad;
    static const std::vector<MyButton> downInputsGamepad;
    static const std::vector<MyButton> focusInputsGamepad;
    static const std::vector<MyButton> hyperInputsGamepad;
    static const std::vector<MyButton> fireInputsGamepad;
    static const std::vector<MyButton> menuInputsGamepad;
    static const std::vector<MyButton> restartInputsGamepad;
protected:
    static const std::array<std::shared_ptr<GameInput>, INPUT_COUNT> gameInputs;
    static Vector2 inputVector;

    static auto getGameInput(const INPUTS _i)
    {
        return gameInputs.at(_i);
    }

    virtual void UpdateInputVector(){};

    public:

    virtual void Reset()
    {
        for (int i = 0; i < INPUT_COUNT; i++)
        {
            for (auto& j : getGameInput(static_cast<INPUTS>(i))->keys)
            {
                j.d = false;
                j.l = true;
            }
            for (auto& j : getGameInput(static_cast<INPUTS>(i))->buttons)
            {
                j.d = false;
                j.l = true;
            }
        }
        UpdateInputVector();
    }

    static auto GetGameInputList() {
        return &gameInputs;
    }

    static std::vector<KeyboardKey> GetGameInputKeys (const INPUTS _i)
    {
        std::vector<KeyboardKey> keys;
        for (const auto& j : getGameInput(_i)->keys)
        {
            keys.emplace_back(j.k);
        }
        return keys;
    }

    virtual bool CheckInputsPressedMenu(INPUTS i){return false;};

    virtual bool CheckInputsPressed(INPUTS i){return false;};

    virtual bool CheckInputsDown(INPUTS i){return false;};

    virtual bool CheckInputsDown(int i){return false;};

    virtual bool CheckInputsReleased(INPUTS i){return false;};

    virtual void UpdateInputsMenu()
    {
        for (int j = 0; j < INPUT_COUNT; j++)
        {
            for (auto& k: gameInputs.at(j)->keys)
            {
                k.ml = k.md;
                k.md = IsKeyDown(k.k);
            }

            for (auto& k: gameInputs.at(j)->buttons)
            {
                k.ml = k.md;
                k.md = false;
                int i = -1;
                while (IsGamepadAvailable(++i))
                {
                    if (IsGamepadButtonDown(i, k.b))
                    {
                        k.md = true;
                        break;
                    }
                }
            }
        }
    }

    virtual void ClearInputsMenu(){};

    virtual void UpdateInputs(){};

    static Vector2 GetInputVector()
    {
        return inputVector;
    }


    static void SetKeyBind(const std::shared_ptr<GameInput>& i, const size_t index, const KeyboardKey _newBind)
    {
        i->keys.at(index).k = _newBind;
    }

    static void SetButtonBind(const std::shared_ptr<GameInput>& i, const size_t index, const GamepadButton _newBind)
    {
        i->buttons.at(index).b = _newBind;
    }
};
#endif //RAYLIB_STG_IINPUTHANDLER_H