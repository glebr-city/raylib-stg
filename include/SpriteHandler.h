//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SPRITEHANDLER_H
#define RAYLIB_STG_SPRITEHANDLER_H
#include <array>
#include <memory>
#include <vector>

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
    ENEMY_1_2,
    BIG_ENEMY_2,

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
    static std::array<std::unique_ptr<MyAnimatedSprite>, ANIMATED_SPRITE_COUNT> animatedSprites;
    static std::array<std::unique_ptr<MyStaticSprite>, STATIC_SPRITE_COUNT> staticSprites;
    static std::array<std::vector<SpriteParametres>, LAYER_COUNT> staticLayers;
    static std::array<std::vector<SpriteParametres>, LAYER_COUNT> animatedLayers;
    public:
    static MyStaticSprite* getStaticSprite(int staticSpriteIndex);
    static Texture2D* getStaticSpriteTexture(int staticSpriteIndex);
    static void QueueMyStaticSprite(const SpriteParametres& opts);
    static void QueueMyAnimatedSprite(const SpriteParametres& opts);
    static void QueueText(TextParametres opts);
    static void AdvanceAnimation();
    static void DrawSprites();
    static void InitSprites()
    { //It would be nice to initialise these as const. but they need to be loaded AFTER the screen is set up. TODO: CHECK AFTER PACKING ASSETS INTO EXECUTABLE
   animatedSprites = {
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/playerSpriteSheet.png"), Rectangle {0,0,13,13}, 40}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/playerBulletSpriteSheet.png"), Rectangle {0,0,7,5}, 12}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/playerBulletHyperSpriteSheet.png"), Rectangle {0,0,15,10}, 18}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/grazeRadiusFilledSpriteSheet.png"), Rectangle {0,0,22,22}, 8}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/hyperAuraSpriteSheet.png"), Rectangle {0,0,17,17}, 2}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/growingRingSpriteSheet.png"), Rectangle {0,0,180,180}, 1}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/scoreItemSpriteSheet.png"), Rectangle {0,0,8,8}, 12}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/bullet1MonochromeSpriteSheet.png"), Rectangle {0,0,9,9}, 8}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/tinyBullet1SpriteSheet.png"), Rectangle {0,0,5,5}, 10}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/diagonalTankSpriteSheet.png"), Rectangle {0,0,15,15}, 30}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/enemy1SpriteSheet.png"), Rectangle {0,0,10,10}, 30}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/spinningRodMonochromeSpriteSheet.png"), Rectangle {0,0,6,6}, 8}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/spinningOvalMonochromeSpriteSheet.png"), Rectangle {0,0,6,6}, 8}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/bigEnemy1SpriteSheet.png"), Rectangle {0,0,31,19}, 30}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/streetlightEnemySpriteSheet.png"), Rectangle {0,0,8,13}, 25}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/spear1SpriteSheet.png"), Rectangle {0,0,11, 21}, 2}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/enemy1_2SpriteSheet.png"), Rectangle {0,0,17,14}, 30}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/sprites/bigEnemy2SpriteSheet.png"), Rectangle {0,0,19,25}, 30}),

   };
    staticSprites = {
        std::make_unique<MyStaticSprite>(MyStaticSprite {LoadTexture("resources/sprites/grazeRadius.png"), Vector2 {22, 22}}),
        std::make_unique<MyStaticSprite>(MyStaticSprite {LoadTexture("resources/sprites/grazeRadiusFilling.png"), Vector2 {22, 22}}),
        std::make_unique<MyStaticSprite>(MyStaticSprite {LoadTexture("resources/sprites/lifeIcon.png"), Vector2{5, 6}}),
        std::make_unique<MyStaticSprite>(MyStaticSprite {LoadTexture("resources/sprites/defaultBackground.png"), Vector2{0, 0}}),
        std::make_unique<MyStaticSprite>(MyStaticSprite {LoadTexture("resources/sprites/diagonalTankBackground.png"), Vector2{0, 0}}),
       std::make_unique<MyStaticSprite>(MyStaticSprite{LoadTexture("resources/sprites/boss1BaseSpriteSheet.png"), {92,57}}),
       std::make_unique<MyStaticSprite>(MyStaticSprite{LoadTexture("resources/sprites/boss1Part1.png"), {92,57}}),
       std::make_unique<MyStaticSprite>(MyStaticSprite{LoadTexture("resources/sprites/boss1Part2.png"), {92,57}}),
       std::make_unique<MyStaticSprite>(MyStaticSprite{LoadTexture("resources/sprites/boss1Part3.png"), {92,57}}),
       std::make_unique<MyStaticSprite>(MyStaticSprite{LoadTexture("resources/sprites/boss1Part4.png"), {92,57}}),
       std::make_unique<MyStaticSprite>(MyStaticSprite{LoadTexture("resources/sprites/boss1SmallPartsSpriteSheet.png"), {92,57}}),
        std::make_unique<MyStaticSprite>(MyStaticSprite{LoadTexture("resources/sprites/explosionSmallSpriteSheet.png"), {10,10}}),
    };
}
    static void DrawMyStaticSprite(const SpriteParametres& opts);
    static void ClearQueues();
};


#endif //RAYLIB_STG_SPRITEHANDLER_H