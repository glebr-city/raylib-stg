//
// Created by g on 06/02/2026.
//

#include "../include/SimpleBullet2.h"


#include "DamageHandler.h"
#include "GlobalVariables.h"
#include "raymath.h"

void SimpleBullet2::spawn(const Vector2 pos, const Vector2 dir, const Color col) {
    position = pos;
    direction = dir;
    color = col;
    hasBeenGrazed = false;
}

void SimpleBullet2::spawn(const Vector2 pos, const Vector2 dir) {
    position = pos;
    direction = dir;
    color = GREEN;
    hasBeenGrazed = false;
}


SimpleBullet2::SimpleBullet2() {
    position = Vector2();
    direction = Vector2();
}

SimpleBullet2::SimpleBullet2(const Vector2 pos, const Vector2 dir) : SimpleBullet(pos) {
    position = pos;
    direction = dir;
}

SimpleBullet2::SimpleBullet2(const Vector2 pos, const Vector2 dir, Color col) : SimpleBullet(pos) {
    position = pos;
    direction = dir;
    color = col;
}

void SimpleBullet2::doPreStep() {
    SpriteHandler::DrawMyAnimatedSprite(sprite, position, color);
}

bool SimpleBullet2::doPhysics(const std::array<Vector2, 2> playerPosAndMovement) {
    std::cout << "SimpleBullet2::doPhysics: " << GlobalVariables::getCurrentPhase() << std::endl;
    Vector2 playerFinalPoint = playerPosAndMovement[0] + (playerPosAndMovement[1] - Vector2Scale(direction, speed));
    if (CheckCollisionRoundBullet(position, radius, playerPosAndMovement[0], playerFinalPoint, grazeValue)) {
        DamageHandler::hitPlayer();
        return false;
    }
    position = Vector2Add(position, direction * speed);
    if (position.x < -2 || position.x > 122 || position.y < -100 || position.y > 182)
        return false;
    return true;
}