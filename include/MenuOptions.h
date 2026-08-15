//
// Created by n on 12/08/2026.
//

#ifndef RAYLIB_STG_MENUOPTIONS_H
#define RAYLIB_STG_MENUOPTIONS_H
#include "PauseHandler.h"
#include "GameHandler.h"
#include "KeyNameDictionary.h"

class MenuOption
{
protected:
    std::string text = {};
public:
    MenuOption(const std::string& _text)
    {
        text = _text;
    }
    virtual ~MenuOption() = default;
    virtual std::string GetText()
    {
        return text;
    }
    virtual bool PressOK()
    {
        return false;
    };
    virtual bool PressLeft()
    {
        return false;
    };
    virtual bool PressRight()
    {
        return false;
    };

    virtual void Update()
    {
    }
    virtual MENUS GetDesiredMenu()
    {
        return MENU_MAIN;
    }
};

class ResumeOption : public MenuOption
{
    public:
    ResumeOption() : MenuOption("resume"){};
    bool PressOK() override
    {
        PauseHandler::SetPause(false);
        return false;
    }
};

class RestartOption : public MenuOption
{
public:
    RestartOption() : MenuOption("restart"){};
    bool PressOK() override
    {
        GameHandler::RestartGame();
        return false;
    }
};

class QuitOption : public MenuOption
{
public:
    QuitOption() : MenuOption("quit"){};
    bool PressOK() override
    {
        CloseWindow();
        return false;
    }
};

class SoundVolumeOption : public MenuOption
{
private:
    uint_fast8_t effectVolume = 100;
public:
    SoundVolumeOption() : MenuOption("effect volume: ")
    {
        effectVolume = GlobalVariables::GetEffectVolume();
        text = text.append(std::to_string(effectVolume));
    };
    bool PressRight() override
    {
        effectVolume = std::min(effectVolume + 10, 100);
        text = "effect volume: ";
        text = text.append(std::to_string(effectVolume));
        //SoundHandler::SetAllSoundVolume(static_cast<float>(soundVolume) / 100);
        GlobalVariables::SetEffectVolume(effectVolume);
        SoundHandler::PlaySound(0, EXPLOSION_2, false);
        return false;
    }

    bool PressLeft() override
    {
        effectVolume = std::max(effectVolume - 10, 0);
        text = "effect volume: ";
        text = text.append(std::to_string(effectVolume));
        //SoundHandler::SetAllSoundVolume(static_cast<float>(soundVolume) / 100);
        GlobalVariables::SetEffectVolume(effectVolume);
        SoundHandler::PlaySound(0, EXPLOSION_2, false);
        return false;
    }
};

class ScreenFilterOption : public MenuOption
{
private:
    RenderTexture2D* renderTexture;
    int textureFilter;
public:
    ScreenFilterOption() : MenuOption("screen filter: ")
    {
        renderTexture = GlobalVariables::GetRenderTexture();
        textureFilter = GlobalVariables::GetTextureFilter();
        if (textureFilter == 1)
            text = text.append("bilinear");
        else
            text = text.append("point");
    }
    bool PressRight() override
    {
        text = "screen filter: ";
        if (textureFilter == 0)
        {
            textureFilter = 1;
            text = text.append("bilinear");
        }
        else
        {
            textureFilter = 0;
            text = text.append("point");
        }
        GlobalVariables::SetRenderTextureFilter(textureFilter);
        SoundHandler::PlaySound(EXPLOSION_2);
        return false;
    }

    bool PressLeft() override
    {
        return PressRight();
    }
};

class ScreenRotationOption : public MenuOption
{
private:
    int screenRotation;
public:
    ScreenRotationOption () : MenuOption("screen rotation: ")
    {
        screenRotation = GlobalVariables::GetScreenRotation();
        text = text.append(std::to_string(screenRotation * 90));
    };
    bool PressRight() override
    {
        text = "screen rotation: ";
        GlobalVariables::SetScreenRotation(++screenRotation);
        screenRotation = GlobalVariables::GetScreenRotation();
        text = text.append(std::to_string(screenRotation * 90));
        SoundHandler::PlaySound(0, EXPLOSION_2, false);
        return false;
    }

    bool PressLeft() override
    {
        screenRotation--;
        text = "screen rotation: ";
        GlobalVariables::SetScreenRotation(screenRotation);
        screenRotation = GlobalVariables::GetScreenRotation();
        text = text.append(std::to_string(screenRotation * 90));
        SoundHandler::PlaySound(0, EXPLOSION_2, false);
        return false;
    }
};

