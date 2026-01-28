#include "platform.h"
#include "config.h"
#include <SDL2/SDL.h>

bool initSDL(SDL_Window** window, SDL_Surface** surface)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
        return false;

    *window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        0);

    if (!*window)
        return false;

    *surface = SDL_GetWindowSurface(*window);
    return true;
}
