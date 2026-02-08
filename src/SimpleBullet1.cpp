//
// Created by g on 05/02/2026.
//

#include "../include/SimpleBullet1.h"

#include <iostream>
#include <ostream>

#include "GameObjectHandler.h"
#include "GlobalVariables.h"
#include "raymath.h"
#include "SpriteHandler.h"


SimpleBullet1::SimpleBullet1(GameObjectHandler & handler, const Vector2 pos, const Vector2 dir) : SimpleBullet(pos) {
    position = pos;
    direction = dir;
    handler.addStepThinker(std::make_unique<SimpleBullet1>(*this));
}

SimpleBullet1::SimpleBullet1(GameObjectHandler & handler, const Vector2 pos, const Vector2 dir, Color col) : SimpleBullet(pos) {
    position = pos;
    direction = dir;
    color = col;
    handler.addStepThinker(std::make_unique<SimpleBullet1>(*this));
}

void SimpleBullet1::PreStep() {
    SpriteHandler::DrawMyAnimatedSprite(sprite, position, color);
}

void SimpleBullet1::doPhysics(const std::array<Vector2, 2> playerPosAndMovement) {
    Vector2 playerFinalPoint = playerPosAndMovement[0] + (playerPosAndMovement[1] - Vector2Scale(direction, speed));
    if (CheckCollisionCircleLine(position, radius, playerPosAndMovement[0], playerFinalPoint))
        color = RED;
    position = Vector2Add(position, direction * speed);
}
