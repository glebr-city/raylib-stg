//
// Created by g on 04/02/2026.
//

#include <array>
#include <iostream>
#include <Player.h>

#include "GameHandler.h"
#include "GlobalVariables.h"
#include "InputHandler.h"
#include "LifeHandler.h"
#include "PhaseHelper.h"
#include "PlayerBullets.h"
#include "../include/raylib/raylib.h"
#include "raymath.h"
#include "SpriteHandler.h"

constexpr float speed = 1.6;
constexpr float focusSpeed = 0.85;
const float* currentSpeed = &speed;
bool leftDown = false;
bool rightDown = false;
bool upDown = false;
bool downDown = false;

Vector2 position;
Vector2 finalPos{}; //Calculated during preStep, applied during doPhysics.
Vector2 inputVector {0, 0};
Rectangle playerRect = {0.0f, 0.0f, 13.0f, 13.0f};
constexpr int fireCooldown = 30; //Frames to wait between player shots
int currentFireCooldown = 0; //Frames remaining until the player may shoot again
bool wishToShoot = false; //Rudimentary buffer!
Texture2D* grazeRadiusFillingSprite;
Rectangle hyperRingRect = {6300, 0, 180, 180};
auto currentHyperRingColour = WHITE; //Using the same effect for Hyper and for taking damage.
ANIMATED_SPRITES grazeRadiusFilledSprite = PLAYER_GRAZE_FILLED;
ANIMATED_SPRITES hyperAuraSprite = PLAYER_HYPER_AURA;
const int hyperCostRate = 3; //How much graze metre to lose on every step in Hyper Mode.
bool hyperOn = false;

Player::Player(const Vector2 pos) {
    hyperRingRect.x = 6300;
    reset(pos);
}

Vector2 Player::GetPosition() {
    return position;
}

Vector2 Player::GetMovement() {
    return Vector2Scale(inputVector, *currentSpeed);
}

Vector2 Player::GetFinalPos()
{
    return finalPos;
}

void Player::setFinalPos() //Called during preStep.
{
    finalPos = position;
    finalPos += Vector2Normalize(inputVector) * *currentSpeed;
    finalPos = Vector2Clamp(finalPos, Vector2{0,0}, Vector2{ static_cast<float>(gameWidth),static_cast<float>(gameHeight)});
}

bool Player::GetHyperOn()
{
    return hyperOn;
}

std::array<Vector2, 2> Player::GetPosAndMovement() { //Used by bullets to perform accurate collision tests.
    return std::array<Vector2, 2>{ position, Vector2Scale(inputVector, *currentSpeed) };
}

void Player::reset(const Vector2 pos) {
    hyperOn = false;
    grazeRadiusFillingSprite = SpriteHandler::getStaticSpriteTexture(PLAYER_GRAZE_FILLING);
    position = pos;
}

