//
// Created by n on 26/10/2026.
//

#ifndef RAYLIB_STG_BOSS3_H
#define RAYLIB_STG_BOSS3_H
#include "Boss.h"

class Boss3 : public Boss
{
private:
    Color drawnColour = WHITE;
    int baseSpriteYOffset = 0; //Used for damage sprites
    public:
    typedef enum
    {
        PRE_FIGHT = 0,
        PHASE_1,
        PHASE_DEFEAT
    }BOSS_3_PHASES;

    void doPostStep() override
    {
        drawnColour = WHITE;
        if (--currentFlashDuration > 0 && GlobalVariables::currentStep() % 61 > 45)
            drawnColour = RED;
        SpriteHandler::QueueMyStaticSprite({.i=BOSS_3_BASE, .pos=position, .yOffset=baseSpriteYOffset, .l = LAYER_GROUNDED, .col = drawnColour});
    }
};
#endif //RAYLIB_STG_BOSS3_H