//
// Created by g on 05/02/2026.
//
#ifndef RAYLIB_STG_BULLET_H
#define RAYLIB_STG_BULLET_H
#include <cfloat>
#include <cmath>
#include "DamageHandler.h"
#include "GrazeConstants.h"
#include "raylib/raylib.h"
#include "Spawnable.h"

class Bullet : public Spawnable {
protected:
    Vector2 startOfTickPos = {};
    u_int scoreValue;
    static constexpr uint grazeValue = 40;

    bool CheckCollisionRoundBullet(const Vector2 _center, const float _radius, const Vector2 p1, Vector2 p2, const int _grazeValue) {
        p2.x += _center.x - startOfTickPos.x;
        p2.y += _center.y - startOfTickPos.y;
        const float dx = p1.x - p2.x;
        const float dy = p1.y - p2.y;
        float dx2;
        float dy2;

        if ((std::fabsf(dx) + std::fabsf(dy)) <= FLT_EPSILON) {
            dx2 = (p1.x - _center.x);
            dy2 = (p1.y - _center.y);
        } else {
            const float lengthSQ = ((dx * dx) + (dy * dy));
            float dotProduct = (((_center.x - p1.x) * (p2.x - p1.x)) + ((_center.y - p1.y) * (p2.y - p1.y))) / (
                                   lengthSQ);
            if (dotProduct > 1.0f) dotProduct = 1.0f;
            else if (dotProduct < 0.0f) dotProduct = 0.0f;
            dx2 = (p1.x - (dotProduct * (dx))) - _center.x;
            dy2 = (p1.y - (dotProduct * (dy))) - _center.y;
        }

        const float distanceSQ = ((dx2 * dx2) + (dy2 * dy2));
        const float radiusSQ = _radius * _radius;
        if (distanceSQ <= radiusSQ + grazeRadiusSQ) {
            if (!hasBeenGrazed) {
                DamageHandler::grazePlayer(_grazeValue);
                hasBeenGrazed = true;
            }
        }

        return (distanceSQ <= radiusSQ);
    }

public:
    bool doPhysics() override = 0;

    Bullet() = default;

    Bullet(const u_int _scoreValue, const Vector2 _pos) : Spawnable(_pos), scoreValue(_scoreValue) {
    }

    void spawn(const Vector2 _position) override {
        Spawnable::position = _position;
        SetStartOfTickPos();
        hasBeenGrazed = false;
    }

    void spawn(const Vector2 _position, const u_int _scoreValue) override {
        position = _position;
        SetStartOfTickPos();
        hasBeenGrazed = false;
        scoreValue = _scoreValue;
    }

    u_int GetScoreValue() override {
        return scoreValue;
    }

    void SetStartOfTickPos() override {
        startOfTickPos = position;
    }


protected:
    bool hasBeenGrazed = false;
    static const float radius;
};


#endif //RAYLIB_STG_BULLET_H
