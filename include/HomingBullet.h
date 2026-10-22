//
// Created by g on 16/10/2026.
//

#ifndef RAYLIB_STG_HOMINGBULLET_H
#define RAYLIB_STG_HOMINGBULLET_H
#include "SimpleBullet.h"

class HomingBullet : public SimpleBullet {
private:
    static constexpr float bulletRadius = 1;
    static constexpr Color bulletColour = {99, 155, 255, 255};
    public:
    HomingBullet() : SimpleBullet(15, {}, BULLET_SMALL_2_MONOCHROME, LAYER_BULLET_HIGH) {
        color = bulletColour;
    }

    bool doPhysics() override {
        if (CheckCollisionRoundBullet(position, bulletRadius, PlayerHandler::GetPlayer().get()->GetPosition(), PlayerHandler::GetPlayer().get()->GetFinalPos(), 10)) {
            DamageHandler::hitPlayer();
            return false;
        }
        return true;
    };

    void spawn(const Vector2 _position) override
    {
        SimpleBullet::spawn(_position);
    };

    [[nodiscard]] bool CheckPosition() const {
        if (position.x < -5 || position.x > 125 || position.y < -15 || position.y > 185) {
            return false;
        }
        return true;
    }

    void SetPosition(const Vector2 _pos) {
        position = _pos;
    }

};
#endif //RAYLIB_STG_HOMINGBULLET_H