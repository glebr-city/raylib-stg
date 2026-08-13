//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SPRITEHANDLER_H
#define RAYLIB_STG_SPRITEHANDLER_H
#include <array>
#include <memory>
#include "raylib/raylib.h"





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
    STREETLIGHT_ENEMY,
    SPEAR_1,

    ANIMATED_SPRITE_COUNT,
} ANIMATED_SPRITES;

typedef enum {
    PLAYER_GRAZE_RADIUS = 0,
    PLAYER_GRAZE_FILLING,
    LIFE_ICON,
    DEFAULT_BACKGROUND,
    DIAGONAL_TANK_BACKGROUND,
    BOSS_1_BASE,
    BOSS_1_PART_1,
    BOSS_1_PART_2,
    BOSS_1_PART_3,
    BOSS_1_PART_4,
    BOSS_1_SMALL_PARTS,
    EXPLOSION_SMALL,

    STATIC_SPRITE_COUNT
} STATIC_SPRITES;

inline constexpr int LAYER_COUNT = 9;

typedef enum
{
    LAYER_BACKGROUND = 0,
    LAYER_GROUNDED,
    LAYER_ENEMY,
    LAYER_PLAYER,
    LAYER_BULLET_LOW,
    LAYER_BULLET,
    LAYER_FOREGROUND,
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
class SpriteHandler{
private:
    public:
    static MyStaticSprite* getStaticSprite(int staticSpriteIndex);
    static Texture2D* getStaticSpriteTexture(int staticSpriteIndex);
    static void QueueMyStaticSprite(const SpriteParametres& opts);
    static void QueueMyAnimatedSprite(const SpriteParametres& opts);
    static void QueueText(TextParametres opts);
    static void AdvanceAnimation();
    static void DrawSprites();
    static void InitSprites();
    static void DrawMyStaticSprite(const SpriteParametres& opts);
    static void ClearQueues();
};


#endif //RAYLIB_STG_SPRITEHANDLER_H