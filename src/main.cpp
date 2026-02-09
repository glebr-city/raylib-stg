#include <array>
#include <iostream>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include <Player.h>
#include <StepThinker.h>

#include "GlobalVariables.h"
#include "InputHandler.h"
#include "PhaseHelper.h"
#include "SimpleBullet1.h"
#include "SimpleBullet2.h"
#include "SpriteHandler.h"
#include "TestPhase1.h"


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
    std::unique_ptr<PhaseHelper> currentPhase = std::make_unique<TestPhase1>();
    static constexpr std::array<KeyboardKey, 3> restartKeys = {KEY_R, KEY_ESCAPE, KEY_BACKSPACE};
    Player player {Vector2 {60, 140}};


    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            resizeValues = AdjustLetterbox();
            zoomFactor = resizeValues[0];
            letterboxSize.x = static_cast<float>(resizeValues[1]);
            letterboxSize.y = static_cast<float>(resizeValues[2]);
            camera.offset = {letterboxSize.x, letterboxSize.y};
            camera.zoom = zoomFactor;
        }
        if (InputHandler::CheckInputsPressed(restartKeys)) {
            currentStep() = 0;
            player = Player {Vector2 {60, 140}};
            currentPhase = std::make_unique<TestPhase1>();
        }
        currentStep()++;
        SpriteHandler::AdvanceAnimation();
        BeginDrawing();


        ClearBackground(BLACK);
        DrawRectangleLines(letterboxSize.x - 1, letterboxSize.y - 1, gameWidth() * zoomFactor + 2, gameHeight() * zoomFactor + 2, DARKGRAY);
        BeginScissorMode(letterboxSize.x, letterboxSize.y, gameWidth() * zoomFactor, gameHeight() * zoomFactor);
        BeginMode2D(camera);
        player.doPreStep();
        currentPhase->doPreStep();
        EndMode2D();
        EndScissorMode();
        std::string tempStr = "Bullet Count: ";
        tempStr.append(std::to_string(currentPhase->getNumActive()));
        DrawText(tempStr.c_str(), 0, 100, 30, RAYWHITE);
        /*DrawText(std::to_string(zoomFactor).c_str(), 100, 100, 50, RAYWHITE);*/
        DrawFPS(100, 150);
        EndDrawing();
        currentPhase->doPhysics(&player);
        player.doPhysics();
    }
}
