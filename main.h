#ifndef __MAIN_H
#define __MAIN_H

typedef enum {
    MENU,
    SINGLEPLAYER,
    MULTIPLAYER,
} GAMESTATE;

typedef struct _Object {
    int x, y, dx, dy;
    
    int (*update)(struct _Object obj); // Point function
} Object;

typedef struct _Player {
    
} Player;

typedef struct _Particle {
    int x, y, dx, dy, ax, ay;
    int duration, size;

} Particle;

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
    Object          *objects;
    int             numobjects;
    
    // Particles
    Particle        *particles;
    int             numparticles;
    
} Game;

void handleEvent(Game *game);

#endif
