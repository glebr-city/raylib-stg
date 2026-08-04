//
// Created by n on 13/07/2026.
//

#ifndef RAYLIB_STG_SPRITEHANDLERENUMS_H
#define RAYLIB_STG_SPRITEHANDLERENUMS_H
#include "raylib.h"

typedef enum {
    PLAYER = 0,
    PLAYER_BULLET,
    PLAYER_BULLET_HYPER,
    PLAYER_GRAZE_FILLED,
    PLAYER_HYPER_AURA,
    PLAYER_HYPER_RING,
    SCORE_ITEM,
    BULLET_1_MONOCHROME,
    BULLET_SMALL_MONOCHROME,
    DIAGONAL_TANK,
    ENEMY_1,
    SPINNING_ROD_MONOCHROME,
    SPINNING_OVAL_MONOCHROME,
    BIG_ENEMY_1,

    ANIMATED_SPRITE_COUNT,
} ANIMATED_SPRITES;

typedef enum {
    PLAYER_GRAZE_RADIUS = 0,
    PLAYER_GRAZE_FILLING,
    LIFE_ICON,
    DEFAULT_BACKGROUND,
    DIAGONAL_TANK_BACKGROUND,

    STATIC_SPRITE_COUNT
} STATIC_SPRITES;

inline constexpr int LAYER_COUNT = 9;

typedef enum
{
    LAYER_BACKGROUND = 0,
    LAYER_GROUNDED = 1,
    LAYER_ENEMY = 3,
    LAYER_PLAYER = 4,
    LAYER_BULLET = 5,
    LAYER_FOREGROUND = 6,
    LAYER_HUD = LAYER_COUNT - 1,
} LAYERS;

struct MyAnimatedSprite{
    Texture2D spriteSheet;
    Rectangle spriteRect;
    int frequency; //How many steps to % by before animating!
    constexpr MyAnimatedSprite(Texture2D _spriteSheet, Rectangle _spriteRect, int _frequency)
    : spriteSheet(_spriteSheet), spriteRect(_spriteRect), frequency(_frequency) {}
};

struct MyStaticSprite{
    Texture2D spriteTexture;
    Vector2 spriteSize;
};

struct SpriteParametres {
    int i; //The index of the sprite in its respective array.
    Vector2 pos = Vector2(0, 0);
    int yOffset = 0; //The yOffset on the sprite sheet, measured in rows.
    LAYERS l = LAYER_BULLET; //The sprite's layer; 0 is the background.
    Color col = WHITE;
    bool corner = false; //centre pivot by default, otherwise, top-left corner.
    Rectangle rect; //Optional!
    bool flashing = false; //For damage animations!
};

struct TextParametres {
    std::string text;
    Vector2 pos;
    int fontSize;
    Color col;
};
#endif //RAYLIB_STG_SPRITEHANDLERENUMS_H