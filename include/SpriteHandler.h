//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SPRITEHANDLER_H
#define RAYLIB_STG_SPRITEHANDLER_H
#include <array>
#include <memory>
#include <vector>

#include "raylib.h"
#include "StepThinker.h"

typedef enum {
    PLAYER = 0,
    PLAYER_BULLET = 1,
    BULLET_1_MONOCHROME = 2,
    BULLET_SMALL_MONOCHROME = 3,
} ANIMATED_SPRITES;

struct MyAnimatedSprite {
    Texture2D spriteSheet;
    Rectangle spriteRect;
    int frequency; //How many steps to % by before animating!
    constexpr MyAnimatedSprite(Texture2D _spriteSheet, Rectangle _spriteRect, int _frequency)
    : spriteSheet(_spriteSheet), spriteRect(_spriteRect), frequency(_frequency) {}
};



    static std::array<std::unique_ptr<MyAnimatedSprite>, 4> animatedSprites;
class SpriteHandler{
private:
    public:
    static void DrawMyAnimatedSprite(int animatedSpriteIndex, Vector2 pos);

    static void DrawMyAnimatedSprite(int animatedSpriteIndex, int yOffset, Vector2 pos);

    static void DrawMyAnimatedSprite(int animatedSpriteIndex, Vector2 pos, Color col);
    static void AdvanceAnimation();
    static void InitAnimatedSprites();
};


#endif //RAYLIB_STG_SPRITEHANDLER_H