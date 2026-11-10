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
        new AnimatedBackgroundSprite(STAGE_3_BACKGROUND, 0, {}, {360, 360}),
        new StaticBackgroundSprite(STAGE_3_BACKGROUND_CLOUDS, 1, {}, {360, 360}, LAYER_BACKGROUND_HIGH, 1.3f),
        new StaticBackgroundSprite(STAGE_3_BACKGROUND_CLOUDS, 0, {}, {360, 360}, LAYER_BACKGROUND_HIGH, 1.7f),
    }))

    {};
};
#endif //RAYLIB_STG_OTHERBACKGROUNDS_H