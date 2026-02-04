#include <array>
#include <iostream>
#include <raylib.h>
#include <raymath.h>

std::array<int, 3> AdjustLetterbox() {
    int zoomFactor = 1;
    Vector2 letterboxSize = {0, 0};
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();
    float aspectRatio = static_cast<float>(screenHeight) / static_cast<float>(screenWidth);
    //std::cout << "thingy: "+ std::to_string(aspectRatio) << std::endl;
    if (aspectRatio < 1.5f) {
        zoomFactor = screenHeight / 180;
    } else {
        zoomFactor = screenWidth / 120;
    }
    letterboxSize.x = ((screenWidth) - (120 * zoomFactor)) / 2;
    letterboxSize.y = ((screenHeight) - (180 * zoomFactor)) / 2;
    std::cout << "letterbox size: " << std::to_string(letterboxSize.x) << "    " << std::to_string(letterboxSize.y) << std::endl;
    const int x = floor(letterboxSize.x);
    const int y = floor(letterboxSize.y);
    return {zoomFactor, x, y};
}

int main() {
    ChangeDirectory(GetApplicationDirectory());
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(120, 180, "raylib");
    int zoomFactor = 1;//std::min(GetScreenHeight() / 180, GetScreenWidth() / 120);
    Vector2 letterboxSize = {0, 0};
    Texture2D playerSpriteSheet = LoadTexture("resources/playerSpriteSheet.png");
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
        playerPosition.y += 0.25f;
        if (currentFrame % 20 == 0) {
            playerRect.x = static_cast<int>(playerRect.x + (playerRect.width)) % playerSpriteSheet.width; // NOLINT(*-narrowing-conversions)
        }
        BeginDrawing();
        ClearBackground(BLACK);
        //DrawRectangleRec(playerRect, DARKGRAY);
        BeginScissorMode(letterboxSize.x, letterboxSize.y, 120 * zoomFactor, 180.0f * zoomFactor);
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

