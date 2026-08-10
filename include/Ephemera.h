//
// Created by n on 10/08/2026.
//

#ifndef RAYLIB_STG_EPHEMERA_H
#define RAYLIB_STG_EPHEMERA_H
#include "BackgroundHandler.h"
#include "SoundHandler.h"
#include "Spawnable.h"
#include "SpriteHandler.h"

class Ephemera : public Spawnable
{
private:
    protected:
    uint_fast16_t stepsElapsed = 0;
    LAYERS layer = LAYER_ENEMY;
    uint_fast16_t maxSteps;
    STATIC_SPRITES sprite;
    SOUNDS sound;
    static void doPreStep(const SpriteParametres& _spriteParams)
    {
        SpriteHandler::QueueMyStaticSprite(_spriteParams);
    }

public:
    explicit Ephemera(const Vector2 _pos, const LAYERS _layer = LAYER_ENEMY, const uint_fast16_t _maxSteps = 120, const STATIC_SPRITES _sprite = EXPLOSION_SMALL, const SOUNDS _sound = EXPLOSION_2)
    {
        position = _pos;
        layer = _layer;
        maxSteps = _maxSteps;
        sprite = _sprite;
        sound = _sound;
        SoundHandler::PlaySound(_sound);
    }
    void spawn(const Vector2 _position) override
    {
        //position = _position;
        //SoundHandler::PlaySound(sound);
    }

    void spawn (const Vector2 _position, const u_int scoreValue) override
    {
        spawn(_position);
    }
    bool doPhysics() override
    {
        if (static_cast<int>(layer) <= static_cast<int>(LAYER_GROUNDED))
            position -= BackgroundHandler::GetScrollVector();
        if (++stepsElapsed > maxSteps)
        {
            return false;
        }
        return true;
    }
    void doPreStep() override = 0;
};

class ExplosionSmall : public Ephemera
{
    static constexpr STATIC_SPRITES SPRITE = EXPLOSION_SMALL;
    static constexpr uint_fast16_t MAX_STEPS = 36;
    static constexpr Vector2 SPRITE_SIZE = {10, 10};
    static constexpr SOUNDS SOUND = EXPLOSION_2;
public:
    explicit ExplosionSmall(const Vector2 pos, const LAYERS _layer = LAYER_ENEMY) : Ephemera(pos, _layer, MAX_STEPS, SPRITE, SOUND) {}
    void doPreStep() override
    {
        const float xOffset = static_cast<int>(stepsElapsed / 4) * 10;
        const Rectangle rect = {xOffset, 0, 10, 10};
        const SpriteParametres opts = {.i = sprite, .pos = position, .yOffset = 0, .l = layer, .col = WHITE, .corner = false, .rect = rect};
        Ephemera::doPreStep(opts);
    }
};
#endif //RAYLIB_STG_EPHEMERA_H