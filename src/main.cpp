#include <array>
#include <iostream>
#include <memory>
#include <../include/raylib/raylib.h>

#include "ConfigHandler.h"
#if DEBUG_BUILD
#include <sstream>
#include <iomanip>
#endif

#include "BackgroundHandler.h"
#include "GameHandler.h"
#include "GlobalVariables.h"
#include "HUDHandler.h"
#include "InputHandler.h"
#include "MenuHandler.h"
#include "PauseHandler.h"
#include "PhaseHelper.h"
#include "SpriteHandler.h"
#include "SoundHandler.h"

int* zoomFactor = nullptr;
RenderTexture2D* target = GlobalVariables::GetRenderTexture();



void doStep()
{
    InputHandler::UpdateInputs();
    SpriteHandler::ClearQueues();
    GameHandler::doPreStep();
    GameHandler::doPhysics();
    GameHandler::doPostStep();
    GlobalVariables::currentStep()++;
    SpriteHandler::AdvanceAnimation();
}

void doDrawing()
{
    BeginTextureMode(*target);
    BeginScissorMode(0, 0, gameWidth, gameHeight); //To fix bleed in the bilinear filter...
    ClearBackground(BLACK);
    SpriteHandler::DrawSprites();
    GameHandler::HandleHUD();
    if (PauseHandler::GetPaused())
    {
        MenuHandler::HandleMenus();
    }
    EndScissorMode();
    EndTextureMode();
    BeginDrawing();
    ClearBackground(BLACK);
    Vector2 realScreenSize = {static_cast<float>(gameWidth * *zoomFactor), static_cast<float>(gameHeight * *zoomFactor)};
    Vector2 realScreenCentre = {static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2)};
    const int screenRotation = GlobalVariables::GetScreenRotation();
    if (screenRotation == 0 || screenRotation == 2)
        DrawRectangleLines(realScreenCentre.x-realScreenSize.x / 2 - 1, realScreenCentre.y-realScreenSize.y / 2 - 1, realScreenSize.x + 2, realScreenSize.y + 2, DARKGRAY);
    else
        DrawRectangleLines(realScreenCentre.x-realScreenSize.y / 2 - 1, realScreenCentre.y-realScreenSize.x / 2 - 1, realScreenSize.y + 2, realScreenSize.x + 2, DARKGRAY);
    DrawTexturePro(target->texture,
        {0, 0, static_cast<float>(target->texture.width), static_cast<float>(-target->texture.height)},
        {static_cast<float>(GetScreenWidth() / 2), static_cast<float>(GetScreenHeight() / 2), realScreenSize.x, realScreenSize.y},
        {static_cast<float>(target->texture.width * *zoomFactor / 2), static_cast<float>(target->texture.height * *zoomFactor / 2)},
        screenRotation * 90, WHITE);

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
#endif
    EndDrawing();
}

int main() {
    ChangeDirectory(GetApplicationDirectory());
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1280, 1280, "raylib");
    SetWindowMinSize(gameWidth * 2, gameHeight * 2);
    InitAudioDevice();
    SpriteHandler::InitSprites(); //Need to initialise this after the window.
    SoundHandler::InitSounds();
    GlobalVariables::InitRenderTexture(gameWidth, gameHeight);
    SetTargetFPS(120);
    std::array<int, 3> resizeValues = GlobalVariables::AdjustLetterbox();
    zoomFactor = GlobalVariables::GetZoomFactor();
    ConfigHandler::ReadFile();
    MenuHandler::InitMenus();
    //letterboxSize.x = static_cast<float>(resizeValues[1]);
    //letterboxSize.y = static_cast<float>(resizeValues[2]);
    GameHandler::RestartGame();
    doStep();
    bool DEBUG_highFramerate = false;


    while (!WindowShouldClose()) {
        if (IsWindowResized()) {
            resizeValues = GlobalVariables::AdjustLetterbox();
            //letterboxSize.x = static_cast<float>(resizeValues[1]);
            //letterboxSize.y = static_cast<float>(resizeValues[2]);
        }
        if (InputHandler::CheckInputsPressed(INPUT_RESTART)) {
            GameHandler::RestartGame();
        }
        if (IsKeyPressed(KEY_ENTER))
        {
            DEBUG_highFramerate = !DEBUG_highFramerate;
            DEBUG_highFramerate ? SetTargetFPS(10) : SetTargetFPS(120);
        }
        if (IsKeyPressed(KEY_ESCAPE))
            CloseWindow();
        if (IsKeyPressed(KEY_PAGE_DOWN))
            GameHandler::NextPhase(true);
        const bool gamePaused = PauseHandler::GetPaused();
        doDrawing();
        if (!gamePaused)
        {
            if (IsKeyPressed(KEY_TAB))
            {
                PauseHandler::SetPause(true);
            } else
            {
                doStep();
            }
        }
    }
}

