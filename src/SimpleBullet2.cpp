//
// Created by g on 06/02/2026.
//

#include "../include/SimpleBullet2.h"

#include <iostream>

#include "GameObjectHandler.h"
#include "GlobalVariables.h"
#include "raymath.h"

SimpleBullet2::SimpleBullet2(GameObjectHandler & handler, const Vector2 pos, const Vector2 dir) : SimpleBullet(pos) {
    position = pos;
    direction = dir;
    handler.addStepThinker(std::make_unique<SimpleBullet2>(*this));
}

SimpleBullet2::SimpleBullet2(GameObjectHandler & handler, const Vector2 pos, const Vector2 dir, Color col) : SimpleBullet(pos) {
    position = pos;
    direction = dir;
    color = col;
    handler.addStepThinker(std::make_unique<SimpleBullet2>(*this));
}

void SimpleBullet2::PreStep() {
    SpriteHandler::DrawMyAnimatedSprite(sprite, position, color);
}

void SimpleBullet2::doPhysics(std::array<Vector2, 2> playerPosAndMovement) {
    Vector2 playerFinalPoint = playerPosAndMovement[0] + (playerPosAndMovement[1] - Vector2Scale(direction, speed));
    if (CheckCollisionCircleLine(position, radius, playerPosAndMovement[0], playerFinalPoint))
        color = RED;
    position = Vector2Add(position, direction * speed);
}