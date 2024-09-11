#ifndef _2DPlayer
#define _2DPlayer

#include "main.h"


void _2DPlayerMove(Rectangle *Player, bool *WallHit, Vector2 *PlayerPosition);
void _CheckCollision2D(Rectangle *Player, Rectangle *WALLS, int WallSize, Vector2 *PlayerPosition, bool *WallHit);





#endif