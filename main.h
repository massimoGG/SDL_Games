#ifndef __MAIN_H
#define __MAIN_H

typedef enum {
    MENU,
    SINGLEPLAYER,
    MULTIPLAYER,
} GAMESTATE;

typdef struct _Object {
    int x, y, dx, dy, ddx, ddy;
    
    int (*update)(struct _Object obj); // Point function
    
    
} Object;

typedef struct _Game {
    int             running;
    
    SDL_Window      *window;
    int             width, height;
    SDL_Renderer    *renderer;
    SDL_Surface     *surface;
    
    // Controls
    SDL_Joystick    *joy;
    SDL_Haptic      *haptic;
    
    // Objects
    
} Game;

void handleEvent(Game *game);

#endif
