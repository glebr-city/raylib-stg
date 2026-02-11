//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_PLAYERBULLET_H
#define RAYLIB_STG_PLAYERBULLET_H
#include "SimpleBullet.h"

class PlayerBullet : public SimpleBullet {
    protected:
    ANIMATED_SPRITES sprite = PLAYER_BULLET;
public:
    PlayerBullet() {
        position = Vector2();
    }
    PlayerBullet(Vector2 pos) {
        position = pos;
    }

    void doPreStep() override {
        SpriteHandler::DrawMyAnimatedSprite(sprite, position);
    }

    bool doPhysics() {
        if (position.y < -6) {
            return false;
        }
        position.y -= 4;
        return true;
    }

};
#endif //RAYLIB_STG_PLAYERBULLET_H