#include <SDL2/SDL_render.h>
#define SDL_MAIN_HANDLED

#include "config.h"
#include "platform.h"
#include "game.h"
#include "input.h"
#include "render.h"
#include "player.h"
#include "entity.h"
#include "projectile.h"

#include <stddef.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

int main()
{
    SDL_Window* window;
    SDL_Renderer* renderer;

    if (!initSDL(&window, &renderer))
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
        updateGame(&player, &entities, &projectiles);
        renderGame(renderer, &player, &entities, &projectiles);
        SDL_Delay((int) frameDelay);
    }

    shutdownSDL(window, renderer);
    return 0;
}