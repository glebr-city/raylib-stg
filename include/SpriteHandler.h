//
// Created by g on 05/02/2026.
//

#ifndef RAYLIB_STG_SPRITEHANDLER_H
#define RAYLIB_STG_SPRITEHANDLER_H
#include <array>
#include <memory>
#include "SpriteHandlerEnums.h"
#include "raylib/raylib.h"






class SpriteHandler{
private:
    public:
    static MyStaticSprite* getStaticSprite(int staticSpriteIndex);
    static Texture2D* getStaticSpriteTexture(int staticSpriteIndex);
    static void QueueMyStaticSprite(const SpriteParametres& opts);
    static void QueueMyAnimatedSprite(const SpriteParametres& opts);
    static void QueueText(TextParametres opts);
    static void AdvanceAnimation();
    static void DrawSprites();
    static void InitSprites();
    static void DrawMyStaticSprite(const SpriteParametres& opts);
    static void ClearQueues();
};


#endif //RAYLIB_STG_SPRITEHANDLER_H