//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SPRITEHANDLER_H
#define RAYLIB_STG_SPRITEHANDLER_H
#include <array>
#include <memory>
#include "SpriteHandlerEnums.h"
#include "raylib.h"






class SpriteHandler{
private:
    static std::array<std::unique_ptr<MyAnimatedSprite>, 14> animatedSprites;
    static std::array<std::unique_ptr<MyStaticSprite>, 5> staticSprites;
    public:
    static MyStaticSprite* getStaticSprite(int staticSpriteIndex);
    static Texture2D* getStaticSpriteTexture(int staticSpriteIndex);
    static void QueueMyStaticSprite(const SpriteParametres& opts);
    static void QueueMyAnimatedSprite(const SpriteParametres& opts);
    static void QueueText(TextParametres opts);
    static void AdvanceAnimation();
    static void DrawSprites();
    static void InitSprites();
};


#endif //RAYLIB_STG_SPRITEHANDLER_H