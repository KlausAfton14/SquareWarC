#include <SDL2/SDL_mouse.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stddef.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

#include "config.h"
#include "platform.h"
#include "game.h"
#include "input.h"
#include "render.h"
#include "player.h"
#include "entity.h"
#include "projectile.h"

int main(int argc, char* argv[])
{
    SDL_Window* window;
    SDL_Surface* surface;

    if (!initSDL(&window, &surface))
        return 1;

    Player player;
    EntityArray entities;
    ProjectileArray projectiles;

    initGame(&player, &entities, &projectiles);

    bool running = true;
    float frameDelay = (1.0f / TARGET_FPS) * 1000;

    while (running)
    {
        handeEvents(&running, &player, &entities, &projectiles);
        updateGame(&entities, &projectiles);
        renderGame(surface, window, &player, &entities, &projectiles);
        SDL_Delay((int) frameDelay);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}