#include <array>
#include <iostream>
#include <memory>
#include <../include/raylib/raylib.h>

#include "ConfigHandler.h"
#include "MainLoopHandler.h"
#if DEBUG_BUILD
#include <sstream>
#include <iomanip>
#endif

#include "BackgroundHandler.h"
#include "GameHandler.h"
#include "GlobalVariables.h"
#include "HUDHandler.h"
#include "InputHandler.h"
#include "MenuHandler.h"
#include "PauseHandler.h"
#include "PhaseHelper.h"
#include "SpriteHandler.h"
#include "SoundHandler.h"









int main() {
    MainLoopHandler::InitApplication();
    while (!WindowShouldClose()) {
        MainLoopHandler::DoMainLoop();
    }
}