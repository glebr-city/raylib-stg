//
// Created by g on 05/02/2026.
//

#include "../include/SimpleBullet.h"

#include <iostream>
#include <ostream>

#include "raymath.h"

SimpleBullet::SimpleBullet(const Vector2 pos) : Bullet(pos){}


void SimpleBullet::doPhysics(const std::array<Vector2, 2> playerPosAndMovement) {
    CheckCollisionCircleLine(position, radius, playerPosAndMovement[0], Vector2Add(playerPosAndMovement[0], playerPosAndMovement[1]));
}
