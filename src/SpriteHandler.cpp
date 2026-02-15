//
// Created by g on 05/02/2026.
//

#include "../include/SpriteHandler.h"

#include <iostream>

#include "GlobalVariables.h"

std::array<std::unique_ptr<MyAnimatedSprite>, 9> SpriteHandler::animatedSprites;
std::array<std::unique_ptr<MyStaticSprite>, 3> SpriteHandler::staticSprites;

void SpriteHandler::InitSprites() {
   animatedSprites = {
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/playerSpriteSheet.png"), Rectangle {0,0,13,13}, 40}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/playerBulletSpriteSheet.png"), Rectangle {0,0,7,5}, 12}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/playerBulletHyperSpriteSheet.png"), Rectangle {0,0,15,10}, 18}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/grazeRadiusFilledSpriteSheet.png"), Rectangle {0,0,22,22}, 8}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/hyperAuraSpriteSheet.png"), Rectangle {0,0,17,17}, 2}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/growingRingSpriteSheet.png"), Rectangle {0,0,180,180}, 1}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/scoreItemSpriteSheet.png"), Rectangle {0,0,8,8}, 12}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/bullet1MonochromeSpriteSheet.png"), Rectangle {0,0,9,9}, 8}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/tinyBullet1SpriteSheet.png"), Rectangle {0,0,5,5}, 4})
    };

    staticSprites = {
        std::make_unique<MyStaticSprite>(MyStaticSprite {LoadTexture("resources/grazeRadius.png"), Vector2 {22, 22}}),
        std::make_unique<MyStaticSprite>(MyStaticSprite {LoadTexture("resources/grazeRadiusFilling.png"), Vector2 {22, 22}}),
        std::make_unique<MyStaticSprite>(MyStaticSprite {LoadTexture("resources/lifeIcon.png"), Vector2{5, 6}})
    };
}

void SpriteHandler::AdvanceAnimation() {
    for (const std::unique_ptr<MyAnimatedSprite> &animated_sprite : animatedSprites) {
        if (GlobalVariables::currentStep() % animated_sprite->frequency == 0) {
            animated_sprite->spriteRect.x = static_cast<float>(static_cast<int>(animated_sprite->spriteRect.x + animated_sprite->spriteRect.width) % animated_sprite->spriteSheet.width);
        }
    }
}

Texture2D* SpriteHandler::getStaticSprite(const int staticSpriteIndex) {
    return &staticSprites.at(staticSpriteIndex)->spriteTexture;
}

void SpriteHandler::DrawStaticSprite(const int staticSpriteIndex, const int yOffset, const Vector2 pos) {
    Vector2 spriteSize = staticSprites[staticSpriteIndex]->spriteSize;
    DrawTextureV(staticSprites[staticSpriteIndex]->spriteTexture, Vector2 {pos.x - (spriteSize.x / 2), pos.y - (spriteSize.y / 2) + yOffset}, WHITE);
}

void SpriteHandler::DrawStaticSprite(const int staticSpriteIndex, const int yOffset, const Vector2 pos, const Color col) {
    Vector2 spriteSize = staticSprites[staticSpriteIndex]->spriteSize;
    DrawTextureV(staticSprites[staticSpriteIndex]->spriteTexture, Vector2 {pos.x - (spriteSize.x / 2), pos.y - (spriteSize.y / 2) + yOffset}, col);
}

void SpriteHandler::DrawStaticSprite(const int staticSpriteIndex, const Vector2 pos, const Color col) {
    Vector2 spriteSize = staticSprites[staticSpriteIndex]->spriteSize;
    DrawTextureV(staticSprites[staticSpriteIndex]->spriteTexture, Vector2 {pos.x - (spriteSize.x / 2), pos.y - (spriteSize.y / 2)}, col);
}

void SpriteHandler::DrawStaticSprite(const int staticSpriteIndex, const Vector2 pos) {
    Vector2 spriteSize = staticSprites[staticSpriteIndex]->spriteSize;
    DrawTextureV(staticSprites[staticSpriteIndex]->spriteTexture, Vector2 {pos.x - (spriteSize.x / 2), pos.y - (spriteSize.y / 2)}, WHITE);
}

void SpriteHandler::DrawMyAnimatedSprite(const int animatedSpriteIndex, const Vector2 pos) {
    Rectangle spriteRect = animatedSprites[animatedSpriteIndex]->spriteRect;
    DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {pos.x - (spriteRect.width / 2), pos.y - (spriteRect.height / 2)}, WHITE);
}

void SpriteHandler::DrawMyAnimatedSprite(const int animatedSpriteIndex, const int yOffset, const Vector2 pos) {
    Rectangle spriteRect = animatedSprites[animatedSpriteIndex]->spriteRect;
    spriteRect.y += yOffset;
    DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {pos.x - (spriteRect.width / 2), pos.y - (spriteRect.height / 2)}, WHITE);
}

void SpriteHandler::DrawMyAnimatedSprite(const int animatedSpriteIndex, const int yOffset, const Vector2 pos, const Color col) {
    Rectangle spriteRect = animatedSprites[animatedSpriteIndex]->spriteRect;
    spriteRect.y += yOffset;
    DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {pos.x - (spriteRect.width / 2), pos.y - (spriteRect.height / 2)}, col);
}


void SpriteHandler::DrawMyAnimatedSprite(const int animatedSpriteIndex, const Vector2 pos, const Color col) {
    Rectangle spriteRect = animatedSprites[animatedSpriteIndex]->spriteRect;
    DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {pos.x - (spriteRect.width / 2), pos.y - (spriteRect.height / 2)}, col);

}
