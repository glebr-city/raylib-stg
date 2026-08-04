#include "BackgroundHandler.h"

#include "raylib.h"
//
// Created by n on 04/08/2026.
//
STATIC_SPRITES BackgroundHandler::backgroundSprite = {};
Vector2 BackgroundHandler::currentScrollVector = {}; //Scrolling for the background and grounded enemies!
Vector2 BackgroundHandler::currentBackgroundPosition = {};