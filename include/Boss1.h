//
// Created by n on 08/08/2026.
//

#ifndef RAYLIB_STG_BOSS1_H
#define RAYLIB_STG_BOSS1_H
#include "Boss.h"

class Boss1 : public Boss
{
    public:
    explicit Boss1(const int _health = 1) : Boss(500, {0, -14, 70, 35}, _health){}

    void doPreStep() override
    {
        SpriteParametres opts = {.i=BOSS_1_BASE, .pos=position, .l = LAYER_GROUNDED};
        if (--currentFlashDuration > 0 && GlobalVariables::currentStep() % 61 > 30)
            opts.col = RED;
            SpriteHandler::QueueMyStaticSprite(opts);
    }
};
#endif //RAYLIB_STG_BOSS1_H