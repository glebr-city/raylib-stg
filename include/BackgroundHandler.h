//
// Created by n on 04/08/2026.
//

#ifndef RAYLIB_STG_BACKGROUNDHANDLER_H
#define RAYLIB_STG_BACKGROUNDHANDLER_H
#include "Background.h"
#include "raymath.h"


class BackgroundHandler
{
private:
    static std::unique_ptr<Background> currentBackground;
    static BACKGROUNDS currentBackgroundIndex;
    static Vector2 currentScrollVector; //Scrolling for the background and grounded enemies!
    static Vector2 currentBackgroundPosition;
    static const std::array<BackgroundRef, BACKGROUND_COUNT> backgrounds;

public:
    static BackgroundRef GetBackground(const BACKGROUNDS _desiredBackground)
    {
        return backgrounds[_desiredBackground];
    }
    static STATIC_SPRITES GetBackgroundSprite()
    {
        return currentBackground->GetBackgroundSprite();
    }
    static void SetBackground(const BACKGROUNDS _desiredBackground)
    {
        if (currentBackgroundIndex == _desiredBackground)
            return;
        currentBackgroundIndex = _desiredBackground;
        Background* newBackground = GetBackground(_desiredBackground).initBackground();
        currentBackground = std::unique_ptr<Background>(newBackground);
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
        return Vector2Add({relativePos.x, relativePos.y - 180}, currentBackgroundPosition);
    }

    static Vector2 GetRelativePos(const Vector2 absolutePos) //Origin here is the bottom left of the screen -- (0, 180)
    {
        return Vector2Subtract({absolutePos.x, absolutePos.y + 180}, {currentBackgroundPosition.x, currentBackgroundPosition.y});
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
        currentBackground->Scroll(currentScrollVector);
        currentBackgroundPosition = Vector2Add(currentBackgroundPosition, currentScrollVector);
    }

    static void DoPreStep()
    {
        currentBackground->DoPreStep();
    }
};
#endif //RAYLIB_STG_BACKGROUNDHANDLER_H