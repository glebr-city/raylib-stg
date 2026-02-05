#include <array>
#include <iostream>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include <Player.h>
#include <StepThinker.h>

#include "GlobalVariables.h"

std::vector<std::unique_ptr<StepThinker>> step_thinkers;

std::array<int, 3> AdjustLetterbox() {
    int zoomFactor = 1;
    Vector2 letterboxSize = {0, 0};
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float aspectRatio = static_cast<float>(screenHeight) / static_cast<float>(screenWidth);
    if (aspectRatio < 1.5f) {
        zoomFactor = screenHeight / gameHeight();
    } else {
        zoomFactor = screenWidth / gameWidth();
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
    InitWindow(gameWidth() * 3, gameHeight() * 3, "raylib");
    SetWindowMinSize(gameWidth(), gameHeight());
    int zoomFactor = 3;
    Vector2 letterboxSize = {0, 0};
    Camera2D camera = { 0 };
    camera.zoom = zoomFactor; // NOLINT(*-narrowing-conversions)
    camera.offset = {letterboxSize.x, letterboxSize.y};

    step_thinkers.push_back(std::make_unique<Player>(Vector2()));
    step_thinkers.push_back(std::make_unique<StepThinker>());

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            std::array<int, 3> resizeValues = AdjustLetterbox();
            zoomFactor = resizeValues[0];
            letterboxSize.x = static_cast<float>(resizeValues[1]);
            letterboxSize.y = static_cast<float>(resizeValues[2]);
            camera.offset = {letterboxSize.x, letterboxSize.y};
            camera.zoom = zoomFactor;
        }
        currentStep()++;
        //Player::PreStep();
        //StepThinker::PreStep();
        BeginDrawing();
        ClearBackground(BLACK);
        BeginScissorMode(letterboxSize.x, letterboxSize.y, gameWidth() * zoomFactor, gameHeight() * zoomFactor);
        BeginMode2D(camera);
        DrawRectangle(0, 0, 10000, 10000, DARKGRAY);
        for (auto& step_thinker : step_thinkers) {
            step_thinker->PreStep();
        }
        EndMode2D();
        EndScissorMode();
        //DrawRectangleRec(letterboxLeft, BLACK);
        //DrawRectangleRec(letterboxRight, BLACK);
        DrawText("raylib text 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18", 100, 100, 50, RAYWHITE);
        EndDrawing();
    }

}

