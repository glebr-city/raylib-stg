//
// Created by n on 10/11/2026.
//

#ifndef RAYLIB_STG_OTHERBACKGROUNDS_H
#define RAYLIB_STG_OTHERBACKGROUNDS_H
#include "Background.h"

class Stage1Background : public Background
{};
class Stage2Background : public Background
{
    public:
    Stage2Background() : Background(STAGE_2_BACKGROUND) {};
};
class Stage3Background : public Background
{
public:
    Stage3Background() : Background(DEFAULT_BACKGROUND, std::vector<BackgroundElementBase*>({
        new AnimatedBackgroundElement(STAGE_3_BACKGROUND)}))
    {
    };
};
#endif //RAYLIB_STG_OTHERBACKGROUNDS_H