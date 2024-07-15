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

    return asteroid;
}

void AsteroidUpdate(Asteroid* asteroid, float deltatime)
{
    if (!asteroid->active)
    {
        return;
    }

    Vector2 current_position = asteroid->position;
    Vector2 position_delta = Vector2Scale(asteroid->velocity, deltatime);

    float rotation_delta = asteroid->rotationSpeed * deltatime;

    asteroid->position = Vector2Add(current_position, position_delta);
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
    const int size_scale = 16;
    int unit = (int)size;

    return (float)(unit * size_scale);
}
