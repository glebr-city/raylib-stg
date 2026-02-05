//
// Created by g on 04/02/2026.
//

#include <iostream>
#include <Player.h>

#include "GlobalVariables.h"
#include "raylib.h"
#include "raymath.h"
Vector2 position;
constexpr float speed = 1.5f;
static Texture2D playerSpriteSheet;
Rectangle playerRect = {0.0f, 0.0f, 13.0f, 13.0f};
Player::Player(Vector2 pos) {
    playerSpriteSheet = LoadTexture("resources/playerSpriteSheet.png");
    position = pos;
}
void Player::PreStep() {
    Vector2 inputVector {};
    if (IsKeyDown((KEY_LEFT))) {
        inputVector.x -= 1;
    }
    if (IsKeyDown((KEY_RIGHT))) {
        inputVector.x += 1;
    }
    if (IsKeyDown((KEY_UP))) {
        inputVector.y -= 1;
    }
    if (IsKeyDown((KEY_DOWN))) {
        inputVector.y += 1;
    }
    if (currentStep() % 40 == 0) {
        playerRect.x = static_cast<int>(playerRect.x + playerRect.width) % playerSpriteSheet.width; // NOLINT(*-narrowing-conversions)
    }
    playerRect.y = -inputVector.x * playerRect.height;
    Vector2Normalize(inputVector);
    position += inputVector * speed;
    position = Vector2Clamp(position, Vector2{1.5f,1.5f}, Vector2{ static_cast<float>(gameWidth() - 1.5f),static_cast<float>(gameHeight() - 1.5f)});
    Vector2 spritePosition {round(position.x - 6.5f), round(position.y - 6.5f)};
    Vector2 spritePositionUnrounded {position.x - 6, position.y - 6 };
    DrawTextureRec(playerSpriteSheet, playerRect, spritePositionUnrounded, WHITE);
    Rectangle {}
    DrawCircle(static_cast<int>(round(position.x)), static_cast<int>(round(position.y)), 0.5f, RED);
    std::cout << "Player PreStep, " << currentStep() << std::endl;
}
