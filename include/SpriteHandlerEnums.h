//
// Created by n on 13/07/2026.
//

#ifndef RAYLIB_STG_SPRITEHANDLERENUMS_H
#define RAYLIB_STG_SPRITEHANDLERENUMS_H
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
    DIAGONAL_TANK = 9,
    ENEMY_1 = 10,
    SPINNING_ROD_MONOCHROME = 11,
    SPINNING_OVAL_MONOCHROME = 12,
    BIG_ENEMY_1 = 13,
} ANIMATED_SPRITES;

typedef enum {
    PLAYER_GRAZE_RADIUS = 0,
    PLAYER_GRAZE_FILLING = 1,
    LIFE_ICON = 2,
    DEFAULT_BACKGROUND = 3,
    DIAGONAL_TANK_BACKGROUND = 4,
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