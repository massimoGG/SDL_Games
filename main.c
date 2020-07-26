#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#ifdef LINUX
// Multiplayer
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#endif

#include <SDL2/SDL.h>

#include "main.h"
#include "gfx.h"
#include "net.h"

int main(int argc, char *argv[]) {

    Game *game = malloc(sizeof(Game));
    memset(game, 0, sizeof(Game));
    
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        // Failed
        printf("Couldn't initialise SDL :(\n");
        return 1;
    }
    
    game->window    = SDL_CreateWindow("SDL TEST", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1536, 864, SDL_WINDOW_SHOWN);
    if (!game->window) {
        printf("Failed to create window\n");
        return 2;
    }
    SDL_GetWindowSize(game->window, &game->width, &game->height);
    
    // Initialise joystick
    for (int i=0; i<SDL_NumJoysticks(); i++) {
        SDL_Joystick *joy = SDL_JoystickOpen(i);
        if (joy) {
            puts("Found a joystick!\n");
            printf("Name: %s\n", SDL_JoystickNameForIndex(0));
            printf("Number of Axes: %d\n", SDL_JoystickNumAxes(joy));
            printf("Number of Buttons: %d\n", SDL_JoystickNumButtons(joy));
            printf("Number of Balls: %d\n", SDL_JoystickNumBalls(joy));
            game->joy = joy;
            game->haptic = SDL_HapticOpenFromJoystick(joy);
            SDL_HapticRumbleInit(game->haptic);
            SDL_JoystickEventState(SDL_ENABLE);
            break;
        }
    }

    game->running = 1;
    // Start SDL renderer
    game->renderer     = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (game->renderer == NULL) {
        printf("Failed to create renderer.\n");
        game->running = 0;
    }
    
    game->surface       = SDL_CreateRGBSurface(0, game->width, game->height, 32, 0,0,0,0);
    if (game->surface == NULL) {
        printf("Failed to create surface.\n");
        game->running = 0;
    }
    
    // Some essential variables
    const unsigned int FPS = 50;
    const unsigned int DELAY_TIME = (int)(1000.0f / FPS);
    long startRefTime, deltaTime;
    

    // Main game loop
    while (game->running) {
        startRefTime = SDL_GetTicks();
        
        // Render stuff
        handleEvent(game);
        /*
        // Status of joystick buttons
        for (int i=0; i<11 ;i++) {
            Uint8 b = SDL_JoystickGetButton(joy, i);
             printf("%d", b);
        }
        // Status of joystick axis
        for (int i=0; i< 6;i++)
             printf("     %d : %d      ", i, SDL_JoystickGetAxis(joy, i));
         printf("       \r");
        */
        
        // TODO: Updatephysics()
        
        renderGame(game);
        
        // Calculate FPS
        deltaTime = SDL_GetTicks() - startRefTime;
        if (deltaTime < DELAY_TIME) {
            SDL_Delay((DELAY_TIME - deltaTime));
        }
        if (deltaTime > 0) {
            char s[20];
            sprintf(s, "%u fps %ums\n", (1000/(SDL_GetTicks() - startRefTime)), DELAY_TIME);
            SDL_SetWindowTitle(game->window, s);
        }
//         fflush(stdout);
    }
    
    SDL_FreeSurface(game->surface);
    SDL_HapticClose(game->haptic);
    SDL_JoystickClose(game->joy);
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    SDL_Quit();
    free(game);
    printf("\n");
    return 0;
}

void handleEvent(Game *game) {
    SDL_Event windowEvent;
    while (SDL_PollEvent(&windowEvent)) {
        switch (windowEvent.type) {
        case SDL_QUIT:
            game->running=0;
            break;
        case SDL_KEYUP:
            switch (windowEvent.key.keysym.sym) {
            case SDLK_ESCAPE:
                game->running=0;
                break;
            default:
                break;
            }
            
        case SDL_JOYAXISMOTION:
            /* FIRST STICK: Left and right = 0; up and down = 1; 
             * SECOND STICK: left and right = 3; up and down = 4
             */
            
            if (windowEvent.jaxis.which == 0)
                if (windowEvent.jaxis.axis == 1)
                    if (windowEvent.jaxis.value < 0)
                        SDL_HapticRumblePlay(game->haptic, 0.75, 500);
            break;
        case SDL_JOYBUTTONDOWN:/*
            for (int i=0; i<11 ;i++) {
                Uint8 b = SDL_JoystickGetButton(joy, i);
                printf("%d", b);
            }*/
            break;
        default:
            break;
        }
    }

    const Uint8 *keystate = SDL_GetKeyboardState(NULL);
    if (keystate[SDL_SCANCODE_UP]) {
        game->running=0;
    }
    if (keystate[SDL_SCANCODE_W]) {
    }
    if (keystate[SDL_SCANCODE_A]) {
    }
    if (keystate[SDL_SCANCODE_S]) {
    }
    if (keystate[SDL_SCANCODE_D]) {
    }

}
