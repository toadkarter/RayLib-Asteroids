#include "player.h"

void PlayerUpdate(Player* player)
{
    int xIn = (int)IsKeyDown(KEY_RIGHT) - (int)IsKeyDown(KEY_LEFT);
    player->rotation += ((float)xIn * PLAYER_ROTATION_SPEED * GetFrameTime());
}

void PlayerDraw(Player* player)
{
    DrawPoly(player->position, 3, 32, player->rotation, RAYWHITE);
}