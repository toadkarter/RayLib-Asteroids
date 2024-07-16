#ifndef ASTEROIDS_GAME_ASTEROIDS_H
#define ASTEROIDS_GAME_ASTEROIDS_H

#include "asteroid.h"

void AddAsteroid(Vector2 position, AsteroidSize size);
Vector2 GetNextAsteroidPosition(void);
int UpdateAsteroids(void);
void DrawAsteroids(void);

#endif
