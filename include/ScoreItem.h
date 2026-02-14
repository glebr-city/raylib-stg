//
// Created by g on 13/02/2026.
//

#ifndef RAYLIB_STG_SCOREITEM_H
#define RAYLIB_STG_SCOREITEM_H
#include <cmath>
#include "raymath.h"
#include "ScoreHandler.h"
#include "Spawnable.h"
#include "SpriteHandler.h"

enum VALUE {
    DARK_SMALL = 0,
    DARK_MEDIUM = 8,
    DARK_LARGE = 16,
    LIGHT_SMALL = 24,
    LIGHT_MEDIUM = 32,
    LIGHT_LARGE = 40
};

class ScoreItem : public Spawnable {
protected:
    float speed = 0;
    float antiGravityXVelocity = 0; //Moving left and right before being sucked up!
    float currentAntiGravity = 0; //The item moves up when spawned. Once this is 0, it is sucked up.
    Vector2 position{};
    VALUE value = DARK_SMALL;
    public:
    using StepThinker::doPhysics;
    ScoreItem() {
        position = Vector2 {};
    }
    ScoreItem(const Vector2 _position) {
        position = _position;
    }
    void doPreStep() override {
        SpriteHandler::DrawMyAnimatedSprite(SCORE_ITEM, value, position);
    }

    bool doPhysics(const std::array<Vector2, 2> playerPosAndMovement) override {
        if (currentAntiGravity > 0) {
            position.x += ((position.x - playerPosAndMovement.at(0).x) * currentAntiGravity / 50);
            position.y -= currentAntiGravity;
            currentAntiGravity -= 0.04f;
            return true;
        }
        if (Vector2DistanceSqr(position, playerPosAndMovement.at(0)) < speed * speed) {
            ScoreHandler::addScore(std::max(10, value * 2));
            return false;
        }
        position += Vector2Normalize(Vector2Subtract(playerPosAndMovement.at(0), position)) * speed;
        speed += 0.03f;
        return true;
    }

    void spawn(const Vector2 _position) override {
        antiGravityXVelocity = _position.x * (static_cast<int>(std::abs(_position.x)) % static_cast<int>(std::abs(position.y))) / 100;
        currentAntiGravity = 1;
        speed = 0;
        position = _position;
        value = DARK_SMALL;
    }

    void spawn(const Vector2 _position, const int _value) {
        int xAsInt = static_cast<int>(std::floor(_position.x));
        int yAsInt = static_cast<int>(std::floor(_position.y));
        currentAntiGravity = 1;
        speed = 0;
        position = _position;

        int divided = static_cast<int>(std::floor(static_cast<double>(_value) / 10));
        switch (divided) {
            case 2: value = DARK_MEDIUM; break;
            case 3: value = DARK_MEDIUM; break;
            default: value = DARK_SMALL; break;
        }
    }
};
#endif //RAYLIB_STG_SCOREITEM_H