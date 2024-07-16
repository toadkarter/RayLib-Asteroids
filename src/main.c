#include <raylib.h>
#include "raygui.h"
#include "constants.h"
#include "debug.h"
#include "game_asteroids.h"

void UpdateDrawFrame(void);
Vector2 GetNextAsteroidPosition(void);

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        UpdateDrawFrame();
    }

    CloseWindow();
    return 0;
}

void UpdateDrawFrame()
{
    int activeAsteroids = UpdateAsteroids();

    BeginDrawing();

    ClearBackground(NEARBLACK);

    DrawAsteroids();
    ShowDebugVisualizations(activeAsteroids);
    ShowDebugMenu();

    EndDrawing();
}
