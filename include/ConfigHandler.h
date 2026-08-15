//
// Created by n on 14/08/2026.
//
#ifndef RAYLIB_STG_CONFIGHANDLER_H
#define RAYLIB_STG_CONFIGHANDLER_H

#include <filesystem>
#include <ostream>
#include <sstream>

#include "GlobalVariables.h"
#include "InputHandler.h"
#include "rini.h"

class ConfigHandler
{
public:
    static void ReadFile()
    {
        std::stringstream ss;
        ss << GetApplicationDirectory() << "userdata";
        std::filesystem::create_directory(ss.str());
        ChangeDirectory(ss.str().c_str());
        rini_data config = rini_load("config.ini");
        GlobalVariables::SetRenderTextureFilter(rini_get_value(config, "screen_filter"));
        GlobalVariables::SetEffectVolume(rini_get_value(config, "effect_volume"));
        GlobalVariables::SetScreenRotation(rini_get_value(config, "screenRotation"));
        //Handle input binds
        for (const auto& i : *InputHandler::GetGameInputList())
        {
            for (size_t j = 0; j < i->keys.size(); j++)
            {
                std::stringstream keyName;
                keyName << "keybind_" << i->name << "_" << j;
                if (const int bind = rini_get_value(config, keyName.str().c_str()); bind > 0)
                    InputHandler::SetKeyBind(i, j, static_cast<KeyboardKey>(bind));
            }
        }
        rini_save(config, "config.ini");
        rini_unload(&config);
        ChangeDirectory(GetApplicationDirectory());
    }
    static void WriteFile()
    {
        std::stringstream ss;
        ss << GetApplicationDirectory() << "userdata";
        std::filesystem::create_directory(ss.str());
        ChangeDirectory(ss.str().c_str());
        rini_data config = rini_load("config.ini");
        rini_set_value(&config, "screen_filter", GlobalVariables::GetTextureFilter(), "");
        rini_set_value(&config, "effect_volume", GlobalVariables::GetEffectVolume(), "");
        rini_set_value(&config, "screenRotation", GlobalVariables::GetScreenRotation(), "");
        //Handle input binds
        for (const auto& i : *InputHandler::GetGameInputList())
        {
            for (size_t j = 0; j < i->keys.size(); j++)
            {
                std::stringstream keyName;
                keyName << "keybind_" << i->name << "_" << j;
                rini_set_value(&config, keyName.str().c_str(), i->keys[j].k, "");
                if (const int bind = rini_get_value(config, keyName.str().c_str()); bind > 0)
                    InputHandler::SetKeyBind(i, j, static_cast<KeyboardKey>(bind));
            }
        }
        rini_save(config, "config.ini");
        rini_unload(&config);
        ChangeDirectory(GetApplicationDirectory());
    }
};
#endif //RAYLIB_STG_CONFIGHANDLER_H