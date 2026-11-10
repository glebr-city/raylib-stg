//
// Created by n on 10/11/2026.
//

#ifndef RAYLIB_STG_BACKGROUND_H
#define RAYLIB_STG_BACKGROUND_H
#include <cstdint>
#include <utility>

#include "raylib.h"
#include "raymath.h"
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
    Vector2 thing{};
    uint_fast16_t stepsElapsed = 0;
    const LAYERS layer = LAYER_ENEMY;
    const float scrollSpeedFactor; //How quickly does the background element move? Parallax scrolling!

    explicit BackgroundElementBase(const Vector2 _pos, const LAYERS _layer = LAYER_BACKGROUND, const float _scrollSpeedFactor = 1.0f) : stepsElapsed(0), layer(_layer), scrollSpeedFactor(_scrollSpeedFactor)
    {
        position = _pos;
    }
public:
    void spawn(const Vector2 _position) override
    {
        position = _position;
    }
    void spawn(const Vector2 _position, u_int _scoreValue) override
    {
        spawn(_position);
    }
    virtual void DoPreStep()=0;
    void Scroll(const Vector2 scrollVector)
    {
        position = Vector2Subtract(position, {scrollVector.x * scrollSpeedFactor, scrollVector.y * scrollSpeedFactor});
    }
};

class AnimatedBackgroundElement : public BackgroundElementBase
{
protected:
    const ANIMATED_SPRITES sprite;
public:
    AnimatedBackgroundElement(const ANIMATED_SPRITES _sprite = BULLET_1_MONOCHROME, const Vector2 _pos = {}, const LAYERS _layer = LAYER_BACKGROUND, const float _scrollSpeedFactor = 1.0f)
    : BackgroundElementBase(_pos, _layer, _scrollSpeedFactor), sprite(_sprite)
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
    const std::vector<BackgroundElementBase*> backgroundElements;
public:
    Background(const STATIC_SPRITES _backgroundSprite = DIAGONAL_TANK_BACKGROUND, std::vector<BackgroundElementBase*> _backgroundElements = {}) : backgroundSprite(_backgroundSprite), backgroundElements(std::move(_backgroundElements))
    {};

    void Scroll(const Vector2 scrollVector)
    {
        for (auto &element : backgroundElements)
        {
            element->Scroll(scrollVector);
        }
    }

    [[nodiscard]] STATIC_SPRITES GetBackgroundSprite() const
    {
        return backgroundSprite;
    }

    void DoPreStep()
    {
        for (auto &element : backgroundElements)
        {
            element->DoPreStep();
        }
    }

};

struct BackgroundRef //Used to list PhaseHelpers without loading them in their entirety.
{
    Background* (*initBackground)();
};
#endif //RAYLIB_STG_BACKGROUND_H