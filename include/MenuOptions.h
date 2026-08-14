//
// Created by n on 12/08/2026.
//

#ifndef RAYLIB_STG_MENUOPTIONS_H
#define RAYLIB_STG_MENUOPTIONS_H
#include "PauseHandler.h"
#include "GameHandler.h"

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
#endif //RAYLIB_STG_MENUOPTIONS_H