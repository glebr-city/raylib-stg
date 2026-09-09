#include "MainLoopHandler.h"









int main() {
    MainLoopHandler::InitApplication();
    while (!WindowShouldClose()) {
        MainLoopHandler::DoMainLoop();
    }
}