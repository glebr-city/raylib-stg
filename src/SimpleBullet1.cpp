//
// Created by g on 05/02/2026.
//

#include "../include/SimpleBullet1.h"

#include <iostream>
#include <ostream>

#include "DamageHandler.h"
#include "GlobalVariables.h"
#include "raymath.h"
#include "SpriteHandler.h"

void SimpleBullet1::spawn(Vector2 pos, Vector2 dir, Color col) {
    position = pos;
    direction = dir;
    color = col;
}

void SimpleBullet1::spawn(Vector2 pos, Vector2 dir) {
    position = pos;
    direction = dir;
    color = GREEN;
}

SimpleBullet1::SimpleBullet1(const Vector2 pos, const Vector2 dir) : SimpleBullet(pos) {
    position = pos;
    direction = dir;
    //handler->addStepThinker(std::make_unique<SimpleBullet1>(*this));
}

SimpleBullet1::SimpleBullet1() {
    position = Vector2();
    direction = Vector2();
}

SimpleBullet1::SimpleBullet1(const Vector2 pos, const Vector2 dir, Color col) : SimpleBullet(pos) {
    position = pos;
    direction = dir;
    color = col;
    //handler->addStepThinker(std::make_unique<SimpleBullet1>(*this));
}

void SimpleBullet1::doPreStep() {
    SpriteHandler::DrawMyAnimatedSprite(sprite, position, color);
}

bool SimpleBullet1::doPhysics(const std::array<Vector2, 2> playerPosAndMovement) {
    Vector2 playerFinalPoint = playerPosAndMovement[0] + (playerPosAndMovement[1] - Vector2Scale(direction, speed));
    if (CheckCollisionCircleLine(position, radius, playerPosAndMovement[0], playerFinalPoint)) {
        DamageHandler::hitPlayer();
        return false;
    }
    if (!hasBeenGrazed && CheckCollisionCircles(position, radius, playerFinalPoint, GlobalVariables::grazeRadius())) {
        DamageHandler::grazePlayer(grazeValue);
        hasBeenGrazed = true;
    }
    position = Vector2Add(position, direction * speed);
    if (position.x < -2 || position.x > 122 || position.y < -1000 || position.y > 182)
        return false;
    return true;
}
