#include "asteroid.h"
#include <raymath.h>

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size)
{
    Asteroid asteroid;
    asteroid.active = true;
    asteroid.position = position;
    asteroid.velocity = velocity;
    asteroid.size = size;
    asteroid.rotation = (float)GetRandomValue(0, 360);
    asteroid.rotationSpeed = (float)GetRandomValue(ASTEROID_ROTATION_SPEED_MIN, ASTEROID_ROTATION_SPEED_MAX);
    asteroid.creationTime = (float)GetTime();

    return asteroid;
}

void AsteroidUpdate(Asteroid* asteroid, float deltatime)
{
    if (!asteroid->active)
    {
        return;
    }

    if (GetTime() > asteroid->creationTime + ASTEROID_LIFE)
    {
        asteroid->active = false;
        return;
    }

    Vector2 currentPosition = asteroid->position;
    Vector2 positionDelta = Vector2Scale(asteroid->velocity, deltatime);

    float rotation_delta = asteroid->rotationSpeed * deltatime;

    asteroid->position = Vector2Add(currentPosition, positionDelta);
    asteroid->rotation += rotation_delta;
}

void AsteroidDraw(Asteroid* asteroid)
{
    if (!asteroid->active)
    {
        return;
    }

    float radius = GetAsteroidRadius(asteroid->size);
    DrawPolyLines(asteroid->position, 3, radius, asteroid->rotation, WHITE);
}

float GetAsteroidRadius(AsteroidSize size)
{
    const int sizeScale = 16;
    int unit = (int)size;

    return (float)(unit * sizeScale);
}
