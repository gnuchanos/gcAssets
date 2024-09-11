#include "include/main.h"



void _2DPlayerMove(Rectangle *player, bool *wallhit, Vector2 *playerposition) {
    if (!*wallhit) {
        playerposition->y = player->y;
        playerposition->x = player->x;
    }

    if (IsKeyDown(KEY_W)) {
        player->y -= 200 * GetFrameTime();
    } else if (IsKeyDown(KEY_S)) {
        player->y += 200 * GetFrameTime();
    }

    if (IsKeyDown(KEY_A)) {
        player->x -= 200 * GetFrameTime();
    } else if (IsKeyDown(KEY_D)) {
        player->x += 200 * GetFrameTime();
    }
}

void _CheckCollision2D(Rectangle *player, Rectangle *walls, int wallsize, Vector2 *playerposition, bool *wallhit) {
    for (int i = 0; i < wallsize; i++) {
        if (CheckCollisionRecs(walls[i], *player)) {
            player->x = playerposition->x;
            player->y = playerposition->y;
            *wallhit = true;
            break;
        } else {
            *wallhit = false;
        }
    } 
}


