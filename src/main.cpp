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
#include "InputHandler.h"
#include "SimpleBullet1.h"
#include "SimpleBullet2.h"
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


void startGame(GameObjectHandler* gameObjectHandler) {
    gameObjectHandler->clearStepThinkers();
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
    SetTargetFPS(120);
    std::array<int, 3> resizeValues = AdjustLetterbox();
    zoomFactor = resizeValues[0];
    letterboxSize.x = static_cast<float>(resizeValues[1]);
    letterboxSize.y = static_cast<float>(resizeValues[2]);
    camera.offset = {letterboxSize.x, letterboxSize.y};
    camera.zoom = zoomFactor;
    static constexpr std::array<KeyboardKey, 3> restartKeys = {KEY_R, KEY_ESCAPE, KEY_BACKSPACE};
    std::unique_ptr<GameObjectHandler> gameObjectHandler = std::make_unique<GameObjectHandler>();
    Player player {Vector2 {60, 140}};
    startGame(gameObjectHandler.get());


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
        if (currentStep() % 10 == 0) {
            float simpleBullet2TempX = currentStep() % 120;
            SimpleBullet2 {gameObjectHandler.get(), Vector2{60, -3}, Vector2 {0, 1}, GREEN};
        }

        //Check if we should restart the game
        if (InputHandler::CheckInputsPressed(restartKeys)) {
            player.~Player();
            player = Player{Vector2 {60, 140}};
            startGame(gameObjectHandler.get());
        }

        if (currentStep() % 1000 == 0) {
            for (int i = 0; i <= 20000; i++) {
                SimpleBullet1 {gameObjectHandler.get(), Vector2{static_cast<float>(i % 120), -3}, Vector2 {0, 1}, GREEN};
            }
        } else if (currentStep() % 600 == 900) {
            gameObjectHandler->removeStepThinkers(30000);
        }

        if (currentStep() % 600 == 0) {
            for (int i = 0; i <= 20000; i++) {
                SimpleBullet2 {gameObjectHandler.get(), Vector2{static_cast<float>(i % 120), -3}, Vector2 {0, 1}, ORANGE};
            }
        } else if (currentStep() % 600 == 500) {
                gameObjectHandler->removeStepThinkers(30000);
        }

        ClearBackground(BLACK);
        DrawRectangleLines(letterboxSize.x - 1, letterboxSize.y - 1, gameWidth() * zoomFactor + 2, gameHeight() * zoomFactor + 2, DARKGRAY);
        BeginScissorMode(letterboxSize.x, letterboxSize.y, gameWidth() * zoomFactor, gameHeight() * zoomFactor);
        BeginMode2D(camera);
        gameObjectHandler->doPreStep(player);
        EndMode2D();
        EndScissorMode();
        std::string tempStr = "Bullet Count: ";
        tempStr.append(std::to_string(gameObjectHandler->getObjectCount()));
        DrawText(tempStr.c_str(), 0, 100, 30, RAYWHITE);
        //DrawText(std::to_string(zoomFactor).c_str(), 100, 100, 50, RAYWHITE);
        DrawFPS(100, 150);
        EndDrawing();
        gameObjectHandler->doPhysics(player);
    }
}
