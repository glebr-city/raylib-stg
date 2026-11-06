//
// Created by g on 05/11/2026.
//

#ifndef RAYLIB_STG_BOSS3COLOURSHIFTBULLET_H
#define RAYLIB_STG_BOSS3COLOURSHIFTBULLET_H
#include "SimpleBullet1VariableSpeed.h"

class Boss3ColourShiftBullet : public SimpleBullet1VariableSpeed {
private:
    static constexpr Vector4 finalColour = {0, 228, 48, 255 };
    Vector4 colourVector{};
    public:
    Boss3ColourShiftBullet() {
        grazeValue = 80;
    }
    void spawn(const float speed, const Vector2 pos, const Vector2 dir, const Color col) override {
        SimpleBullet1VariableSpeed::spawn(speed, pos, dir, col);
        colourVector = Vector4(color.r, color.g, color.b, color.a);
    }
    void doPostStep() override {
        colourVector = Vector4MoveTowards(colourVector, finalColour, 5);
        color = Color(colourVector.x, colourVector.y, colourVector.z, colourVector.w);
        SpriteHandler::QueueMyAnimatedSprite({.i = sprite, .pos = position, .l = LAYER_BULLET_LOW, .col = color});
    }
};
#endif //RAYLIB_STG_BOSS3COLOURSHIFTBULLET_H