#include <array>
#include <iostream>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include <Player.h>
#include <StepThinker.h>

#include "GameObjectHandler.h"
#include "GlobalVariables.h"
#include "PhysicsObject.h"
#include "SimpleBullet1.h"
#include "SpriteHandler.h"



std::array<int, 3> AdjustLetterbox() {
    int zoomFactor = 1;
    Vector2 letterboxSize = {0, 0};
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float aspectRatio = static_cast<float>(screenHeight) / static_cast<float>(screenWidth);
    if (aspectRatio < 1.5f) {
        zoomFactor = std::fmaxf(2.0f, floor(screenHeight / gameHeight() / 2) * 2);
    } else {
        zoomFactor = std::fmaxf(2.0f, floor(screenWidth / gameWidth() / 2) * 2);
    }
    letterboxSize.x = ((screenWidth) - (gameWidth() * zoomFactor)) / 2;
    letterboxSize.y = ((screenHeight) - (gameHeight() * zoomFactor)) / 2;
    const int x = floor(letterboxSize.x);
    const int y = floor(letterboxSize.y);
    return {zoomFactor, x, y};
}
//Need to push to vertices for both StepThinker and PhysicsObject
void CreateGameObject(GameObject *game_object) {
    if (auto a = dynamic_cast<PhysicsObject*>(game_object)) {

    }

}

int main() {
    ChangeDirectory(GetApplicationDirectory());
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 1280, "raylib");
    SetWindowMinSize(gameWidth() * 2, gameHeight() * 2);
    SpriteHandler::InitAnimatedSprites(); //Need to initialise this after the window.
    int zoomFactor = 2;
    Vector2 letterboxSize = {0, 0};
    Camera2D camera = { 0 };
    camera.zoom = zoomFactor; // NOLINT(*-narrowing-conversions)
    camera.offset = {letterboxSize.x, letterboxSize.y};

    Player player {Vector2 {60, 140}};
    GameObjectHandler gameObjectHandler = GameObjectHandler();


    SetTargetFPS(1000);
    std::array<int, 3> resizeValues = AdjustLetterbox();
    zoomFactor = resizeValues[0];
    letterboxSize.x = static_cast<float>(resizeValues[1]);
    letterboxSize.y = static_cast<float>(resizeValues[2]);
    camera.offset = {letterboxSize.x, letterboxSize.y};
    camera.zoom = zoomFactor;
    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            resizeValues = AdjustLetterbox();
            zoomFactor = resizeValues[0];
            letterboxSize.x = static_cast<float>(resizeValues[1]);
            letterboxSize.y = static_cast<float>(resizeValues[2]);
            camera.offset = {letterboxSize.x, letterboxSize.y};
            camera.zoom = zoomFactor;
        }
        currentStep()++;
        SpriteHandler::AdvanceAnimation();
        BeginDrawing();

        if (currentStep() % 5 == 0) {
            int tempCurrentStep = currentStep();
            float tempX = (65 - static_cast<float>(tempCurrentStep % 50) / 5);
            SimpleBullet1 {gameObjectHandler, Vector2 {tempX, -1}, Vector2 {0, 1}, RED};
            //CreateObject(tempBullet, tempBullet);
        }

        if (currentStep() % 2 == 0) {
            int tempCurrentStep = currentStep();
            float tempX = (tempCurrentStep % 240 + static_cast<float>(tempCurrentStep % 30 / 3)) / 2;
            Color clr {160, 160, 160, 255};
            //step_thinkers->push_back(std::make_unique<SimpleBullet1>(Vector2 {tempX, -1}, Vector2 {0, 1}, clr));
            SimpleBullet1 {gameObjectHandler, Vector2 {tempX, -1}, Vector2 {0, 1}, clr};
            tempX = 120 - tempX;
            SimpleBullet1 {gameObjectHandler, Vector2 {tempX, -1}, Vector2 {0, 1}, clr};
        } else if (currentStep() % 5 == 3) {
            int tempCurrentStep = currentStep();
            float tempX = (tempCurrentStep % 240 + static_cast<float>(tempCurrentStep % 30 / 3)) / 2;
            Color clr {255, 100, 100, 255};
            tempX = 90 - (static_cast<int>(floor(tempX)) % 20);
            SimpleBullet1 {gameObjectHandler,Vector2 {tempX, -1}, Vector2 {0, 1}, clr};
            tempX = 30 + (static_cast<int>(floor(tempX)) % 20);
            SimpleBullet1 {gameObjectHandler,Vector2 {tempX, -1}, Vector2 {0, 1}, clr};
        }  else if (currentStep() % 20 == 10) {
            int tempCurrentStep = currentStep();
            float tempX = (tempCurrentStep % 240 + static_cast<float>(tempCurrentStep % 30 / 3)) / 2;
            Color clr {255, 75, 75, 255};
            tempX = 120 - (static_cast<int>(floor(tempX)) % 20);
            SimpleBullet1 {gameObjectHandler,Vector2 {tempX, -1}, Vector2 {0, 1}, clr};
            tempX = (static_cast<int>(floor(tempX)) % 20);
            SimpleBullet1 {gameObjectHandler,Vector2 {tempX, -1}, Vector2 {0, 1}, clr};
        }

        ClearBackground(BLACK);
        DrawRectangleLines(letterboxSize.x - 1, letterboxSize.y - 1, gameWidth() * zoomFactor + 2, gameHeight() * zoomFactor + 2, DARKGRAY);
        BeginScissorMode(letterboxSize.x, letterboxSize.y, gameWidth() * zoomFactor, gameHeight() * zoomFactor);
        BeginMode2D(camera);
        player.PreStep();
        gameObjectHandler.doPreStep();
        EndMode2D();
        EndScissorMode();
        std::string tempStr = "Bullet Count: ";
        tempStr.append(std::to_string(gameObjectHandler.getObjectCount()));
        DrawText(tempStr.c_str(), 0, 100, 30, RAYWHITE);
        //DrawText(std::to_string(zoomFactor).c_str(), 100, 100, 50, RAYWHITE);
        DrawFPS(100, 150);
        EndDrawing();
        gameObjectHandler.doPhysics(player.getPosition());
    }
}
