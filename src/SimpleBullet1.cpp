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

void SimpleBullet1::doPhysics(Vector2 playerPosition) {
    position = Vector2Add(position, direction * speed);
    if (Vector2Distance(position, playerPosition) <= radius) {
        std::cout << currentStep() << ": Bullet collided!!!!!!!!!!!" << std::endl;
    }
}
