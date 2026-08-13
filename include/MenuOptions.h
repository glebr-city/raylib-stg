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
    uint_fast8_t soundVolume = 100;
public:
    SoundVolumeOption() : MenuOption("sound volume: ")
    {
        soundVolume = 100;
        text = text.append(std::to_string(soundVolume));
    };
    bool PressRight() override
    {
        soundVolume = std::min(soundVolume + 10, 100);
        text = "sound volume: ";
        text = text.append(std::to_string(soundVolume));
        //SoundHandler::SetAllSoundVolume(static_cast<float>(soundVolume) / 100);
        SetMasterVolume(static_cast<float>(soundVolume) / 100);
        SoundHandler::PlaySound(0, EXPLOSION_2, false);
        return false;
    }

    bool PressLeft() override
    {
        soundVolume = std::max(soundVolume - 10, 0);
        text = "sound volume: ";
        text = text.append(std::to_string(soundVolume));
        //SoundHandler::SetAllSoundVolume(static_cast<float>(soundVolume) / 100);
        SetMasterVolume(static_cast<float>(soundVolume) / 100);
        SoundHandler::PlaySound(0, EXPLOSION_2, false);
        return false;
    }
};
#endif //RAYLIB_STG_MENUOPTIONS_H