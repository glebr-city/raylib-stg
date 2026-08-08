//
// Created by n on 30/07/2026.
//

//
// Created by g on 05/02/2026.
//

#include "SimpleBullet3.h"


#include <iostream>
#include <ostream>

#include "DamageHandler.h"
#include "GlobalVariables.h"
#include "../include/raylib/raymath.h"
#include "SpriteHandler.h"

void SimpleBullet3::spawn(Vector2 pos, Vector2 dir, Color col) {
    position = pos;
    direction = dir;
    color = col;
    hasBeenGrazed = false;
}

void SimpleBullet3::spawn(Vector2 pos, Vector2 dir) {
    position = pos;
    direction = dir;
    color = GREEN;
    hasBeenGrazed = false;
}

SimpleBullet3::SimpleBullet3(const Vector2 pos, const Vector2 dir) : SimpleBullet(pos) {
    position = pos;
    direction = dir;
    //handler->addStepThinker(std::make_unique<SimpleBullet3>(*this));
}

SimpleBullet3::SimpleBullet3() {
    position = Vector2();
    direction = Vector2();
}

SimpleBullet3::SimpleBullet3(const Vector2 pos, const Vector2 dir, Color col) : SimpleBullet(pos) {
    position = pos;
    direction = dir;
    color = col;
    //handler->addStepThinker(std::make_unique<SimpleBullet3>(*this));
}

void SimpleBullet3::doPreStep() {
    SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_BULLET, .col = color});
}

bool SimpleBullet3::doPhysics() {
    if (CheckCollisionRoundBullet(position, radius, PlayerHandler::GetPlayer().get()->GetPosition(), PlayerHandler::GetPlayer().get()->GetFinalPos(), grazeValue)) {
        DamageHandler::hitPlayer();
        return false;
    }
    position = Vector2Add(position, direction * speed);
    if (position.x < -2 || position.x > 122 || position.y < -1000 || position.y > 182)
        return false;
    return true;
}