class ControlRebindOption : public MenuOption
{
private:
    size_t selectedBind = 0;
    std::shared_ptr<GameInput> gameInput = nullptr;
    bool isGamepad = false;
    bool waitingForGamepadRelease = false;
public:
    ControlRebindOption(const std::shared_ptr<GameInput>& input, bool _isGamepad = false) : MenuOption(input->name)
    {
        gameInput = input;
        text = text.append(":");
        isGamepad = _isGamepad;
    };

    std::vector<std::string_view> GetBinds()
    {
        std::vector<std::string_view> binds = {};
        text = gameInput->name;
        if (isGamepad)
        {
            for (const auto k : gameInput->buttons)
            {
                binds.emplace_back(GetMyButtonName(k.b));
            }
            return binds;
        }
        for (const auto k : gameInput->keys)
        {
            binds.emplace_back(GetMyKeyName(k.k));
        }
        return binds;
    }

    int GetSelectedBind()
    {
        return selectedBind;
    }

    void SetSelectedBind(const int _bind)
    {
        selectedBind = _bind;
    }

    bool PressRight() override
    {
        ++selectedBind %= GetBinds().size();
        return false;
    }

    bool PressLeft() override
    {
        if (selectedBind < 1)
            selectedBind = GetBinds().size() - 1;
        else
            selectedBind--;
        return false;
    }

    bool PressOK() override
    {
        selectedBind = 0;
        return false;
    }

   bool HandleRebinding() //return true to finish rebinding
    {
        if (isGamepad)
            return HandleRebindingGamepad();
        if (InputHandler::CheckInputsPressedMenu(INPUT_MENU))
        {
            for (int j = 0; j < gameInput->keys.size(); j++)
            {
                if (j != selectedBind && gameInput->keys.at(j).k != 0)
                {
                    InputHandler::SetKeyBind(gameInput, selectedBind, static_cast<KeyboardKey>(0));
                    return true;
                }
            }
            return true;
        }
        if (const int keyPressed = GetKeyPressed(); keyPressed != 0)
        {
            InputHandler::SetKeyBind(gameInput, selectedBind, static_cast<KeyboardKey>(keyPressed));
            return true;
        }
        return false;
    }

    void WaitForGamepadRelease() //Hacky way to avoid the fire key immediately being read as a new button bind; the keyboard equivalent has a built-in queue that fixes this.
    {
        waitingForGamepadRelease = true;
    }

private:
    bool HandleRebindingGamepad() //return true to finish rebinding
    {
        if (waitingForGamepadRelease)
        {
            if (GetGamepadButtonPressed() == 0)
                waitingForGamepadRelease = false;
            return false;
        }
        if (InputHandler::CheckInputsPressedMenu(INPUT_MENU))
        {
            for (int j = 0; j < gameInput->buttons.size(); j++)
            {
                if (j != selectedBind && gameInput->buttons.at(j).b != 0)
                {
                    InputHandler::SetButtonBind(gameInput, selectedBind, static_cast<GamepadButton>(0));
                    return true;
                }
            }
            return true;
        }
        if (const int buttonPressed = GetGamepadButtonPressed(); buttonPressed != 0)
        {
            InputHandler::SetButtonBind(gameInput, selectedBind, static_cast<GamepadButton>(buttonPressed));
            return true;
        }
        return false;
    }
};

class ControlMenuEnterOption : public MenuOption
{
public:
    ControlMenuEnterOption() : MenuOption("controls"){}
    bool PressOK() override
    {
        return true;
    };
    MENUS GetDesiredMenu() override
    {
        return MENU_CONTROL_DEVICE_SELECTION;
    }
};

class ControlDeviceSelectionMenuOptionKeyboard : public MenuOption
{
public:
    ControlDeviceSelectionMenuOptionKeyboard() : MenuOption("keyboard") {}
    MENUS GetDesiredMenu() override
    {
        return MENU_CONTROLS;
    }

    bool PressOK() override
    {
        return true;
    }
};

class ControlDeviceSelectionMenuOptionGamepad : public MenuOption
{
public:
    ControlDeviceSelectionMenuOptionGamepad() : MenuOption("gamepad") {}
    MENUS GetDesiredMenu() override
    {
        return MENU_CONTROLS_GAMEPAD;
    }

    bool PressOK() override
    {
        return true;
    }

};
#endif //RAYLIB_STG_MENUOPTIONS_H