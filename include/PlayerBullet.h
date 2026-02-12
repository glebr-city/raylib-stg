//
// Created by g on 11/02/2026.
//

#ifndef RAYLIB_STG_PLAYERBULLET_H
#define RAYLIB_STG_PLAYERBULLET_H
#include "SimpleBullet.h"

class PlayerBullet : public SimpleBullet {
    protected:
    //static const ANIMATED_SPRITES sprite = PLAYER_BULLET;
    static inline const ANIMATED_SPRITES sprite = PLAYER_BULLET;
    static inline const float colliderOffsetX = -3.5f;
    static inline const float colliderOffsetY = -2.5f;
    Rectangle collider{-1000, -1000, 0, 0};
public:
    PlayerBullet() {
        position = Vector2 {-1000, -1000};
        collider = Rectangle {colliderOffsetX, colliderOffsetY, 7, 10};
    }
    PlayerBullet(Vector2 pos) {
        position = pos;
        collider = Rectangle {position.x + colliderOffsetX, position.y + colliderOffsetY, 7, 10};
    }

    void doPreStep() override {
        SpriteHandler::DrawMyAnimatedSprite(sprite, position);
    }

    bool doPhysics(std::array<Vector2, 2> playerPosAndMovement) override {
        //std::cout << "!!! PlayerBullet::doPhysics should be called with no parameters." << std::endl;
        return doPhysics();
    }
    bool doPhysics() {
        if (position.y < -6) {
            return false;
        }
        position.y -= 4;
        collider.x = position.x + colliderOffsetX;
        collider.y = position.y + colliderOffsetY;
        return true;
    }
    Rectangle* getCollider() {
        return &collider;
    }

};
#endif //RAYLIB_STG_PLAYERBULLET_H