void Player::doPreStep() {
    inputVector = InputHandler::GetInputVector();


    if (InputHandler::CheckInputsPressed(INPUT_FOCUS))
        currentSpeed = &focusSpeed;
    else if (InputHandler::CheckInputsReleased(INPUT_FOCUS)) {
        currentSpeed = &speed;
    }

    if (InputHandler::CheckInputsPressed(INPUT_HYPER))
    {
        if (hyperOn)
        {
            endHyper();
        }
    }

    if (InputHandler::CheckInputsDown(INPUT_HYPER)) {
        if (!hyperOn) {
            if (currentGrazeMetre >= maxGrazeMetre)
                startHyper();
        }
    }
    if (InputHandler::CheckInputsDown(INPUT_FIRE)) {
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
            currentFireCooldown = 4;
        } else {
            SoundHandler::PlaySound(SLIDE_4);
            PlayerBullets::spawnPlayerBullet(false, position);
            currentFireCooldown = fireCooldown;
        }
    } else if (currentFireCooldown == fireCooldown - 7) {
        //SoundHandler::PlaySound(SLIDE_3);
        PlayerBullets::spawnPlayerBullet(false, position);
    } else if (currentFireCooldown == fireCooldown - 14) {
        //SoundHandler::PlaySound(SLIDE_3);
        PlayerBullets::spawnPlayerBullet(false, position);
    } else if (currentFireCooldown == fireCooldown - 24) {
        wishToShoot = false;
    }
    if (hyperOn)
    {
        ScoreHandler::setMultiplier(2 + std::min(8.0, (currentGrazeMetre) * 0.0055));
        float xOffset = static_cast<float>(GlobalVariables::currentStep() % 31) / 4;
        const unsigned char tempAlpha = static_cast<char>(std::max(static_cast<float>(0), 255 - static_cast<float>(GlobalVariables::currentStep() % 31) * 8));
        const Color hyperGhostColour = {200, 200, 0, tempAlpha};
        SpriteHandler::QueueMyAnimatedSprite({.i = PLAYER, .pos = Vector2Add(position, {xOffset, 1}), .yOffset = static_cast<int>(-inputVector.x), .l =LAYER_PLAYER, .col = hyperGhostColour});
        SpriteHandler::QueueMyAnimatedSprite({.i = PLAYER, .pos = Vector2Add(position, {-xOffset, 1}), .yOffset = static_cast<int>(-inputVector.x), .l =LAYER_PLAYER, .col = hyperGhostColour});
        SpriteHandler::QueueMyAnimatedSprite({.i = PLAYER, .pos = Vector2Add(position, {xOffset, xOffset}), .yOffset = static_cast<int>(-inputVector.x), .l =LAYER_PLAYER,  .col = hyperGhostColour});
        SpriteHandler::QueueMyAnimatedSprite({.i = PLAYER, .pos = Vector2Add(position, {-xOffset, xOffset}), .yOffset = static_cast<int>(-inputVector.x), .l =LAYER_PLAYER,  .col = hyperGhostColour});
        SpriteHandler::QueueMyAnimatedSprite({.i = PLAYER, .pos = Vector2Add(position, {0, xOffset}), .yOffset = static_cast<int>(-inputVector.x), .l =LAYER_PLAYER, .col = hyperGhostColour});
        xOffset /= 2;
        SpriteHandler::QueueMyAnimatedSprite({.i = PLAYER, .pos = Vector2Add(position, {xOffset, 1}), .yOffset = static_cast<int>(-inputVector.x), .l =LAYER_PLAYER, .col = hyperGhostColour});
        SpriteHandler::QueueMyAnimatedSprite({.i = PLAYER, .pos = Vector2Add(position, {-xOffset, 1}), .yOffset = static_cast<int>(-inputVector.x), .l =LAYER_PLAYER, .col = hyperGhostColour});
        SpriteHandler::QueueMyAnimatedSprite({.i = PLAYER, .pos = Vector2Add(position, {xOffset, xOffset}), .yOffset = static_cast<int>(-inputVector.x), .l =LAYER_PLAYER, .col = hyperGhostColour});
        SpriteHandler::QueueMyAnimatedSprite({.i = PLAYER, .pos = Vector2Add(position, {-xOffset, xOffset}), .yOffset = static_cast<int>(-inputVector.x), .l =LAYER_PLAYER, .col = hyperGhostColour});
        GlobalVariables::setGrazeMetre(std::max(0, GlobalVariables::getGrazeMetre() - hyperCostRate));
        if (GlobalVariables::getGrazeMetre() <= 0)
            endHyper();
    }
    hyperRingRect.x = std::min(6300.0f, hyperRingRect.x + 180);
    setFinalPos();
}

void Player::doPhysics(Vector2 pos) {
    std::cout << "!!! Player::doPhysics should be called with no parameters.";
    doPhysics();
}

bool Player::doPhysics() {
    position = finalPos;
    return true;
}

void Player::doPostStep()
{
    SpriteHandler::QueueMyAnimatedSprite({.i=PLAYER_HYPER_RING, .pos=Vector2 {position.x - 90, position.y - 90}, .l=LAYER_PLAYER, .col=currentHyperRingColour, .corner = true, .rect=hyperRingRect});
    SpriteHandler::QueueMyStaticSprite({.i = PLAYER_GRAZE_RADIUS, .pos = position, .l = LAYER_PLAYER});
    const float tempHeight = floor(static_cast<float>(currentGrazeMetre) / maxGrazeMetre * 22);
    const float tempX = currentGrazeMetre >= maxGrazeMetre ? 22 : 0;
    if (GlobalVariables::getGrazeMetre() < maxGrazeMetre)
        SpriteHandler::QueueMyStaticSprite({.i=PLAYER_GRAZE_FILLING, .pos=Vector2 {position.x - grazeRadius, position.y + grazeRadius - tempHeight}, .col=WHITE, .corner=true, .rect=Rectangle{tempX, 22 - tempHeight, 22, tempHeight}});
    else
        SpriteHandler::QueueMyAnimatedSprite({grazeRadiusFilledSprite, position});
    SpriteHandler::QueueMyAnimatedSprite({PLAYER,  position, static_cast<int>(-inputVector.x), LAYER_PLAYER,}); //Counting on digital movement only.
}

void Player::startHyper() {
    currentHyperRingColour = WHITE;
    hyperRingRect.x = 0;
    GlobalVariables::getCurrentPhase()->cancelBullets();
    SoundHandler::StopSound(PLAYER_HYPER_3, 0);
    SoundHandler::PlaySound(0, PLAYER_HYPER_1, false);
    hyperOn = true;
}

void Player::endHyper() {
    hyperRingRect.x = 0;
    GlobalVariables::getCurrentPhase()->cancelBullets();
    hyperOn = false;
    SoundHandler::StopSound(PLAYER_HYPER_1, 0);
    SoundHandler::PlaySound(0, PLAYER_HYPER_2, false);
    GlobalVariables::setGrazeMetre(0);
    ScoreHandler::setMultiplier(1);
}

void Player::getHit() {
    if (!LifeHandler::canSpawnPlayer())
    {
        GameHandler::RestartGame();
        return;
    }
    SoundHandler::PlaySound(PLAYER_HIT);
    hyperOn = false;
    GlobalVariables::setGrazeMetre(0);
    ScoreHandler::setMultiplier(1);
    currentHyperRingColour = RED;
    hyperRingRect.x = 0;
}