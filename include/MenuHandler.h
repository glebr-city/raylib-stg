//
// Created by n on 12/08/2026.
//

#ifndef RAYLIB_STG_MENUHANDLER_H
#define RAYLIB_STG_MENUHANDLER_H
#include "PauseHandler.h"
#include "raylib.h"

class MenuHandler
{
public:
    static void HandleMenus()
    {
        if (IsKeyPressed(KEY_TAB))
        {
            PauseHandler::SetPause(false);
            return;
        }
    }
};
#endif //RAYLIB_STG_MENUHANDLER_H