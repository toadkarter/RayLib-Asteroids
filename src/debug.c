#include "debug.h"
#include "raygui.h"
#include "constants.h"
#include <raymath.h>

static bool showDebugMenu = false;
static bool showAsteroidCount = false;
static bool showAngleCone = false;
static bool debugUseCheckbox = false;
static Vector2 line0[2] = {0};
static Vector2 line1[2] = {0};

void ShowDebugMenu(void)
{
    if (IsKeyPressed(KEY_TAB))
    {
        showDebugMenu = !showDebugMenu;
    }

    if (showDebugMenu)
    {
        if (!debugUseCheckbox)
        {
            Rectangle r = {10, SCREEN_HEIGHT - 80, 180, 60};
            GuiToggle(r, "Show Asteroid Count", &showAsteroidCount);

            r.x += 180 + 10;
            GuiToggle(r, "Show Angle Cone", &showAngleCone);

            r.x += 180 + 10;
            GuiToggle(r, "Switch Menu Style", &debugUseCheckbox);
        }
        else
        {
            Rectangle r = {10, SCREEN_HEIGHT - 40, 20, 20};
            GuiCheckBox(r, "Show Asteroid Count", &showAsteroidCount);

            r.y -= 30;
            GuiCheckBox(r, "Show Angle Cone", &showAngleCone);

            r.y -= 30;
            GuiCheckBox(r, "Switch Menu Style", &debugUseCheckbox);
        }
    }
}

void ShowDebugVisualizations(int asteroidCount)
{
    if (showAngleCone)
    {
        DrawLineV(line0[0], line0[1], RED);
        DrawLineV(line1[0], line1[1], BLUE);
    }

    if (showAsteroidCount)
    {
        DrawRectangle(10, 10, 275, 52, Fade(BLACK, 0.6f));
        DrawText(TextFormat("ASTEROIDS: %d", asteroidCount), 20, 20, 32, WHITE);
    }
}

void SetLastCone(Vector2 position, Vector2 velocity)
{
    line0[0] = position;
    line1[0] = position;

    line0[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10), -ASTEROID_RANDOM_ANGLE));
    line1[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10), ASTEROID_RANDOM_ANGLE));
}
