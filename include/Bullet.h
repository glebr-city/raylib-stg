//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_BULLET_H
#define RAYLIB_STG_BULLET_H
#include <cfloat>
#include <cmath>

#include "DamageHandler.h"
#include "GrazeConstants.h"
#include "raylib.h"
#include "Spawnable.h"


class Bullet  : public Spawnable {
protected:
 int scoreValue = 0;
 static constexpr int grazeValue = 40;
 bool CheckCollisionRoundBullet(const Vector2 _center, const float _radius, const Vector2 p1, const Vector2 p2, const int _grazeValue)
 {
  float dx = p1.x - p2.x;
  float dy = p1.y - p2.y;

  if ((std::fabsf(dx) + std::fabsf(dy)) <= FLT_EPSILON)
  {
   return CheckCollisionCircles(p1, 0, _center, _radius);
  }

  const float lengthSQ = ((dx*dx) + (dy*dy));
  float dotProduct = (((_center.x - p1.x)*(p2.x - p1.x)) + ((_center.y - p1.y)*(p2.y - p1.y)))/(lengthSQ);

  if (dotProduct > 1.0f) dotProduct = 1.0f;
  else if (dotProduct < 0.0f) dotProduct = 0.0f;

  const float dx2 = (p1.x - (dotProduct*(dx))) - _center.x;
  const float dy2 = (p1.y - (dotProduct*(dy))) - _center.y;
  const float distanceSQ = ((dx2*dx2) + (dy2*dy2));
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
 bool doPhysics(std::array<Vector2, 2> playerPosAndMovement) override = 0;
 Bullet() {
  position = Vector2();
 }
 Bullet(const Vector2 pos) {
  position = pos;
 }

 void spawn(const Vector2 _position) override {
  position = _position;
  hasBeenGrazed = false;
 }

 void spawn(const Vector2 _position, int _scoreValue) override {
  position = _position;
  hasBeenGrazed = false;
  scoreValue = _scoreValue;
 }


protected:
 bool hasBeenGrazed = false;
 static const float radius;
 Vector2 position{};
};


#endif //RAYLIB_STG_BULLET_H