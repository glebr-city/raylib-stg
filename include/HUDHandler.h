//
// Created by g on 15/02/2026.
//

#ifndef RAYLIB_STG_HUDHANDLER_H
#define RAYLIB_STG_HUDHANDLER_H
#include <string>

#include "raylib.h"
#include "ScoreHandler.h"

class HUDHandler {
private:
    static const Color scoreColour;
    static const Color multiplierColour;
    static int yOffset;
    static const Texture2D lifeIcon;
public:
    static void doPreStep(const Vector2 playerPos);
};
#endif //RAYLIB_STG_HUDHANDLER_H