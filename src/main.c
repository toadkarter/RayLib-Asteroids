#include <raylib.h>
#include <raymath.h>
#include "asteroid.h"

const int screenWidth = 600;
const int screenHeight = 600;
const Vector2 screenCenter = {(float)screenWidth / 2, (float)screenHeight / 2};

#define NEARBLACK CLITERAL(Color){15, 15, 15, 255}

#define ASTEROIDS_MAX 64
#define ASTEROID_RANDOM_ANGLE (30 * DEG2RAD)
static AsteroidSize sizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM, ASTEROID_LARGE};
static Asteroid asteroids[ASTEROIDS_MAX] = {0};

void UpdateDrawFrame(void);
void AddAsteroid(Vector2 position, AsteroidSize size);

// DEBUG
bool showAngleCone = false;
Vector2 line0[2];
Vector2 line1[2];
//

int main()
{
    InitWindow(screenWidth, screenHeight, "Asteroids");

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
    float frametime = GetFrameTime();

    for (int i = 0; i < ASTEROIDS_MAX; i++)
    {
        Asteroid* currentAsteroid = &asteroids[i];
        AsteroidUpdate(currentAsteroid, frametime);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        int size_index = GetRandomValue(0, 2);
        AddAsteroid(GetMousePosition(), sizes[size_index]);
    }

    BeginDrawing();

    ClearBackground(NEARBLACK);

    for (int i = 0; i < ASTEROIDS_MAX; i++)
    {
        Asteroid* currentAsteroid = &asteroids[i];
        AsteroidDraw(currentAsteroid);
    }

    if (showAngleCone)
    {
        DrawLineV(line0[0], line0[1], RED);
        DrawLineV(line1[0], line1[1], BLUE);
    }

    EndDrawing();
}

void AddAsteroid(Vector2 position, AsteroidSize size)
{
    bool created = false;
    Vector2 velocity = Vector2Subtract(screenCenter, position);
    velocity = Vector2Scale(Vector2Normalize(velocity), (float)GetRandomValue(ASTEROID_SPEED_MIN, ASTEROID_SPEED_MAX));

    if (showAngleCone)
    {
        line0[0] = position;
        line1[0] = position;

        line0[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10), -ASTEROID_RANDOM_ANGLE));
        line1[1] = Vector2Add(position, Vector2Rotate(Vector2Scale(velocity, 10), ASTEROID_RANDOM_ANGLE));
    }

    velocity = Vector2Rotate(velocity, (float)GetRandomValue((int)-ASTEROID_RANDOM_ANGLE, ASTEROID_RANDOM_ANGLE));

    for (int i = 0; i < ASTEROIDS_MAX; i++)
    {
        if (!asteroids[i].active)
        {
            Asteroid asteroid = CreateAsteroid(position, velocity, size);
            asteroids[i] = asteroid;
            created = true;
            break;
        }
    }

    if (!created)
    {
        TraceLog(LOG_ERROR, "Failed to create asteroid because there were no inactive spots in the array");
    }
}
