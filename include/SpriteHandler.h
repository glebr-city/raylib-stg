//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SPRITEHANDLER_H
#define RAYLIB_STG_SPRITEHANDLER_H
#include <array>
#include <memory>

#include "raylib.h"

typedef enum {
    PLAYER = 0,
    PLAYER_BULLET = 1,
    PLAYER_BULLET_HYPER = 2,
    PLAYER_GRAZE_FILLED = 3,
    PLAYER_HYPER_AURA = 4,
    PLAYER_HYPER_RING = 5,
    SCORE_ITEM = 6,
    BULLET_1_MONOCHROME = 7,
    BULLET_SMALL_MONOCHROME = 8,
} ANIMATED_SPRITES;

typedef enum {
    PLAYER_GRAZE_RADIUS = 0,
    PLAYER_GRAZE_FILLING = 1,
    LIFE_ICON = 2,
} STATIC_SPRITES;

struct MyAnimatedSprite {
    Texture2D spriteSheet;
    Rectangle spriteRect;
    int frequency; //How many steps to % by before animating!
    constexpr MyAnimatedSprite(Texture2D _spriteSheet, Rectangle _spriteRect, int _frequency)
    : spriteSheet(_spriteSheet), spriteRect(_spriteRect), frequency(_frequency) {}
};

struct MyStaticSprite {
    Texture2D spriteTexture;
    Vector2 spriteSize;
};



class SpriteHandler{
private:
    static std::array<std::unique_ptr<MyAnimatedSprite>, 9> animatedSprites;
    static std::array<std::unique_ptr<MyStaticSprite>, 3> staticSprites;
    public:
    static Texture2D* getStaticSprite(int staticSpriteIndex);
    static void DrawStaticSprite(int staticSpriteIndex, Vector2 pos);
    static void DrawStaticSprite(int staticSpriteIndex, int yOffset, Vector2 pos);
    static void DrawStaticSprite(int staticSpriteIndex, int yOffset, Vector2 pos, Color col);
    static void DrawStaticSprite(int staticSpriteIndex, Vector2 pos, Color col);

    static void DrawMyAnimatedSprite(int animatedSpriteIndex, Vector2 pos);
    static void DrawMyAnimatedSprite(int animatedSpriteIndex, int yOffset, Vector2 pos);
    static void DrawMyAnimatedSprite(int animatedSpriteIndex, int yOffset, Vector2 pos, Color col);
    static void DrawMyAnimatedSprite(int animatedSpriteIndex, Vector2 pos, Color col);
    static void AdvanceAnimation();

    static void InitSprites();
};


#endif //RAYLIB_STG_SPRITEHANDLER_H