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

enum VALUESPRITE {
    DARK_SMALL = 0,
    DARK_MEDIUM = 8,
    DARK_LARGE = 16,
    LIGHT_SMALL = 24,
    LIGHT_MEDIUM = 32,
    LIGHT_LARGE = 40
};

class ScoreItem : public Spawnable {
protected:
    int stepsElapsed = 0;
    float speed = 0;
    float antiGravityXVelocity = 0; //Moving left and right before being sucked up!
    float currentAntiGravity = 0; //The item moves up when spawned. Once this is 0, it is sucked up.
    Vector2 position{};
    int value = 0;
    VALUESPRITE valueSprite = DARK_SMALL;
    public:
    using StepThinker::doPhysics;
    ScoreItem() {
        position = Vector2 {};
    }
    ScoreItem(const Vector2 _position) {
        position = _position;
    }
    void doPreStep() override {
        SpriteHandler::DrawMyAnimatedSprite(SCORE_ITEM, valueSprite, position);
    }

    bool doPhysics(const std::array<Vector2, 2> playerPosAndMovement) override {
        stepsElapsed++;
        if (currentAntiGravity > 0) {
            position.x += ((position.x - playerPosAndMovement.at(0).x) * currentAntiGravity / 50);
            position.y -= currentAntiGravity;
            currentAntiGravity -= 0.04f;
            return true;
        }
        float distanceSQ = Vector2DistanceSqr(position, playerPosAndMovement.at(0));
        if (distanceSQ < speed * speed) {
            std::cout << std::max(10, value * 50) << " " << stepsElapsed << std::endl;
            ScoreHandler::addScore(std::max(10, value * 50));
            return false;
        }
        position += Vector2Normalize(Vector2Subtract(playerPosAndMovement.at(0), position)) * speed;
        speed += 0.03f - 0.0000001f * distanceSQ;
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
        value = divided;
        if (divided <= 5) {
            valueSprite = DARK_SMALL;
        } else if (divided <= 10) {
            valueSprite = DARK_MEDIUM;
        } else if (divided <= 20) {
            valueSprite = DARK_LARGE;
        } else if (divided <= 30) {
            valueSprite = LIGHT_SMALL;
        } else if (divided <= 40) {
            valueSprite = LIGHT_MEDIUM;
        } else {
            valueSprite = LIGHT_LARGE;
        }
    }
};
#endif //RAYLIB_STG_SCOREITEM_H