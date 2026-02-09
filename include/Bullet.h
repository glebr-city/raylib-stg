//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_BULLET_H
#define RAYLIB_STG_BULLET_H
#include "raylib.h"
#include "StepThinker.h"


class Bullet  : public StepThinker{
public:
 bool doPhysics(std::array<Vector2, 2> playerPosAndMovement) override = 0;
 Bullet() {
  position = Vector2();
 }
 Bullet(Vector2 pos) {
  position = pos;
 }

 virtual void spawn(const Vector2 _position) {
  position = _position;
 }
private:
 static const float radius;
 Vector2 position{};

};


#endif //RAYLIB_STG_BULLET_H