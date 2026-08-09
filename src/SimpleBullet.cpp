//
// Created by g on 05/02/2026.
//

#include "../include/SimpleBullet.h"

#include <iostream>
#include <ostream>

#include "../include/raylib/raymath.h"


void SimpleBullet::doPreStep() {
    SpriteHandler::QueueMyAnimatedSprite({sprite, position});
}

bool SimpleBullet::doPhysics() {
    const std::array<Vector2, 2> playerPosAndMovement = PlayerHandler::GetPlayer().get()->GetPosAndMovement();
    return !CheckCollisionCircleLine(position, radius, playerPosAndMovement[0], Vector2Add(playerPosAndMovement[0], playerPosAndMovement[1]));
}

void SimpleBullet::spawn(const Vector2 _position) {
    position = _position;
    hasBeenGrazed = false;
}

Vector2 SimpleBullet::GetPosition() {
    return position;
}
