//
// Created by n on 10/11/2026.
//

#ifndef RAYLIB_STG_BACKGROUND_H
#define RAYLIB_STG_BACKGROUND_H
#include <cstdint>
#include "Spawnable.h"
#include "SpriteHandler.h"

typedef enum {
    BACKGROUND_STAGE_1 = 0,
    BACKGROUND_STAGE_2,
    BACKGROUND_STAGE_3,

    BACKGROUND_COUNT
} BACKGROUNDS;

class BackgroundElementBase : public Spawnable
{
protected:
    uint_fast16_t stepsElapsed = 0;
    LAYERS layer = LAYER_ENEMY;
    explicit BackgroundElementBase(const Vector2 _pos, const LAYERS _layer = LAYER_BACKGROUND)
    {
        position = _pos;
        layer = _layer;
    }
public:
    virtual void DoPreStep() = 0;
};

class AnimatedBackgroundElement : public BackgroundElementBase
{
protected:
    const ANIMATED_SPRITES sprite;
public:
    AnimatedBackgroundElement(const ANIMATED_SPRITES _sprite = BULLET_1_MONOCHROME, const Vector2 _pos = {}, const LAYERS _layer = LAYER_BACKGROUND)
    : BackgroundElementBase(_pos, _layer), sprite(_sprite)
    {};
    void DoPreStep() override
    {
        const SpriteParametres opts = {sprite, position, 0, layer};
        SpriteHandler::QueueMyAnimatedSprite(opts);
    };
};

class StaticBackgroundElement : public BackgroundElementBase
{
protected:
    const STATIC_SPRITES sprite;
};

class Background : public StepThinker
{
    const STATIC_SPRITES backgroundSprite;
public:
    Background(const STATIC_SPRITES _backgroundSprite = DIAGONAL_TANK_BACKGROUND) : backgroundSprite(_backgroundSprite)
    {};

    [[nodiscard]] STATIC_SPRITES GetBackgroundSprite() const
    {
        return backgroundSprite;
    }
};

struct BackgroundRef //Used to list PhaseHelpers without loading them in their entirety.
{
    Background* (*initBackground)();
};
#endif //RAYLIB_STG_BACKGROUND_H