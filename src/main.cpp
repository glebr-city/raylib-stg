#include <array>
#include <iostream>
#include <memory>
#include <../include/raylib/raylib.h>
#if DEBUG_BUILD
#include <sstream>
#include <iomanip>
#endif

#include "BackgroundHandler.h"
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
    GameHandler::RestartGame();
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
            GameHandler::RestartGame();
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            DEBUG_highFramerate = !DEBUG_highFramerate;
            DEBUG_highFramerate ? SetTargetFPS(360) : SetTargetFPS(120);
        }
        if (IsKeyPressed(KEY_ESCAPE))
            CloseWindow();
        if (IsKeyPressed(KEY_TAB))
            GlobalVariables::TogglePaused();
        const bool gamePaused = GlobalVariables::GetPaused();
        InputHandler::UpdateInputVector();
        if (!gamePaused)
        {
            SpriteHandler::ClearQueues();
            GameHandler::doPreStep();
            GameHandler::doPhysics();
            GlobalVariables::currentStep()++;
            SpriteHandler::AdvanceAnimation();
        }
#if DEBUG_BUILD
        if (!gamePaused)
        {
            GlobalVariables::currentStep()++;
            SpriteHandler::AdvanceAnimation();
        }
#endif
        BeginDrawing();
        ClearBackground(BLACK);
        DrawRectangleLines(letterboxSize.x - 1, letterboxSize.y - 1, gameWidth * zoomFactor + 2, gameHeight * zoomFactor + 2, DARKGRAY);
        BeginScissorMode(letterboxSize.x, letterboxSize.y, gameWidth * zoomFactor, gameHeight * zoomFactor);
        BeginMode2D(camera);
        SpriteHandler::DrawSprites();
        GameHandler::HandleHUD();
        EndMode2D();
        EndScissorMode();
#if DEBUG_BUILD
        const auto backgroundPos = BackgroundHandler::GetBackgroundPosition();
        const auto playerPos = PlayerHandler::GetPlayer()->GetFinalPos();
        const auto absolutePos = BackgroundHandler::GetAbsolutePos(playerPos);

        std::stringstream ss;

        ss << GlobalVariables::getCurrentPhase()->getPhaseName()
        << "\nFPS: " << GetFPS()
        << "\nBullet Count: " << GlobalVariables::getCurrentPhase()->getNumActive()
        << " \nSteps Elapsed: " << GlobalVariables::getCurrentPhase()->getStepsElapsed()
        << "\nCurrent Graze: \n"
        << GlobalVariables::getGrazeMetre()
        << " \nStage Coordinates: (" <<
            std::fixed << std::setprecision(2)
        << backgroundPos.x << "," << backgroundPos.y << ")"
            <<"\nPlayer Pos:\n"
           << "(" << playerPos.x << ", " << playerPos.y << ")"
           << "\n("
           << absolutePos.x << ", " << absolutePos.y
           << ")";
        DrawText(ss.str().c_str(), 0, 100, 30, RAYWHITE);
        //DrawFPS(100, 195);
#endif
        EndDrawing();
    }
}
