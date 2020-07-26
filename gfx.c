#include "gfx.h"

void drawCircle(SDL_Renderer *renderer, int x, int y, int radius) {
    // Radius of 10 at (x,y)
    // x^2 + y^2 = r^2 -> y^2 = r^2 - x^2
    // Draw the circle like horizontal scan lines
    for (int cy = -radius; cy < radius; cy++) {
        // Find x coord of one side of the circle 
        int cx = (int)sqrt(pow(radius, 2) - pow(cy, 2));
        SDL_RenderDrawLine(renderer, x-cx, y+cy, x+cx, y+cy);
    }
}

static float rico(Point *a, Point *b) {
    int dy = (b->y - a->y);
    int dx = (b->x - a->x);
    if (dx==0)
        return 0; // Devision by 0 is not a joke!
    return dy/dx;
}

static void sort(Point *list[], int num) {
    for (int cur=0; cur<num;cur++){
        for (int i=1; i<num; i++) {
            if (list[i]->y < list[i-1]->y) {
                // Swap
                Point *t = list[i];
                list[i] = list[i-1];
                list[i-1] = t;
            }
        }
    }
}

void drawTriangle(SDL_Renderer *renderer, Point p1, Point p2, Point p3) {
    Point *list[3]; // Array of 3 pointers
    list[0]=&p1;
    list[1]=&p2;
    list[2]=&p3;
    sort(list,3);
    
    for (int i=0;i<3;i++)
        printf("Point %d: %d %d\n",i,list[i]->x, list[i]->y);

    // We hebben 3 ricos nodig
    
    // Draw them like horizontal scan lines
}

void drawGraph(SDL_Renderer *renderer, Point start, int width, int height, int *p, int points) {
    SDL_RenderDrawLine(renderer, start.x, start.y, start.x, start.y - height);  // | 
    SDL_RenderDrawLine(renderer, start.x, start.y, start.x+width, start.y);     // -
    SDL_RenderDrawLine(renderer, start.x, start.y-height, start.x+width, start.y-height);   // -
    SDL_RenderDrawLine(renderer, start.x+width, start.y, start.x+width, start.y-height);     // |
    for (int tp=0; tp<points; tp++/*TODO: if 100 width. 50 points -> per 2*/) {
        int tmpx = start.x + tp*(width/points);
        int tmpy = start.y - (int)(((float)height/100)*p[tp]);
        SDL_RenderDrawPoint(renderer, tmpx, tmpy); // TODO Some shit
        if (tp!=0)
            SDL_RenderDrawLine(renderer, start.x + (tp-1)*(width/points), start.y - (int)(((float)height/100)*p[tp-1]), tmpx, tmpy);
    }
}
static void shiftList(int p[], int size) {
    // Shift all with one
    for (int i=1;i<size;i++) {
        p[i-1]=p[i];
    }
}

void renderGame(Game *game) {
    // Clear surface
    SDL_Renderer    *renderer = game->renderer;
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    
    
    
    SDL_SetRenderDrawColor(renderer, 255,255,255, SDL_ALPHA_OPAQUE);
    for (int w=0; w<game->width; w+=100) {
        for (int h=0; h<game->height; h+=100) {
            //drawCircle(renderer, w, h, 2);
            SDL_RenderDrawPoint(renderer, w,h);
        }
    }
    
    
    
    SDL_SetRenderDrawColor(renderer, 200,55, 20, SDL_ALPHA_OPAQUE);
    static double rad;
    if (rad>=2*3.14159) 
        rad=0;
    rad+=0.1;
    drawCircle(renderer, 500 + 200*cos(rad), 200 + 200*sin(rad), 20);

#define SIZEA 50
    // Graph with random shit
    static int points[SIZEA];
    if (points[0] == 0) {
        for (int i=0;i<SIZEA;i++) {
            points[i] = rand() % 100;
        }
    }
    // First graph
    Point start =   {400,400};
    drawGraph(renderer, start, 400, 200, points, SIZEA);

    // Shift graph
    shiftList(points, SIZEA);
    // Generate new data
    int r=0;
    while (r==0)
        r = rand() % 100;
    points[SIZEA-1]=r;
    
    
    
    SDL_SetRenderDrawColor(renderer, 255,60,23, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(renderer, 320, 200, 300, 240);
    SDL_RenderDrawLine(renderer, 300, 240, 340, 240);
    SDL_RenderDrawLine(renderer, 340, 240, 320, 200);

    // Render it
    SDL_RenderPresent(renderer);
}

// Draw explosion? :O
// Draw particle
