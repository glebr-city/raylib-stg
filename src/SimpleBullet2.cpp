//
// Created by g on 06/02/2026.
//

#include "../include/SimpleBullet2.h"


#include "DamageHandler.h"
#include "GlobalVariables.h"
#include "../include/raylib/raymath.h"

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
    SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_BULLET, .col = color});
}