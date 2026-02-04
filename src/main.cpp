#include <array>
#include <iostream>
#include <memory>
#include <raylib.h>
#include <raymath.h>
#include <vector>

#include "Player.h"
#include "../include/StepThinker.h"

constexpr int gameScreenWidth = 120;
constexpr int gameScreenHeight = 180;

std::array<int, 3> AdjustLetterbox() {
    int zoomFactor = 1;
    Vector2 letterboxSize = {0, 0};
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float aspectRatio = static_cast<float>(screenHeight) / static_cast<float>(screenWidth);
    if (aspectRatio < 1.5f) {
        zoomFactor = screenHeight / gameScreenHeight;
    } else {
        zoomFactor = screenWidth / gameScreenWidth;
    }
    letterboxSize.x = ((screenWidth) - (gameScreenWidth * zoomFactor)) / 2;
    letterboxSize.y = ((screenHeight) - (gameScreenHeight * zoomFactor)) / 2;
    const int x = floor(letterboxSize.x);
    const int y = floor(letterboxSize.y);
    return {zoomFactor, x, y};
}

int main() {
    ChangeDirectory(GetApplicationDirectory());
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(gameScreenWidth * 3, gameScreenHeight * 3, "raylib");
    SetWindowMinSize(gameScreenWidth, gameScreenHeight);
    int zoomFactor = 3;
    Vector2 letterboxSize = {0, 0};
    const Texture2D playerSpriteSheet = LoadTexture("resources/playerSpriteSheet.png");
    Rectangle playerRect = {0.0f, 0.0f, 13.0f, 13.0f};
    Camera2D camera = { 0 };
    camera.zoom = zoomFactor; // NOLINT(*-narrowing-conversions)
    camera.offset = {letterboxSize.x, letterboxSize.y};
    int currentFrame = 0;
    Vector2 playerPosition = {0.0f, 0.0f};

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
        currentFrame++;
        std::vector<std::unique_ptr<StepThinker>> tempArray;
        tempArray.push_back(std::make_unique<Player>());
        tempArray.push_back(std::make_unique<StepThinker>());
        for (auto& step_thinker : tempArray) {
            step_thinker->PreStep();
        }
        //Player::PreStep();
        //StepThinker::PreStep();
        playerPosition.y += 0.25f;
        if (currentFrame % 20 == 0) {
            playerRect.x = static_cast<int>(playerRect.x + (playerRect.width)) % playerSpriteSheet.width; // NOLINT(*-narrowing-conversions)
        }
        BeginDrawing();
        ClearBackground(BLACK);
        //DrawRectangleRec(playerRect, DARKGRAY);
        BeginScissorMode(letterboxSize.x, letterboxSize.y, gameScreenWidth * zoomFactor, gameScreenHeight * zoomFactor);
        BeginMode2D(camera);
        DrawRectangle(0, 0, 10000, 10000, DARKGRAY);
        DrawTextureRec(playerSpriteSheet, playerRect, playerPosition, WHITE);
        //DrawTexture(playerSpriteSheet, 1, 1, WHITE);
        EndMode2D();
        EndScissorMode();
        //DrawRectangleRec(letterboxLeft, BLACK);
        //DrawRectangleRec(letterboxRight, BLACK);
        DrawText("raylib text 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18", 100, 100, 50, RAYWHITE);
        EndDrawing();
    }

}

