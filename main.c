#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>
#include "stdbool.h"
#include "SDL2/SDL.h"

#define WINDOW_TITLE "SquareWar"
#define WINDOW_WIDTH 901
#define WINDOW_HEIGHT 601
#define TARGET_FPS 60
#define BACKGROUND_COLOR 0x00141414

#define PLAYER_SIZE 50
#define ENTITIE_SIZE 20

struct Player
{
    int x;
    int y;
    int size;
    int health;
    int ammo;
};

struct Entitie
{   
    int x;
    int y;
    int size;
    int health;
};

struct Projectile
{
    int x;
    int y;
    int size;
    int damage;
    int angle;
};

struct Player spawn_player(int x, int y)
{
    struct Player player = {
        x - (PLAYER_SIZE / 2),
        y - (PLAYER_SIZE / 2),
        PLAYER_SIZE,
        100,
        25
    };

    return player;
};

struct Entitie spawn_entitie(int x, int y)
{
    struct Entitie entitie = {
        x - (ENTITIE_SIZE / 2),
        y - (ENTITIE_SIZE / 2),
        ENTITIE_SIZE,
        50
    };

    return entitie;
};

struct Projectile spawn_projectile(struct Player player, int size, int target_x, int target_y)
{
    struct Projectile projectile = {
        player.x - (size / 2),
        player.y - (size / 2),
        size,
        50
    };

    return projectile;
};

void draw_player(SDL_Surface *surface, struct Player player)
{
    SDL_Rect playerRect = {
        player.x,
        player.y,
        player.size,
        player.size
    };

    SDL_FillRect(surface, &playerRect, 0x000000ff);
}

void draw_entities(SDL_Surface *surface, struct Entitie *entities, int entitiesCount)
{
    for(int i; i < entitiesCount; i++)
    {
        SDL_Rect entitieRect = {
            entities[i].x,
            entities[i].y,
            entities[i].size,
            entities[i].size
        };

        SDL_FillRect(surface, &entitieRect, 0x00ff0000);
    }
}

void draw_projectiles(SDL_Surface *surface, struct Projectile *projectiles, int projectilesCount)
{
    for(int i; i < projectilesCount; i++)
    {
        SDL_Rect projectileRect = {
            projectiles[i].x,
            projectiles[i].y,
            projectiles[i].size,
            projectiles[i].size
        };

        SDL_FillRect(surface, &projectileRect, 0x0000ff00);
    }
}

int main(int argc, char *argv[])
{
    SDL_Window *window;
    bool done = false;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED, 
        SDL_WINDOWPOS_CENTERED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        0
    );

    SDL_Surface *surface = SDL_GetWindowSurface(window);
    SDL_Rect windowRect = {
        0,
        0,
        WINDOW_WIDTH,
        WINDOW_HEIGHT
    };
    SDL_FillRect(surface, &windowRect, BACKGROUND_COLOR);

    float frameDelay = (1.0 / TARGET_FPS) * 1000;
    int mouse_x;
    int mouse_y;

    int stratingX = (int)(WINDOW_WIDTH / 2); 
    int stratingY = (int)(WINDOW_HEIGHT / 2); 

    struct Player player_1 = spawn_player(stratingX, stratingY);
    struct Entitie entitie_1 = spawn_entitie(20, 20);
    struct Entitie entitie_2 = spawn_entitie(600, 500);

    struct Entitie entities[] = {
        entitie_1,
        entitie_2
    };

    int entitiesCount = (sizeof(entities) / sizeof(*entities));

    while(!done)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    done = true;
                    break;
                case SDL_MOUSEMOTION:
                    mouse_x = event.motion.x;
                    mouse_y = event.motion.y;
                    printf("x: %d, y: %d\n", mouse_x, mouse_y);
                    break;
            }
        }

        draw_entities(surface, entities, entitiesCount);
        draw_player(surface, player_1);

        SDL_UpdateWindowSurface(window);
        SDL_Delay((int)frameDelay);
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


// projectile system !!!