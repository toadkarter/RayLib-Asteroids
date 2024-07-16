#include <raylib.h>
#include "raygui.h"
#include "constants.h"
#include "debug.h"
#include "game_asteroids.h"
#include "player.h"

static Player player;

void UpdateDrawFrame(void);

int main()
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Asteroids");

    player = (Player){.position = SCREEN_CENTER, .rotation = 270, .velocity = (Vector2){0}};

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
    PlayerUpdate(&player);

    BeginDrawing();

    ClearBackground(NEARBLACK);

//    DrawAsteroids();
    PlayerDraw(&player);
    ShowDebugVisualizations(activeAsteroids);
    ShowDebugMenu();

    EndDrawing();
}
