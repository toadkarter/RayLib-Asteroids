#ifndef ASTEROIDS_PLAYER_H
#define ASTEROIDS_PLAYER_H

#include "raylib.h"

#define PLAYER_ROTATION_SPEED 360

typedef struct Player
{
    Vector2 position;
    Vector2 velocity;
    float rotation;
} Player;

void PlayerUpdate(Player* player);
void PlayerDraw(Player* player);

#endif
