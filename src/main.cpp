#include <array>
#include <iostream>
#include <memory>
#include <raylib.h>

#include "GameHandler.h"
#include "GlobalVariables.h"
#include "HUDHandler.h"
#include "InputHandler.h"
#include "PhaseHelper.h"
#include "SpriteHandler.h"
#include "SoundHandler.h"

std::array<int, 3> AdjustLetterbox() {
    int zoomFactor = 1;
    Vector2 letterboxSize = {0, 0};
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float aspectRatio = static_cast<float>(screenHeight) / static_cast<float>(screenWidth);
    if (aspectRatio < 1.5f) {
        zoomFactor = std::fmaxf(2.0f, floor(screenHeight / gameHeight / 2) * 2);
    } else {
        zoomFactor = std::fmaxf(2.0f, floor(screenWidth / gameWidth / 2) * 2);
    }
    letterboxSize.x = ((screenWidth) - (gameWidth * zoomFactor)) / 2;
    letterboxSize.y = ((screenHeight) - (gameHeight * zoomFactor)) / 2;
    const int x = floor(letterboxSize.x);
    const int y = floor(letterboxSize.y);
    return {zoomFactor, x, y};
}



int main() {
    ChangeDirectory(GetApplicationDirectory());
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 1280, "raylib");
    SetWindowMinSize(gameWidth * 2, gameHeight * 2);
    InitAudioDevice();
    SpriteHandler::InitSprites(); //Need to initialise this after the window.
    SoundHandler::InitSounds();
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
    static constexpr std::array<KeyboardKey, 3> restartKeys = {KEY_R, KEY_ESCAPE, KEY_BACKSPACE};
    camera.offset = {letterboxSize.x, letterboxSize.y};
    camera.zoom = zoomFactor;
    GameHandler::restartGame();
    bool DEBUG_highFramerate = false;


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
            GameHandler::restartGame();
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            DEBUG_highFramerate = !DEBUG_highFramerate;
            DEBUG_highFramerate ? SetTargetFPS(360) : SetTargetFPS(120);
        }
        if (IsKeyPressed(KEY_ESCAPE))
            CloseWindow();
        GlobalVariables::currentStep()++;
        SpriteHandler::AdvanceAnimation();
        BeginDrawing();


        ClearBackground(BLACK);
        DrawRectangleLines(letterboxSize.x - 1, letterboxSize.y - 1, gameWidth * zoomFactor + 2, gameHeight * zoomFactor + 2, DARKGRAY);
        BeginScissorMode(letterboxSize.x, letterboxSize.y, gameWidth * zoomFactor, gameHeight * zoomFactor);
        BeginMode2D(camera);
        GameHandler::doPreStep();
        SpriteHandler::DrawSprites();
        EndMode2D();
        EndScissorMode();
        std::string tempStr = GlobalVariables::getCurrentPhase()->getPhaseName();
        tempStr.append("\nBullet Count: ");
        tempStr.append(std::to_string(GlobalVariables::getCurrentPhase()->getNumActive()));
        tempStr.append(std::string(" \nSteps Elapsed: "));
        tempStr.append(std::to_string(GlobalVariables::getCurrentPhase()->getStepsElapsed()));
        tempStr.append(" \nStage Coordinates: ");
        tempStr.append("(" + std::to_string(GlobalVariables::getCurrentBackgroundPosition()->x) + ", " + std::to_string(GlobalVariables::getCurrentBackgroundPosition()->y) + ")");
        tempStr.append("\nCurrent Graze: ");
        tempStr.append(std::to_string(GlobalVariables::getGrazeMetre()));
        DrawText(tempStr.c_str(), 0, 100, 30, RAYWHITE);
        /*DrawText(std::to_string(zoomFactor).c_str(), 100, 100, 50, RAYWHITE);*/
        DrawFPS(100, 195);
        EndDrawing();
        GameHandler::doPhysics();
    }
}
