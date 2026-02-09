//
// Created by g on 05/02/2026.
//

#include "../include/SimpleBullet.h"

#include <iostream>
#include <ostream>

#include "raymath.h"

SimpleBullet::SimpleBullet() {
    position = Vector2();
}

SimpleBullet::SimpleBullet(const Vector2 pos) : Bullet(pos){}


bool SimpleBullet::doPhysics(const std::array<Vector2, 2> playerPosAndMovement) {
    return !CheckCollisionCircleLine(position, radius, playerPosAndMovement[0], Vector2Add(playerPosAndMovement[0], playerPosAndMovement[1]));
}

void SimpleBullet::spawn(Vector2 _position) {
    position = _position;
}
