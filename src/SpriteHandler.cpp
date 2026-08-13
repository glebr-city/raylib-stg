//
// Created by g on 05/02/2026.
//

#include "../include/SpriteHandler.h"

#include <iostream>
#include <vector>

#include "BackgroundHandler.h"
#include "GlobalVariables.h"
#include "HUDHandler.h"

std::array<std::unique_ptr<MyAnimatedSprite>, ANIMATED_SPRITE_COUNT> animatedSprites;
std::array<std::unique_ptr<MyStaticSprite>, STATIC_SPRITE_COUNT> staticSprites;

std::array<std::vector<SpriteParametres>, LAYER_COUNT> staticLayers;
std::array<std::vector<SpriteParametres>, LAYER_COUNT> animatedLayers;
std::vector<TextParametres> textLayer;

void SpriteHandler::InitSprites() { //It would be nice to initialise these as const. but they need to be loaded AFTER the screen is set up. TODO: CHECK AFTER PACKING ASSETS INTO EXECUTABLE
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

void SpriteHandler::AdvanceAnimation() {
    for (const std::unique_ptr<MyAnimatedSprite> &animated_sprite : animatedSprites) {
        if (GlobalVariables::currentStep() % animated_sprite->frequency == 0) {
            animated_sprite->spriteRect.x = static_cast<float>(static_cast<int>(animated_sprite->spriteRect.x + animated_sprite->spriteRect.width) % animated_sprite->spriteSheet.width);
        }
    }
}

void SpriteHandler::DrawSprites() //Draws queued sprites!
{
    //First, we draw the background.
    const MyStaticSprite* backgroundSprite = getStaticSprite(BackgroundHandler::GetBackgroundSprite());
    const Vector2 currentBackgroundPosition = BackgroundHandler::GetBackgroundPosition();
    DrawTextureRec(backgroundSprite->spriteTexture, Rectangle{floor(currentBackgroundPosition.x), floor(backgroundSprite->spriteSize.y - 180 + currentBackgroundPosition.y), 120, 180}, Vector2(0, 0), WHITE);
    for (int i = 0; i < LAYER_COUNT; i++)
    {
        for (const SpriteParametres& opts : staticLayers[i]) //Draw every static sprite on the given layer.
        {
            const int staticSpriteIndex = opts.i;
            const int yOffset = opts.yOffset;
            const Vector2 pos = opts.pos;
            const Color col = opts.col;
            Vector2 spriteSize = staticSprites[staticSpriteIndex]->spriteSize;
            Rectangle spriteRect;
            if (opts.rect.width == 0) //Hacky and with poor performance...
            {
                spriteRect = Rectangle{0, 0, spriteSize.x, spriteSize.y};
                spriteRect.y += yOffset * spriteRect.height;
            }
            else
                spriteRect = opts.rect;
            if (opts.corner)
                DrawTextureRec(staticSprites[staticSpriteIndex]->spriteTexture, spriteRect, Vector2 {round(pos.x), round(pos.y)}, col);
            else
                DrawTextureRec(staticSprites[staticSpriteIndex]->spriteTexture, spriteRect, Vector2 {round(pos.x - (spriteSize.x / 2)), round(pos.y - (spriteSize.y / 2))}, col);
        }
        //Line removed to facilitate neat pausing.
        //staticLayers[i].clear();
        for (const SpriteParametres& opts : animatedLayers[i]) //Now, draw every animated sprite on the same layer.
        {
            const int animatedSpriteIndex = opts.i;
            const int yOffset = opts.yOffset;
            const Vector2 pos = opts.pos;
            Color col = opts.col;
            if (opts.flashing && GlobalVariables::currentStep() % 31 > 15)
                col = RED;
            Rectangle spriteRect;
            if (opts.rect.width == 0) //Hacky and with poor performance...
            {
                spriteRect = animatedSprites[animatedSpriteIndex]->spriteRect;
                spriteRect.y += yOffset * spriteRect.height;
            }
            else
                spriteRect = opts.rect;
            if (opts.corner)
                DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {round(pos.x), round(pos.y)}, col);
            else
                DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {round(pos.x - (spriteRect.width / 2)), round(pos.y - (spriteRect.height / 2))}, col);

        }
            //Line removed to facilitate neat pausing.
            //animatedLayers[i].clear();
    }

    //Now, draw the text.
    for (TextParametres& opts : textLayer)
    {
        DrawText(opts.text.c_str(), opts.pos.x, opts.pos.y, opts.fontSize, opts.col);
    }
    //Line removed to facilitate neat pausing.
    //textLayer.clear();

}

void SpriteHandler::ClearQueues() //Not performant, but I'd like to have a neat pause screen...
{
    for (int i = 0; i < LAYER_COUNT; i++)
    {
        animatedLayers[i].clear();
        staticLayers[i].clear();
    }
    textLayer.clear();

}

MyStaticSprite* SpriteHandler::getStaticSprite(const int staticSpriteIndex) {
    return staticSprites.at(staticSpriteIndex).get();
}

Texture2D* SpriteHandler::getStaticSpriteTexture(const int staticSpriteIndex)
{
    return &staticSprites.at(staticSpriteIndex).get()->spriteTexture;
}

void SpriteHandler::QueueMyStaticSprite(const SpriteParametres& opts) {
    staticLayers[opts.l].emplace_back(opts);
}


void SpriteHandler::QueueMyAnimatedSprite(const SpriteParametres& opts) {
    animatedLayers[opts.l].emplace_back(opts);
}

void SpriteHandler::QueueText(TextParametres opts)
{
    textLayer.emplace_back(opts);
}

void SpriteHandler::DrawMyStaticSprite(const SpriteParametres& opts) //Draw a sprite NOW -- used by the HUD.
{
    const int staticSpriteIndex = opts.i;
    const int yOffset = opts.yOffset;
    const Vector2 pos = opts.pos;
    const Color col = opts.col;
    Vector2 spriteSize = staticSprites[staticSpriteIndex]->spriteSize;
    Rectangle spriteRect;
    if (opts.rect.width == 0) //Hacky and with poor performance...
    {
        spriteRect = Rectangle{0, 0, spriteSize.x, spriteSize.y};
        spriteRect.y += yOffset * spriteRect.height;
    }
    else
        spriteRect = opts.rect;
    if (opts.corner)
        DrawTextureRec(staticSprites[staticSpriteIndex]->spriteTexture, spriteRect, Vector2 {round(pos.x), round(pos.y + yOffset * spriteSize.y)}, col);
    else
        DrawTextureRec(staticSprites[staticSpriteIndex]->spriteTexture, spriteRect, Vector2 {round(pos.x - (spriteSize.x / 2)), round(pos.y - (spriteSize.y / 2) + yOffset * spriteSize.y)}, col);
}