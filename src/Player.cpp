//
// Created by g on 04/02/2026.
//

#include <array>
#include <iostream>
#include <Player.h>

#include "GlobalVariables.h"
#include "InputHandler.h"
#include "PhaseHelper.h"
#include "PlayerBullets.h"
#include "raylib.h"
#include "raymath.h"
#include "SpriteHandler.h"

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
Vector2 position;
Vector2 inputVector {0, 0};
Rectangle playerRect = {0.0f, 0.0f, 13.0f, 13.0f};
constexpr int fireCooldown = 30; //Frames to wait between player shots
int currentFireCooldown = 0; //Frames remaining until the player may shoot again
bool wishToShoot = false; //Rudimentary buffer!
Texture2D grazeRadiusSprite;
Texture2D grazeRadiusFillingSprite;
Texture2D hyperRingSprite;
Rectangle hyperRingRect = {6300, 0, 180, 180};
ANIMATED_SPRITES grazeRadiusFilledSprite = PLAYER_GRAZE_FILLED;
ANIMATED_SPRITES hyperAuraSprite = PLAYER_HYPER_AURA;
int hyperCostRate = 3; //How much graze metre to lose on every step in Hyper Mode.
bool hyperOn = false;

Player::Player(Vector2 pos) {
    grazeRadiusSprite = LoadTexture("resources/grazeRadius.png");
    grazeRadiusFillingSprite = LoadTexture("resources/grazeRadiusFilling.png");
    hyperRingSprite = LoadTexture("resources/growingRingSpriteSheet.png");
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

    if (InputHandler::CheckInputsPressed(hyperKeys)) {
        if (!hyperOn) {
            if (currentGrazeMetre >= maxGrazeMetre)
                startHyper();
        }
        else {
            endHyper();
        }
    }
    if (InputHandler::CheckInputsDown(fireKeys)) {
        wishToShoot = true;
    }

    if (--currentFireCooldown <= 0 && wishToShoot) {
        wishToShoot = false;
        if (hyperOn) {
            float xOffset;
            if (GlobalVariables::currentStep() % 51 < 26)
                xOffset = (static_cast<float>(GlobalVariables::currentStep() % 51)) - 12.5f;
            else
                xOffset = 41.66667f - (static_cast<float>((GlobalVariables::currentStep() % 51)));
            xOffset /= 50;
            PlayerBullets::spawnPlayerBullet(true, Vector2Add(position, Vector2 {0, -3}), xOffset);
            currentFireCooldown = 5;
        } else {
            PlayerBullets::spawnPlayerBullet(false, position);
            currentFireCooldown = fireCooldown;
        }
    } else if (currentFireCooldown == fireCooldown - 7) {
        PlayerBullets::spawnPlayerBullet(false, position);
    } else if (currentFireCooldown == fireCooldown - 14) {
        PlayerBullets::spawnPlayerBullet(false, position);
    } else if (currentFireCooldown == fireCooldown - 24) {
        wishToShoot = false;
    }
    if (hyperOn) {
        ScoreHandler::setMultiplier(1 + (static_cast<float>(currentGrazeMetre) * 0.0040408));
        float xOffset = static_cast<float>(GlobalVariables::currentStep() % 31) / 4;
        const unsigned char tempAlpha = static_cast<char>(std::max(static_cast<float>(0), 255 - static_cast<float>(GlobalVariables::currentStep() % 31) * 8));
        const Color hyperGhostColour = {200, 200, 0, tempAlpha};
        SpriteHandler::DrawMyAnimatedSprite(PLAYER, static_cast<int>(-inputVector.x * 13), Vector2Add(position, {xOffset, 1}), hyperGhostColour);
        SpriteHandler::DrawMyAnimatedSprite(PLAYER, static_cast<int>(-inputVector.x * 13), Vector2Add(position, {-xOffset, 1}), hyperGhostColour);
        SpriteHandler::DrawMyAnimatedSprite(PLAYER, static_cast<int>(-inputVector.x * 13), Vector2Add(position, {xOffset, xOffset}), hyperGhostColour);
        SpriteHandler::DrawMyAnimatedSprite(PLAYER, static_cast<int>(-inputVector.x * 13), Vector2Add(position, {-xOffset, xOffset}), hyperGhostColour);
        SpriteHandler::DrawMyAnimatedSprite(PLAYER, static_cast<int>(-inputVector.x * 13), Vector2Add(position, {0, xOffset}), hyperGhostColour);
        xOffset /= 2;
        SpriteHandler::DrawMyAnimatedSprite(PLAYER, static_cast<int>(-inputVector.x * 13), Vector2Add(position, {xOffset, 1}), hyperGhostColour);
        SpriteHandler::DrawMyAnimatedSprite(PLAYER, static_cast<int>(-inputVector.x * 13), Vector2Add(position, {-xOffset, 1}), hyperGhostColour);
        SpriteHandler::DrawMyAnimatedSprite(PLAYER, static_cast<int>(-inputVector.x * 13), Vector2Add(position, {xOffset, xOffset}), hyperGhostColour);
        SpriteHandler::DrawMyAnimatedSprite(PLAYER, static_cast<int>(-inputVector.x * 13), Vector2Add(position, {-xOffset, xOffset}), hyperGhostColour);
        GlobalVariables::setGrazeMetre(std::max(0, GlobalVariables::getGrazeMetre() - hyperCostRate));
        if (GlobalVariables::getGrazeMetre() <= 0)
            endHyper();
    }
    hyperRingRect.x = std::min(6300.0f, hyperRingRect.x + 180);
    DrawTextureRec(hyperRingSprite, hyperRingRect, Vector2 {position.x - 90, position.y - 90}, WHITE);
    DrawTextureV(grazeRadiusSprite, Vector2 {position.x - grazeRadius, position.y - grazeRadius}, WHITE);
    float tempHeight = floor(static_cast<float>(currentGrazeMetre) / maxGrazeMetre * 22);
    float tempX = currentGrazeMetre >= maxGrazeMetre ? 22 : 0;
    if (GlobalVariables::getGrazeMetre() < maxGrazeMetre)
        DrawTextureRec(grazeRadiusFillingSprite, Rectangle{tempX, 22 - tempHeight, 22, tempHeight}, Vector2 {position.x - grazeRadius, position.y + grazeRadius - tempHeight}, WHITE);
    else
        SpriteHandler::DrawMyAnimatedSprite(grazeRadiusFilledSprite, position);
    SpriteHandler::DrawMyAnimatedSprite(PLAYER, static_cast<int>(-inputVector.x * 13), position); //Counting on digital movement only.
    Vector2Normalize(inputVector);
}

void Player::doPhysics(Vector2 pos) {
    std::cout << "!!! Player::doPhysics should be called with no parameters.";
    doPhysics();
}

bool Player::doPhysics() {
    position += inputVector * *currentSpeed;
    position = Vector2Clamp(position, Vector2{0,0}, Vector2{ static_cast<float>(gameWidth),static_cast<float>(gameHeight)});
    return true;
}

void Player::startHyper() {
    hyperRingRect.x = 0;
    GlobalVariables::getCurrentPhase()->cancelBullets();
    hyperOn = true;
}

void Player::endHyper() {
    hyperRingRect.x = 0;
    GlobalVariables::getCurrentPhase()->cancelBullets();
    hyperOn = false;
    GlobalVariables::setGrazeMetre(0);
    ScoreHandler::setMultiplier(1);
}

