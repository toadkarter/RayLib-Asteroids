#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "raylib.h"

typedef enum AsteroidSize
{
    ASTEROID_SMALL = 1,
    ASTEROID_MEDIUM = 2,
    ASTEROID_LARGE = 4,
} AsteroidSize;

#define ASTEROID_ROTATION_SPEED_MIN 5
#define ASTEROID_ROTATION_SPEED_MAX 240

typedef struct Asteroid
{
    bool active;
    AsteroidSize size;
    Vector2 position;
    float rotation;
    float rotationSpeed;
    Vector2 velocity;

} Asteroid;

Asteroid CreateAsteroid(Vector2 position, Vector2 velocity, AsteroidSize size);

void AsteroidUpdate(Asteroid* asteroid, float deltatime);
void AsteroidDraw(Asteroid* asteroid);

float GetAsteroidRadius(AsteroidSize size);

#endif
