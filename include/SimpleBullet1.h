//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SIMPLEBULLET1_H
#define RAYLIB_STG_SIMPLEBULLET1_H
#include "raylib.h"
#include "SimpleBullet.h"


class SimpleBullet1 : public SimpleBullet{
    private:
    static constexpr float radius = 2.5f;
    static constexpr float speed = 2;
    static constexpr ANIMATED_SPRITES sprite = BULLET_1_MONOCHROME;
    Vector2 position{};
    Vector2 direction{};
    Color color = WHITE;

public:
    SimpleBullet1(GameObjectHandler &handler, const Vector2 pos, const Vector2 dir);
    SimpleBullet1(GameObjectHandler &handler, const Vector2 pos, const Vector2 dir, Color col);
    //static void Create(GameObjectHandler &handler, const Vector2 pos, const Vector2 dir);
    //static void Create(GameObjectHandler &handler, const Vector2 pos, const Vector2 dir, Color col);
private:
    void PreStep() override;
    void doPhysics(std::array<Vector2, 2> playerPosAndMovement) override;
};


#endif //RAYLIB_STG_SIMPLEBULLET1_H