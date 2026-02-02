#define SDL_MAIN_HANDLED

#include "config.h"
#include "platform.h"
#include "game.h"
#include "input.h"
#include "render.h"
#include "player.h"
#include "entity.h"
#include "projectile.h"

#include <stdlib.h>
#include <time.h>
#include <stddef.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

int main()
{
    srand((unsigned) time(NULL));

    SDL_Window* window;
    SDL_Renderer* renderer;

    if (!initSDL(&window, &renderer))
        return 1;

    initRenderAssets(renderer);

    bool running = true;

    while (running)
    {
        GameState gameState = GAME_RUNNING;

        Player player;
        EntityArray entities;
        ProjectileArray projectiles;

        initGame(&player, &entities, &projectiles);

        float frameDelay = (1.0f / TARGET_FPS) * 1000;

        while (gameState == GAME_RUNNING)
        {
            handeEvents(&running, &player, &entities, &projectiles);
            updateGame(&player, &entities, &projectiles, &gameState);
            renderGame(renderer, &player, &entities, &projectiles);
            SDL_Delay((int) frameDelay);
        }

        switch (gameState)
        {
        case GAME_RUNNING:
            break;

        case GAME_OVER:
            printf("GAME OVER!\n");

            bool waitingForChoice = true;

            float menuFrameDelay = (1.0f / 30) * 1000;

            while (waitingForChoice && running)
            {
                SDL_Event event;
                while (SDL_PollEvent(&event))
                {
                    switch (event.type)
                    {
                    case SDL_QUIT:
                        running = false;
                        waitingForChoice = false;
                        break;
                    case SDL_KEYDOWN:
                        if (event.key.keysym.scancode == SDL_SCANCODE_R)
                            waitingForChoice = false;
                    }
                }

                SDL_Delay((int) menuFrameDelay);
            }
            break;
        }
    }

    shutdownSDL(window, renderer);
    return 0;
}