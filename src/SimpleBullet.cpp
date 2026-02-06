//
// Created by g on 05/02/2026.
//

#include "../include/SimpleBullet.h"

#include <iostream>
#include <ostream>

#include "raymath.h"

SimpleBullet::SimpleBullet(const Vector2 pos) : Bullet(pos){}


void SimpleBullet::doPhysics(Vector2 playerPos) {
    if (Vector2Distance(position, playerPos) <= radius) {
        std::cout << "Bullet collision!!!!!!!!!!!!" << std::endl;
    }
}
