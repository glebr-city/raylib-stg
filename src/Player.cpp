//
// Created by g on 04/02/2026.
//

#include <algorithm>
#include <array>
#include <iostream>
#include <Player.h>

#include "DamageHandler.h"
#include "GlobalVariables.h"
#include "InputHandler.h"
#include "PhaseHelper.h"
#include "raylib.h"
#include "raymath.h"
#include "SpriteHandler.h"
Vector2 position;
constexpr float speed = 1.6;
constexpr float focusSpeed = 0.85;
const float* currentSpeed = &speed;
bool leftDown = false;
bool rightDown = false;
bool upDown = false;
bool downDown = false;
static constexpr std::array<KeyboardKey, 3> leftKeys = {KEY_P, KEY_LEFT, KEY_A};
static constexpr std::array<KeyboardKey, 3> rightKeys = {KEY_RIGHT, KEY_RIGHT_BRACKET, KEY_D};
static constexpr std::array<KeyboardKey, 3> upKeys = {KEY_UP, KEY_RIGHT_ALT, KEY_W};
static constexpr std::array<KeyboardKey, 3> downKeys = {KEY_DOWN, KEY_LEFT_BRACKET, KEY_S};
static constexpr std::array<KeyboardKey, 3> focusKeys = {KEY_LEFT_SHIFT, KEY_RIGHT_SHIFT, KEY_SPACE};
static constexpr std::array<KeyboardKey, 3> hyperKeys = {KEY_X, KEY_LEFT_CONTROL, KEY_PERIOD};
static constexpr std::array<KeyboardKey, 2> fireKeys = {KEY_Z, KEY_SLASH};
Vector2 inputVector {0, 0};
Rectangle playerRect = {0.0f, 0.0f, 13.0f, 13.0f};
constexpr int fireCooldown = 30; //Frames to wait between player shots
int currentFireCooldown = 0; //Frames remaining until the player may shoot again

Player::Player(Vector2 pos) {
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

    if (InputHandler::CheckInputsPressed(hyperKeys) && currentGrazeMetre >= maxGrazeMetre)
        startHyper();
    if (--currentFireCooldown <= 0 && InputHandler::CheckInputsDown(fireKeys)) {
        currentFireCooldown = fireCooldown;
        GlobalVariables::spawnPlayerBullet(position);
    } else if (currentFireCooldown == fireCooldown - 5) {
        GlobalVariables::spawnPlayerBullet(position);
    } else if (currentFireCooldown == fireCooldown - 10) {
        GlobalVariables::spawnPlayerBullet(position);
    }
    SpriteHandler::DrawMyAnimatedSprite(PLAYER, static_cast<int>(-inputVector.x * 13), position); //Counting on digital movement only.
    Vector2Normalize(inputVector);

    //std::cout << "Player PreStep, " << std::to_string(leftKeys[0]) << std::endl;
}

void Player::doPhysics(Vector2 pos) {
    std::cout << "!!! Player::doPhysics should be called with no parameters.";
    doPhysics();
}

void Player::doPhysics() {
    position += inputVector * *currentSpeed;
    position = Vector2Clamp(position, Vector2{0,0}, Vector2{ static_cast<float>(GlobalVariables::gameWidth()),static_cast<float>(GlobalVariables::gameHeight())});
}

void Player::startHyper() {
    GlobalVariables::getCurrentPhase()->startHyper();
    GlobalVariables::setCurrentGrazeMetre(0);
}

