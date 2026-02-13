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
    static inline const ANIMATED_SPRITES hyperSprite = PLAYER_BULLET_HYPER;
    ANIMATED_SPRITES currentSprite = sprite;
    static inline const float colliderOffsetX = -3.5f;
    static inline const float colliderOffsetY = -2.5f;
    float xSpeed = 0;
    Rectangle collider{-1000, -1000, 0, 0};
public:
    PlayerBullet() : PlayerBullet(false) {};
    PlayerBullet(bool isHyper) {
        position = Vector2 {-1000, -1000};
        if (isHyper) {
            currentSprite = hyperSprite;
            collider = Rectangle {colliderOffsetX, colliderOffsetY, 16, 10};
        } else {
            collider = Rectangle {colliderOffsetX, colliderOffsetY, 7, 10};
        }
    }
    PlayerBullet(bool isHyper, Vector2 pos) {
        position = pos;
        if (isHyper) {
            currentSprite = hyperSprite;
            collider = Rectangle {position.x + colliderOffsetX, position.y + colliderOffsetY, 16, 10};
        } else {
            collider = Rectangle {position.x + colliderOffsetX, position.y + colliderOffsetY, 7, 10};
        }
    }

    void doPreStep() override {
        SpriteHandler::DrawMyAnimatedSprite(currentSprite, position);
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
        position.x += xSpeed;
        collider.x = position.x + colliderOffsetX;
        collider.y = position.y + colliderOffsetY;
        return true;
    }
    Rectangle* getCollider() {
        return &collider;
    }

    void spawn(const bool isHyper, const Vector2 _position) {
        if (isHyper) {
            currentSprite = hyperSprite;
            collider = Rectangle {colliderOffsetX, colliderOffsetY, 16, 10};
        } else {
            currentSprite = sprite;
            collider = Rectangle {colliderOffsetX, colliderOffsetY, 7, 10};
        }
        xSpeed = 0;
        position = _position;
        hasBeenGrazed = false;
    }

    void spawn(const bool isHyper, const Vector2 _position, float _xSpeed) {
        if (isHyper) {
            currentSprite = hyperSprite;
            collider = Rectangle {colliderOffsetX, colliderOffsetY, 16, 10};
        } else {
            currentSprite = sprite;
            collider = Rectangle {colliderOffsetX, colliderOffsetY, 7, 10};
        }
        position = _position;
        xSpeed = _xSpeed;
        hasBeenGrazed = false;
    }
};
#endif //RAYLIB_STG_PLAYERBULLET_H