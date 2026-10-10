//
// Created by g on 13/02/2026.
//

#ifndef RAYLIB_STG_SCOREITEM_H
#define RAYLIB_STG_SCOREITEM_H
#include <cmath>

#include "raylib/raymath.h"
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

inline const int scoreItemMultiplier = 50;

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
        SpriteHandler::QueueMyAnimatedSprite({SCORE_ITEM, position, valueSprite, LAYER_ENEMY});
    }

    bool doPhysics() override {
        stepsElapsed++;
        const Vector2 playerFinalPos = PlayerHandler::GetPlayer().get()->GetFinalPos();
        if (currentAntiGravity > 0) {
            position.x += ((position.x - playerFinalPos.x) * currentAntiGravity / 50);
            position.y -= currentAntiGravity;
            currentAntiGravity -= 0.04f;
            return true;
        }
        const float distanceSQ = Vector2DistanceSqr(position, playerFinalPos);
        if (distanceSQ < speed * speed) {
            ScoreHandler::addScore(std::max(10, value * scoreItemMultiplier), false);
            return false;
        }
        position += Vector2Normalize(Vector2Subtract(playerFinalPos, position)) * speed;
        speed += 0.03f - 0.0000003f * distanceSQ;
        return true;
    }

    void spawn(const Vector2 _position) override {
        antiGravityXVelocity = _position.x * (static_cast<int>(std::abs(_position.x)) % static_cast<int>(std::abs(position.y))) / 100;
        currentAntiGravity = 1;
        speed = 0;
        position = _position;
        value = DARK_SMALL;
    }

    void spawn(const Vector2 _position, const u_int _value) override {
        int xAsInt = static_cast<int>(std::floor(_position.x));
        int yAsInt = static_cast<int>(std::floor(_position.y));
        currentAntiGravity = 1;
        speed = 0;
        position = _position;

        const int divided = static_cast<int>(std::floor(static_cast<double>(_value) * 0.1));
        value = divided;

        valueSprite = DARK_SMALL;
        if (divided <= 5) {
            return;
        }
        if (divided <= 10) {
            valueSprite = DARK_MEDIUM;
            return;
        }
        if (divided <= 20) {
            valueSprite = DARK_LARGE;
            return;
        }
        if (divided <= 30) {
            valueSprite = LIGHT_SMALL;
            return;
        }
        if (divided <= 40) {
            valueSprite = LIGHT_MEDIUM;
            return;
        }
        valueSprite = LIGHT_LARGE;
        return;
    }
};
#endif //RAYLIB_STG_SCOREITEM_H