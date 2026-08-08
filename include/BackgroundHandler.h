//
// Created by n on 04/08/2026.
//

#ifndef RAYLIB_STG_BACKGROUNDHANDLER_H
#define RAYLIB_STG_BACKGROUNDHANDLER_H
#include "raylib/raylib.h"
#include "raymath.h"
#include "SpriteHandler.h"
#include "SpriteHandlerEnums.h"

class BackgroundHandler
{
private:
    static STATIC_SPRITES backgroundSprite;
    static Vector2 currentScrollVector; //Scrolling for the background and grounded enemies!
    static Vector2 currentBackgroundPosition;
public:
    static STATIC_SPRITES GetBackgroundSprite()
    {
        return backgroundSprite;
    }
    static void SetBackgroundSprite(const STATIC_SPRITES newBackgroundSprite)
    {
        backgroundSprite = newBackgroundSprite;
    }
    static Vector2 GetBackgroundPosition()
    {
        return currentBackgroundPosition;
    }
    static void SetBackgroundPosition(const Vector2 newBackgroundPosition)
    {
        currentBackgroundPosition = newBackgroundPosition;
    }

    static Vector2 GetAbsolutePos(const Vector2 relativePos) //Origin here is the bottom left of the screen -- (0, 180)
    {
        return Vector2Subtract({relativePos.x, relativePos.y - 180}, currentBackgroundPosition);
    }

    static Vector2 GetRelativePos(const Vector2 absolutePos) //Origin here is the bottom left of the screen -- (0, 180)
    {
        return Vector2Add({absolutePos.x, absolutePos.y + 180}, currentBackgroundPosition);
    }

    static Vector2 GetScrollVector() //Get the (current) scroll vector; used by grounded enemies and the background.
    {
        return currentScrollVector;
    }
    static void SetScrollVector(const Vector2 newScrollVector)
    {
        currentScrollVector = newScrollVector;
    }

    static void ScrollBackground()
    {
        currentBackgroundPosition = Vector2Add(currentBackgroundPosition, currentScrollVector);
    }
};
#endif //RAYLIB_STG_BACKGROUNDHANDLER_H