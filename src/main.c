#include "raylib.h"
#include "asteroid.h"

int screenWidth = 600;
int screenHeight = 600;

#define NEARBLACK CLITERAL(Color){15, 15, 15, 255}

#define MAX_ASTEROIDS 64
static AsteroidSize sizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM, ASTEROID_LARGE};
static Asteroid asteroids[MAX_ASTEROIDS] = {0};

void UpdateDrawFrame(void);
void AddAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);

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

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        Asteroid* current_asteroid = &asteroids[i];
        AsteroidUpdate(current_asteroid, frametime);
    }

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        int size_index = GetRandomValue(0, 2);
        AddAsteroid(GetMousePosition(), (Vector2){200, 0}, sizes[size_index]);
    }

    BeginDrawing();

    ClearBackground(NEARBLACK);

    for (int i = 0; i < MAX_ASTEROIDS; i++)
    {
        Asteroid* current_asteroid = &asteroids[i];
        AsteroidDraw(current_asteroid);
    }

    EndDrawing();
}

void AddAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size)
{
    bool created = false;
    for (int i = 0; i < MAX_ASTEROIDS; i++)
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
