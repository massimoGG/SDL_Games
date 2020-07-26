#ifndef __GFX_H
#define __GFX_H

#include <SDL2/SDL.h>
#include "main.h"

typedef struct _Point{
    int x;
    int y;
} Point;

void drawCircle(SDL_Renderer *renderer, int x, int y, int radius);
void drawTriangle(SDL_Renderer *renderer, Point p1, Point p2, Point p3);

void renderGame(Game *game);

#endif
