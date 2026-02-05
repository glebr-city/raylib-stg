//
// Created by g on 05/02/2026.
//

#include "../include/SimpleBullet1.h"

#include "raymath.h"
#include "SpriteHandler.h"

SimpleBullet1::SimpleBullet1(const Vector2 pos, const Vector2 dir) : SimpleBullet(pos) {
    position = pos;
    direction = dir;
}

void SimpleBullet1::PreStep() {
    position = Vector2Add(position, direction * speed);
    SpriteHandler::DrawMyAnimatedSprite(BULLET_1_RED, position);
}
