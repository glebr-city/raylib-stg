//
// Created by g on 04/02/2026.
//

#include <algorithm>
#include <array>
#include <iostream>
#include <Player.h>

#include "GlobalVariables.h"
#include "InputHandler.h"
#include "raylib.h"
#include "raymath.h"
#include "SpriteHandler.h"
Vector2 position;
constexpr float speed = 1.8;
constexpr float focusSpeed = 0.7;
const float* currentSpeed = &speed;
bool leftDown = false;
bool rightDown = false;
bool upDown = false;
bool downDown = false;
static Texture2D playerSpriteSheet;
static constexpr std::array<KeyboardKey, 3> leftKeys = {KEY_P, KEY_LEFT, KEY_A};
static constexpr std::array<KeyboardKey, 3> rightKeys = {KEY_RIGHT, KEY_RIGHT_BRACKET, KEY_D};
static constexpr std::array<KeyboardKey, 3> upKeys = {KEY_UP, KEY_RIGHT_ALT, KEY_W};
static constexpr std::array<KeyboardKey, 3> downKeys = {KEY_DOWN, KEY_LEFT_BRACKET, KEY_S};
static constexpr std::array<KeyboardKey, 3> focusKeys = {KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT, KEY_SPACE};
Vector2 inputVector {0, 0};
Rectangle playerRect = {0.0f, 0.0f, 13.0f, 13.0f};

Player::Player(Vector2 pos) {
    playerSpriteSheet = LoadTexture("resources/playerSpriteSheet.png");
    position = pos;
}

Vector2 Player::getPosition() {
    return position;
}

Vector2 Player::getMovement() {
    return Vector2Scale(inputVector, *currentSpeed);
}

std::array<Vector2, 2> Player::getPosAndMovement() {
    return std::array<Vector2, 2>{ position, Vector2Scale(inputVector, *currentSpeed) };
}

void Player::doPreStep() {
    if (InputHandler::CheckInputsPressed(leftKeys))
        inputVector.x = -1;
    else if (InputHandler::CheckInputsPressed(rightKeys))
        inputVector.x = 1;
    else if (InputHandler::CheckInputsReleased(leftKeys)) {
        if (InputHandler::CheckInputsDown(rightKeys))
            inputVector.x = 1;
        else
            inputVector.x = 0;
    } else if (InputHandler::CheckInputsReleased(rightKeys)) {
        if (InputHandler::CheckInputsDown(leftKeys))
            inputVector.x = -1;
        else
            inputVector.x = 0;
    }

    if (InputHandler::CheckInputsPressed(upKeys))
        inputVector.y = -1;
    else if (InputHandler::CheckInputsPressed(downKeys))
        inputVector.y = 1;
    else if (InputHandler::CheckInputsReleased(upKeys)) {
        if (InputHandler::CheckInputsDown(downKeys))
            inputVector.y = 1;
        else
            inputVector.y = 0;
    } else if (InputHandler::CheckInputsReleased(downKeys)) {
        if (InputHandler::CheckInputsDown(upKeys))
            inputVector.y = -1;
        else
            inputVector.y = 0;
    }

    if (InputHandler::CheckInputsPressed(focusKeys))
        currentSpeed = &focusSpeed;
    else if (InputHandler::CheckInputsReleased(focusKeys)) {
        currentSpeed = &speed;
    }
    if (currentStep() % 40 == 0) {
        playerRect.x = static_cast<int>(playerRect.x + playerRect.width) % playerSpriteSheet.width; // NOLINT(*-narrowing-conversions)
    }
    playerRect.y = -inputVector.x * playerRect.height;
    Vector2Normalize(inputVector);
    Vector2 spritePosition {position.x - 6.5f, position.y - 6.5f};
    DrawTextureRec(playerSpriteSheet, playerRect, spritePosition, WHITE);

    //std::cout << "Player PreStep, " << std::to_string(leftKeys[0]) << std::endl;
}

void Player::doPhysics(Vector2 pos) {
    std::cout << "!!! Player::doPhysics should be called with no parameters.";
    Player::doPhysics();
}

void Player::doPhysics() {
    position += inputVector * *currentSpeed;
    position = Vector2Clamp(position, Vector2{0,0}, Vector2{ static_cast<float>(gameWidth()),static_cast<float>(gameHeight())});
}
