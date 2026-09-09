//
// Created by g on 05/02/2026.
//

#include "../include/SpriteHandler.h"

#include <iostream>
#include <vector>

#include "BackgroundHandler.h"
#include "GlobalVariables.h"
#include "HUDHandler.h"



std::array<std::unique_ptr<MyAnimatedSprite>, ANIMATED_SPRITE_COUNT> SpriteHandler::animatedSprites{};
std::array<std::unique_ptr<MyStaticSprite>, STATIC_SPRITE_COUNT> SpriteHandler::staticSprites{};
std::array<std::vector<SpriteParametres>, LAYER_COUNT> SpriteHandler::staticLayers{};
std::array<std::vector<SpriteParametres>, LAYER_COUNT> SpriteHandler::animatedLayers{};
std::vector<TextParametres> textLayer;


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
    DrawTextureRec(backgroundSprite->spriteTexture, Rectangle{ round(currentBackgroundPosition.x),  round(backgroundSprite->spriteSize.y - 180 + currentBackgroundPosition.y), 120, 180}, Vector2(0, 0), WHITE);
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
                DrawTextureRec(staticSprites[staticSpriteIndex]->spriteTexture, spriteRect, Vector2 {std:: round(pos.x), std:: round(pos.y)}, col);
            else
                DrawTextureRec(staticSprites[staticSpriteIndex]->spriteTexture, spriteRect, Vector2 {std::round(pos.x - (spriteSize.x / 2)), std:: round(pos.y - (spriteSize.y / 2))}, col);
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
                DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {std::round(pos.x), std::round(pos.y)}, col);
            else
                DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {std::round(pos.x - (spriteRect.width / 2)), std::round(pos.y - (spriteRect.height / 2))}, col);

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