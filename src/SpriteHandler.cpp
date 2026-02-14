//
// Created by g on 05/02/2026.
//

#include "../include/SpriteHandler.h"

#include <iostream>
#include <ostream>

#include "GlobalVariables.h"


void SpriteHandler::InitAnimatedSprites() {
   animatedSprites = {
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/playerSpriteSheet.png"), Rectangle {0,0,13,13}, 40}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/playerBulletSpriteSheet.png"), Rectangle {0,0,7,5}, 12}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/playerBulletHyperSpriteSheet.png"), Rectangle {0,0,15,10}, 18}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/grazeRadiusFilledSpriteSheet.png"), Rectangle {0,0,22,22}, 8}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/hyperAuraSpriteSheet.png"), Rectangle {0,0,17,17}, 2}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/growingRingSpriteSheet.png"), Rectangle {0,0,180,180}, 1}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/scoreItemSpriteSheet.png"), Rectangle {0,0,8,8}, 20}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/bullet1MonochromeSpriteSheet.png"), Rectangle {0,0,9,9}, 8}),
       std::make_unique<MyAnimatedSprite>(MyAnimatedSprite{LoadTexture("resources/tinyBullet1SpriteSheet.png"), Rectangle {0,0,5,5}, 4})
    };
}

void SpriteHandler::AdvanceAnimation() {
    for (const std::unique_ptr<MyAnimatedSprite> &animated_sprite : animatedSprites) {
        if (GlobalVariables::currentStep() % animated_sprite->frequency == 0) {
            animated_sprite->spriteRect.x = static_cast<float>(static_cast<int>(animated_sprite->spriteRect.x + animated_sprite->spriteRect.width) % animated_sprite->spriteSheet.width);
        }
    }
}

void SpriteHandler::DrawMyAnimatedSprite(int animatedSpriteIndex, Vector2 pos) {
    Rectangle spriteRect = animatedSprites[animatedSpriteIndex]->spriteRect;
    DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {pos.x - (spriteRect.width / 2), pos.y - (spriteRect.height / 2)}, WHITE);
}

void SpriteHandler::DrawMyAnimatedSprite(int animatedSpriteIndex, int yOffset, Vector2 pos) {
    Rectangle spriteRect = animatedSprites[animatedSpriteIndex]->spriteRect;
    spriteRect.y += yOffset;
    DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {pos.x - (spriteRect.width / 2), pos.y - (spriteRect.height / 2)}, WHITE);
}

void SpriteHandler::DrawMyAnimatedSprite(int animatedSpriteIndex, int yOffset, Vector2 pos, Color col) {
    Rectangle spriteRect = animatedSprites[animatedSpriteIndex]->spriteRect;
    spriteRect.y += yOffset;
    DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {pos.x - (spriteRect.width / 2), pos.y - (spriteRect.height / 2)}, col);
}


void SpriteHandler::DrawMyAnimatedSprite(int animatedSpriteIndex, Vector2 pos, Color col) {
    Rectangle spriteRect = animatedSprites[animatedSpriteIndex]->spriteRect;
    DrawTextureRec(animatedSprites[animatedSpriteIndex]->spriteSheet, spriteRect, Vector2 {pos.x - (spriteRect.width / 2), pos.y - (spriteRect.height / 2)}, col);

}
