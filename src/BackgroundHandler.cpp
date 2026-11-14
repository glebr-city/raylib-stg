#include "BackgroundHandler.h"

#include "OtherBackgrounds.h"
#include "raylib.h"
//
// Created by n on 04/08/2026.
//
BACKGROUNDS BackgroundHandler::currentBackgroundIndex = BACKGROUND_STAGE_1;
std::unique_ptr<Background> BackgroundHandler::currentBackground = nullptr;
Vector2 BackgroundHandler::currentScrollVector = {}; //Scrolling for the background and grounded enemies!
Vector2 BackgroundHandler::currentBackgroundPosition = {};

const std::array<BackgroundRef, BACKGROUND_COUNT> BackgroundHandler::backgrounds = {{
    {[]() -> Background* { return new Stage1Background(); }},
{[]() -> Background* { return new Stage2Background(); }},
{[]() -> Background* { return new Stage3Background(); }},
    }};