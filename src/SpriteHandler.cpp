//
// Created by g on 05/02/2026.
//

#include "../include/SpriteHandler.h"

#include <iostream>
#include <ostream>

#include "GlobalVariables.h"


void SpriteHandler::InitAnimatedSprites() {
   animatedSprites = {
        std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/bullet1MonochromeSpriteSheet.png"), Rectangle {0,0,9,9}, 8})
    };
}

void SpriteHandler::AdvanceAnimation() {
    for (const std::unique_ptr<MyAnimatedSprite> &animated_sprite : animatedSprites) {
        if (currentStep() % animated_sprite->frequency == 0) {
            animated_sprite->spriteRect.x = static_cast<float>(static_cast<int>(animated_sprite->spriteRect.x + animated_sprite->spriteRect.width) % animated_sprite->spriteSheet.width);
        }
    }
}

void SpriteHandler::DrawMyAnimatedSprite(int animatedSpriteIndex, Vector2 pos) {
    Rectangle spriteRect = animatedSprites[animatedSpriteIndex]->spriteRect;
    DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {pos.x - (spriteRect.width / 2) - 0.5f, pos.y - (spriteRect.height / 2) - 0.5f}, BLUE);
}

void SpriteHandler::DrawMyAnimatedSprite(int animatedSpriteIndex, Vector2 pos, Color col) {
    Rectangle spriteRect = animatedSprites[animatedSpriteIndex]->spriteRect;
    DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {pos.x - (spriteRect.width / 2) - 0.5f, pos.y - (spriteRect.height / 2) - 0.5f}, col);

}
