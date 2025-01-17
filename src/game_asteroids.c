#include "game_asteroids.h"
#include "constants.h"
#include "debug.h"
#include <raymath.h>

static AsteroidSize sizes[] = {ASTEROID_SMALL, ASTEROID_MEDIUM, ASTEROID_LARGE};
static Asteroid asteroids[ASTEROIDS_MAX] = {0};
static float lastAsteroidCreationTime = -1.0f;

void AddAsteroid(Vector2 position, AsteroidSize size)
{
    bool created = false;
    Vector2 velocity = Vector2Subtract(SCREEN_CENTER, position);
    velocity = Vector2Scale(Vector2Normalize(velocity), (float)GetRandomValue(ASTEROID_SPEED_MIN, ASTEROID_SPEED_MAX));
    velocity = Vector2Rotate(velocity, (float)GetRandomValue((int)-ASTEROID_RANDOM_ANGLE, ASTEROID_RANDOM_ANGLE));

    SetLastCone(position, velocity);

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

Vector2 GetNextAsteroidPosition(void)
{
    float padding = 128;
    Vector2 result = {-padding, padding};

    if (GetRandomValue(0, 1))
    {
        if (GetRandomValue(0, 1))
        {
            result.y = (float)SCREEN_HEIGHT + padding;
        }

        result.x = (float)GetRandomValue((int)-padding, SCREEN_WIDTH + (int)padding);
    }
    else
    {
        if (GetRandomValue(0, 1))
        {
            result.x = (float)SCREEN_WIDTH + padding;
        }

        result.y = (float)GetRandomValue((int)-padding, SCREEN_HEIGHT + (int)padding);
    }

    return result;
}

int UpdateAsteroids(void)
{
    int activeAsteroids = 0;

    float frametime = GetFrameTime();
    float time = (float)GetTime();

    for (int i = 0; i < ASTEROIDS_MAX; i++)
    {
        Asteroid* currentAsteroid = &asteroids[i];
        bool bAsteroidUpdated = AsteroidUpdate(currentAsteroid, frametime);
        if (bAsteroidUpdated)
        {
            activeAsteroids++;
        }
    }

    if (time > lastAsteroidCreationTime + ASTEROID_DELAY)
    {
        int size_index = GetRandomValue(0, 2);
        AddAsteroid(GetNextAsteroidPosition(), sizes[size_index]);
        lastAsteroidCreationTime = time;
    }

    return activeAsteroids;
}

void DrawAsteroids(void)
{
    for (int i = 0; i < ASTEROIDS_MAX; i++)
    {
        Asteroid* currentAsteroid = &asteroids[i];
        AsteroidDraw(currentAsteroid);
    }
}